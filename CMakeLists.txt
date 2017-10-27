cmake_minimum_required(VERSION 3.8)
project(MillenniumFalconSimulation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DataStructures/BtkMatrix.h DataStructures/BtkMatrixNode.h MillenniumFalconBacktracking/Backtracking.cpp MillenniumFalconBacktracking/Backtracking.h DataStructures/LinkedList.h DataStructures/Node.cpp DataStructures/Node.h DataStructures/PfdMatrixNode.h DataStructures/PfdMatrix.h RebelBase.h cmake-build-debug/resources/background.jpg cmake-build-debug/resources/asteroid.png cmake-build-debug/resources/rebelbase.png cmake-build-debug/resources/millennium_falcon.png Asteroid.cpp Asteroid.h MillenniumFalcon.cpp MillenniumFalcon.h Entity.cpp Entity.h MillenniumFalconBacktracking/BacktrackingWindow.cpp MillenniumFalconBacktracking/BacktrackingWindow.h)
add_executable(MillenniumFalconSimulation ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MillenniumFalconSimulation ${SFML_LIBRARIES})
endif()