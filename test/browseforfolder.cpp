// browseforfolder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Shlobj.h"

int _tmain(int argc, _TCHAR* argv[])
{

	TCHAR szDir[MAX_PATH];
	BROWSEINFO bInfo;
	bInfo.hwndOwner = NULL;
		bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = szDir; // Address of a buffer to receive the display name of the folder selected by the user
	bInfo.lpszTitle = L"Please, select a folder"; // Title of the dialog
	bInfo.ulFlags = 0;
	bInfo.lpfn = NULL;
	bInfo.lParam = 0;
	bInfo.iImage = -1;

	LPITEMIDLIST lpItem = SHBrowseForFolder(&bInfo);
	if (lpItem != NULL)
	{
		SHGetPathFromIDList(lpItem, szDir);
		//......
	}

	return 0;
}

