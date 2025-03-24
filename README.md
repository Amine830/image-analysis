# Projet d'Analyse d'Images

Ce projet est une application de traitement d'images développée avec OpenCV et Qt, offrant à la fois une interface en ligne de commande (CLI) et une interface graphique (GUI). Il permet d'appliquer divers filtres et transformations à des images.

Le projet a pour objectif de recoder toutes les fonctions de filtrage et de transformations géométriques afin de comprendre en profondeur leurs mécanismes et leur implémentation algorithmique.

## Table des matières
- Fonctionnalités
- Prérequis
- Installation
- Utilisation
  - Version CLI
  - Version GUI
- Structure du projet
- Documentation des fonctions
- Jeu de données d'images

## Fonctionnalités

### Filtres disponibles
- Filtre médian
- Filtre gaussien
- Filtre de Sobel (détection de contours)
- Filtre moyenneur

### Opérations sur les histogrammes
- Affichage de l'histogramme
- Affichage de l'histogramme cumulé
- Égalisation d'histogramme
- Étirement d'histogramme

### Transformations géométriques
- Zoom / Agrandissement
- Réduction
- Rotation
- Retournement (flip)
- Compression

## Prérequis

- CMake (version 3.22 ou plus récente)
- OpenCV 4.x
- Qt 6.x (pour l'interface graphique)
- Compilateur C++ compatible avec C++11 ou supérieur

## Installation

1. Clonez le dépôt :

```bash
git clone https://github.com/Amine830/image-analysis.git
cd image-analysis
```

2. Assurez-vous que les scripts de construction sont exécutables :

```bash
chmod +x build_cli.sh build_gui.sh
```
## Utilisation

### Version CLI

Pour exécuter l'application en ligne de commande :

```bash
./build_cli.sh
```

L'interface CLI vous permettra de :
1. Charger une image depuis votre système de fichiers
2. Appliquer différents filtres et transformations
3. Enregistrer l'image modifiée

L'application affichera les histogrammes à chaque étape du traitement.

### Version GUI

Pour exécuter l'application avec l'interface graphique :

```bash
./build_gui.sh
```

L'interface graphique offre une expérience plus intuitive avec des boutons pour chaque opération disponible :
- Chargement et sauvegarde d'images
- Boutons dédiés pour chaque type de filtre et transformation
- Affichage en temps réel de l'image et des histogrammes

## Structure du projet

Le projet est organisé comme suit :

```
image-analysis/
├── build_cli.sh             # Script pour compiler et exécuter la version CLI
├── build_gui.sh             # Script pour compiler et exécuter l'interface graphique
├── CMakeLists.txt           # Configuration CMake principale
├── Filters.cpp              # Implémentation des filtres
├── Filters.h                # Déclaration des fonctions de filtrage
├── ImageProcessor.cpp       # Classe de traitement d'images
├── ImageProcessor.h         # Interface de la classe de traitement
├── main.cpp                 # Point d'entrée de la version CLI
├── QtProject/               # Sources de l'interface graphique
│   ├── CMakeLists.txt       # Configuration CMake pour Qt
│   ├── main.cpp             # Point d'entrée GUI
│   ├── mainwindow.cpp       # Implémentation de l'interface
│   ├── mainwindow.h         # Déclaration de la classe MainWindow
│   └── mainwindow.ui        # Définition de l'interface utilisateur
└── img/                     # Dossier contenant les images
    ├── Donnee1/             # Premier jeu d'images de test
    ├── Donnee2/             # Second jeu d'images de test
    ├── Interface graphique/ # Captures d'écran de l'interface
    └── results/             # Résultats des traitements
```

## Configuration du projet

Si Qt n'est pas trouvé automatiquement, vous pouvez définir le chemin manuellement en modifiant le fichier CMakeLists.txt :

```cmake
set(CMAKE_PREFIX_PATH "/chemin/vers/qt/6.x.x/gcc_64")
```

Par exemple :
```cmake
set(CMAKE_PREFIX_PATH "/home/ubuntu/install/qt/6.8.1/gcc_64")
```

Alternativement, vous pouvez définir cette variable lors de l'appel à CMake :

```bash
cmake -DCMAKE_PREFIX_PATH="/chemin/vers/qt/6.x.x/gcc_64" .
```

## Documentation des fonctions

### Filtres

- **Filtre médian** : Réduit le bruit tout en préservant les contours
- **Filtre gaussien** : Applique un flou qui préserve les structures générales
- **Filtre de Sobel** : Détecte les contours dans l'image
- **Filtre moyenneur** : Applique un flou simple en calculant la moyenne des pixels adjacents

### Opérations sur les histogrammes

- **Égalisation d'histogramme** : Améliore le contraste en répartissant uniformément les intensités
- **Étirement d'histogramme** : Améliore le contraste en étirant la plage des valeurs d'intensité

### Transformations géométriques

- **Zoom** : Agrandit l'image en utilisant une interpolation
- **Réduction** : Réduit la taille de l'image 
- **Rotation** : Pivote l'image selon un angle donné
- **Retournement (flip)** : Inverse l'image horizontalement ou verticalement
- **Compression** : Réduit la taille du fichier en conservant une qualité acceptable

## Jeu de données d'images

Le dossier `img/` contient :
- **Donnee1/** et **Donnee2/** : Images de test pour expérimenter les fonctionnalités
- **Interface graphique/** : Captures d'écran de l'interface utilisateur
- **results/** : Exemples de résultats de traitements d'images

## Résolution de problèmes

1. **Erreur de compilation** : Vérifiez que OpenCV et Qt sont correctement installés
2. **Qt non trouvé** : Définissez le chemin correct vers Qt comme indiqué dans la section Configuration
3. **Images non chargées** : Assurez-vous que les chemins d'accès sont corrects et relatifs au répertoire d'exécution