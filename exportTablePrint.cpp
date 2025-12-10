#include <windows.h>
#include <iostream>


/*

Use: .\exportTablePrint.exe [DLL]

*/

int main(int argc, char ** argv) {
    char* dllPath = argv[1];

    // Load DLL into memory
    HMODULE hModule = LoadLibraryA(dllPath);
    if (!hModule) {
        std::cerr << "Failed to load DLL\n";
        return 1;
    }

    // Get DOS Header
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        std::cerr << "Not a valid PE file\n";
        return 1;
    }

    // Get NT Headers
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((BYTE*)hModule + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        std::cerr << "Invalid NT headers\n";
        return 1;
    }

    // Get Export Directory
    DWORD exportRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    if (!exportRVA) {
        std::cerr << "No export table found\n";
        return 1;
    }

    PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)hModule + exportRVA);

    DWORD* nameRVAs = (DWORD*)((BYTE*)hModule + exportDir->AddressOfNames);
    WORD* nameOrdinals = (WORD*)((BYTE*)hModule + exportDir->AddressOfNameOrdinals);

    std::cout << "Exported functions:\n";
    for (DWORD i = 0; i < exportDir->NumberOfNames; ++i) {
        char* funcName = (char*)hModule + nameRVAs[i];
        std::cout << funcName << "\n";
    }

    FreeLibrary(hModule);
    return 0;
}
