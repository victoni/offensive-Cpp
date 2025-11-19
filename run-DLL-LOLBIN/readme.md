# Running DLL from LOLBIN

1. rundll32.exe
	- Run a DLL with `rundll32.exe mydll.dll,FUNCTION`. FUNCTION is your function name implemented in the DLL.
	- T1218.011
2. regsvr32.exe
	- (Un)Registers DLL as COM components. Also runs them.
	- T1218.010

## Contents

1. `mpclient.cpp`. Example source code for DLL to run with rundll32. After compiling: `rundll32.exe mpclient.dll,Main`
2. `mpclientunregister.dll`. Example source code for DLL to run **register** with regsvr32.exe, after compiling. Example: `regsvr32.exe /s mpclientunregister.dll`. The code that runs is inside the function DllRegisterServer. To unregister a DLL: `regsvr32.exe /u /s mpclientunregister.dll`. The code for **unregistering** will be implemented inside the function DllUnRegisterServer.

## Compilation

`x86_64-w64-mingw32-g++ -static -static-libgcc -static-libstdc++ --shared -o mpclientregister.dll mpclientregister.cpp`