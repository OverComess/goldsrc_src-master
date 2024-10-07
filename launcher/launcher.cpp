#include <Windows.h>
#include <sys/stat.h>

#if defined(_WIN32)

int checkIsSteamRunning(char* appCmdLine)
{
    char FileName[MAX_PATH];
    CHAR directoryBuffer[MAX_PATH];
    DWORD data;

    HMODULE moduleHandle = GetModuleHandleA(NULL);
    GetModuleFileNameA(moduleHandle, FileName, (sizeof(FileName) / sizeof(CHAR)));

    char* isPath = strrchr(FileName, '\\');
    if (isPath)
        *isPath = 0;

    HKEY hKey;
    if (!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Valve\\Steam", &hKey))
    {
        RegSetValueExA(hKey, "TempAppPath", NULL, REG_SZ, (const BYTE*)FileName, strlen(FileName) + 1);
        RegSetValueExA(hKey, "TempAppCmdLine", NULL, REG_SZ, (const BYTE*)appCmdLine, strlen(appCmdLine) + 1);
        data = -1;
        RegSetValueExA(hKey, "TempAppID", NULL, REG_DWORD, (const BYTE*)data, sizeof(data));
        RegCloseKey(hKey);
    }

    HWND steamWindow = FindWindowA("Valve_SteamIPC_Class", "Hidden Window");
    if (steamWindow)
        return PostMessageA(steamWindow, 1027, NULL, NULL);

    directoryBuffer[0] = '\0';
    char Buffer[MAX_PATH];

    return 0;
}

bool checkFileSystem(char* cmdLine, const char* libFileName, const char* FileName)
{
    char* cmdContainsSteam;
    char steamEndLineChar;
    struct _stat64i32 stat64_32;

    cmdContainsSteam = strstr(cmdLine, "-steam");

    if (cmdContainsSteam)
    {
        steamEndLineChar = cmdContainsSteam[6];
        if (!steamEndLineChar || isspace(steamEndLineChar))
            return 0;
    }

    if (!_stat64i32(FileName, &stat64_32) || _stat64i32(libFileName, &stat64_32))
        return 0;
    checkIsSteamRunning(cmdLine);

    return 1;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if (checkFileSystem(lpCmdLine, "filesystem_stdio.dll", "filesystem_stdio.dll"))
		return 0;

    HANDLE mutex = CreateMutexA(NULL, NULL, "ValveHalfLifeLauncher");
    if (mutex)
        GetLastError();



	return 0;
	
}

#endif