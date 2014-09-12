/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsWorld_
#define _hrengin_IPhysicsWorld_

#include <hrengin/common/types.h>

#include <hrengin/common/Vector3d.h>

#include <hrengin/physics/IDebugDrawer.h>
#include <hrengin/physics/CollisionFilter.h>
#include <hrengin/physics/IRayResultCallback.h>

namespace hrengin {
namespace physics {

class ICollisionObject;
class ICollisionPhantom;
class IRigidBody;

/* This class is responsible for collision detection, dynamics simulation etc */
class IPhysicsWorld {
public:
	virtual ~IPhysicsWorld() {};
	
	virtual void addBody(IRigidBody* body) = 0;
	virtual void addBody(IRigidBody* body, CollisionFilter filter) = 0;
	virtual void addObject(ICollisionObject* object) = 0;
	virtual void addObject(ICollisionObject* object, CollisionFilter filter) = 0;
	
	virtual void removeBody(IRigidBody* body) = 0;
	virtual void removeObject(ICollisionObject* object) = 0;

	virtual void setDebugDrawer(IDebugDrawer* drawer) = 0;

	virtual void castRay(Vector3d<f32> from, Vector3d<f32> to, IRayResultCallback* callback) = 0;

	virtual bool step() = 0;

	// internal implementation details
	class Details;
	
	// for internal use only
	virtual IPhysicsWorld::Details* getDetails() = 0;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsWorld_