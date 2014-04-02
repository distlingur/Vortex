#include "OrbitingAffector.h"

using namespace Ogre;

// Instantiate statics
OrbitingAffector::CmdAngle OrbitingAffector::msAngleCmd;
OrbitingAffector::CmdRadius OrbitingAffector::msRadiusCmd;
OrbitingAffector::CmdDrop OrbitingAffector::msDropCmd;

OrbitingAffector::OrbitingAffector(ParticleSystem* psys) 
	:ParticleAffector(psys),
	mAngle(0),
	mRadius(0),
	mDrop(0)
{
	mType = "Orbiting";
	count = 0;

	// Setup parameters
	if(createParamDictionary("Orbiting")) {
		addBaseParameters();
		ParamDictionary* dict = getParamDictionary();

		dict->addParameter(ParameterDef("angle", 
			"The angle of the particle from last pos to new pos",
			PT_REAL), 
			&msAngleCmd);
		dict->addParameter(ParameterDef("radius", 
			"The distance from middle of vortex to the particle",
			PT_REAL), 
			&msRadiusCmd);
		dict->addParameter(ParameterDef("drop", 
			"The distance downwards the particle travels",
			PT_REAL), 
			&msDropCmd);
	}
}

OrbitingAffector::~OrbitingAffector(void)
{
}

void OrbitingAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed) {
	ParticleIterator pi = pSystem->_getIterator();    
	Particle* p;
	Ogre::Radian theAngle;
	float distanceToOrigin;

	int degrees = 1;
	float degToRad = degrees * Ogre::Math::PI/180;
	int theDistance = 20;
	float decreasingRadius = theDistance * degToRad/(2 * Ogre::Math::PI);

	


	while (!pi.end())
    {
		p = pi.getNext();
		p->setDimensions(2, 2);
		theAngle = (Ogre::Vector2(1,0)).angleTo(Ogre::Vector2(p->position.x,p->position.z));//(Ogre::Vector3(0,0,0)).angleBetween(p->position);

		distanceToOrigin = Ogre::Math::Sqrt(Ogre::Math::Sqr(p->position.x) + Ogre::Math::Sqr(p->position.z));


		distanceToOrigin -= decreasingRadius;
		//std::cout << "ANGLE BEFORE OPERATOR: " << theAngle << std::endl;
		theAngle.operator+=((Ogre::Radian)degToRad);
		//std::cout << "ANGLE AFTER OPERATOR: " << theAngle << std::endl;


		if(distanceToOrigin > 0)
		{
			p->position.x = distanceToOrigin * Ogre::Math::Cos(theAngle);
			p->position.z = distanceToOrigin * Ogre::Math::Sin(theAngle);
			
		}
		p->position.y -= mDrop;

		//std::cout << "ANGLE FINAL: " << theAngle << std::endl;
		//theAngle = p->position.angleBetween(Ogre::Vector3(0,0,0));

		
	}

	/*while (!pi.end())
    {
		p = pi.getNext();
		p->setDimensions(2, 2);

		mAngle += mAngle;
		if(mAngle > 360)
			mAngle = mAngle - 360;
		p->position.x = mRadius * Ogre::Math::Cos(mAngle);
		p->position.z = mRadius * Ogre::Math::Sin(mAngle);
		p->position.y -= mDrop;

		//p->
	}*/
}


//-----------------------------------------------------------------------
Real OrbitingAffector::getAngle(void) const
{
    return mAngle;
}
//-----------------------------------------------------------------------
void OrbitingAffector::setAngle(const Real& angle)
{
    mAngle = angle;
}
//-----------------------------------------------------------------------
Real OrbitingAffector::getRadius(void) const
{
    return mRadius;
}
//-----------------------------------------------------------------------
void OrbitingAffector::setRadius(const Real& radius)
{
    mRadius = radius;
}
//-----------------------------------------------------------------------
Real OrbitingAffector::getDrop(void) const
{
    return mDrop;
}
//-----------------------------------------------------------------------
void OrbitingAffector::setDrop(const Real& drop)
{
    mDrop = drop;
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Command objects
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
String OrbitingAffector::CmdAngle::doGet(const void* target) const
{
    return StringConverter::toString(
        static_cast<const OrbitingAffector*>(target)->getAngle() );
}
void OrbitingAffector::CmdAngle::doSet(void* target, const String& val)
{
    static_cast<OrbitingAffector*>(target)->setAngle(
        StringConverter::parseReal(val));
}
//-----------------------------------------------------------------------
String OrbitingAffector::CmdRadius::doGet(const void* target) const
{
    return StringConverter::toString(
        static_cast<const OrbitingAffector*>(target)->getRadius() );
}
void OrbitingAffector::CmdRadius::doSet(void* target, const String& val)
{
    static_cast<OrbitingAffector*>(target)->setRadius(
        StringConverter::parseReal(val));
}
//-----------------------------------------------------------------------
String OrbitingAffector::CmdDrop::doGet(const void* target) const
{
    return StringConverter::toString(
        static_cast<const OrbitingAffector*>(target)->getDrop() );
}
void OrbitingAffector::CmdDrop::doSet(void* target, const String& val)
{
    static_cast<OrbitingAffector*>(target)->setDrop(
        StringConverter::parseReal(val));
}