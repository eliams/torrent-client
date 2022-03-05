add_library(bencode_parser STATIC
    include/bencode_parser.h
    src/bencode_parser.cpp
)

target_include_directories(bencode_parser
    PUBLIC 
        include
)
