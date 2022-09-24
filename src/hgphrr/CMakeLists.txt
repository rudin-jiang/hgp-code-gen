add_executable(
    hgphrr_path_gen_random
    hgphrr_path_gen_random.cpp
)

target_link_libraries(
    hgphrr_path_gen_random PRIVATE
    hgplib
)

add_executable(
    hgphrr_code_gen
    hgphrr_code_gen.cpp
)

target_link_libraries(
    hgphrr_code_gen PUBLIC
    hgplib
)