# NisSrv.exe DLL hijacking

DLL hijacking (T1574.001) for nissrv.exe, a Windows-signed executable.

## Contents

1. `mpclient.cpp`, the source code for generating the DLL. The function that runs your code gets called when nissrv.exe calls the MpUtilsExportFunctions function.
2. `mpclientalone.cpp` the source code for generating the DLL. The function that runs your code gets called when DLL is loaded by nissrv.exe

## Compilation

`x86_64-w64-mingw32-g++ -static -static-libgcc -static-libstdc++ --shared -o mpclient.dll mpclient.cpp`