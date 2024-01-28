cmake_minimum_required(VERSION 3.12)

project(aa_lab_04)

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

add_executable(lab_04
    main.cpp
    utils.cpp
    )

# add_executable(lab_04_test
#     test.cpp
#     )

# target_link_libraries(lab_04_test gtest gtest_main)
