cmake_minimum_required(VERSION 3.10)

project(torrent-client
        DESCRIPTION "A light cli bittorrent client"
        HOMEPAGE_URL https://github.com/eliams/torrent-client
        LANGUAGES CXX
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

add_executable(torrent-client
    include/bencode_parser.h
    src/bencode_parser.cpp
    src/main.cpp
)

target_include_directories(torrent-client
    PRIVATE
        include
)
