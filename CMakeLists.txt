cmake_minimum_required(VERSION 3.16)

project(WordPatternCounter VERSION 1.0 LANGUAGES CXX)

# Use C++17 or newer
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core)

# Define the executable
add_executable(${PROJECT_NAME}
    main.cpp
)

# Link against Qt6 Core library
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
)

# Enable automatic handling of Qt-related things like MOC (optional here, but good practice)
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)
