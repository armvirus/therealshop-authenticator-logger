#pragma once

namespace memory
{
    inline std::string get_clipboard_text()
    {
        OpenClipboard(0);
        HANDLE clipboard_data = GetClipboardData(CF_TEXT);

        std::string text(static_cast<char*>(GlobalLock(clipboard_data)));

        GlobalUnlock(clipboard_data);
        CloseClipboard();

        return text;
    }

    inline void empty_clipboard()
    {
        const char* output = "";
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }

    inline std::uint32_t find_process_id(std::wstring process_name)
    {
        PROCESSENTRY32 process_info;
        process_info.dwSize = sizeof(process_info);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (snapshot == INVALID_HANDLE_VALUE)
        {
            return 0;
        }

        Process32First(snapshot, &process_info);
        if (!process_name.compare(process_info.szExeFile))
        {
            CloseHandle(snapshot);
            return process_info.th32ProcessID;
        }

        while (Process32Next(snapshot, &process_info))
        {
            if (!process_name.compare(process_info.szExeFile))
            {
                CloseHandle(snapshot);
                return process_info.th32ProcessID;
            }
        }

        CloseHandle(snapshot);
        return 0;
    }
}