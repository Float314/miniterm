#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include "download.hpp"

int downloadFile(const std::string& url, const std::string& outputPath) {
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outputPath.c_str(), "wb");
        if (!fp) {
            std::cerr << "Error opening file for writing: " << outputPath << std::endl;
            curl_easy_cleanup(curl);
            return 1; // Failure
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        fclose(fp);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error downloading file: " << curl_easy_strerror(res) << std::endl;
            return 1; // Failure
        }
        return 0; // Success
    }
    return 1; // Failure
}