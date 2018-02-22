//------------------------------------------------------//
//	Global includes & definitions to be used everywhere	//
//------------------------------------------------------//

#ifndef GLOBAL_H
#define GLOBAL_H

//------------------------------------------------------//
//	Errorlog global definition							//
//------------------------------------------------------//
#include "ErrorLog.h"

#define LOG_STREAM &std::cout

//------------------------------------------------------//
//	Custom types declaration							//
//------------------------------------------------------//

#include <glm/glm.hpp>

//Shape & physics types
typedef glm::vec3 Size;
typedef glm::vec3 Position;
typedef glm::vec3 Force;
typedef glm::vec3 Velocity;


typedef enum
{
	NO_MOTION = 0x0000,
	MOTION_UP = 0x0001,
	MOTION_DOWN = 0x0002,
	MOTION_LEFT = 0x0004,
	MOTION_RIGHT = 0x0008
} MotionEnum;

typedef enum
{
	NO_TYPE = 0,
	BOX = 8,
	RHOMBI = 24
} Shape_type;

#endif /* GLOBAL_H */