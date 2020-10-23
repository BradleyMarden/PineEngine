#pragma once
#ifdef PINE_PLATFORM_WINDOWS
#ifdef PINE_BUILD_DLL
#define PINE_API __declspec(dllexport)
#else
#define PINE_API __declspec(dllimport)
#endif

#else
#error Pine currently only supports Windows!
#endif

//NOT FROM BRAD TO SELF vv
//For some reason if the game project recieves a link error, use the following in the librarian console in this project, just change the path to the new one. REMEBER TO INCLUDE ANY NEW DEPENDENCIES!!
/////OUT:"C:\Users\brads\Desktop\TestForlib\PineEngine\bin\Debug-x64\PineEngine\PineEngine.lib" "C:\Users\brads\Desktop\TestForlib\PineEngine\PineEngine\Vendor\enet-1.3.16\lib\enet64.lib" "C:\Users\brads\Desktop\TestForlib\PineEngine\PineEngine\Vendor\SDL2-2.0.12\lib\x64\SDL2.lib"  /MACHINE:X64 /NOLOGO 