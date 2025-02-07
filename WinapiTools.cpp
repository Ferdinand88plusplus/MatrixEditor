#include "WinapiTools.h"


#include <windows.h>
#include <commdlg.h>

std::string OpenFileDialog()
{
    // dialog params
    OPENFILENAME openFileName;
    char szFile[260] = { 0 };

    ZeroMemory(&openFileName, sizeof(openFileName));
    openFileName.lStructSize = sizeof(openFileName);
    openFileName.hwndOwner = nullptr;
    openFileName.lpstrFile = szFile;
    openFileName.nMaxFile = sizeof(szFile);
    openFileName.lpstrFilter = "All files";
    openFileName.nFilterIndex = 1;
    openFileName.lpstrFileTitle = nullptr;
    openFileName.nMaxFileTitle = 0;
    openFileName.lpstrInitialDir = nullptr;  // Начальная директория
    openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&openFileName) == TRUE)
    {
        return openFileName.lpstrFile; 
    }

    // dialog canceled, return empty string
    return ""; 
}
