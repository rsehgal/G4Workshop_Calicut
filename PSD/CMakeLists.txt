cmake_minimum_required(VERSION 3.16)
project(PSD)

# Find Geant4 package
find_package(Geant4 REQUIRED)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB MAC_FILES ${PROJECT_SOURCE_DIR}/MacFiles/*)
message(STATUS ${MAC_FILES})
file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

option(VERBOSE "Use Decay constants for gamma" OFF)
if(VERBOSE)
add_definitions(-DVERBOSE)
endif(VERBOSE)


option(FOR_GAMMA "Use Decay constants for gamma" ON)
if(FOR_GAMMA)
add_definitions(-DFOR_GAMMA)
endif(FOR_GAMMA)

option(FOR_NEUTRON "Use Decay constants for neutron" OFF)
if(FOR_NEUTRON)
add_definitions(-DFOR_NEUTRON)
endif(FOR_NEUTRON)

# Include directories
include_directories(${Geant4_INCLUDE_DIRS} include)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

# Add source files
file(GLOB SOURCES src/*.cpp)
file(GLOB MAC_FILES *.mac)
file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} PSD.cpp)

# Link with Geant4 libraries
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})

# Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

add_executable(PlotPulse ../test/PlotPulse.cpp)
target_link_libraries(PlotPulse ${ROOT_LIBRARIES})

add_executable(PlotPulse2 ../test/PlotPulse2.cpp)
target_link_libraries(PlotPulse2 ${ROOT_LIBRARIES})

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
