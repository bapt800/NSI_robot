#include <SoftwareSerial.h>
#include "Ultrasonic.h"

bool fix_motor_rigth = false;
bool fix_motor_left = false;


Ultrasonic ultrasonic(2);
void run(int vitesse, int direction);



SoftwareSerial   SerialBluetooth(5, 6);


void setup() {

  pinMode( 13 , OUTPUT);
  pinMode( 12 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 8 , OUTPUT);
  pinMode( 11 , OUTPUT); //vitesse  moteur G
  pinMode( 3 , OUTPUT); //vitesse  moteur D

  digitalWrite(8 , LOW); //frein
  digitalWrite(9 , LOW); //frein

  digitalWrite(13 , HIGH);
  digitalWrite(12 , HIGH);


  Serial.begin(9600);
  SerialBluetooth.begin(9600);



}

char cDirection = 's';
unsigned int uiVitesse = 0;

void loop()
{


  if ( SerialBluetooth.available()  )  // si données reçues en Bluetooth
  {
    cDirection = SerialBluetooth.read(); // lecture des octets
  }
  else if (Serial.available() ) {
    cDirection = Serial.read();
  }


  if ( SerialBluetooth.available() )  // si données reçues en terminal
  {
    uiVitesse = SerialBluetooth.read() - 48;
    if (uiVitesse <= 3 && uiVitesse > 0) //problemme vitesse min moteur
    {
      uiVitesse = 4;
    }
    uiVitesse = uiVitesse * 28;
  }
  else if (Serial.available() ) {
    uiVitesse = Serial.parseInt();
    if (uiVitesse <= 3 && uiVitesse > 0) //problemme vitesse min moteur
    {
      uiVitesse = 4;
    }
    uiVitesse = uiVitesse * 28;
  }




  Serial.println(uiVitesse);
  Serial.println(cDirection);

  run(uiVitesse, cDirection);

  delay(250);
}



void run(int vitesse, char direction)
{
  unsigned int vitesse_rigth = vitesse;
  unsigned int vitesse_left = vitesse;
  bool sens_rigth_motor = true;
  bool sens_left_motor = true;
  //fix_motor_rigth

  switch (direction)
  {
    case 'd':
      sens_rigth_motor = true ^ fix_motor_rigth;
      sens_left_motor = true ^ fix_motor_left;

      vitesse_rigth = vitesse / 2;
      vitesse_left = vitesse;
      break;
    case 'g':
      sens_rigth_motor = true ^ fix_motor_rigth;
      sens_left_motor = true ^ fix_motor_left;

      vitesse_rigth = vitesse;
      vitesse_left = vitesse / 2;
      break;
    case 'a':
      sens_rigth_motor = true ^ fix_motor_rigth;
      sens_left_motor = true ^ fix_motor_left;

      vitesse_rigth = vitesse;
      vitesse_left = vitesse;
      break;
    case 'r':
      sens_rigth_motor = false ^ fix_motor_rigth;
      sens_left_motor = false ^ fix_motor_left;

      vitesse_rigth = vitesse;
      vitesse_left = vitesse;
      break;
    default:
      vitesse_rigth = 0;
      vitesse_left = 0;
      break;

  }

  digitalWrite(13 , sens_rigth_motor);
  digitalWrite(12 , sens_left_motor);
  analogWrite(3 , vitesse_rigth); //vitesse  moteur D
  analogWrite(11 , vitesse_left); //vitesse  moteur G



}


