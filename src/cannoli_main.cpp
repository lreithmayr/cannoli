#include "ray_tracer.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>

// Camera parameters
constexpr float ASPECT_RATIO = 3.0 / 2.0;
constexpr float FOCAL_LENGTH = 1.0;
constexpr float VFOV = 60.0;

// Canvas parameters
constexpr int CANVAS_WIDTH = 800;

// Ray tracer parameters
constexpr int SAMPLES = 32;
constexpr int MAX_BOUNCES = 8;

cannoli::Scene LoadScene(std::string &fpath) {
  cannoli::Scene scene;

  // Load all meshes from the .obj file
  objl::Loader loader;
  bool loadout = loader.LoadFile(fpath);
  if (loadout) {
	cannoli::LOG("Mesh loaded successfully.");
  } else {
	cannoli::ERROR("Failed to load mesh!");
  }

  for (auto &msh : loader.LoadedMeshes) {
	float rand = cannoli::random_float(0.1, 1.0);
	auto random_color = cannoli::ColorRGB::random(0.2, 0.9);

	if ( rand > 0.5) {
	  std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::LambertianBRDF>(random_color);
	  cannoli::Mesh mesh(msh, mat);
	  scene.Add(std::make_shared<cannoli::Mesh>(mesh));
	} else {
	  std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::MetalBRDF>(random_color, 0.1);
	  cannoli::Mesh mesh(msh, mat);
	  scene.Add(std::make_shared<cannoli::Mesh>(mesh));
	}
  }
  return scene;
}

int main() {
  // std::string obj_path = "../scenes/cube.obj";
  std::string obj_fpath = "../scenes/simple_scene.obj";
  std::string out_path = "../images/triIndex_output.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(10, 5, 20),
						 cannoli::PointXYZ(0, -1, 0),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  cannoli::Scene scene = LoadScene(obj_fpath);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}