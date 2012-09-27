#pragma once
#include <string>
#include "Node.h"
#include "stdafx.h"

class BufferParser
{
public:
	BufferParser(void);
	BufferParser(std::string f);
	~BufferParser(void);
	void parseFile();
	void testParsing();
	float getDelta();
	float getStep();
	glm::vec3 getBufferSize();
	glm::vec3 getBackgroundColor();
	glm::vec3 getMaterialColor();
	glm::vec2 getResolution();
	glm::vec3 getCameraPosition();
	glm::vec3 getViewingDirection();
	glm::vec3 getUpVector();
	glm::vec3 getLightPosition();
	glm::vec3 getLightColor();
	float getFOVY();
	Node* getVoxelBuffer();
	char* getOutputFileName();
	glm::vec3 getBoundary();
	Node *voxelBuffer;

private:
	std::string fileName;
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
	char outputFileName[30];			
	float fieldOfViewY;
	
};

