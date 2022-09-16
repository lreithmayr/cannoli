#include "ray_tracer.h"
#include "object.h"
#include "sphere.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>
#include <cmath>
#include <memory>

// Camera parameters
#define ASPECT_RATIO 3.0/2.0
#define FOCAL_LENGTH 1.0
#define VFOV 20.0

// Canvas parameters
#define CANVAS_WIDTH 1200

// Ray tracer parameters
#define SAMPLES 500
#define MAX_BOUNCES 50

// Scene options
#define SCENE_OBJECT_RANGE 11

using namespace cannoli;

cannoli::Scene CreateRandomScene() {
  cannoli::Scene scene;

  // Create Materials

  std::shared_ptr<Material> ground = std::make_shared<LambertianBRDF>();
  std::shared_ptr<Object> sphere_ground = std::make_shared<Sphere>(Vec3f(0, -1000, -1), 1000, ground);
  sphere_ground->SetBaseColor(ColorRGB(0.5, 0.5, 0.5));
  scene.Add(sphere_ground);

  std::shared_ptr<Material> material1 = std::make_shared<LambertianBRDF>();
  std::shared_ptr<Object> s1 = std::make_shared<Sphere>(Vec3f(-4, 1, 0), 1.0, material1);
  s1->SetBaseColor(ColorRGB(0.4, 0.2, 0.1));
  scene.Add(s1);

  std::shared_ptr<Material> material2 = std::make_shared<MetalBRDF>(ColorRGB(0.8, 0.6, 0.5), 0.4);
  std::shared_ptr<Object> s2 = std::make_shared<Sphere>(Vec3f(0, 1, 0), 1.0, material2);
  scene.Add(s2);

  std::shared_ptr<Material> material3 = std::make_shared<MetalBRDF>(ColorRGB(0.7, 0.6, 0.5), 0.0);
  std::shared_ptr<Object> s3 = std::make_shared<Sphere>(Vec3f(4, 1, 0), 1.0, material3);
  scene.Add(s3);

  for (int a = -(SCENE_OBJECT_RANGE); a < SCENE_OBJECT_RANGE; a++) {
	for (int b = -(SCENE_OBJECT_RANGE); b < SCENE_OBJECT_RANGE; b++) {
	  float choose_mat = random_float();
	  PointXYZ center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

	  if ((center - PointXYZ(4, 0.2, 0)).length() > 0.9) {
		std::shared_ptr<Material> sphere_material;

		if (choose_mat < 0.8) {
		  // Diffuse
		  auto albedo = ColorRGB::random(0.5, 1);
		  sphere_material = std::make_shared<LambertianBRDF>(albedo);
		  scene.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
		} else if (choose_mat < 0.95) {
		  // Metal
		  auto albedo = ColorRGB::random(0.5, 1);
		  auto fuzz = 0;
		  sphere_material = std::make_shared<MetalBRDF>(albedo, fuzz);
		  scene.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
		} else {
		  // Fuzzed Metal
		  auto albedo = ColorRGB::random(0.5, 1);
		  auto fuzz = random_float(0, 0.5);
		  sphere_material = std::make_shared<MetalBRDF>(albedo, fuzz);
		  scene.Add(make_shared<Sphere>(center, 0.2, sphere_material));
		}
	  }
	}
  }
  return scene;
}

int main() {
  std::string out_path = "../images/fullScene_RTIOW.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO,
						 FOCAL_LENGTH,
						 VFOV,
						 cannoli::PointXYZ(13.0, 2.0, 3),
						 cannoli::PointXYZ(0, 0, 0),
						 cannoli::Vec3f(0, 1, 0));

  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  cannoli::Scene scene = CreateRandomScene();

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path, SAMPLES, MAX_BOUNCES);
  rt.Trace();
}
