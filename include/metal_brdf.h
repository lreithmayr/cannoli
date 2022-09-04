#ifndef CANNOLI_SRC_METAL_BRDF_H_
#define CANNOLI_SRC_METAL_BRDF_H_

#include "material.h"

namespace cannoli {
  class MetalBRDF : public Material {
   public:
	MetalBRDF() = default;

   private:
	float m_metalReflectance;
  };

} // namespace cannoli

#endif //CANNOLI_SRC_METAL_BRDF_H_
