cmake_minimum_required(VERSION 3.23)
project(cannoli)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === TEST ===
add_executable(vec3_test ${PROJECT_SOURCE_DIR}/test/vec3_test.cpp)
target_link_libraries(vec3_test gtest_main)
add_test(NAME example_test COMMAND example)

# === RUN ===
add_executable(cannoli ${PROJECT_SOURCE_DIR}/src/cannoli.cpp)
