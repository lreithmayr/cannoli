#include "ray_tracer.h"
#include "lambertian_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>

// Camera parameters
constexpr float ASPECT_RATIO = 3.0 / 2.0;
constexpr float FOCAL_LENGTH = 1.0;
constexpr float VFOV = 50.0;

// Canvas parameters
constexpr int CANVAS_WIDTH = 800;

// Ray tracer parameters
constexpr int SAMPLES = 32;
constexpr int MAX_BOUNCES = 8;

int main() {
  std::string obj_path = "../scenes/cube.obj";
  // std::string obj_path = "../scenes/simple_scene.obj";
  std::string out_path = "../images/cannoli_output.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(0, -1, 2),
						 cannoli::PointXYZ(2.5, 1, -1.5),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  // Create mesh material
  cannoli::ColorRGB color(1, 0.8, 0.8);
  auto mesh_material = std::make_shared<cannoli::LambertianBRDF>(color);

  // Load the mesh from the .obj file
  auto mesh = std::make_shared<cannoli::Mesh>(obj_path, mesh_material);

  cannoli::Scene scene;
  scene.Add(mesh);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}

