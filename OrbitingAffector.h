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
    class CmdAngle : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
	class CmdRadius : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
	class CmdDrop : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };


	OrbitingAffector(ParticleSystem* psys);

	~OrbitingAffector(void);

	void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

	Real getAngle(void) const;
	void setAngle(const Real& col);
	Real getRadius(void) const;
	void setRadius(const Real& col);
	Real getDrop(void) const;
	void setDrop(const Real& col);

	/// Command objects
	static CmdAngle msAngleCmd;
	static CmdRadius msRadiusCmd;
	static CmdDrop msDropCmd;

protected:
	Real mAngle;
	Real mRadius;
	Real mDrop;
};

#endif