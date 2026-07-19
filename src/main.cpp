#include <iostream> 
#include <unordered_map>
#include <print>
#include <vector>


#if defined(_WIN32) || defined(_WIN64)
#define FILE_LONG_PATH
#include <windows.h>
#include <shellapi.h>
#include <winbase.h>
#endif

#include "nescoffee.hpp"
#include "file_operations.hpp"
#include "download.hpp"

const std::string introductory_txt = R"md(
miniterm - Mini Terminal. 

Licensed under a Modified MIT License (MIT No attribution or MIT-0). 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 

Refer to the License File For more info...
)md";

const std::string help_txt = R"md(
miniterm - Mini terminal. Licensed under the MIT-0 License... 

type "nescoffee" command for something special ;)
)md";

enum class subcmd { 
    Normal, // done 
    copy, // done
    del, // done
    download, // done 
    nescoffee, // https://www.youtube.com/watch?v=PLM8PjzxRoo || https://www.instagram.com/p/DX2NdgpKZTY/ 
    cd, // done
    md, // done
    deldir, // done 
    pwd, // done
    move, // done 
    rick // nichecoffee
};

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    // For Windows: Use Windows API or enable ANSI if supported
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
    }
#else
    // For Linux/macOS: Use ANSI escape codes
    std::cout << "\033[2J\033[1;1H";
#endif
}

std::vector<std::string> splitArgs(const std::string& input) {
    std::vector<std::string> args;
    std::string current;
    bool inQuotes = false;

    for (char c : input) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ' ' && !inQuotes) {
            if (!current.empty()) {
                args.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        args.push_back(current);
    }
    return args;
}

int main() { 
    std::cout << introductory_txt;
    while(true) { 
        std::string command__; 
        std::cout << "\033[0;32mminiterm\033[0;37m | \033[1;34m" << getCurrentDir() <<
            (isGitRepository(getCurrentDir()) ? " (" + getCurrentGitBranch(getCurrentDir()) + ")" : "") 
            << "\033[0;37m> ";
        std::getline(std::cin, command__);

        if(command__.empty()) continue;

        auto args = splitArgs(command__);
        std::string cmd = args[0];

        if(cmd == "exit") break;
        else if(cmd == "clear") { 
            clearScreen();
        } 
        else if(cmd == "nescoffee" || cmd == "rick") { 
            openNescoffee();
        }
        else if(cmd == "pwd") {
            std::cout << getCurrentDir() << std::endl;
        }
        else if(cmd == "cd") {
            if(args.size() < 2) {
                std::cerr << "Usage: cd <path>" << std::endl;
            } else {
                try {
                    std::filesystem::current_path(args[1]);
                } catch(const std::filesystem::filesystem_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        }
        else if(cmd == "md") {
            if(args.size() < 2) {
                std::cerr << "Usage: md <directory>" << std::endl;
            } else {
                createDir(args[1]);
            }
        }
        else if(cmd == "deldir") {
            if(args.size() < 2) {
                std::cerr << "Usage: deldir <directory>" << std::endl;
            } else {
                deleteDir(args[1]);
            }
        }
        else if(cmd == "copy") {
            if(args.size() < 3) {
                std::cerr << "Usage: copy <source> <destination>" << std::endl;
            } else {
                copyfile(args[1], args[2]);
            }
        }
        else if(cmd == "del") {
            if(args.size() < 2) {
                std::cerr << "Usage: del <file>" << std::endl;
            } else {
                deletefile(args[1]);
            }
        }
        else if (cmd == "help") { 
            std::cout << help_txt;
        }
        else if(cmd == "move" || cmd == "mv") {
            if(args.size() < 3) {
                std::cerr << "Usage: move <source> <destination>" << std::endl;
            } else {
                movefile(args[1], args[2]);
            }
        }
        else if(cmd == "download") {
            if(args.size() < 2) {
                std::cerr << "Usage: download <url> [output_path]" << std::endl;
            } else if(args.size() == 2) {
                std::string url = args[1];
                std::string filename = url.substr(url.find_last_of("/\\") + 1);
                if(filename.empty()) filename = "download";
                std::string dest = getCurrentDir() + "\\" + filename;
                downloadFile(url, dest);
            } else {
                downloadFile(args[1], args[2]);
            }
        }
        else { 
            auto thing = std::system(command__.c_str());
            if (thing != 0) { 
                std::cout << "Process Exited with Exit code: " << thing << std::endl;
            }
        }
    }
    return 0;
}