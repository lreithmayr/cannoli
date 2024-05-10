#include "ray_tracer.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>
#include <chrono>
#include <ratio>
#include <fmt/chrono.h>

int main() {
  // Camera parameters
  constexpr float ASPECT_RATIO = 3.0 / 2.0;
  constexpr float FOCAL_LENGTH = 1.0;
  constexpr float VFOV = 30.0;

  // Canvas parameters
  constexpr int CANVAS_WIDTH = 800;

  // Ray tracer parameters
  constexpr int SAMPLES = 30;
  constexpr int MAX_BOUNCES = 4;

  // Scene parameters
  std::string scene_name = "blocks.obj";
  std::string scene_path = fmt::format("../models/{}", scene_name);
  std::string out_path = fmt::format("../images/cannoli_output_{}_samples-{}_maxBounces-{}.ppm", scene_name, SAMPLES, MAX_BOUNCES);

  // Initialize the camera
  cannoli::Camera camera;
  camera.setAspectRatio(ASPECT_RATIO);
  camera.setFocalLength(FOCAL_LENGTH);
  camera.setVerticalFOV(VFOV);
  camera.setOrigin(cannoli::PointXYZ(20, 10, 10));
  camera.setViewDirection(cannoli::PointXYZ(0, 3, 0));
  camera.setUp(cannoli::Vec3f(0, 1, 0));
  camera.initialize();

  // Initialize the canvas
  cannoli::Canvas canvas;
  canvas.setAspectRation(ASPECT_RATIO);
  canvas.setWidth(CANVAS_WIDTH);
  canvas.initialize();

  // Construct the scene
  cannoli::Scene scene;
  scene.load(scene_path);

  // Initialize the ray tracer
  cannoli::RayTracer rt;
  rt.loadScene(scene);
  rt.setCamera(camera);
  rt.setCanvas(canvas);
  rt.setOutputPath(out_path);
  rt.setSamples(SAMPLES);
  rt.setMaxBounces(MAX_BOUNCES);

  const auto start = std::chrono::steady_clock::now();
  rt.trace();
  const auto end = std::chrono::steady_clock::now();
  auto dur = std::chrono::duration<double>(end - start);
  fmt::print("Time taken: {} seconds", dur.count());
}