#ifndef CANNOLI_SRC_BVH_H_
#define CANNOLI_SRC_BVH_H_

#include "aabb.h"

namespace cannoli {
class BVHNode {
 public:
  BVHNode(AABB &boundingBox, std::vector<int> &triangles);

 protected:
  AABB m_boundingBox;
  BVHNode *m_childA{nullptr};
  BVHNode *m_childB{nullptr};
  std::vector<int> m_associatedTriangleIndices;
};

class BVH {
 public:
  BVH() = default;

 protected:
  std::vector<BVHNode> m_nodes;
};
} // namespace cannoli
#endif //CANNOLI_SRC_BVH_H_

