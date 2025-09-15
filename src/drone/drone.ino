
//----------- PINS -----------
#define FRONT_LEFT_MOTOR_PIN 3
#define FRONT_RIGHT_MOTOR_PIN 5
#define REAR_LEFT_MOTOR_PIN 4
#define REAR_RIGHT_MOTOR_PIN 6
#define LED_YESIL_PIN 30
#define LED_KIRMIZI_PIN 28
#define BUZZER_PIN 27
#define INTERRUPT_PIN 0 

//----------- RECEIVER & TRANSMITTER -----------
#define TRANSMITTER_JOYSTICK_MIN_VALUE -0.84
#define TRANSMITTER_JOYSTICK_MAX_VALUE 0.86
#define TRANSMITTER_JOYSTICK_DEAD_BAND 0.04
#define TRANSMITTER_ARMING_DURATION_IN_MILLISECONDS 1000
#define TRANSMITTER_ARMING_JOYSTICK_TOLERANCE 0.08

//----------- IMU CALIBRATION -----------
#define ACCEL_OFFSET_X -2776
#define ACCEL_OFFSET_Y 2141
#define ACCEL_OFFSET_Z 288
#define GYRO_OFFSET_X 60
#define GYRO_OFFSET_Y 14
#define GYRO_OFFSET_Z 22

//----------- ESC's -----------
#define MIN_MOTOR_PULSE_WIDTH 1000
#define MAX_MOTOR_PULSE_WIDTH 2000

//----------- LIMITS -----------
#define THROTTLE_START_POINT 10  // between 0-180
#define THROTTLE_LIMIT_POINT 180 // between 0-180
double QUADCOPTER_MAX_TILT_ANGLE = 20.00; // roll, pitch tilt angle limit in degrees
double QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND = 180.00;

//----------- TIMEOUTS -----------
#define IMU_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 100
#define RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 500
#define PROGRAM_TIMEOUT_IN_MILLISECONDS WDTO_1S // Watch Dog Timer parameter

//----------- PID CONFIGURATION-----------
double KP_roll_pitch = 0.30;
double KI_roll_pitch = 0.10;
double KD_roll_pitch = 0.13;

double KP_yaw = 0.40;
double KI_yaw = 0.50;
double KD_yaw = 0.00;

//----------- PID CONTROL LIMITS-----------
double ROLL_PITCH_CONTROL_SIGNAL_LIMIT = KP_roll_pitch * QUADCOPTER_MAX_TILT_ANGLE * 2;
