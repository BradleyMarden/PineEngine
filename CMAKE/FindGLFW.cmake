FIND_PATH(GLFW_INCLUDE_DIR glfw3.h
        HINTS
        ${glfw}
        $ENV{glfw}
        PATH_SUFFIXES include/GLFW include glfw-3.3.4
        i686-w64-mingw32/include/GLFW
        x86_64-w64-mingw32/include/GLFW
        glfw-3.3.4/include/GLFW
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include/GLFW
        /usr/include/GLFW
        ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/glfw-3.3.4/include/GLFW
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        )

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    FIND_LIBRARY(GLFW_LIBRARY_TEMP
            NAMES glfw3
            HINTS
            ${glfw}
            $ENV{glfw}
            PATH_SUFFIXES lib64 lib lib-vc2019
            lib-vc2019
            x86_64-w64-mingw32/lib/Release
            glfw-3.3.4.bin.WIN64/lib-vc2019
            PATHS
            ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/glfw-3.3.4/lib-vc2019
            /sw
            /opt/local
            /opt/csw
            /opt
            )
ENDIF()

SET(GLFW_FOUND "NO")
IF(GLFW_LIBRARY_TEMP)
    # Set the final string here so the GUI reflects the final state.
    SET(GLFW_LIBRARY ${GLFW_LIBRARY_TEMP} CACHE STRING "Where the GLFW Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(GLFW_LIBRARY_TEMP "${GLFW_LIBRARY_TEMP}" CACHE INTERNAL "")
    SET(GLFW_FOUND "YES")
ENDIF(GLFW_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW REQUIRED_VARS GLFW_LIBRARY GLFW_INCLUDE_DIR)
