cmake_minimum_required(VERSION 3.10)
project(ft_donut CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajout du dossier d'en-têtes
include_directories(include)

# Définition des fichiers source
set(SOURCES
    src/main.cpp
    src/donut.cpp
)

# Création de l'exécutable
add_executable(ft_donut ${SOURCES})

# Options de compilation
if(MSVC)
  target_compile_options(ft_donut PRIVATE /W4)
else()
  target_compile_options(ft_donut PRIVATE -Wall -Wextra -Werror)
endif()

# Création d'un dossier obj pour les fichiers objets
set_target_properties(ft_donut PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    OBJECTS_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj"
)
