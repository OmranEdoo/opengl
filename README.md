# TP 1

## Données
J'ai importé un MNT de la région montagneuse de Santa Monica en Californie, aux États-Unis. 

## Dépendances
Pour cela, j'ai utilisé les librairies GDAL/Ogr qu'il faut donc installer en plus des librairies d'OpenGL afin de faire fonctionner l'application.

## Installation et compilation
J'ai codé sur Visual Studio et je n'ai pas utilisé CMake ni QMake mais l'extension vcpkg qui m'a permis d'installer facilement les librairies requises.

## Traitement
J'ai utilisé des indexes buffer afin de réduire l'utilisation de la mémoire.
J'ai mélangé la texture et une matrice de couleur afin d'avoir un effet neige et roche, 
tout cela est implémenté dans la classe layerraster et les fichiers shaders.

## Description des modes
Il y a trois modes dans mon application. Pour changer de mode, il suffit d'appuyer sur les touches 1, 2 et 3.

- **MODE 1** : la caméra peut bouger dans toutes les directions avec les flèches directionnelles, les touches Espace et Shift sans que la caméra ne peut pas aller sous ou hors du MNT. Le cube suit une trajectoire circulaire en suivant la hauteur du MNT.

- **MODE 2** : le cube suit toujours la même trajectoire mais la caméra le suit par derrière en restant orientée vers lui.

- **MODE 3** : la caméra suit le cube qui peut avancer sur le MNT avec les touches directionnelles, la touche Espace permet de sauter.

Pour toute question ou remarque, me contacter à l'adresse mail omranedoo@gmail.com.
