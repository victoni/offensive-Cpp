# Process enumeration

Enumerate processes (T1057) via the `CreateToolhelp32Snapshot` Windows API call.

## Contents

1. `processEnum.cpp` enumerates the processes and prints the details of a process given its PID.
2. `processEnumTargeted.cpp` finds details of a process given the binary name.

## Compilation

`x86_64-w64-mingw32-g++ -static -static-libgcc -static-libstdc++ processEnum.cpp`