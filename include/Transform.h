#pragma once
#ifndef Transform_HPP
#define Transform_HPP

#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
public:
    // Constructor
    Transform();
    // Destructor
    ~Transform();

    // Resets matrix transformations to the identity matrix
    void LoadIdentity();
    // Performs a translation of an object
    void Translate(float x, float y, float z);
    // Performs rotation about an axis
    void Rotate(float radians, float x, float y, float z);
    // Performs rotation about an axis
    void Scale(float x, float y, float z);
    // Returns the transformation matrix
    GLfloat* GetTransformMatrix();

    // Takes in a transform and sets internal matrix.
    void ApplyTransform(Transform t);
    // Returns the transformation matrix
    glm::mat4 GetInternalMatrix();

private:
    // Stores the actual transformation matrix
    glm::mat4 m_modelTransformMatrix;
    
};

#endif