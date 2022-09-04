#include "ray_tracer.h"
#include "object.h"
#include "sphere.h"
#include "lambertian_brdf.h"
#include "metal_brdf.h"

#include <iostream>

#define ASPECT_RATIO 16.0/9.0
#define CANVAS_WIDTH 400
#define VIEWPORT_HEIGHT 2.0
#define FOCAL_LENGTH 1.0

int main() {
  std::string out_path = "../images/scene_1.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH);
  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  // Create Materials

  cannoli::LambertianBRDF lambertian;
  cannoli::MetalBRDF metal1(cannoli::ColorRGB(0.8, 0.8, 0.8));
  cannoli::MetalBRDF metal2(cannoli::ColorRGB(0.8, 0.6, 0.2));

  // Create some object(s)
  cannoli::Sphere sphere_ground(cannoli::Vec3f(0, -100.5, -1), 100, &lambertian);
  cannoli::Sphere sphere1(cannoli::Vec3f(0.0, 0.0, -1.0), 0.5, &lambertian);
  cannoli::Sphere sphere2(cannoli::Vec3f(-1.0, 0.0, -1.0), 0.5, &metal1);
  cannoli::Sphere sphere3(cannoli::Vec3f(1.0, 0.0, -1.0), 0.5, &metal2);

  sphere_ground.SetBaseColor(cannoli::ColorRGB(0.8, 0.8, 0.0));
  sphere1.SetBaseColor(cannoli::ColorRGB(0.7, 0.3, 0.3));

  //Create a scene and add the object(s)
  cannoli::Scene scene;
  scene.Add(&sphere1);
  scene.Add(&sphere2);
  scene.Add(&sphere3);
  scene.Add(&sphere_ground);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path);
  rt.Trace();
}
