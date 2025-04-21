# cmake_minimum_required(VERSION 3.30)

# project(StockTrading)
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# #Add Source File
# add_executable(my_app main.cpp src/order.cpp src/orderBook.cpp src/stock.cpp src/trader.cpp)

# #Set C++ standard
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# set(CMAKE_OSX_ARCHITECTURES "arm64")
# # Add include directories
# # include_directories(include)
# # Specify additional libraries or dependancies
# target_link_libraries(my_app PRIVATE pthread)

cmake_minimum_required(VERSION 3.10)

project(StockTrading LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type and debug flags
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Set architecture for macOS
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Add executable
add_executable(my_app
    main.cpp
    src/order.cpp
    src/orderBook.cpp
    src/stock.cpp
    src/trader.cpp
)

# Add include directories
target_include_directories(my_app PRIVATE include)

# Link libraries
target_link_libraries(my_app PRIVATE pthread)

# Add compiler warnings
target_compile_options(my_app PRIVATE -Wall -Wextra -Wpedantic)