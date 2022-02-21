# Exigences

Lorsqu'on utilise le Bluetooth nous devons utiliser des caratcères et chaque mouvemant sera interprété ainsi:
- Gauche => ```g```
- Droite => ```d```
- Avancer => ```a```
- Reculer => ```r```
- Stop => ```s```

| Entrées/Sorties  | Fonction  |
| :------------: | :------------: |
| 13 | Sens de rotation du moteur de droite |
| 12 | Sens de rotation du moteur de gauche |
| 9 | Frein du moteur de droite |
| 8| Frein du moteur de gauche |
| 11| Le moteur de droite |
| 3| Le moteur de gauche |
| 5 | Réception données |
| 6 | Transmission données |



# Partie Application
____
APPLICATION ANDROID 
Nous avons utilisé le site [appinventor](http://ai2.appinventor.mit.edu "appinventor") créer par le MIT qui permet de faire des applications sous format scratch afin de build un .apk sans faire du ```Java et Android Studio```.

> Avant de s'attaquer sur notre application nous devons créer une sélection d'item qui va nous permettre à chaque démarrage de l'application de connaître les clients Bluetooth et de s'y connecter en le choisissant.

![ANDROID_BLUETOOTH.PNG](https://github.com/bapt800/NSI_robot/blob/main/Images/ANDROID_BLUETOOTH.PNG)

```c
/*On met deux variables globales.*/
char direction;
int vitesse;
```
(Image à intégrer)

``` 
Et récupérer des évènements de nos boutons (Droite, Gauche, Avancer, Reculer, Stop ) pressés/appuyés
Qui renvoie une chaine de caractèressous format direction + vitesse
```
(Image des fonctions à intégrer)
```
Quand chaque bouton est relâché, on envoie le chaîne de caractère au client bluetooth.
```
(Image à intégrer)

# Partie Robot

> Les information de l'application sont transmise en Bluetooth et reçu par l'Arduino.
On utilise la classe SoftwareSerial pour recuperer les donnés de la carte.

> Les données sont sous la forme:
> 	- d'un caractere qui sera la direction
> 	- et d'un chiffre (0-9) qui sera la vitesse

```c++
SoftwareSerial   SerialBluetooth(5, 6);
```
```c++
  if ( SerialBluetooth.available()  )  // si données reçues en Bluetooth
  {
    cDirection = SerialBluetooth.read();  //lecture de la direction
  }
  
  
    if ( SerialBluetooth.available() )  // si données reçues en Bluetooth
  {
    uiVitesse = SerialBluetooth.read() - 48; //lecture de la vitesse
    if (uiVitesse <= 3 && uiVitesse > 0) //problemme vitesse mini des moteurs
    {
      uiVitesse = 4;
    }
    uiVitesse = uiVitesse * 28; //convertie le chiffre (0-9) en nombre (0-255)
  }
```

> La fonction suivante permet de commander la vitesse et la direction du robot.
```c++
void run(int vitesse, char direction);
```
```c++
  digitalWrite(13 , sens_rigth_motor); //sens de marche du moteur droit
  digitalWrite(12 , sens_left_motor); //sens de marche du moteur gauche
  analogWrite(3 , vitesse_rigth); //vitesse  moteur droit
  analogWrite(11 , vitesse_left); //vitesse  moteur gauche
```
___
> Sachant que les robots peuvent avoir des branchement de cables différents, nous avons intégré un systeme de correction rapide de cela via le code suivant.

```c++
bool fix_motor_rigth = false;
bool fix_motor_left = false;

void run(int vitesse, char direction)
{
	...
      sens_rigth_motor = true ^ fix_motor_rigth;
      sens_left_motor = true ^ fix_motor_left;
}
```
___
> Nous avons ajouter un systeme de detection des obstacles, cela stop le robot si obstacle il y a, à moins de 10cm de celui-ci.
```c++
bool hasObjectFar()
{
  int RangeInCentimeters = ultrasonic.MeasureInCentimeters(); 
  if(RangeInCentimeters > 10)
    return false;
  else{
    return true;
  }
}
```

