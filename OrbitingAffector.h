#pragma once
#ifndef __OrbitingAffector_H__
#define __OrbitingAffector_H__

#include "OgreParticleFXPrerequisites.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreParticleAffector.h"

using namespace Ogre;
	
class OrbitingAffector : public ParticleAffector
{
public:
	OrbitingAffector(ParticleSystem* psys);

	~OrbitingAffector(void);

	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);
};

#endif