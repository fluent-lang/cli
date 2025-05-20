include(FetchContent)
cmake_minimum_required(VERSION 3.30)
project(cli)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG        main
)

FetchContent_Declare(
        fluent_libc
        GIT_REPOSITORY https://github.com/rodrigoo-r/fluent_libc
        GIT_TAG        master
)

FetchContent_MakeAvailable(unordered_dense)
FetchContent_MakeAvailable(fluent_libc)
set(CMAKE_CXX_STANDARD 20)

add_library(cli STATIC
        library.cpp
        include/fluent/cli/argv_impl.h
        include/fluent/cli/flag/flag_type.h
        include/fluent/cli/flag/flag.h
        include/fluent/cli/algorithm/padding/padding.h
        include/fluent/cli/algorithm/help_generator/help_generator.h
)
target_include_directories(cli PRIVATE ${CMAKE_BINARY_DIR}/_deps/unordered_dense-src/include)
target_include_directories(cli PRIVATE ${CMAKE_BINARY_DIR}/_deps/fluent_libc-src/include)
target_link_libraries(cli PRIVATE unordered_dense)
target_link_libraries(cli PRIVATE fluent_libc)
