#pragma once
#ifndef __OrbitingAffector_H__
#define __OrbitingAffector_H__

#include "OgreParticleFXPrerequisites.h"
#include "OgreParticle.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"
#include "OgreParticleAffector.h"

using namespace Ogre;
	
class OrbitingAffector : public ParticleAffector
{
public:
	/** Command object for color (see ParamCommand).*/
    class CmdColor : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };

	OrbitingAffector(ParticleSystem* psys);

	~OrbitingAffector(void);

	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

	void setColor(const ColourValue& col);
	ColourValue getColor(void) const;

	/// Command objects
	static CmdColor msColorCmd;

protected:
	ColourValue mCol;
};

#endif