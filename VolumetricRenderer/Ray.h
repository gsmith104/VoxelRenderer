#pragma once
#include "stdafx.h"
#include "glm/glm.hpp"
class Ray
{
public:
	Ray(void);
	Ray(float d, float s, glm::vec3 bSize, glm::vec3 bgCol, glm::vec3 matCol, glm::vec2 res, glm::vec3 camPos, glm::vec3 viewDir, glm::vec3 upVec, float fovy, glm::vec3 lightPos, glm::vec3 lightCol, Node* buf);
	~Ray(void);
	glm::vec3 standardizeVector(glm::vec3 input);
	glm::vec3 calculateRay(int pixelX, int pixelY);
	glm::vec3 rayMarch(int pixelX, int pixelY);
	int indexVoxel(glm::vec3 rayLoc, glm::vec3 bufferSize);

private:
	float delta;
	float step;
	glm::vec3 bufferSize;
	glm::vec3 backgroundColor;
	glm::vec3 materialColor;
	glm::vec2 resolution;
	glm::vec3 cameraPosition;
	glm::vec3 viewingDirection;
	glm::vec3 upVector;
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
	glm::vec3 boundary;
	float fieldOfViewY;
	Node *voxelBuffer;
	glm::vec3 location;
};

