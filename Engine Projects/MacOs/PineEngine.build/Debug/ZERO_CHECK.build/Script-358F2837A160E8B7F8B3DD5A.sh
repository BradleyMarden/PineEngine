#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode
  make -f /Users/bradley/documents/C++Projects/LatestVersion/PineEngine/xcode/CMakeScripts/ReRunCMake.make
fi

