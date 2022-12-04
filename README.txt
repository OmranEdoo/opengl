J'ai réalisé le TP 1. J'ai importé un MNT.
J'ai utilisé des indexes buffer afin de réduire l'utilisation de la mémoire.
J'ai mélangé la texture et une matrice de couleur afin d'avoir un effet neige et roche, 
tout cela est implémenté dans la classe layerraster et les fichiers shaders.
Il y a trois modes dans mon application. 
Pour changer de mode, il suffit d'appuyer sur les touches 1, 2 et 3.

Description des modes:
    - MODE 1: la caméra peut bouger dans toutes les directions avec les flèches directionnelles, 
    les touches Espace et Shift sans que la caméra ne peut pas aller sous ou hors du MNT.
    Le cube suit une trajectoire circulaire en suivant la hauteur du MNT.
    - MODE 2: le cube suit toujours la même trajectoire mais la caméra le suit par derrière 
    en restant orientée vers lui.
    - MODE 3: la caméra suit le cube qui peut avancer sur le MNT avec les touches directionnelles,
    la touche Espace permet de sauter.
