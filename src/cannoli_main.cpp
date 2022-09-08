#include "ray_tracer.h"
#include "object.h"
#include "sphere.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>

// Camera parameters
#define ASPECT_RATIO 16.0/9.0
#define FOCAL_LENGTH 1.0
#define VFOV 90.0

// Canvas parameters
#define CANVAS_WIDTH 400

// Ray tracer parameters
#define SAMPLES 50
#define MAX_BOUNCES 6

// TODO: Refactor this into a JSON or TOML config file.
cannoli::Scene CreateRandomScene() {
  cannoli::Scene scene;

  // Create Materials

  std::shared_ptr<cannoli::Material> lambertian = std::make_shared<cannoli::LambertianBRDF>();
  std::shared_ptr<cannoli::Material>
	  metal1 = std::make_shared<cannoli::MetalBRDF>(cannoli::ColorRGB(0.8, 0.8, 0.8), 0.3);
  std::shared_ptr<cannoli::Material>
	  metal2 = std::make_shared<cannoli::MetalBRDF>(cannoli::ColorRGB(0.8, 0.6, 0.2), 1.0);

  // Create some object(s)
  std::shared_ptr<cannoli::Object>
	  sphere_ground = std::make_shared<cannoli::Sphere>(cannoli::Vec3f(0, -100.5, -1), 100, lambertian);
  std::shared_ptr<cannoli::Object>
	  sphere1 = std::make_shared<cannoli::Sphere>(cannoli::Vec3f(0.0, 0.0, -1.0), 0.5, lambertian);
  std::shared_ptr<cannoli::Object>
	  sphere2 = std::make_shared<cannoli::Sphere>(cannoli::Vec3f(-1.0, 0.0, -1.0), 0.5, metal1);
  std::shared_ptr<cannoli::Object>
	  sphere3 = std::make_shared<cannoli::Sphere>(cannoli::Vec3f(1.0, 0.0, -1.0), 0.5, metal2);

  sphere_ground->SetBaseColor(cannoli::ColorRGB(0.8, 0.8, 0.0));
  sphere1->SetBaseColor(cannoli::ColorRGB(0.7, 0.3, 0.3));

  //Create a scene and add the object(s)
  scene.Add(sphere1);
  scene.Add(sphere2);
  scene.Add(sphere3);
  scene.Add(sphere_ground);

  return scene;
}

int main() {
  std::string out_path = "../images/scene_fuzz.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(-1.0, 2.0, 1),
						 cannoli::PointXYZ(0, 0, -1.0),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  cannoli::Scene scene = CreateRandomScene();
  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}
