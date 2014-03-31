#include "OrbitingAffector.h"

using namespace Ogre;

// Instantiate statics
OrbitingAffector::CmdColor OrbitingAffector::msColorCmd;

OrbitingAffector::OrbitingAffector(ParticleSystem* psys) :ParticleAffector(psys)
{
	mType = "Orbiting";

	// defaults
	mCol.setAsRGBA(1);

	// Setup parameters
	if(createParamDictionary("Orbiting")) {
		addBaseParameters();
		ParamDictionary* dict = getParamDictionary();

		dict->addParameter(ParameterDef("color", "Determine color of particles",
			PT_COLOURVALUE), &msColorCmd);
	}
}

OrbitingAffector::~OrbitingAffector(void)
{
}

void OrbitingAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed) {
	ParticleIterator pi = pSystem->_getIterator();    
	Particle* p;

	
}

//-----------------------------------------------------------------------
void OrbitingAffector::setColor(const ColourValue& col)
{
    mCol = col;
}
//-----------------------------------------------------------------------
ColourValue OrbitingAffector::getColor(void) const
{
    return mCol;
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Command objects
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
String OrbitingAffector::CmdColor::doGet(const void* target) const
{
    return StringConverter::toString(
        static_cast<const OrbitingAffector*>(target)->getColor() );
}
void OrbitingAffector::CmdColor::doSet(void* target, const String& val)
{
    static_cast<OrbitingAffector*>(target)->setColor(
        StringConverter::parseColourValue(val));
}