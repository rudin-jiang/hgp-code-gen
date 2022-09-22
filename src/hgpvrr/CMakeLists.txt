add_executable(
    hgpvrr_code_gen
    hgpvrr_code_gen.cpp
)

target_link_libraries(
    hgpvrr_code_gen PRIVATE
    hgplib
)


add_executable(
    hgpvrr_path_gen_random
    hgpvrr_path_gen_random.cpp
)

target_link_libraries(
    hgpvrr_path_gen_random PRIVATE
    hgplib
)