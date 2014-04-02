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

	while (!pi.end())
    {
		p = pi.getNext();
		p->setDimensions(1, 1);
		/*mAngle += mAngle;
		if(mAngle > 360)
			mAngle = mAngle - 360;
		p->position.x = mRadius * Ogre::Math::Cos(mAngle);
		p->position.z = mRadius * Ogre::Math::Sin(mAngle);*/
		p->position.y += mDrop;
	}
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