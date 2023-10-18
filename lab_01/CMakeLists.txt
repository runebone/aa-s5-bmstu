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
    main.cpp
    func.cpp
    benchmark.cpp
    )

add_executable(lab_01_test
    test.cpp
    func.cpp
    )

target_link_libraries(lab_01_test gtest gtest_main)
