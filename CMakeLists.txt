cmake_minimum_required(VERSION 3.12)
project(aa_labs VERSION 1.0.0)

option(BUILD_LAB "Build a specific lab (e.g., lab_01, lab_02, lab_03)" "")

# Check if the BUILD_LAB option is specified
if(BUILD_LAB)
    # Check which lab is specified and add the corresponding subdirectory
    if(${BUILD_LAB} STREQUAL "1")
        add_subdirectory(lab_01)
    elseif(${BUILD_LAB} STREQUAL "2")
        add_subdirectory(lab_02)
    elseif(${BUILD_LAB} STREQUAL "3")
        add_subdirectory(lab_03)
    else()
        message(FATAL_ERROR "Invalid lab name specified. Please use one of: 1.")
    endif()

else()
    message(FATAL_ERROR "Please specify a lab to build using -DBUILD_LAB=<lab_name> option.")
endif()
