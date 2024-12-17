
# fichier CMakeLists.txt pour le projet ImageAnalysis
# /mnt/e/Univ/M1/Image/image-analysis

cmake_minimum_required(VERSION 3.16)

# Nom du projet global
project(ImageAnalysis)

# Le chemin d'installation d'OpenCV
set(OpenCV_DIR /home/ubuntu/install/build)

# Utiliser C++17 pour tout le projet
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver les dépendances OpenCV
find_package(OpenCV REQUIRED)

# Trouver les dépendances Qt
set(CMAKE_PREFIX_PATH "/home/ubuntu/install/qt/6.8.1/gcc_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Inclure les répertoires d'en-têtes pour OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Ajouter les fichiers sources du projet OpenCV existant
set(SOURCES
    main.cpp
    ImageProcessor.cpp
    Filters.cpp
)

# Créer un exécutable OpenCV (sans interface graphique)
add_executable(OpenCVApp ${SOURCES})
target_link_libraries(OpenCVApp ${OpenCV_LIBS})

# Ajouter le sous-répertoire pour le projet Qt
add_subdirectory(QtProject)
