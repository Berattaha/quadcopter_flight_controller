#include <avr/wdt.h>
void setup()
{
  wdt_enable(PROGRAM_TIMEOUT_IN_MILLISECONDS);

  /* Serial for printing the command */
 // Serial.begin(115200);
  initializeMotors();
  initializeOutputSignals();
  initializeReceiver();
  initializeIMU();
  LostFrame = 1;
  Failsafe = 1;


  quadcopter_initialization_completed();
}

void loop()
{
  wdt_reset();
  syncOutputSignals();
  
  struct ReceiverCommands receiverCommands = GetReceiverCommands();
  struct IMU_Values imu_values = GetIMUvalues();
  
  if(LostFrame != 0 || Failsafe !=0 ||  (receiverCommands.Throttle < THROTTLE_START_POINT) || !receiverCommands.Armed || imu_values.Error){
    stopMotors();
    resetPidVariables();
    return;
  }
   
  if(imu_values.NewDataAvailable){
  struct MotorPowers motorPowers = calculateMotorPowers(receiverCommands, imu_values);
  spinMotors(motorPowers);

   if( motorPowers.frontLeftMotorPower > 170 || motorPowers.frontRightMotorPower > 170 ||  motorPowers.rearLeftMotorPower > 170 || motorPowers.rearRightMotorPower > 170 ){
      stopMotors();
      resetPidVariables();
  }


      /*Serial.print(receiverCommands.RollAngle);
      Serial.print("\t");
      Serial.print(receiverCommands.PitchAngle);
      Serial.print("\t");
      Serial.print(receiverCommands.Throttle);
      Serial.print("\t");
      Serial.print(receiverCommands.YawAngleChange);
      Serial.print("\t");
    
     */ /*Serial.print(LostFrame);
      Serial.print("\t");
      Serial.println(Failsafe);
      Serial.print("\n");
      Serial.println(motorPowers.frontLeftMotorPower);
      //Serial.print("\t");
      Serial.println( motorPowers.frontRightMotorPower);
      //Serial.print("\t");
      Serial.println( motorPowers.rearLeftMotorPower);
      //Serial.print("\t");
      Serial.println(motorPowers.rearRightMotorPower);*/
  }
 
}  
  
