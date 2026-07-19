#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>

int downloadFile(const std::string& url, const std::string& outputPath);