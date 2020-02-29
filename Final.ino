#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define CW  0
#define CCW 1
// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1
// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B
char val;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
}
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
   setupArdumoto(); // Set all pins as outputs
  if(!mag.begin())
  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails();
}
void loop(void) 
{
    if ( Serial.available() ) {
          Serial.println("Digite opcion:");
    val = Serial.read();
    if ( val == 's' ) {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
    }
    if ( val == 'l' ) {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
      driveArdumoto(MOTOR_A, CW, 255);
      driveArdumoto(MOTOR_B, CW, 255);
    }
    if ( val == 'r' ) {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
      driveArdumoto(MOTOR_A, CCW, 255);
      driveArdumoto(MOTOR_B, CCW, 255);
    }
    if ( val == 'u' ) {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
      driveArdumoto(MOTOR_A, CCW, 255);
      driveArdumoto(MOTOR_B, CW, 255);
    }
    if ( val == 'd' ) {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
      driveArdumoto(MOTOR_A, CW, 255);
      driveArdumoto(MOTOR_B, CCW, 255);
    }
    if (val == 'z') {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
      driveArdumoto(MOTOR_A, CW, 255); 
      driveArdumoto(MOTOR_B, CW, 255); 
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
    }
    if (val == 'x') {
      stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
        sensors_event_t event; 
        mag.getEvent(&event);     
        float heading = atan2(event.magnetic.y, event.magnetic.x);
        if(heading < 0)
          heading += 2*PI;
        if(heading > 2*PI)
          heading -= 2*PI;
        float valorActual = heading * 180/M_PI; 
        Serial.print("Digite el valor:");
        float valorFuturo = Serial.parseFloat();
        bool auxB = false;
        valorFuturo = valorActual+valorFuturo;
        if(valorFuturo>355){
          valorFuturo = valorFuturo-360;
          auxB=true;
        }
        Serial.print("ValorActual");Serial.println(valorActual);
        Serial.print("ValorFuturo: "); Serial.println(valorFuturo);
        while(true){
          sensors_event_t event; 
          mag.getEvent(&event);
              heading = atan2(event.magnetic.y, event.magnetic.x);
        if(heading < 0)
          heading += 2*PI;
        if(heading > 2*PI)
          heading -= 2*PI;
          valorActual = heading * 180/M_PI; 
      driveArdumoto(MOTOR_A, CCW, 195);
      driveArdumoto(MOTOR_B, CCW, 195);
        Serial.print("ValorActual");Serial.println(valorActual);
        Serial.print("ValorFuturo: "); Serial.println(valorFuturo);
      if(auxB){
        if(valorActual<valorFuturo){
         Serial.print("Salir: ");
           stopArdumoto(MOTOR_A);
           stopArdumoto(MOTOR_B);
          break;
         }                                                                                                                                                       
      }else{
        if(valorActual>valorFuturo){
           Serial.print("Salir: ");
           stopArdumoto(MOTOR_A);
           stopArdumoto(MOTOR_B);
          break;
         }
      }
     }       
    }
  }
}
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }
}
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}
void setupArdumoto()
{
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
