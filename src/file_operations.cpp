#include <filesystem>
#include <iostream>

int copyfile(const std::string& source, const std::string& destination) {
    try {
        std::filesystem::copy(source, destination, std::filesystem::copy_options::overwrite_existing);
        return 0; // Success
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
        return 1; // Failure
    }
}

int deletefile(const std::string& path) {
    try {
        if (std::filesystem::remove(path)) {
            return 0; // Success
        } else {
            std::cerr << "File not found: " << path << std::endl;
            return 1; // File not found
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
        return 1; // Failure
    }
}

int movefile(const std::string& source, const std::string& destination) {
    try {
        std::filesystem::rename(source, destination);
        return 0; // Success
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
        return 1; // Failure
    }
}

int deleteDir(const std::string dir) { 
    try { 
        std::filesystem::remove_all(dir); 
        return 0; // Success
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting directory: " << e.what() << std::endl;
        return 1; // Failure
    }
}

int createDir(const std::string dir) { 
    try { 
        std::filesystem::create_directory(dir); 
        return 0; // Success
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return 1; // Failure
    }
}

std::string getCurrentDir() { 
    try { 
        return std::filesystem::current_path().string(); 
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting current directory: " << e.what() << std::endl;
        return ""; // Failure
    }
}

#include <git2.h>
#include <string>

bool isGitRepository(const std::string& folderPath) {
    // Flag to ensure libgit2 is initialized (must be called at least once in your program)
    git_libgit2_init();

    git_repository* repo = nullptr;
    
    // GIT_REPOSITORY_OPEN_NO_SEARCH ensures it only checks the specified folder
    // and doesn't walk up to parent directories.
    int error = git_repository_open_ext(
        &repo, 
        folderPath.c_str(), 
        GIT_REPOSITORY_OPEN_NO_SEARCH, 
        nullptr
    );

    // If a repo was successfully found/opened, clean up its memory
    if (repo != nullptr) {
        git_repository_free(repo);
    }

    // git_libgit2_shutdown(); // Call this when your overall program exits

    // If error code is 0, it is a valid git repository
    return (error == 0);
}

std::string getCurrentGitBranch(const std::string& folderPath) {
    // Ensure libgit2 is initialized
    git_libgit2_init();

    git_repository* repo = nullptr;
    git_reference* headRef = nullptr;
    std::string branchName = "";

    // 1. Attempt to open the repository (don't search parent directories)
    int error = git_repository_open_ext(&repo, folderPath.c_str(), GIT_REPOSITORY_OPEN_NO_SEARCH, nullptr);
    if (error != 0) {
        // Not a git repository (or couldn't be opened)
        return "";
    }

    // 2. Get the HEAD reference
    error = git_repository_head(&headRef, repo);
    if (error == 0) {
        // 3. Check if HEAD points to a valid branch (symbolic reference)
        if (git_reference_is_branch(headRef)) {
            // git_reference_shorthand converts "refs/heads/main" to just "main"
            const char* shortName = git_reference_shorthand(headRef);
            if (shortName != nullptr) {
                branchName = shortName;
            }
        }
    }

    // Cleanup resources to prevent memory leaks
    if (headRef != nullptr) {
        git_reference_free(headRef);
    }
    if (repo != nullptr) {
        git_repository_free(repo);
    }

    return branchName;
}