#ifndef __OrbitingAffectorFactory_H__
#define __OrbitingAffectorFactory_H__

#include "OgreParticleFXPrerequisites.h"
#include "OgreParticleAffectorFactory.h"
#include "OrbitingAffector.h"

using namespace Ogre;

/** Factory class for OrbitingAffector. */
class _OgreParticleFXExport OrbitingAffectorFactory : public ParticleAffectorFactory
{
	/** See ParticleAffectorFactory */
	String getName() const { return "Orbiting"; }

	/** See ParticleAffectorFactory */
	ParticleAffector* createAffector(ParticleSystem* psys)
	{
		ParticleAffector* p = OGRE_NEW OrbitingAffector(psys);
		mAffectors.push_back(p);
		return p;
	}
};

#endif