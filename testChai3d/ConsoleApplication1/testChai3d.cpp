#include <chai3d/chai3d.h>
#include <iostream>
#include <Windows.h>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/NodeCallback>

using namespace chai3d;

cWorld* world;

cHapticDeviceHandler* handler;

cGenericHapticDevicePtr hapticDevice;

cToolCursor* tool;

cMesh* object;


bool simulationRunning = false;

bool simulationFinished = false;

std::string obj_filename("../../../data/camera/camera.3ds");




int main(int argc, char* argv[])
{
	world = new cWorld();
	handler = new cHapticDeviceHandler();
	handler->getDevice(hapticDevice, 0);
	hapticDevice->open();
	hapticDevice->calibrate();
	cHapticDeviceInfo info;
	if (hapticDevice)
	{
		info = hapticDevice->getSpecifications();
		std::cout << "Haptico activo" << std::endl;
		cVector3d position;
		hapticDevice->getPosition(position);
		std::cout << "Posicion inicial: " << position << std::endl;
	}

	/*std::cout << "Haptic device model: " << info.m_modelName << std::endl;
	while (true)
	{
		cVector3d position;
		hapticDevice->getPosition(position);
		Sleep(10);
		std::cout << "Position: " << position << std::endl;
	}
	std::cout << "Chai3d test" << std::endl;
	*/return 0;
}