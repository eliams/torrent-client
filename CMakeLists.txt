cmake_minimum_required(VERSION 3.10)

project(torrent-client
        DESCRIPTION "A light cli bittorrent client"
        HOMEPAGE_URL https://github.com/eliams/torrent-client
        LANGUAGES CXX
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_executable(torrent-client
    src/main.cpp
)

target_include_directories(torrent-client
    PUBLIC
        include
)
