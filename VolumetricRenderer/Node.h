#pragma once
class Node
{
public:
	Node(void);
	Node(float d);
	float getDensity();
	void setDensity(float d);
	void setLightValue(float value);
	float getLightValue();
	~Node(void);
private:
		float density;
		float lightValue;
};

