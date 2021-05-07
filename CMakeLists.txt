cmake_minimum_required(VERSION 3.12)
#may need to look at seperating out into mac/windows

Message("")
Message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
Message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
Message( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
Message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )
Message( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
Message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )
Message( STATUS "CMAKE_FINDCMAKE: " ${CMAKE_SOURCE_DIR}/CMAKE )
project(PineEngine VERSION 0.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")

add_subdirectory(PineEngine)

 include_directories(
    Game/Source
    PineEngine/Source
    PineEngine/Source/Pine/Core
    PineEngine/Source/Pine/Logging
    PineEngine/Source/Pine/Maths
    PineEngine/Source/Pine/Networking
    PineEngine/Vendor/spdlog/include
    PineEngine/Vendor/glew-2.1.0/include
    #PineEngine/Vendor/SDL/2.0.14/include
    PineEngine/Vendor/enet-1.3.16/include
    )

 add_executable(
    Game 
    Game/Source/main.cpp
    Game/Source/MyGame.cpp
 )
#message(WARNING "${CMAKE_SOURCE_DIR}/Vendor/SDL/2.0.14/lib/libSDL2.a"

# ------- Finds ---------- #


#------- SDL2-------------#
FIND_PACKAGE(SDL2 REQUIRED)
Message("")
Message( STATUS "FINDING SDL2" )
IF (${SDL2_FOUND})
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})
    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})
ELSE()
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})
    Message( FATAL_ERROR "SDL2 NOT FOUND" )
ENDIF()

FIND_PACKAGE(SDL2_IMAGE)
Message("")
Message( STATUS "FINDING SDL2_IMAGE" )
Message( STATUS "SDL2_IMAGE_FOUND: " ${SDL2_IMAGE_FOUND})
IF (${SDL2_IMAGE_FOUND})
    Message( STATUS "SDL2_IMAGE_INCLUDE_DIR: " ${SDL2_IMAGE_INCLUDE_DIR})
    Message( STATUS "SDL2_IMAGE_LIBRARY: " ${SDL2_IMAGE_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2_IMAGE NOT FOUND" )
ENDIF()

FIND_PACKAGE(SDL2TTF)
Message("")
Message( STATUS "FINDING SDL2TTF" )
Message( STATUS "SDL2TTF_FOUND: " ${SDL2TTF_FOUND} )
IF (${SDL2TTF_FOUND})
    Message( STATUS "SDL2TTF_INCLUDE_DIR: " ${SDL2TTF_INCLUDE_DIR})
    Message( STATUS "SDL2TTF_LIBRARY: " ${SDL2TTF_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2TTF NOT FOUND" )
ENDIF()
Message("")

FIND_PACKAGE(SDL2Mixer)

Message( STATUS "FINDING SDL2Mixer" )
Message( STATUS "SDL2Mixer_FOUND: " ${SDL2Mixer_FOUND} )

Message("")





# ------- End Finds ------ #

# ------- Inc & Link ---- #

#ile(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(Game PineEngine ${SDL2_LIBRARY} ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/enet-1.3.16/lib/libenet.a)

# ------- End ----------- #
