#include "include.hpp"

int main()
{
    std::string previous_text;
    bool got_email = false, got_password = false;

    memory::empty_clipboard();

    SetConsoleTitleA("Authenticator account logger\n");
    std::cout << "[+] run activator and click authenticate and wait\n";

    while (true)
    {
        std::string clipboard_text = memory::get_clipboard_text();

        if (!clipboard_text.empty() && previous_text != clipboard_text)
        {
            previous_text = clipboard_text;

            if (!got_email && !got_password && clipboard_text.find("@") != std::string::npos)
            {
                std::cout << "[+] email [" << clipboard_text << "]\n";
                got_email = true;
            }
            else if (got_email && !got_password)
            {
                std::cout << "[+] password [" << clipboard_text << "]\n";
                got_password = true;
            }
            else if (got_email && got_password && clipboard_text.size() == 6)
            {
                std::uint32_t process_id = memory::find_process_id(L"Activator.exe");

                HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
                TerminateProcess(handle, 0);

                std::cout << "[+] 2fa code [" << clipboard_text << "]\n[=] exiting...";
                
                std::this_thread::sleep_for(std::chrono::seconds(8));
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}