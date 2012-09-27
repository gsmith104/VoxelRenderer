// VolumetricRenderer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BufferParser.h"
#include "Ray.h"
#include "EasyBMP.h"

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	BMP finalImage;
	BufferParser* configInfo = new BufferParser(argv[1]);
	configInfo->parseFile();

	Ray* camera = new Ray(configInfo->getDelta(), configInfo->getStep(), configInfo->getBufferSize(), configInfo->getBackgroundColor(), configInfo->getMaterialColor(), configInfo->getResolution(),
		configInfo->getCameraPosition(), configInfo->getViewingDirection(), configInfo->getUpVector(), configInfo->getFOVY(), configInfo->getLightPosition(), configInfo->getLightColor(), configInfo->getVoxelBuffer());
	finalImage.SetSize(configInfo->getResolution().x, configInfo->getResolution().y);

	int halfwayDone = configInfo->getResolution().y/2;
	int quarterDone = configInfo->getResolution().y/4;


	//Iterate through pixels and calculate vector
	for (int i = 0; i<configInfo->getResolution().y; i++){
			
		if (i == quarterDone){
			cout<<"25% complete"<<endl;
		}
		else if(i == halfwayDone){
			cout<<"50% complete"<<endl;
		}
		else if(i == halfwayDone+quarterDone){
			cout<<"75% complete"<<endl;
		}

		for (int j = 0; j<configInfo->getResolution().x; j++) {

			glm::vec3 color = camera->rayMarch(j,i);

			finalImage(j,configInfo->getResolution().y-1-i)->Red = color.x * 255;
			finalImage(j,configInfo->getResolution().y-1-i)->Green = color.y * 255;
			finalImage(j,configInfo->getResolution().y-1-i)->Blue = color.z * 255;	
		}
	}

	finalImage.WriteToFile(configInfo->getOutputFileName());

	delete configInfo; 
	delete camera;
	

return 0 ; 
} 


