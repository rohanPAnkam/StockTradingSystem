cmake_minimum_required(VERSION 3.30)

project(StockTrading)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Add Source File
add_executable(my_app main.cpp src/order.cpp src/orderBook.cpp src/stock.cpp src/trader.cpp)

#Set C++ standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Add include directories
# include_directories(include)
# Specify additional libraries or dependancies
target_link_libraries(my_app PRIVATE pthread)
