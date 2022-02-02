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
Nous avons utilisé le site ```http://ai2.appinventor.mit.edu``` créer par le MIT qui permet de faire des applications sous format scratch afin de build un .apk sans faire du ```Java et Android Studio```.

> Avant de s'attaquer sur notre application nous devons créer une sélection d'item qui va nous permettre à chaque démarrage de l'application de connaître les clients Bluetooth et de s'y connecter en le choisissant.

(Image à intégré)

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
___
> Sachant que les robots peuvent avoir des branchement de cables différents, nous avonc intégré un systeme de logique de correction rapide de cela via le code.

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

- Le moteur droit est inversé.
- Le courant est continue pas alternatif
