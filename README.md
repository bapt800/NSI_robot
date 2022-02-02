# Exigences

Lorsqu'on utilise le Bluetooth nous devons utiliser des caratcères et chaque mouvemant sera interprété ainsi:
- Gauche => ```g```
- Droite => ```d```
- Avancer => ```a```
- Reculer => ```r```
- Stop => ```s```

Entrées/Sorties  | Fonction |
--- | --- |
13 | Moteur Gauche |
--- | Moteur Droite |
13 | Frein Gauche |
--- | Frein Droite |


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
___
> Sachant que nous avons notre Robot nommé "Liza" qui a des caractéristique enfin des défauts (cette p*te)
exemple: 

- Le moteur droit est inversé.
- Le courant est continue pas alternatif
