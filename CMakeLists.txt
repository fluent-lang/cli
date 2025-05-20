include(FetchContent)
cmake_minimum_required(VERSION 3.30)
project(cli)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG        main
)

FetchContent_MakeAvailable(unordered_dense)
set(CMAKE_CXX_STANDARD 20)

add_library(cli STATIC
        library.cpp
        include/fluent/cli/argv_impl.h
        include/fluent/cli/flag/flag_type.h
        include/fluent/cli/flag/flag.h
)
target_include_directories(cli PRIVATE ${CMAKE_BINARY_DIR}/_deps/unordered_dense-src/include)
target_link_libraries(cli PRIVATE unordered_dense)
