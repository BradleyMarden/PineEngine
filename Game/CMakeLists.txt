cmake_minimum_required(VERSION 3.12)
project(PineEngine VERSION 0.3)
set(CMAKE_CXX_STANDARD 17)

add_executable(Game 
   # Source/main.cpp
    Source/MyGame.cpp
    Source/Player.cpp

)





target_include_directories(Game PUBLIC "../PineEngine/Source")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Core")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Logging")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Maths")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Networking")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Events")
target_include_directories(Game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../PineEngine/Source/Pine/Rendering")

#VENDOR INCLUDES
target_include_directories(Game PUBLIC "../PineEngine/Vendor/spdlog/include")
target_include_directories(Game PUBLIC "../PineEngine/Vendor/glew-2.1.0/include")
target_include_directories(Game PUBLIC "../PineEngine/Vendor/SDL/2.0.14/include")
target_include_directories(Game PUBLIC "../PineEngine/Vendor/enet-1.3.16/include")
#might not need glm here
target_include_directories(Game PUBLIC "../PineEngine/Vendor/glm")


add_library(
    PineEngine
    STATIC
    IMPORTED
    ../build/PineEngine/libPineEngine.a
    )