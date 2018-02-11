/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  

#include <stdlib.h>
#include <stdio.h>

#include "pilot.h"
#include "robot.h"
#include "prose.h"

static void sendMvt(VelocityVector vel);
//static int hasBumped();

// a completer
static Pilot pilot; //global, interne au fichier

/**
 * Start Pilot
 *
 */
extern void Pilot_start(){
	Robot_start();

	PilotState * state = &(pilot.state);

	state->collision = NO_BUMP;
	state->luminosity = 1;
	state->speed = Robot_getRobotSpeed();

}


/**
 * Stop Pilot
 *
 */
extern void Pilot_stop(){
	Robot_stop();
}


/**
 * initialize in memory the object Pilot
 */
extern void Pilot_new(){
	Robot_new();
}


/**
 * destruct the object Pilot from memory 
 */
extern void Pilot_free(){
	Robot_free();
}

/**
 * setVelocity
 * 
 * @brief description 
 * @param vel 
 */
extern void Pilot_setVelocity(VelocityVector vel){
	pilot.speed = vel;
	sendMvt(vel);
}

/**
 * getVelocity
 *
 * @brief description
 * @return VelocityVector
 */
extern VelocityVector Pilot_getVelocity(){
	return pilot.speed;
}

/**
 * getState
 * 
 * @brief description 
 * @return PilotState
 */
extern PilotState Pilot_getState(){
	SensorState state = Robot_getSensorState();
	pilot.state.collision = state.collision;
	pilot.state.luminosity = state.luminosity;
	return pilot.state;
}

/**
 * check
 * 
 * @brief description 
 */
extern void Pilot_check(){
	
}

/**
 * checkMAE
 * 
 * @brief description 
 */
extern void Pilot_checkMAE(){
	
}

static void sendMvt(VelocityVector vel){
	switch(vel.dir){
		case LEFT:
			Robot_setVelocity(vel.power, -vel.power);
			break;
		case RIGHT:
			Robot_setVelocity(-vel.power, vel.power);
			break;
		case FORWARD:
			Robot_setVelocity(vel.power, vel.power);
			break;
		case BACKWARD:
			Robot_setVelocity(-vel.power, -vel.power);
			break;
	}
}

//static int hasBumped(){
//	SensorState sensor = Robot_getSensorState();
//	if(sensor.collision == BUMPED){
//		pilot.state.collision = BUMPED;
//		return 1;
//	}else{
//		return 0;
//	}
//}
