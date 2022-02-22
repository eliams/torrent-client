cmake_minimum_required(VERSION 3.10)

project(torrent-client)

add_executable(torrent-client
    src/main.cc
)

target_include_directories(torrent-client
    PUBLIC
        include
)
