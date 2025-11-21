#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <tlhelp32.h>

using namespace std;

int main(int argc, char const *argv[]){
	
	// create a snapshot with all processes at the time
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE){
		cout << "[+] Snapshot failed" << endl;
	}

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	// if we succeed in getting the first process
	if(Process32First(hSnapshot, &processEntry)){
		// while we get a process from the list
		do {

			// string comparison char* and wchar_t*
			// https://stackoverflow.com/questions/41876355/compare-c-string-of-types-char-and-wchar-t
			std::wstring k(L"notepad.exe");
			std::string t(processEntry.szExeFile);
			std::wstring a(t.begin(), t.end());

			// if the process is notepad
			if (a.compare(k) == 0){
				wcout << L"PID: " << processEntry.th32ProcessID << "\n";
				wcout << L"PPID: " << processEntry.th32ParentProcessID << "\n";
				wcout << L"NAME: " << processEntry.szExeFile << "\n" << endl;
				CloseHandle(hSnapshot);
				return 0;
				
			}
		} while(Process32Next(hSnapshot, &processEntry));
	}

}