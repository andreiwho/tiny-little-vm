cmake_minimum_required(VERSION 3.10)

include(conan/conanbuildinfo.cmake)
project(tlvm) 
    conan_basic_setup()

    file(GLOB_RECURSE tlvm_sources src/*.* LIST_DIRECTORIES True)
    add_executable(tlvm ${tlvm_sources})

    target_link_libraries(
        tlvm
            PUBLIC
        ${CONAN_LIBS}
    )

    target_compile_features(
        tlvm
            PUBLIC
        cxx_std_20
    )