
#include <cstdio>
#include <iostream>
#include <print>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define FILE_LONG_PATH
#include <windows.h>
#include <shellapi.h>
#endif

void OpenURL(const std::string& url);

int openNescoffee();