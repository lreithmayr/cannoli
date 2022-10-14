#include "ray_tracer.h"

#include <iostream>
#include <cmath>
#include <memory>

// Camera parameters
constexpr float ASPECT_RATIO = 3.0 / 2.0;
constexpr float FOCAL_LENGTH = 1.0;
constexpr float VFOV = 20.0;

// Canvas parameters
constexpr int CANVAS_WIDTH = 800;

// Ray tracer parameters
constexpr int SAMPLES = 32;
constexpr int MAX_BOUNCES = 8;

int main() {
  std::string obj_path = "../scenes/cube.obj";
  std::string out_path = "../images/this_will_not_work.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(13.0, 2.0, 3),
						 cannoli::PointXYZ(0, 0, 0),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  // Load the mesh from the .obj file
  auto mesh = std::make_shared<cannoli::Mesh>(obj_path);

  // for (int j = 0; j < mesh->GetIndices().size(); j += 3) {
  // 	std::cout << "T" << j / 3 << ": " << mesh->GetIndices()[j] << ", " << mesh->GetIndices()[j + 1] << ", "
  // 			  << mesh->GetIndices()[j + 2] << "\n";
  // }

  cannoli::Scene scene;
  scene.Add(mesh);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}
