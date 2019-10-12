
#include "tracker.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/NodeCallback>
#include <osg/Texture2D>
#include <osg/PolygonMode>
#include <osgGA/GUIEventHandler>

#include <string>
#include <iostream>

osgViewer::Viewer viewer;
Tracker tracker;

void setProjectionMatrix(osg::Vec3d pa, osg::Vec3d pb, osg::Vec3d pc, osg::Vec3d pe, double n, double f);
osg::Group* createTexturedPlane();
osg::Vec3d calibration(0.0f, 0.0f, 0.0f);

class Teclado : public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
	{		
		switch (ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEY_Space):
		{
			// COMPLETAR AQUI CODIGO DE CALIBRACION
			tracker.getPosition(calibration);
			calibration.z() = 0.0f;
			return true;
		}

		default:
			return false;
		}
	}
};

int main(int , char **)
{
	// ************** OSG ************//
    
	bool use_fullscreen = false;

	if (use_fullscreen)
	{
		// set window in full screen
		viewer.setUpViewOnSingleScreen(0);
	}
	else
	{
		// set window in widonwed mode
		viewer.setUpViewInWindow(100, 100, 800, 600);
	}

	//std::string obj_filename("../../data/camera/camera.3ds");
	//std::string obj_filename("../../data/pool/ball.3ds");
	//std::string obj_filename("../../data/gear/gear.3ds");
	//std::string obj_filename("../../data/tooth/tooth.3ds");
	//std::string obj_filename("../../data/box/box.3ds");
	//std::string obj_filename("../../data/face/face.3ds");
	std::string obj_filename("../../data/cow.osg");

	// load model
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(obj_filename);
	if (!model)
	{
		printf("Error in OSG - 3D Model failed to load correctly.\n");
		return (-1);
	}

	// model position, rotation (attitude) and scale
	osg::PositionAttitudeTransform* modelXForm;
	modelXForm = new osg::PositionAttitudeTransform();
	modelXForm->setPosition(osg::Vec3(0, 0, 0.0));
	modelXForm->setAttitude(osg::Quat(-osg::PI / 2., osg::Vec3(1, 0, 0)));
	float scale = 0.1 / model->getBound().radius();
	modelXForm->setScale(osg::Vec3(scale, scale, scale));
	modelXForm->setDataVariance(osg::Object::STATIC);
	modelXForm->addChild(model);

	// add model to scenegraph
	osg::Group* rootnode = new osg::Group;
	rootnode->addChild(modelXForm);

	// set scenegraph
	viewer.setSceneData(rootnode);

	//********** LIGHTS *************//

	// Set light intensity
	osg::Light* light = viewer.getCamera()->getView()->getLight();
	if (light != NULL)
	{
		light->setDiffuse(osg::Vec4(scale, scale, scale, 1));
		light->setAmbient(osg::Vec4(0, 0, 0, 1));
		light->setSpecular(osg::Vec4(0, 0, 0, 1));
	}

	//********** TRACKING ***********//

	// start tracker	
	tracker.start();

	//********** TECLADO ***********//
	
	viewer.addEventHandler(new Teclado());

	// ******* SETUP COORDINATES ****** //

	osg::Vec3d position;

	// set screen coordinates with respect to origin
	// origin is center of screen
	osg::Vec3d lower_left(-0.24, -0.135, 0);
	osg::Vec3d lower_right(0.24, -0.135, 0);
	osg::Vec3d upper_left(-0.24, 0.135, 0);

	// near plane
	double near_plane = 0.01;
	// far plane
	double far_plane = 10.;

	// ******* RUN ****** //

	// run viewer
	viewer.realize();
	while (!viewer.done())
	{

		// get head position
		tracker.getPosition(position);
		tracker.printPosition();

		osg::Vec3d head_position(position);
		osg::Matrixd track_rot;
		//track_rot.makeRotate(osg::DegreesToRadians(45.0f), osg::Vec3d(0.0f, 1.0f, 0.0f)); //rotacion
		//head_position = track_rot * head_position; 
		//head_position += osg::Vec3d(0.24f,0.135f,0.0f); //desplazamiento
		head_position -= calibration;

		// compute prjection matrices given sceen and head positions
		setProjectionMatrix(lower_left, lower_right, upper_left, head_position, near_plane, far_plane);
		
		// do openscenegraph stuff
		viewer.frame();

		// sleep for a while
		OpenThreads::Thread::microSleep(10000);
	}

	// close tracker
	tracker.close();

	// wait for thread to shut down
	OpenThreads::Thread::microSleep(1000000);

	return 0;

}

// Compute projection matrices (asymmetric frustum) from screen and eye coordinates
void setProjectionMatrix(osg::Vec3d pa, osg::Vec3d pb, osg::Vec3d pc, osg::Vec3d pe, double n, double f)
{

	osg::Vec3d va, vb, vc;
	osg::Vec3d vr, vu, vn;
	double l, r, b, t, d;

	// Compute an orthonormal basis for the screen.
	vr = pb - pa;
	vu = pc - pa;
	vr.normalize();
	vu.normalize();
	vn = vr^vu;
	vn.normalize();

	// Compute the screen corner vectors.
	va = pa - pe;
	vb = pb - pe;
	vc = pc - pe;

	// Find the distance from the eye to screen plane.
	d = -va*vn;
	
	// Find the extent of the perpendicular projection.
	l = (vr*va) * n / d;
	r = (vr*vb) * n / d;
	b = (vu*va) * n / d;
	t = (vu*vc) * n / d;
	
	// set matrices
	viewer.getCamera()->setProjectionMatrixAsFrustum(l, r, b, t, n, f);
	viewer.getCamera()->setViewMatrix(osg::Matrix::translate(-pe[0],-pe[1],-pe[2]));

}

