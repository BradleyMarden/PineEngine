# PineEngine

![PineEngine](/PineEngineText.png?raw=true "PineEngine")
Pine Engine



NOTE:
please clone rather than download via zip. github compression ruins the audio fodler, and wont clone the SPDLOG module.

SUPPORT
if missing DLLs please check 'EngineProject/INCLUDE THESE IF MISSING' folder, 
and copy the contents to the bin/release or bin/debug root folder.

PineEngine folder is container for engine code
Game folder is container for game code.

To run the premade demo game exe, please navigate to EngineProject/Windows/bin
In there are two folders. Both run, however one is a Release version, the other a debug version. 

if SPDLOG errors, please use git submodule update --init --recursive
will only work if cloned from github

want to add changes?

Please use CMake to compile. 

1-navigate to Engine Project folder
2-Open Windows folder
3-To rebuild type cmake ../..