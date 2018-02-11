/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  
// a completer

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "adminui.h"
#include "prose.h"
#include "robot.h"

static void captureChoice();
static void askMvt(Direction dir);
static void ask4log();
static void askClearLog();
static void quit();
static void search(char *chaine);
//static void run();
//static void display();

// caraible pilot glogale au fichier
static PilotState state;

/* Variable de sortie du programme. */
static int keepGoing = 1;

/**
 * Fonction permettant de gérer le CTRL+C
 */
static void intHandler(int dummy)
{
    keepGoing = 0;
}

/**
 * Start AdminUI and waits for the user's input until the user ask to quit
 *
 */
extern void AdminUI_start(){
	Pilot_start();
	// wait for user input

	// fget puis scanf
	// feget borne automatiquement
	// !!! ppenser a rajouter le '/0'

	/* Interception d'un Ctrl+C pour arrêter le programme proprement. */
	// securité en cas d'imossibilité d'arreter
	signal(SIGINT, intHandler);

	PilotState state;

	while(keepGoing)
	{
		captureChoice();
		printf("\n");
		fflush(stdout);
	}
}


/**
 * Stop AdminUI
 *
 */
extern void AdminUI_stop(){
	Pilot_stop();
}


/**
 * initialize in memory AdminUI
 * 
 */
extern void AdminUI_new(){
	Pilot_new();
}


/**
 * destruct the AdminUI from memory 
 *
 */
extern void AdminUI_free(){
	Pilot_free();
}


/**
 * get the user input and call the right function according to it
 *
 */
static void captureChoice(){


	state = Pilot_getState();

	if(state.collision == BUMPED){
		VelocityVector vel;
		vel.dir = FORWARD;
		vel.power = 0;
		Pilot_setVelocity(vel);
	}

    char chaine[20];
	printf("Tapez une phrase : ");
	fgets(chaine, sizeof chaine, stdin);
	search(chaine);
	//printf("Vous avez tape : '%s'  \n", chaine);

	if(strcmp(chaine,"z")== 0){
		printf("Robot, en avant toute !\n");
		askMvt(FORWARD);
	}else if(strcmp(chaine,"q")== 0){
			printf("Robot, a gauche toute !\n");
			askMvt(LEFT);
	}else if(strcmp(chaine,"s")== 0){
			printf("Robot, retraite !\n");
			askMvt(BACKWARD);
	}else if(strcmp(chaine,"d")== 0){
			printf("Robot, a droite toute !\n");
			askMvt(RIGHT);
	}else if(strcmp(chaine,"quit")== 0){
			quit();
	}else if(strcmp(chaine,"log")== 0){
			ask4log();
	}else if(strcmp(chaine,"clear")== 0){
			askClearLog();
	}else{
			printf("Commande Inconnu \n");
	}

}

//function to delete retour a la ligne
static void search(char *chaine){
    char *p = strchr(chaine, '\n');
    if (p){
        *p = 0;
    }
}

/**
 * send the mvt ask from the user to the robot
 *
 */
static void askMvt(Direction dir){

	VelocityVector vel;
	vel.dir = dir;
	vel.power = 90;

	state = Pilot_getState();

	if(state.collision != BUMPED){
		Pilot_setVelocity(vel);
		printf("Ordre effectué !\n");
	}else{
		printf("Impossible de bouger : Capteur en contact !\n");
		vel.power = 0;
		Pilot_setVelocity(vel);
	}
}

/**
 * get the robot state and display it
 *
 */
static const char *DIRECTION[] = {
    "Babord", "Tribord", "l'Avant", "l'Arriere",
};
static void ask4log(){
	state = Pilot_getState();
	VelocityVector speed = Pilot_getVelocity();

	printf("____________________________\n\n");
	printf("Capitaine !\n");
	printf("Notre vitesse de croisiere est de %d\n", speed.power);
	printf("Nous faisons actuellement cap vers %s\n", DIRECTION[speed.dir]);
	if(state.collision == BUMPED){
		printf("Actuellement nous sommes bloqués par un obstacle\n");
	}else{
		printf("Actuellement nous sommes libre de nos mouvements\n");
	}
	printf("Notre luminosité actuelle est de %f\n", state.luminosity);
	printf("\n_____________________________\n");

}

/**
 * clear the log
 *
 */
static void askClearLog(){
	system("clear");
}

/**
 * quit
 */
static void quit(){
    keepGoing = 0;
}

///**
// * run
// *
// */
//static void run(){
//
//}
//
///**
// * display
// *
// */
//static void display(){
//
//}
