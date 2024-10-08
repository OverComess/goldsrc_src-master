#include <Windows.h>
#include <stdio.h>
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

    /*if (GetCurrentDirectoryA(sizeof(Buffer) * sizeof(char), Buffer))
    {
        char* correctPath = strrchr(Buffer, '\\');
        char directoryPathPtr;

        if (correctPath)
        {
            while (true)
            {
                correctPath[1] = '\0';
                strcat(correctPath, "steam_dev.exe");
                FILE* steamDevExeFile = fopen(correctPath, "rb");

                if (steamDevExeFile)
                    break;

                correctPath[1] = 0;
                strcat(correctPath, "steam.exe");
                FILE* steamExeFile = fopen(correctPath, "rb");

                if (steamExeFile)
                {
                    fclose(steamExeFile);
                    int counter = 0;

                    do
                    {
                        directoryPathPtr = Buffer[counter++];
                        directoryBuffer[counter] = directoryPathPtr;
                    } while (directoryPathPtr);

                }

            }
        }
    }
    

    if (!directoryBuffer)
    {
        if (!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Valve\\Steam", (PHKEY)data))
        {
            DWORD cbData = 260;
            RegQueryValueExA((HKEY)data, "SteamExe");
            RegCloseKey(((HKEY)data));
        }
        directoryPtr = directoryBuffer;
        if (!directoryBuffer)
            return MessageBoxA(NULL, "Error running game: could not find steam.exe to launch", "Fatal Error", )
    }

    */
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
    const char* FsModule = "filesystem_stdio.dll";
	//if (checkFileSystem(lpCmdLine, FsModule, FsModule))
		//return 0;

    HANDLE mutex = CreateMutexA(NULL, NULL, "ValveHalfLifeLauncher");
    if (mutex)
        GetLastError();







	return 0;
	
}

#endif