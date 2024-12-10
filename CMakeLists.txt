cmake_minimum_required(VERSION 3.10)
project(exec)

# Spécifier le chemin d'installation d'OpenCV (modifiez si nécessaire)
set(OpenCV_DIR /home/ubuntu/install/build)

# Trouver OpenCV
find_package(OpenCV REQUIRED)

# Inclure les répertoires d'en-têtes
include_directories(${OpenCV_INCLUDE_DIRS})

# Lister tous les fichiers sources (au même niveau que CMakeLists.txt)
set(SOURCES
    main.cpp
    ImageProcessor.cpp
    Filters.cpp
)

# Ajouter l'exécutable
add_executable(exec ${SOURCES})

# Lier les bibliothèques OpenCV
target_link_libraries(exec ${OpenCV_LIBS})
