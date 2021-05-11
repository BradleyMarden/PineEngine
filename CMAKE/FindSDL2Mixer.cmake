# OpenClonk, http://www.openclonk.org
#
# Copyright (c) 2016, The OpenClonk Team and contributors
#
# Distributed under the terms of the ISC license; see accompanying file
# "COPYING" for details.
#
# "Clonk" is a registered trademark of Matthes Bender, used with permission.
# See accompanying file "TRADEMARK" for details.
#
# To redistribute this file separately, substitute the full license texts
# for the above references.

# Locate SDL_Mixer 2.
# This module defines
#  SDL2Mixer_INCLUDE_DIRS - a list of directories that need to be added to the include path
#  SDL2Mixer_LIBRARIES - a list of libraries to link against to use SDL2
#  SDL2Mixer_FOUND - if false, SDL2 cannot be used

if(SDL2Mixer_FIND_QUIETLY)
    set(_FIND_SDL2_ARG QUIET)
endif()

find_package(SDL2 ${_FIND_SDL2_ARG})
find_path(SDL2Mixer_INCLUDE_DIR SDL_mixer.h 
    HINTS
    ${SDL2}
    PATH_SUFFIXES include/SDL2
    i686-w64-mingw32/include/SDL2
    x86_64-w64-mingw32/include/SDL2
    SDL2_mixer-2.0.4/include
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/SDL2_mixer-2.0.4/include
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
)
mark_as_advanced(SDL2Mixer_INCLUDE_DIR)
    find_library(SDL2Mixer_LIBRARY 
    NAMES SDL2_mixer
    HINTS
    ${SDL2}
    $ENV{SDL2}
    PATH_SUFFIXES lib64 lib
    lib/x64
    x86_64-w64-mingw32/lib
    PATHS
    ${CMAKE_SOURCE_DIR}/PineEngine/Vendor/SDL2_mixer-2.0.4/lib/x64
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    )
mark_as_advanced(SDL2Mixer_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2Mixer REQUIRED_VARS SDL2Mixer_LIBRARY SDL2Mixer_INCLUDE_DIR
        SDL2_LIBRARY SDL2_INCLUDE_DIR)

if (SDL2Mixer_FOUND)
    set(SDL2Mixer_LIBRARIES ${SDL2Mixer_LIBRARY} ${SDL2_LIBRARIES})
    set(SDL2Mixer_INCLUDE_DIRS ${SDL2Mixer_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
endif()