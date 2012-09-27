#include "stdafx.h"
#include "BufferParser.h"

using namespace std;

BufferParser::BufferParser(void)
{
}

BufferParser::BufferParser(std::string f)
{
	fileName = f;
}

void BufferParser::parseFile()
{

	string tempString;

	ifstream configFile (fileName);
	if (configFile.is_open())
	{
		cout<<"Parsing "<<fileName<<endl;
		configFile >> tempString >> delta;
		configFile >> tempString >> step;
		configFile >> tempString >> bufferSize.x >> bufferSize.y>> bufferSize.z;
		configFile >> tempString >> backgroundColor.x >> backgroundColor.y >> backgroundColor.z;
		configFile >> tempString >> materialColor.x >> materialColor.y >> materialColor.z;
		configFile >> tempString >> outputFileName;
		configFile >> tempString >> resolution.x >> resolution.y;
		configFile >> tempString >> cameraPosition.x >> cameraPosition.y >> cameraPosition.z;
		configFile >> tempString >> viewingDirection.x >> viewingDirection.y >> viewingDirection.z;
		configFile >> tempString >> upVector.x >> upVector.y >> upVector.z;
		configFile >> tempString >> fieldOfViewY;
		configFile >> tempString >> lightPosition.x >> lightPosition.y >> lightPosition.z;
		configFile >> tempString >> lightColor.x >> lightColor.y >> lightColor.z;

		

		voxelBuffer = (Node*)malloc(sizeof(Node)*(bufferSize.x * bufferSize.y * bufferSize.z));
		
		//TODO - Test for specific number of times with for loop
		int limit = bufferSize.x * bufferSize.y * bufferSize.z;
		float tempI;
		//cout<<limit<<endl;
		for(int i = 0; i<limit; i++)
		{
			string line;
			getline(configFile, line);
			//configFile >> tempI;
			tempI = atof(line.c_str());
			voxelBuffer[i].setDensity(tempI);
			voxelBuffer[i].setLightValue(-1.0);

		}
		
	configFile.close();
	}
	else 
	{
		cout<<"Unable to open file."<<endl;
	}
}



void BufferParser::testParsing()
{
	//cout <<"DELTA "<<delta<<endl;
	//cout <<"STEP "<<step<<endl;
	//cout <<"XYZC "<<bufferSize.x<<" "<<bufferSize.y <<" "<<bufferSize.z<<endl;
	//cout <<"Light Position "<<lightPosition.x<<" "<<lightPosition.y <<" "<<lightPosition.z<<endl;
	//cout <<"Camera Position "<<cameraPosition.x<<" "<<cameraPosition.y <<" "<<cameraPosition.z<<endl;

	//cout<<voxelBuffer[1].getDensity()<<endl;
	//cout<<voxelBuffer[10000].getDensity()<<endl;
	//for(int i =0; i<1000000; i++)
	//{
	//	if (voxelBuffer[i].getDensity()>0){
	//		cout<<voxelBuffer[i].getDensity();
	//	}
	//}

}

float BufferParser::getDelta(){
	return delta;
}

float BufferParser::getStep(){
	return step;
}

glm::vec3 BufferParser::getBufferSize(){
	return bufferSize;
}

glm::vec3 BufferParser::getBackgroundColor(){
	return backgroundColor;
}

glm::vec3 BufferParser::getMaterialColor()
{
	return materialColor;
}

glm::vec2 BufferParser::getResolution()
{
	return resolution;
}

glm::vec3 BufferParser::getCameraPosition()
{
	return cameraPosition;
}

glm::vec3 BufferParser::getViewingDirection()
{
	return viewingDirection;
}

glm::vec3 BufferParser::getUpVector()
{
	return upVector;
}

glm::vec3 BufferParser::getLightPosition()
{
	return lightPosition;
}

glm::vec3 BufferParser::getLightColor()
{
	return lightColor;
}

float BufferParser::getFOVY(){
	return fieldOfViewY;
}

char* BufferParser::getOutputFileName()
{
	return outputFileName;
}

glm::vec3 BufferParser::getBoundary()
{
	return boundary;
}

Node* BufferParser::getVoxelBuffer(){
	return voxelBuffer;
}

BufferParser::~BufferParser(void)
{
	free(voxelBuffer);
}

