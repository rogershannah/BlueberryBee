#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::LoadIdentity()
{
}

void Transform::Translate(float x, float y, float z)
{
}

void Transform::Rotate(float radians, float x, float y, float z)
{
}

void Transform::Scale(float x, float y, float z)
{
}

GLfloat* Transform::GetTransformMatrix()
{
	return nullptr;
}

void Transform::ApplyTransform(Transform t)
{
}

glm::mat4 Transform::GetInternalMatrix()
{
	return glm::mat4();
}
