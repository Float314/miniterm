# command -  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_C_COMPILER=clang-cl -DCMAKE_TOOLCHAIN_FILE="G:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake_minimum_required(VERSION 3.15) 

project(miniterm)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(libgit2 CONFIG REQUIRED)

set(SOURCES 
    src/main.cpp
    src/file_operations.cpp
    src/download.cpp
    src/nescoffee.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenSSL::SSL
    OpenSSL::Crypto
    CURL::libcurl
    libgit2::libgit2package
)