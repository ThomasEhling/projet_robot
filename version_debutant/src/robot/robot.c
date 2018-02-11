/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  

#include <stdlib.h>
#include <stdio.h>

#include "robot.h"
#include "prose.h"

#define LEFT_MOTOR MD
#define RIGHT_MOTOR MA
#define LIGHT_SENSOR S1
#define FRONT_BUMPER S3
#define FLOOR_SENSOR S2

// a completer
static Robot * robot; //global, interne au fichier


/**
 * Start the Robot (initialize communication and open port)
 */
extern void Robot_start(){


		/* Initialisation des moteurs. */
		robot->mD = Motor_open(MD);
		if (robot->mD == NULL) PProseError("Problème d'ouverture du moteur droit (port MD)");

		robot->mG = Motor_open(MA);
		if (robot->mG == NULL) PProseError("Problème d'ouverture du moteur gauche (port MA)");

		robot->lS = LightSensor_open(S1);
		if (robot->lS == NULL) PProseError("Problème d'ouverture du capteur lumiere (port S1)");

		robot->cS_front = ContactSensor_open(S3);
		if (robot->cS_front == NULL) PProseError("Problème d'ouverture du capteur frontal (port S3)");

		robot->cS_floor = ContactSensor_open(S2);
		if (robot->cS_floor == NULL) PProseError("Problème d'ouverture du capteur du sol (port S2)");

}


/**
 * Stop Robot (stop communication and close port)
 */
extern void Robot_stop(){
	//close communication with infox
	Robot_setVelocity(0,0);
	Motor_close(robot->mD);
	Motor_close(robot->mG);
	LightSensor_close(robot->lS);
	ContactSensor_close(robot->cS_front);
	ContactSensor_close(robot->cS_floor);
}


/**
 * @briel initialize in memory the object Robot
 * 
 */

extern void Robot_new(){
	robot = (Robot *) malloc(sizeof(Robot));
	//TODO: assert(robot!=-NULL);
}


/**
 *  @brief destruct the object Robot from memory 
 */
extern void Robot_free(){
	/* Fermeture des accès aux moteurs. */
	free(robot);
}

/**
 * Robot_getRobotSpeed
 * 
 * @brief return the speed of the robot (positive average of the right's and left's current wheel power) 
 * @return speed of the robot (beetween 0 and 100)
 */
extern int Robot_getRobotSpeed(){
	
	//TODO : handle case error return E_GCMD

	return (Motor_getCmd(robot->mD)+Motor_getCmd(robot->mG))/2;

}

/**
 * Robot_getSensorState
 * 
 * @brief return the captor's states of the bumper and the luminosity
 * @return SensorState
 */
extern SensorState Robot_getSensorState(){

	SensorState state;

	if(ContactSensor_getStatus(robot->cS_floor)==PRESSED||ContactSensor_getStatus(robot->cS_front)==PRESSED){
		state.collision = BUMPED;
	}else{
		state.collision = NO_BUMP;
	}

	//LightSensor ls = LightSensor_getStatus(robot->lS);
	//TODO adapt light sensor
	state.luminosity = LightSensor_getStatus(robot->lS);

	return state;

}

/**
 * Robot_setVelocity
 * 
 * @brief set the power on the wheels of the robot
 * @param int mr : right's wheel power, value between -10O and 100
 * @param int ml : left's wheel power, value between -100 and 100
 */

extern void Robot_setVelocity(int mr,int ml){
	/* Appliquer les consignes aux moteurs. */
		if (Motor_setCmd(robot->mD, mr) == -1) {
			PProseError("Problème de commande du moteur droit");
		}
		if (Motor_setCmd(robot->mG, ml) == -1) {
			PProseError("Problème de commande du moteur gauche");
		}
}

