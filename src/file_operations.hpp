#include <filesystem>
#include <iostream>

int copyfile(const std::string& source, const std::string& destination);

int deletefile(const std::string& path); 

int movefile(const std::string& source, const std::string& destination);

int deleteDir(const std::string dir); 

int createDir(const std::string dir); 

std::string getCurrentDir();

#include <git2.h>
#include <string>

bool isGitRepository(const std::string& folderPath);

std::string getCurrentGitBranch(const std::string& folderPath);