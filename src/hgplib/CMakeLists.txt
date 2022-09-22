add_library(
    hgplib
    ijk.cpp
    pair.cpp
    gen_utility.cpp
)

target_include_directories(
    hgplib PUBLIC
    .
)

