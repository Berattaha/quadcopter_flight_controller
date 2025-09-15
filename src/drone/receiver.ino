#include "SBUS.h"

/* The Teensy SBUS interfaces on Serial2 */
SBUS sbus(Serial2);

/* 16 SBUS channels, reading */
float SbusRead[16];
/* Failsafe and lost frame status */
bool Failsafe, LostFrame;


struct ReceiverCommands prevReceiverCommands;
bool armed = false;
unsigned long reciever_last_communication_time = millis();

void initializeReceiver(){
    //while (!Serial) {}
    sbus.begin(); 
    
}

struct ReceiverCommands GetReceiverCommands(){
    struct ReceiverRawValues receiverRawValues = getReceiverRawValues();
    if (receiverRawValues.TransmitterCommunicationFailure) {
      return getFailureReceiverCommand();
    } 
    
  /* print the received values */
   if (receiverRawValues.NewDataAvailable) {
    reciever_last_communication_time = millis();
      
    struct ReceiverCommands cmd;
    cmd.RollAngle = map_double(SbusRead[0], TRANSMITTER_JOYSTICK_MAX_VALUE, TRANSMITTER_JOYSTICK_MIN_VALUE, -QUADCOPTER_MAX_TILT_ANGLE, QUADCOPTER_MAX_TILT_ANGLE);
    cmd.PitchAngle = map_double(SbusRead[1], TRANSMITTER_JOYSTICK_MAX_VALUE, TRANSMITTER_JOYSTICK_MIN_VALUE, -QUADCOPTER_MAX_TILT_ANGLE, QUADCOPTER_MAX_TILT_ANGLE);
    cmd.Throttle = map_double(SbusRead[2], TRANSMITTER_JOYSTICK_MAX_VALUE, TRANSMITTER_JOYSTICK_MIN_VALUE, 0, THROTTLE_LIMIT_POINT);
    cmd.YawAngleChange = map_double(ignoreDeadBand(SbusRead[3]), TRANSMITTER_JOYSTICK_MAX_VALUE, TRANSMITTER_JOYSTICK_MIN_VALUE, -QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND, QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND);
    cmd.Armed = getArmStatus(receiverRawValues, SbusRead);
    cmd.Error = false;
        
    prevReceiverCommands = cmd;
    return cmd;

  }else if(millis() - RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS > reciever_last_communication_time){
     return getFailureReceiverCommand();   
  }else{
    return prevReceiverCommands;
  }
}

struct ReceiverCommands getFailureReceiverCommand() {
  struct ReceiverCommands cmd;
  cmd.Error = true;
  return cmd;
}

//prevent small receiver value changes to affect yaw while joystick is on the center
float ignoreDeadBand(float val) {
  float center = (TRANSMITTER_JOYSTICK_MIN_VALUE + TRANSMITTER_JOYSTICK_MAX_VALUE) / 2.0;
  if (abs(val - center) <= TRANSMITTER_JOYSTICK_DEAD_BAND)
    return center;
  else
    return val;
}

  struct ReceiverRawValues getReceiverRawValues() {
  struct ReceiverRawValues v;
  v.NewDataAvailable = false;
  v.TransmitterCommunicationFailure = false;

 /* if (sbus.readCal(&SbusRead[0], &Failsafe, &LostFrame)){
  v.NewDataAvailable = true;
    if (sBus.Failsafe() != 0) {
      v.TransmitterCommunicationFailure = true;
      return v;
    }

    sBus.toChannels = 0;
    int i = 0;
    for (int16_t channelValue : sBus.channels) {
      v.ChannelValues[i] = channelValue;
      i++;
    }
  }

  return v;
}*/
if (sbus.readCal(&SbusRead[0], &Failsafe, &LostFrame)) {
    v.NewDataAvailable = true;
    if (Failsafe != 0) {
      v.TransmitterCommunicationFailure = true;
     return v;
    }
      //sBus.toChannels = 0;    
    /*int i = 0;
    for (float channelValue : SbusRead) {
      v.ChannelValues[i] = channelValue;
      i++;
    }*/
  }

  return v;
  }

bool hasArmingStarted = false;
bool hasDisarmingStarted = false;
unsigned long armingStartTime;
unsigned long disarmingStartTime;

bool getArmStatus(ReceiverRawValues rawValues, float channels[]) {
  if (!rawValues.NewDataAvailable || rawValues.TransmitterCommunicationFailure) {
    return armed;
  }

  if (isArming(channels) && !armed) {
    hasDisarmingStarted = false;
    if (!hasArmingStarted) {
      armingStartTime = millis();
      hasArmingStarted = true;
    } else {
      if (millis() - armingStartTime >= TRANSMITTER_ARMING_DURATION_IN_MILLISECONDS) {
        armed = true;
        quadcopter_armed();
      }
    }
  } else if (isDisarming(channels) && armed) {
    hasArmingStarted = false;
    if (!hasDisarmingStarted) {
      disarmingStartTime = millis();
      hasDisarmingStarted = true;
    } else {
      if (millis() - disarmingStartTime >= TRANSMITTER_ARMING_DURATION_IN_MILLISECONDS) {
        armed = false;
        quadcopter_disarmed();
      }
    }
  } else {
    hasArmingStarted = false;
    hasDisarmingStarted = false;
  }

  return armed;
}

bool isArming(float channels[]) {
  if (isThrottleStickPositonAtFullDown(channels) && isYawStickPositionAtFullRight(channels)) {
    return true;
  }
  return false;
}

bool isDisarming(float channels[]) {
  if (isThrottleStickPositonAtFullDown(channels) && isYawStickPositionAtFullLeft(channels)) {
    return true;
  }
  return false;
}

bool isThrottleStickPositonAtFullDown(float channels[]) {
  if (abs(channels[2] + TRANSMITTER_JOYSTICK_MIN_VALUE) < TRANSMITTER_ARMING_JOYSTICK_TOLERANCE) {
    return true;
  }
  return false;
}

bool isYawStickPositionAtFullLeft(float channels[]) {
  if (abs(channels[3] - TRANSMITTER_JOYSTICK_MIN_VALUE) < TRANSMITTER_ARMING_JOYSTICK_TOLERANCE) {
    return true;
  }
  return false;
}

bool isYawStickPositionAtFullRight(float channels[]) {
  if (abs(channels[3] - TRANSMITTER_JOYSTICK_MAX_VALUE) < TRANSMITTER_ARMING_JOYSTICK_TOLERANCE) {
    return true;
  }
  return false;
}

double map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
