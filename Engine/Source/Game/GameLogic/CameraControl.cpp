#include "CameraControl.h"

#include <iostream>

using namespace xe;

CameraControl::~CameraControl()
{

}

void CameraControl::execute(float32 deltaS)
{
	std::cout << "CameraControl executed" << std::endl;
}