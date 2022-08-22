cmake_minimum_required(VERSION 3.23)
project(cannoli)

set(CMAKE_CXX_STANDARD 20)

# === PROJECT SETUP ===

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} SHARED
        src/light_ray.cpp
)

# === GOOGLETEST SETUP ===

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# === TEST ===
add_executable(vec3_test ${PROJECT_SOURCE_DIR}/test/vec3f_test.cpp)
target_link_libraries(vec3_test gtest_main)
add_test(NAME Vec3Test COMMAND vec3test)

# === RUN ===
add_executable(cannoli_main ${PROJECT_SOURCE_DIR}/src/cannoli_main.cpp)
target_link_libraries(
        cannoli_main ${PROJECT_NAME}
)
