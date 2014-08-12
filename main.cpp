#include <windows.h>
#include "detours.h"
#include "Shlobj.h"

typedef 
PIDLIST_ABSOLUTE (WINAPI* tSHBrowseForFolderW)	(LPBROWSEINFO lpbi);
PIDLIST_ABSOLUTE  WINAPI hook_SHBrowseForFolderW(LPBROWSEINFO lpbi);

MologieDetours::Detour<tSHBrowseForFolderW>* detour_SHBrowseForFolderW = NULL;

PIDLIST_ABSOLUTE WINAPI hook_SHBrowseForFolderW(LPBROWSEINFO lpbi) {
	lpbi->ulFlags |= BIF_EDITBOX | BIF_STATUSTEXT;
	return detour_SHBrowseForFolderW->GetOriginalFunction()( lpbi );
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			try
			{
				detour_SHBrowseForFolderW = new MologieDetours::Detour<tSHBrowseForFolderW>("Shell32.dll", "SHBrowseForFolderW", hook_SHBrowseForFolderW);
			}
			catch(MologieDetours::DetourException &e)
			{
				// Something went wrong, too bad
				
				return FALSE;
			}
			break;
		case DLL_PROCESS_DETACH:
			delete detour_SHBrowseForFolderW;
			break;
	}
	return TRUE;
}