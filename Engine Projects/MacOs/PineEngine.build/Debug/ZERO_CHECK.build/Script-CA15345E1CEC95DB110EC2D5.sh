#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine Projects/MacOs"
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine\ Projects/MacOs/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine Projects/MacOs"
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine\ Projects/MacOs/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine Projects/MacOs"
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine\ Projects/MacOs/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine Projects/MacOs"
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/Engine\ Projects/MacOs/CMakeScripts/ReRunCMake.make
fi

