# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build

# Include any dependencies generated for this target.
include CMakeFiles/Game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Game.dir/flags.make

CMakeFiles/Game.dir/Game/Source/main.cpp.o: CMakeFiles/Game.dir/flags.make
CMakeFiles/Game.dir/Game/Source/main.cpp.o: ../Game/Source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Game.dir/Game/Source/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game.dir/Game/Source/main.cpp.o -c /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/main.cpp

CMakeFiles/Game.dir/Game/Source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game.dir/Game/Source/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/main.cpp > CMakeFiles/Game.dir/Game/Source/main.cpp.i

CMakeFiles/Game.dir/Game/Source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game.dir/Game/Source/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/main.cpp -o CMakeFiles/Game.dir/Game/Source/main.cpp.s

CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o: CMakeFiles/Game.dir/flags.make
CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o: ../Game/Source/MyGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o -c /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/MyGame.cpp

CMakeFiles/Game.dir/Game/Source/MyGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game.dir/Game/Source/MyGame.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/MyGame.cpp > CMakeFiles/Game.dir/Game/Source/MyGame.cpp.i

CMakeFiles/Game.dir/Game/Source/MyGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game.dir/Game/Source/MyGame.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/Source/MyGame.cpp -o CMakeFiles/Game.dir/Game/Source/MyGame.cpp.s

# Object files for target Game
Game_OBJECTS = \
"CMakeFiles/Game.dir/Game/Source/main.cpp.o" \
"CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o"

# External object files for target Game
Game_EXTERNAL_OBJECTS =

bin/Game: CMakeFiles/Game.dir/Game/Source/main.cpp.o
bin/Game: CMakeFiles/Game.dir/Game/Source/MyGame.cpp.o
bin/Game: CMakeFiles/Game.dir/build.make
bin/Game: PineEngine/libPineEngine.a
bin/Game: /usr/local/lib/libSDL2main.a
bin/Game: /usr/local/lib/libSDL2.dylib
bin/Game: ../PineEngine/Vendor/enet-1.3.16/lib/libenet.a
bin/Game: CMakeFiles/Game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/Game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Game.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying SDL2.dll to build directory"
	/usr/local/Cellar/cmake/3.19.3/bin/cmake -E copy /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/PineEngine/Vendor/SDL2-2.0.14/lib/x64/SDL2.dll /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/bin/SDL2.dll
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying SDL2_image.dll to build directory"
	/usr/local/Cellar/cmake/3.19.3/bin/cmake -E copy /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/PineEngine/Vendor/SDL2_image-2.0.5/lib/x64/SDL2_image.dll /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/bin/SDL2_image.dll
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying SDL2_mixer.dll to build directory"
	/usr/local/Cellar/cmake/3.19.3/bin/cmake -E copy /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/PineEngine/Vendor/SDL2_mixer-2.0.4/lib/x64/SDL2_mixer.dll /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/bin/SDL2_mixer.dll
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying SDL2_ttf.dll to build directory"
	/usr/local/Cellar/cmake/3.19.3/bin/cmake -E copy /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/PineEngine/Vendor/SDL2_ttf-2.0.15/lib/x64/SDL2_ttf.dll /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/bin/SDL2_ttf.dll

# Rule to build all files generated by this target.
CMakeFiles/Game.dir/build: bin/Game

.PHONY : CMakeFiles/Game.dir/build

CMakeFiles/Game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Game.dir/clean

CMakeFiles/Game.dir/depend:
	cd /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/build/CMakeFiles/Game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Game.dir/depend
