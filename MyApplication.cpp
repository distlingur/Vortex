#include "MyApplication.h"
#include <stdio.h>



MyApplication::MyApplication() : _root(NULL), _sceneManager(NULL), _listener(NULL) {
	// Do some constructing
}


MyApplication::~MyApplication() {
	delete _root;
	delete _listener;
}

void MyApplication::loadResources() {
	// Load the chosen resource file.
	Ogre::ConfigFile cf;

	//cf.load("c://OgreSDK//resources_d.cfg");
	//cf.load("resources_d.cfg");
	cf.load("C://Users//Raggi//Skoli//Hogun//Final//Vortex//resources_d.cfg");


	// Create the necessary vars for iterating the resource file.
	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
	Ogre::String sectionName, typeName, dataName;

	pAffFact = new OrbitingAffectorFactory();
	Ogre::ParticleSystemManager::getSingleton().addAffectorFactory(pAffFact);

	// For each section - load each resource or collection
	while (sectionIter.hasMoreElements()) {
		
		sectionName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			dataName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
		}
	}
	// Initialize the resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


int MyApplication::startUp() {
	// Create the root with the selected configurations

	//_root = new Ogre::Root("c://OgreSDK//plugins_d.cfg");
	_root = new Ogre::Root("plugins_d.cfg");


	// Show the configuration window.
	if (!_root->showConfigDialog()) {
		return -1;
	}

	// Create a Window
	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Draaikolk");

	// Initiate the scenemanager.
	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

	// Create a camera and configure it.
	Ogre::Camera* camera = _sceneManager->createCamera("Camera");
	camera->setPosition(Ogre::Vector3(0, 100, 150));
	camera->lookAt(Ogre::Vector3(0, 0, 0));
	camera->setNearClipDistance(5);

	// Create a viewport for the camera.
	Ogre::Viewport* viewPort = window->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	camera->setAspectRatio(Ogre::Real(viewPort->getActualWidth() / Ogre::Real(viewPort->getActualHeight())));

	// Load the resources.
	loadResources();

	// Create the scene with the loaded resources.
	createScene();

	// Initialize the framelistener and set it as the defult frameListener for the application.
	_listener = new MyFrameListener(window, camera, _SinbadNode, _SinbadEnt);
	_root->addFrameListener(_listener);

	return 0;
}

void MyApplication::createScene() {

	// Create Sinbad the mad Ogre pirate buccaneer guy.
	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode("Sinbad");
	_SinbadNode->attachObject(_SinbadEnt);

	// Create the plane.
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	// Set the plane as the ground and add a texture to it.
	/*Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");*/

	// Set up the scene lighting
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	Ogre::Light* light1 = _sceneManager->createLight("Light1");
	light1->setType(Ogre::Light::LT_DIRECTIONAL);
	light1->setDirection(1, -1, 0);
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	_sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);
	
	// Particle system extravaganza
	Ogre::Vector3 emitter;
	Ogre::Vector3 origin;
	Ogre::Vector3 direction;
	direction = emitter - origin;
	float ringRadius = 30.0;

	const int nodeAmount = 15;

	Ogre::SceneNode* sceneNodes[nodeAmount];
	Ogre::ParticleSystem* particleSystems[nodeAmount];

	for(int i = 0; i < nodeAmount; i++)
	{
		particleSystems[i] = _sceneManager->createParticleSystem(std::to_string(static_cast<long long>(i)), "Draaikolk/VortexStream");
		
	}

	for(int i = 0; i < nodeAmount; i++)
	{
		sceneNodes[i] = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / nodeAmount*(i+1)) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / nodeAmount*(i+1)) ) * ringRadius);
		sceneNodes[i]->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
		sceneNodes[i]->attachObject(particleSystems[i]);
	}

	/*
	Ogre::SceneNode* particleNode1 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*1) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*1) ) * ringRadius);
	Ogre::SceneNode* particleNode2 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*2) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*2) ) * ringRadius);
	Ogre::SceneNode* particleNode3 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*3) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*3) ) * ringRadius);
	Ogre::SceneNode* particleNode4 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*4) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*4) ) * ringRadius);
	Ogre::SceneNode* particleNode5 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*5) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*5) ) * ringRadius);
	
	Ogre::SceneNode* particleNode6 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*6) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*6) ) * ringRadius);
	Ogre::SceneNode* particleNode7 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*7) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*7) ) * ringRadius);
	Ogre::SceneNode* particleNode8 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*8) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*8) ) * ringRadius);
	Ogre::SceneNode* particleNode9 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*9) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*9) ) * ringRadius);
	Ogre::SceneNode* particleNode10 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*10) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*10) ) * ringRadius);

	Ogre::SceneNode* particleNode11 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*11) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*11) ) * ringRadius);
	Ogre::SceneNode* particleNode12 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*12) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*12) ) * ringRadius);
	Ogre::SceneNode* particleNode13 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*13) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*13) ) * ringRadius);
	Ogre::SceneNode* particleNode14 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*14) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*14) ) * ringRadius);
	Ogre::SceneNode* particleNode15 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::TWO_PI / 15*15) , 0 , Ogre::Math::Sin(Ogre::Math::TWO_PI / 15*15) ) * ringRadius);
	*/


	/*
	Ogre::ParticleSystem* ringPartSystem1 = _sceneManager->createParticleSystem("vortex1", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem2 = _sceneManager->createParticleSystem("vortex2", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem3 = _sceneManager->createParticleSystem("vortex3", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem4 = _sceneManager->createParticleSystem("vortex4", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem5 = _sceneManager->createParticleSystem("vortex5", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem6 = _sceneManager->createParticleSystem("vortex6", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem7 = _sceneManager->createParticleSystem("vortex7", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem8 = _sceneManager->createParticleSystem("vortex8", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem9 = _sceneManager->createParticleSystem("vortex9", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem10 = _sceneManager->createParticleSystem("vortex10", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem11 = _sceneManager->createParticleSystem("vortex11", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem12 = _sceneManager->createParticleSystem("vortex12", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem13 = _sceneManager->createParticleSystem("vortex13", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem14 = _sceneManager->createParticleSystem("vortex14", "Draaikolk/VortexStream");
	Ogre::ParticleSystem* ringPartSystem15 = _sceneManager->createParticleSystem("vortex15", "Draaikolk/VortexStream");
	*/


	/*
	particleNode1->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode2->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode3->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode4->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode5->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode6->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode7->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode8->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode9->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode10->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode11->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode12->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode13->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode14->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	particleNode15->lookAt(direction, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
	*/
/*
	particleNode1->attachObject(ringPartSystem1);
	particleNode2->attachObject(ringPartSystem2);
	particleNode3->attachObject(ringPartSystem3);
	particleNode4->attachObject(ringPartSystem4);
	particleNode5->attachObject(ringPartSystem5);
	particleNode6->attachObject(ringPartSystem6);
	particleNode7->attachObject(ringPartSystem7);
	particleNode8->attachObject(ringPartSystem8);
	particleNode9->attachObject(ringPartSystem9);
	particleNode10->attachObject(ringPartSystem10);
	particleNode11->attachObject(ringPartSystem11);
	particleNode12->attachObject(ringPartSystem12);
	particleNode13->attachObject(ringPartSystem13);
	particleNode14->attachObject(ringPartSystem14);
	particleNode15->attachObject(ringPartSystem15);*/
}

// Render the frame
void MyApplication::renderOneFrame() {
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}

// Should the app keep rendering.
bool MyApplication::keepRunning() {
	return _keepRunning;
}