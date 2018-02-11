/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  
/**
 * @file  main.c
 *
 * @brief  Launch the Robot's programm for basic version (no modularity, no socket, no task, no error's management)
 *
 * @author Jerome Delatour
 * @date 19-04-2016
 * @version 1
 * @section License
 *
 * The MIT License
 *
 * Copyright (c) 2016, Jerome Delatour
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "prose.h"
#include "./robot/adminui.h"
#include "robot/robot.h"


/**
 * starts the robot V1 application
 */
int main (int argc, char *argv[])
{

	printf("Programme exemple Version_debutant\n");
	fflush(stdout);

#ifdef INTOX
	/* Initialisation pour l'utilisation du simulateur Intox. */
	if (ProSE_Intox_init("127.0.0.1", 12345) == -1) {
		PProseError("Problème d'initialisation du simulateur Intox");
		return EXIT_FAILURE;
	}
#endif

  AdminUI_new();
  AdminUI_start();
  AdminUI_stop();
  AdminUI_free();

#ifdef INTOX
	/* Arrêt de l'utilisation du simulateur Intox. */
	ProSE_Intox_close();
#endif

  return 0;
}

