== Triangles ==

* Defined by three vertices (i.e. edge points) (0, 1, 2) numbered CCW
* Each vertex defined by (x, y, z) coordinates ==> A single triangle is represented as an array of three (x, y, z)
  coordinates
    * Using floats (sizeof(float) = 4 bytes): 36 bytes

== Triangle Mesh ==

* Collection of triangles to approximate surface of an object (volumen representation not important for opaque objects)
    * Piecewise planar approximation of a surface
* Indexed Triangle Set:
    * Float array containing the position of all vertices of the mesh
    * For each triangle: Array containing three indices into the vertex array describing the triangle's three vertices
* Each triangle contains a pointer to its first vertex in the mesh
    * tri_i = (vert[3*i], vert[3 * i + 1], vert[3 * i + 2])

== Class: TriangleMesh ==

Data:

* std::array<float, num_verts> verts: Float array containing all vertices of the mesh
*  

