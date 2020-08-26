cmake_minimum_required(VERSION 3.12)

add_executable(Result_Test
    main.cpp

    result/result.cpp
    result/policy/monad.cpp
)

target_include_directories(Result_Test PRIVATE
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(Result_Test PRIVATE cxx_std_17)

target_compile_options(Result_Test
                       PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
                       $<$<CXX_COMPILER_ID:MSVC>:/W4>
                       $<$<CXX_COMPILER_ID:MSVC>:/WX>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Werror>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>)
