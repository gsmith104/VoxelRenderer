#include "stdafx.h"
#include "Node.h"


Node::Node(void)
{
	lightValue = -1;
}

Node::Node(float d)
{
	lightValue = -1;
	density = d;
}

float Node::getDensity()
{
	return density;
}

void Node::setDensity(float d)
{
	density = d;
}

void Node::setLightValue(float value)
{	
	lightValue = value;
}

float Node::getLightValue()
{
	return lightValue;
}

Node::~Node(void)
{
}
