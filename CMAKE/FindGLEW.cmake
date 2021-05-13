FIND_PATH(GLEW_INCLUDE_DIR glew.h
        HINTS
        ${glew}
        $ENV{glew}
        PATH_SUFFIXES include/GL include glew
        i686-w64-mingw32/include/GL
        x86_64-w64-mingw32/include/GL
        glew-2.1.0/include/GL
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include/GL
        /usr/include/GL
        ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/glew-2.1.0/include/GL
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        )

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    FIND_LIBRARY(GLEW_LIBRARY_TEMP
            NAMES glew32
            HINTS
            ${glew}
            $ENV{glew}
            PATH_SUFFIXES lib64 lib
            lib/Release/x64
            x86_64-w64-mingw32/lib/Release
            glew-2.1.0/lib/Release/x64
            PATHS
            ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/glew-2.1.0/lib/Release/x64
            /sw
            /opt/local
            /opt/csw
            /opt
            )
    # On 32bit build find the 32bit libs
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
    FIND_LIBRARY(GLEW_LIBRARY_TEMP
            NAMES glew32
            HINTS
            ${glew}
            $ENV{glew}
            PATH_SUFFIXES lib
            lib/Release/Win32
            i686-w64-mingw32/lib/Release/Win32
            glew-2.1.0/lib/Release/WIN32
            PATHS
            ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/glew-2.1.0/lib/Release/Win32
            /sw
            /opt/local
            /opt/csw
            /opt
            )
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)

SET(GLEW_FOUND "NO")
IF(GLEW_LIBRARY_TEMP)
    # Set the final string here so the GUI reflects the final state.
    SET(GLEW_LIBRARY ${GLEW_LIBRARY_TEMP} CACHE STRING "Where the GLEW Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(GLEW_LIBRARY_TEMP "${GLEW_LIBRARY_TEMP}" CACHE INTERNAL "")
    SET(GLEW_FOUND "YES")
ENDIF(GLEW_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW REQUIRED_VARS GLEW_LIBRARY GLEW_INCLUDE_DIR)
