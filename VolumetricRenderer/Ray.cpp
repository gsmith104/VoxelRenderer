#include "stdafx.h"
#include <math.h>
#include "Ray.h"
#include "LightRay.h"


Ray::Ray(void)
{

}

Ray::Ray(float d, float s, glm::vec3 bSize, glm::vec3 bgCol, glm::vec3 matCol, glm::vec2 res, glm::vec3 camPos, glm::vec3 viewDir,glm::vec3 upVec, float fovy, glm::vec3 lightPos, glm::vec3 lightCol, Node* buf)
{
	delta = d;
	step = s;
	bufferSize = bSize;
	backgroundColor = bgCol;
	materialColor = matCol;
	resolution = res;
	cameraPosition = camPos;
	viewingDirection = viewDir;
	upVector = upVec;
	fieldOfViewY = fovy;
	lightPosition = lightPos;
	lightColor = lightCol;
	voxelBuffer = buf;
	boundary = bufferSize*delta;
}

Ray::~Ray(void)
{
}

glm::vec3 Ray::calculateRay(int pixelX, int pixelY)
{
	//NOTE: Probably want to keep most of this stuff in an initialization function so the computation isn't repeated each time


	//Performs calculations from slide 149 

	glm::vec3 a = glm::cross(viewingDirection, upVector);
	glm::vec3 b = glm::cross(a,viewingDirection);
	glm::vec3 m = cameraPosition + viewingDirection;
	glm::vec3 v = (b*glm::length(viewingDirection)*glm::tan(glm::radians(fieldOfViewY)))/glm::length(b);
	
	//Calculate the ratio for the h vector
	float resRatio = resolution.x/resolution.y;
	float hLength= v.y*resRatio;
	float fovX = glm::atan(hLength/glm::length(viewingDirection));

	glm::vec3 h = (a*glm::length(viewingDirection)*glm::tan(fovX))/glm::length(a);

	glm::vec3 p = m + (2 * (pixelX/resolution.x) - 1) * h + (2 * (pixelY/resolution.y) - 1) * v;

	return p;
}

glm::vec3 Ray::rayMarch(int pixelX, int pixelY)
{
	//Establish initial vector
	glm::vec3 p = calculateRay(pixelX, pixelY);
	glm::vec3 r = (p-cameraPosition)/glm::length(p-cameraPosition);

	float T = 1.0, rho = 0, Q = 1.0, lightRho = 0, k = .6;
	glm::vec3 c;
	c.x = 0;
	c.y = 0;
	c.z = 0;
	
	//Jumps the vector right to the edge of the voxel array in the z direction
	float distanceToBuffer = cameraPosition.z;
	float stepNum = glm::abs(cameraPosition.z/r.z);
	glm::vec3 Xi = cameraPosition +  r * (stepNum);


	//Check to see if the ray will completely miss the voxel array
	if (Xi.x < 0 || Xi.x > boundary.x || Xi.y < 0 || Xi.y > boundary.y || Xi.z < -boundary.z){
		return backgroundColor;
	}
	else {
		Xi += (r*step);

		//Check that the ray is still inside the voxel space
		while (Xi.x > 0 && Xi.x < boundary.x && Xi.y > 0 && Xi.y < boundary.y && Xi.z>-boundary.z && Xi.z<0)
		{
			glm::vec3 tempRay = standardizeVector(Xi);
			int voxelIndex = indexVoxel(tempRay, bufferSize);
			rho = voxelBuffer[voxelIndex].getDensity();
			
			//If there is material at the voxel, run the lighting calculations
			if (rho>0){

				glm::vec3 lightRay = standardizeVector(Xi);
				glm::vec3 lightVector = glm::normalize(lightPosition-lightRay);
			
				/*if (voxelBuffer[voxelIndex].getLightValue() != -1)
				{
					Q = voxelBuffer[voxelIndex].getLightValue();
				}
				else 
				{*/
					float deltaQ;
					int voxelLightIndex, voxelLightIndex2 = 0;

					//Test that the lightRay is still inside the voxel space
					while(lightRay.x > 0 && lightRay.x < boundary.x && lightRay.y > 0 && lightRay.y < boundary.y && lightRay.z > -boundary.z && lightRay.z < 0)
					{
						glm::vec3 tempRay = standardizeVector(lightRay);

						voxelLightIndex = indexVoxel(tempRay, bufferSize);
						if (voxelLightIndex != voxelLightIndex2){
						lightRho = voxelBuffer[voxelLightIndex].getDensity();
						deltaQ = glm::exp(-k*lightRho*step);	
						Q*=deltaQ;
						}
						voxelLightIndex2 = voxelLightIndex;
						lightRay += (lightVector*step);
					}
				 
					voxelBuffer[voxelIndex].setLightValue(Q);
				//}
			}
		
			float deltaT = glm::exp(-k*step*rho);
			T*= deltaT;			
			c += ((1-deltaT)/k)*materialColor*T*Q*lightColor;			
			Xi += (r*step);
		}

		return (c*(1-T))+(T*backgroundColor);
	}
}

	
int Ray::indexVoxel(glm::vec3 rayLoc, glm::vec3 bufferSize)
{
	int x, y, z;

	x = glm::floor(rayLoc.x)/delta;
	y = glm::floor(rayLoc.y)/delta;
	z = glm::floor(glm::abs(rayLoc.z))/delta;

	int index = bufferSize.x * y + x + bufferSize.x * bufferSize.y * z;

	return index;


}

glm::vec3 Ray::standardizeVector(glm::vec3 input)
{
	glm::vec3 sVector;
	sVector.x = glm::floor(input.x)+delta/2;
	sVector.y = glm::floor(input.y)+delta/2;
	sVector.z = glm::floor(input.z)+delta/2;

	return sVector;

}
