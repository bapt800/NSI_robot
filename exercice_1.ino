#include <SoftwareSerial.h>




void run(int vitesse, int direction);



SoftwareSerial   mySerial(5, 6);


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
  mySerial.begin(9600);



}

char cDirection = 's';
unsigned int uiVitesse = 0;

void loop()
{


  if ( mySerial.available()  )  // si données reçues en Bluetooth
  {
    cDirection = mySerial.read(); // lecture des octets
  }
  else if (Serial.available() ) {
    cDirection = Serial.read();
  }


  if ( mySerial.available() )  // si données reçues en terminal
  {
    uiVitesse = mySerial.read() - 48;
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


  switch (direction)
  {
    case 'd':
      digitalWrite(13 , HIGH);
      digitalWrite(12 , HIGH);
      break;
    case 'g':
      digitalWrite(13 , LOW);
      digitalWrite(12 , LOW);
      break;
    case 'a':
      digitalWrite(13 , HIGH);
      digitalWrite(12 , LOW);
      break;
    case 'r':
      digitalWrite(13 , LOW);
      digitalWrite(12 , HIGH);
      break;
    default:
      vitesse = 0;
      break;

  }


  analogWrite(11 , vitesse); //vitesse  moteur G
  analogWrite(3 , vitesse); //vitesse  moteur D

}



