#ifndef PRIMITIVEGEOMETRY_HPP
#define PRIMITIVEGEOMETRY_HPP

#include <Texture.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>

// Purpose of this class is to store vertice and triangle information
class PrimitiveGeometry {
public:
	// Constructor
	PrimitiveGeometry();
	// Destructor
	~PrimitiveGeometry();

	// Functions for working with individual vertices
	unsigned int GetBufferSizeInBytes();
	// Retrieve the 
	unsigned int GetBufferDataSize();
	// Retrieve the Buffer Data Size
	float* GetBufferDataPtr();
	// Add a new vertex 
	void AddVertex(float x, float y, float z, float s, float t);
	// gen pushes all attributes into a single vector
	void Gen();
	// Functions for working with Indices
	// Creates a triangle from 3 indicies
	// When a triangle is made, the tangents and bi-tangents are also
	// computed
	void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);
	// Retrieve how many indicies there are
	unsigned int GetIndicesSize();
	//return the indices
	std::vector<unsigned int> GetIndices();
	// Retrieve the pointer to the indices
	unsigned int* GetIndicesDataPtr();

private:
	// m_bufferData stores all of the vertexPositons, coordinates, normals, etc.
	// This is all of the information that should be sent to the vertex Buffer Object
	std::vector<float> m_bufferData;

	// Individual components of 
	std::vector<float> m_vertexPositions;
	std::vector<float> m_textureCoords;
	std::vector<float> m_normals;
	std::vector<float> m_tangents;
	std::vector<float> m_biTangents;

	// The indices for a indexed-triangle mesh
	std::vector<unsigned int> m_indices;
};





#endif