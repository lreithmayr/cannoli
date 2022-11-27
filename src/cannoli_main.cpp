#include "ray_tracer.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>

cannoli::Scene LoadScene(std::string &fpath) {
  cannoli::Scene scene;

  // Load all meshes from the .obj file
  objl::Loader loader;
  bool loadout = loader.LoadFile(fpath);
  if (loadout) {
	for (auto &msh : loader.LoadedMeshes) {
	  float rand = cannoli::random_float(0.1, 1.0);
	  auto random_color = cannoli::ColorRGB::random(0.2, 0.9);
	  auto random_fuzz = cannoli::random_float(0.2, 0.9);

	  if (rand > 0.5) {
		std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::LambertianBRDF>(random_color);
		cannoli::Mesh mesh(msh, mat);
		scene.Add(std::make_shared<cannoli::Mesh>(mesh));
	  } else {
		std::shared_ptr<cannoli::Material> mat = std::make_shared<cannoli::MetalBRDF>(random_color, random_fuzz);
		cannoli::Mesh mesh(msh, mat);
		scene.Add(std::make_shared<cannoli::Mesh>(mesh));
	  }

	  fmt::print(" Random Color: {} \n", random_color);
	  fmt::print(" Random Fuzz: {} \n", random_fuzz);
	}

  } else {
	fmt::print(stderr, "Failed to load mesh!\n");
  }
  return scene;
}

// Camera parameters
constexpr float ASPECT_RATIO = 3.0 / 2.0;
constexpr float FOCAL_LENGTH = 1.0;
constexpr float VFOV = 30.0;

// Canvas parameters
constexpr int CANVAS_WIDTH = 800;

// Ray tracer parameters
constexpr int SAMPLES = 300;
constexpr int MAX_BOUNCES = 8;

int main() {
  std::string obj_fpath = "../models/blocks.obj";

#if AABB_INT
 //   std::string out_path = "../images/triIndex_output_bbox.ppm";
	std::string out_path = fmt::format("../images/cannoli_output_samples-{}_maxBounces-{}.ppm", SAMPLES, MAX_BOUNCES);
#else
  std::string out_path = "../images/triIndex_output.ppm";
#endif

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(20, 10, 10),
						 cannoli::PointXYZ(0, 3, 0),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  cannoli::Scene scene = LoadScene(obj_fpath);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}