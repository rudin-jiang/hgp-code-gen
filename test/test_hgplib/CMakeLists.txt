add_executable(
    test_ijk
    test_ijk.cpp
)

target_link_libraries(
    test_ijk PRIVATE
    hgplib
    gtest
    gtest_main
)