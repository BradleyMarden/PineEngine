
FILE(GLOB_RECURSE MY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
Message( STATUS "FINDING HEADERS" ${MY_HEADERS} )

add_library(
    PineEngine
#CORE
    Source/Pine/Core/Core.cpp
    Source/Pine/Core/Game.cpp
    Source/Pine/Core/Input.cpp
    Source/Pine/Core/Scene.cpp
    Source/Pine/Core/window.cpp
    Source/Pine/Core/EntryPoint.cpp
    Source/Pine/Core/PineObject.cpp
    Source/Pine/Core/IPineObject.cpp
    Source/Pine/Core/ComponentSystem.cpp
#Components
    Source/Pine/Components/Component.cpp
    Source/Pine/Components/MaterialComponent.cpp
    Source/Pine/Components/NetworkComponent.cpp
    Source/Pine/Components/RendererComponent.cpp
    Source/Pine/Components/TransformComponent.cpp
#LOGGING
    Source/Pine/Logging/Log.cpp
#MATHS
    Source/Pine/Maths/PMaths.cpp
#Networking
    Source/Pine/Networking/Networking.cpp
    #MAY NEED TO ADD SERVER NETWORKING CLASS
#PRIMITIVES -OUTDATED, SUBSEQUENTLY REMOVED

#Rendering
    Source/Pine/Rendering/Renderer.cpp
    Source/Pine/Rendering/Shader.cpp
    Source/Pine/Rendering/LayerManager.cpp
    Source/Pine/Rendering/Layer.cpp
    Source/Pine/Rendering/VertexBuffer.cpp
    Source/Pine/Rendering/IndexBuffer.cpp
    Source/Pine/Rendering/OrthographicCamera.cpp
    Source/Pine/Rendering/OrthographicCameraController.cpp
#Events
    Source/Pine/Events/EventSystem.cpp
    Source/Pine/Events/Event.cpp
    Source/Pine/Events/EventBinder.cpp
#imgui
    Vendor/imgui1.83/imgui.cpp
    Vendor/imgui1.83/imgui_demo.cpp
    Vendor/imgui1.83/imgui_draw.cpp
    Vendor/imgui1.83/imgui_impl_opengl3.cpp
    Vendor/imgui1.83/imgui_impl_sdl.cpp
    Vendor/imgui1.83/imgui_tables.cpp
    Vendor/imgui1.83/imgui_widgets.cpp
#Headers
    ${MY_HEADERS}
)


target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Core")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Components")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Logging")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Maths")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Networking")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Rendering")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Pine/Events")

#VENDOR INCLUDES
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glew-2.1.0/include")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui1.83")
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm")


#target_include_directories(PineEngine PUBLIC ${GLFW_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${GLEW_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2_IMAGE_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2TTF_INCLUDE_DIR})
target_include_directories(PineEngine PUBLIC ${SDL2Mixer_INCLUDE_DIRS})
target_include_directories(PineEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/enet-1.3.16/include")


#PRE-PROCESSOR DIRECTIVES
Message( STATUS "Project release mode: " ${DEBUG_OR_RELEASE})
if((NOT ${DEBUG_OR_RELEASE} STREQUAL "Debug") AND (NOT ${DEBUG_OR_RELEASE} STREQUAL "Release"))

    Message( FATAL_ERROR "ERROR: Project release mode need to be either 'Debug' or 'Release'. Please Check spelling and rebuild." ${SDL2_INCLUDE_DIR})

elseif(${DEBUG_OR_RELEASE} STREQUAL "Debug")

    #add_compile_definitions(_CONSOLE)
    #add_compile_definitions(DEBUG)
    #Set(CMAKE_BUILD_TYPE ${DEBUG_OR_RELEASE})
    if(APPLE)
        add_compile_definitions(PINE_PLATFORM_MACOS)
        add_compile_definitions(DEBUG)

    else(WIN32)

        add_compile_definitions(PINE_PLATFORM_WINDOWS)
        add_compile_definitions(DEBUG)

    endif()

else(${DEBUG_OR_RELEASE} STREQUAL "Release")
    #Set(CMAKE_BUILD_TYPE ${DEBUG_OR_RELEASE})

    if(APPLE)
        add_compile_definitions(PINE_PLATFORM_MACOS)

    else(WIN32)

        add_compile_definitions(PINE_PLATFORM_WINDOWS)
        endif()
endif()









