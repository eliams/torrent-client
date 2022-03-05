cmake_minimum_required(VERSION 3.10)

project(torrent-client
        DESCRIPTION "A light cli bittorrent client"
        HOMEPAGE_URL https://github.com/eliams/torrent-client
        LANGUAGES CXX
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

add_executable(torrent-client
    src/main.cpp
)

target_include_directories(torrent-client
    PRIVATE
        include
)

target_link_libraries(torrent-client
    PRIVATE
        bencode_parser
)

add_subdirectory(bencode_parser)
