// nescoffee

#include <cstdio>
#include <iostream>
#include <print>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define FILE_LONG_PATH
#include <windows.h>
#include <shellapi.h>
#endif

void OpenURL(const std::string& url) {
    if (url.empty()) {
        return;
    }

#if defined(_WIN32) || defined(_WIN64)
    // Windows: Use ShellExecuteA from shellapi.h
    // "open" specifies the default action for the URL protocol
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

#elif defined(__APPLE__)
    // macOS: Use the 'open' command via system()
    std::string command = "open " + url;
    std::system(command.c_str());

#elif defined(__linux__) || defined(__FreeBSD__)
    // Linux/Unix: Use 'xdg-open' which routes to the user's default browser
    std::string command = "xdg-open " + url;
    std::system(command.c_str());

#else
    #error "Unknown or unsupported operating system."
#endif
}

int openNescoffee() { 
    const std::string insta_url = "https://www.instagram.com/p/DX2NdgpKZTY/"; 
    const std::string yt_url = "https://www.youtube.com/watch?v=PLM8PjzxRoo"; 

    std::string plat;

    while (!(plat == "I" || plat == "Y" ||
            plat == "i" || plat == "y")
    ) { 
        std::println("Choose platform for which you like to open \n Y = Youtube, I = Instagram "); 
        std::cin >> plat;

        if(!(plat == "I" || plat == "Y" ||
            plat == "i" || plat == "y")) { 
                std::println("Invalid Option. Please re-enter platform...");
            }
    } 

    if(plat == "I" || plat == "i") { 
        OpenURL(insta_url);
    } else if (plat == "Y" || plat == "y") OpenURL(yt_url);

    return 0; 
}