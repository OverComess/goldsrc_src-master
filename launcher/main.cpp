#include <Windows.h>
#include <sys/stat.h>

int checkIsSteamRunning(char* appCmdLine)
{
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

	return 0;
	
}