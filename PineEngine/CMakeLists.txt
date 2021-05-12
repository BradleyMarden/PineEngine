
#NEED TO FIX ECS, SPDLOG and REIMPPORT SDL2 for mac
FILE(GLOB_RECURSE MY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
Message( STATUS "FINDING HEADERS" ${MY_HEADERS} )

add_library(
    PineEngine
#CORE
    Source/Pine/Core/Core.cpp
    Source/Pine/Core/Game.cpp
    Source/Pine/Core/Input.cpp
#ECS
    
#LOGGING
    Source/Pine/Logging/Log.cpp
#MATHS
    Source/Pine/Maths/PMaths.cpp
#Networking
    Source/Pine/Networking/Networking.cpp
    #MAY NEED TO ADD SERVER NETWORKING CLASS
#PRIMITIVES -OUTDATED, SUBSEQUENTLY REMOVED

#Rendering

#Headers
    ${MY_HEADERS}
)
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Core")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Logging")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Maths")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Networking")

Message( STATUS "WE ARE HEREREERERER:" ${SDL2_INCLUDE_DIR})
#VENDOR INCLUDES
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glew-2.1.0/include")
target_include_directories(PineEngine PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2_IMAGE_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2Mixer_INCLUDE_DIRS})
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/enet-1.3.16/include")









#PART WAY THROUGH ADDING SDL COPIED THROUGH USR DIR
#FIXING THE INCLUDES WHEN PC BAT RUN OUT








