#include "PrimitiveGeometry.h"

PrimitiveGeometry::PrimitiveGeometry()
{
}

PrimitiveGeometry::~PrimitiveGeometry()
{
}


void PrimitiveGeometry::Gen()
{
	assert((m_vertexPositions.size() / 3) == (m_textureCoords.size() / 2));

	int coordsPos = 0;
	for (int i = 0; i < m_vertexPositions.size() / 3; ++i) {
		// First vertex
			// vertices
		m_bufferData.push_back(m_vertexPositions[i * 3 + 0]);
		m_bufferData.push_back(m_vertexPositions[i * 3 + 1]);
		m_bufferData.push_back(m_vertexPositions[i * 3 + 2]);
		// m_normals
		m_bufferData.push_back(m_normals[i * 3 + 0]);
		m_bufferData.push_back(m_normals[i * 3 + 1]);
		m_bufferData.push_back(m_normals[i * 3 + 2]);
		// texture information
		m_bufferData.push_back(m_textureCoords[coordsPos * 2 + 0]);
		m_bufferData.push_back(m_textureCoords[coordsPos * 2 + 1]);
		++coordsPos;
		// tangents
		m_bufferData.push_back(m_tangents[i * 3 + 0]);
		m_bufferData.push_back(m_tangents[i * 3 + 1]);
		m_bufferData.push_back(m_tangents[i * 3 + 2]);
		// bi-tangents
		m_bufferData.push_back(m_biTangents[i * 3 + 0]);
		m_bufferData.push_back(m_biTangents[i * 3 + 1]);
		m_bufferData.push_back(m_biTangents[i * 3 + 2]);
	}
}

void PrimitiveGeometry::MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2)
{
	//vertices
	m_indices.push_back(vert0);
	m_indices.push_back(vert1);
	m_indices.push_back(vert2);

	// Look up the actual vertex positions
	glm::vec3 pos0(m_vertexPositions[vert0 * 3 + 0], m_vertexPositions[vert0 * 3 + 1], m_vertexPositions[vert0 * 3 + 2]);
	glm::vec3 pos1(m_vertexPositions[vert1 * 3 + 0], m_vertexPositions[vert1 * 3 + 1], m_vertexPositions[vert1 * 3 + 2]);
	glm::vec3 pos2(m_vertexPositions[vert2 * 3 + 0], m_vertexPositions[vert2 * 3 + 1], m_vertexPositions[vert2 * 3 + 2]);

	// Look up the texture coordinates
	glm::vec2 tex0(m_textureCoords[vert0 * 2 + 0], m_textureCoords[vert0 * 2 + 1]);
	glm::vec2 tex1(m_textureCoords[vert1 * 2 + 0], m_textureCoords[vert1 * 2 + 1]);
	glm::vec2 tex2(m_textureCoords[vert2 * 2 + 0], m_textureCoords[vert2 * 2 + 1]);

	// Now create an edge with two edges
	// This section is inspired by: https://learnopengl.com/Advanced-Lighting/Normal-Mapping
	glm::vec3 edge0 = pos1 - pos0;
	glm::vec3 edge1 = pos2 - pos0;

	// The difference of y's and x's
	glm::vec2 deltaUV0 = tex1 - tex0;
	glm::vec2 deltaUV1 = tex2 - tex0;

	float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

	glm::vec3 tangent;
	glm::vec3 bitangent;

	tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
	tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
	tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
	bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
	bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);
	bitangent = glm::normalize(bitangent);

	// Compute a normal
	// For now we sort of 'cheat' since this is a quad the 'z' axis points straight out
	glm::vec3 normal1{ m_normals[vert0 * 3 + 0] ,m_normals[vert0 * 3 + 1], m_normals[vert0 * 3 + 2] };
	glm::vec3 normal2{ m_normals[vert1 * 3 + 0] ,m_normals[vert1 * 3 + 1], m_normals[vert1 * 3 + 2] };
	glm::vec3 normal3{ m_normals[vert2 * 3 + 0] ,m_normals[vert2 * 3 + 1], m_normals[vert2 * 3 + 2] };


	m_normals[vert0 * 3 + 0] = 0.0f;	m_normals[vert0 * 3 + 1] = 0.0f;	m_normals[vert0 * 3 + 2] = 1.0f;
	m_normals[vert1 * 3 + 0] = 0.0f;	m_normals[vert1 * 3 + 1] = 0.0f;	m_normals[vert1 * 3 + 2] = 1.0f;
	m_normals[vert2 * 3 + 0] = 0.0f;	m_normals[vert2 * 3 + 1] = 0.0f;	m_normals[vert2 * 3 + 2] = 1.0f;

	// Compute a tangent
	m_tangents[vert0 * 3 + 0] = tangent.x; m_tangents[vert0 * 3 + 1] = tangent.y; m_tangents[vert0 * 3 + 2] = tangent.z;
	m_tangents[vert1 * 3 + 0] = tangent.x; m_tangents[vert1 * 3 + 1] = tangent.y; m_tangents[vert1 * 3 + 2] = tangent.z;
	m_tangents[vert2 * 3 + 0] = tangent.x; m_tangents[vert2 * 3 + 1] = tangent.y; m_tangents[vert2 * 3 + 2] = tangent.z;

	// Compute a bi-tangent
	m_biTangents[vert0 * 3 + 0] = bitangent.x; m_biTangents[vert0 * 3 + 1] = bitangent.y; m_biTangents[vert0 * 3 + 2] = bitangent.z;
	m_biTangents[vert1 * 3 + 0] = bitangent.x; m_biTangents[vert1 * 3 + 1] = bitangent.y; m_biTangents[vert1 * 3 + 2] = bitangent.z;
	m_biTangents[vert2 * 3 + 0] = bitangent.x; m_biTangents[vert2 * 3 + 1] = bitangent.y; m_biTangents[vert2 * 3 + 2] = bitangent.z;

}

// Adds a vertex, assoc texture coords, and normals with tangests and bitangents
void PrimitiveGeometry::AddVertex(float x, float y, float z, float s, float t) {
	m_vertexPositions.push_back(x);
	m_vertexPositions.push_back(y);
	m_vertexPositions.push_back(z);
	// Add texture coordinates
	m_textureCoords.push_back(s);
	m_textureCoords.push_back(t);
	// Push back placeholders for m_normals
	m_normals.push_back(0.0f);
	m_normals.push_back(0.0f);
	m_normals.push_back(1.0f);
	// Push back placeholders for tangents
	m_tangents.push_back(0.0f);
	m_tangents.push_back(0.0f);
	m_tangents.push_back(1.0f);
	// push back placeholders for bi-tangents
	m_biTangents.push_back(0.0f);
	m_biTangents.push_back(0.0f);
	m_biTangents.push_back(1.0f);
}

// Retrieves a pointer to our data.
float* PrimitiveGeometry::GetBufferDataPtr() {
	return m_bufferData.data();
}

// Retrieves the size of our data 
unsigned int PrimitiveGeometry::GetBufferDataSize() {
	return m_bufferData.size();
}

// Retrieves the number of bytes of our data
unsigned int PrimitiveGeometry::GetBufferSizeInBytes() {
	return m_bufferData.size() * sizeof(float);
}

// Retrieves the number of indices that we have.
unsigned int PrimitiveGeometry::GetIndicesSize() {
	return m_indices.size();
}

// Retrieves the indices
std::vector<unsigned int> PrimitiveGeometry::GetIndices() {
	return m_indices;
}

// Retrieves a pointer to the indices that we have
unsigned int* PrimitiveGeometry::GetIndicesDataPtr() {
	return m_indices.data();
}