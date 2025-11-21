#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <tlhelp32.h>
#include <psapi.h>

using namespace std;

void FindProcess(DWORD pid){
	
	// getting a handle for the process
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (hProcess == NULL){
		cout << "[+] Process handle failed";
	}

	HMODULE lphModule[1024];
	DWORD cbNeeded;
	BOOL hProcessModules = EnumProcessModules(hProcess, lphModule, sizeof(lphModule), &cbNeeded);

	int lphModuleSize = sizeof(lphModule) / sizeof(HMODULE);

	for(int i = 0; i < lphModuleSize; i++){
		TCHAR lpFileName[MAX_PATH];
		DWORD nSize = sizeof(lpFileName);
		if(GetModuleFileNameExA(hProcess, lphModule[i], lpFileName, nSize)){
			printf("%#llx \t\t%s\n", lphModule[i], lpFileName);
		}
	}

}

int main(int argc, char const *argv[]){
	
	// create a snapshot with all processes at the time
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE){
		cout << "[+] Snapshot failed" << endl;
	}

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if(Process32First(hSnapshot, &processEntry)){
		while(Process32Next(hSnapshot, &processEntry)){

			wcout << L"PID: " << processEntry.th32ProcessID << "\n";
			wcout << L"PPID: " << processEntry.th32ParentProcessID << "\n";
			wcout << L"NAME: " << processEntry.szExeFile << "\n" << endl;
		}
		memset(&processEntry, 0, sizeof(processEntry));
		processEntry.dwSize = sizeof(PROCESSENTRY32);
	}

	CloseHandle(hSnapshot);
	
	DWORD pid;
	cout << "\n\nProces iD: ";
	cin >> pid;

	FindProcess(pid);
	return 0;
}