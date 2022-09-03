#include "ray_tracer.h"
#include "object.h"
#include "sphere.h"
#include "material.h"
#include "lambertian_brdf.h"

#include <iostream>

#define ASPECT_RATIO 16.0/9.0
#define CANVAS_WIDTH 400
#define VIEWPORT_HEIGHT 2.0
#define FOCAL_LENGTH 1.0

int main() {
  std::string out_path = "../images/lambertian_refactored.ppm";

  // Create a camera and a canvas on which to render the scene
  cannoli::Camera camera(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH);
  cannoli::Canvas canvas(ASPECT_RATIO, CANVAS_WIDTH);

  // Create Materials

  cannoli::LambertianBRDF lambertian;

  // Create some object(s)
  cannoli::Sphere sphere(cannoli::Vec3f(0, 0, -1), 0.5, &lambertian);
  cannoli::Sphere sphere2(cannoli::Vec3f(0, -100.5, -1), 100, &lambertian);


  //Create a scene and add the object(s)
  cannoli::Scene scene;
  scene.Add(&sphere);
  scene.Add(&sphere2);

  // Pass the scene, camera and canvas to the ray tracer and trace away
  cannoli::RayTracer rt(scene, camera, canvas, out_path);
  rt.Trace();
}
