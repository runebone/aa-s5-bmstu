cmake_minimum_required(VERSION 3.12)

project(aa_lab_03)

set(LIBS_DIR /nix/var/nix/profiles/per-user/human/profile/lib)
set(INCS_DIR /nix/var/nix/profiles/per-user/human/profile/include)

include_directories(
    ${INCS_DIR}
    /home/human/Code/include/googletest/googletest/include
    /home/human/Code/include/googletest/googlemock/include
    )

link_directories(
    ${LIBS_DIR}
    )

add_executable(lab_03
    main.cpp
    sort_bitonic.cpp
    sort_bubble.cpp
    sort_radix.cpp
    dbg.cpp
    )

# add_executable(lab_03_test
#     test.cpp
#     )

# target_link_libraries(lab_03_test gtest gtest_main)
