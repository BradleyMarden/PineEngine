#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject
  make -f /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject
  make -f /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject
  make -f /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject
  make -f /Users/bradley/Documents/C++Projects/LatestVersion/PineEngine/Game/XCodeProject/CMakeScripts/ReRunCMake.make
fi

