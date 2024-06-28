#include "bvh.h"

cannoli::BVHNode::BVHNode(cannoli::AABB &boundingBox, std::vector<int> &triangles) :
  m_boundingBox(boundingBox), m_associatedTriangleIndices(triangles) {}
