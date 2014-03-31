#include "OrbitingAffector.h"

using namespace Ogre;

OrbitingAffector::OrbitingAffector(ParticleSystem* psys) :ParticleAffector(psys)
{
	mType = "Orbiting";


}

OrbitingAffector::~OrbitingAffector(void)
{
}

void OrbitingAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
{}