cmake_minimum_required(VERSION 3.12)

project(aa_lab_01)

set(LIBS_DIR /nix/var/nix/profiles/per-user/human/profile/lib)
set(INCS_DIR /nix/var/nix/profiles/per-user/human/profile/include)

include_directories(
    ${INCS_DIR}
    /home/human/Code/googletest/googletest/include
    /home/human/Code/googletest/googlemock/include
    )

link_directories(
    ${LIBS_DIR}
    )

add_executable(lab_01
    # old/main.cpp
    # old/errors.cpp
    # old/menu.cpp
    # old/algorithm.cpp
    main.cpp
    func.cpp
    test.cpp
)

target_link_libraries(lab_01 gtest gtest_main)
