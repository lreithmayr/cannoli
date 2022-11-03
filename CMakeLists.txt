cmake_minimum_required(VERSION 3.23)

project(cannoli)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native -fconcepts -pthread -DPBR_INTERSECTION")
# === PROJECT SETUP ===

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${EIGEN3_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} SHARED
        # Source Files
        src/ray_tracer.cpp
        src/sphere.cpp
        src/lambertian_brdf.cpp
        src/metal_brdf.cpp
        src/mesh.cpp

        # Header Files
        include/utils.h
        include/canvas.h
        include/camera.h
        include/color.h
        include/light_ray.h
        include/point.h
        include/ray_tracer.h
        include/vec3f.h
        include/object.h
        include/scene.h
        include/material.h
        include/sphere.h
        include/object_type.h
        include/hit_record.h
        include/lambertian_brdf.h
        include/metal_brdf.h
        include/mesh.h
        include/obj_file_loader.h
        )

# === DEPENDENCIES ===

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

#list(APPEND CMAKE_INCLUDE_PATH "/usr/local/include")
FIND_PACKAGE(
Eigen3 3.4 REQUIRED NO_MODULE
)

FIND_PACKAGE(
        Threads REQUIRED
)

# === TEST ===
add_executable(vec3_test ${PROJECT_SOURCE_DIR}/test/vec3f_test.cpp)
target_link_libraries(vec3_test gtest_main pthread)
add_test(NAME Vec3Test COMMAND vec3test)

# === RUN ===
add_executable(cannoli_main ${PROJECT_SOURCE_DIR}/src/cannoli_main.cpp)
target_link_libraries(
        cannoli_main ${PROJECT_NAME} Eigen3::Eigen
)
