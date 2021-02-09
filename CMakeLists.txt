cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
project(RestaurantFoodPrep)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(restaurantFoodPrep ${project_SRCS})
