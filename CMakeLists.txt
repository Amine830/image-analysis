cmake_minimum_required(VERSION 3.10)
project(exec)


set(OpenCV_DIR /home/ubuntu/install/build)

# Trouver OpenCV
find_package(OpenCV REQUIRED)

# Inclure les répertoires d'en-têtes d'OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Ajouter l'exécutable
add_executable(exec histo.cpp)

# Lier les bibliothèques OpenCV
target_link_libraries(exec ${OpenCV_LIBS})
