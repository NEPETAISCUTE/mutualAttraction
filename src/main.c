#include <ctype.h>
#include <pthread.h>
#include <raylib.h>
#include <raymath.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "world.h"

/*
 *
 *  TODO
 *  - implement a system of balls X
 *  - make them attract each other X
 *  - make them not able to go outside the screen X
 *  - implement multithreading for handling attractions X
 *  - probably debug whether or not the gravity works since sometimes some balls don't feel like they're really attracted X
 *  - refactor the project so that it's more digest
 *  - implement quad tree for handling gravity
 *
 */

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

const unsigned int DEFAULT_BALL_COUNT = 32;
const unsigned int DEFAULT_THREAD_COUNT = 1;
void handleArgs(int argc, char** argv, uint32_t* ballCount, uint32_t* threadCount) {
	srand(time(NULL));
	if (argc >= 2) {
		char* balls = argv[1];
		char* thread;
		if (argc >= 3)
			thread = argv[2];
		else
			thread = NULL;

		while (*balls) {
			if (!isdigit(*balls)) {
				fputs("the ball count specified is not a number\n", stderr);
				exit(EXIT_FAILURE);
			}
			balls++;
		}
		if (thread) {
			while (*thread) {
				if (!isdigit(*thread)) {
					fputs("the thread count specified is not a number\n", stderr);
					exit(EXIT_FAILURE);
				}
				thread++;
			}
		}
		*ballCount = atoi(argv[1]);
		if (thread)
			*threadCount = atoi(argv[2]);
		else
			*threadCount = DEFAULT_THREAD_COUNT;
	} else if (argc == 1) {
		*ballCount = DEFAULT_BALL_COUNT;
		*threadCount = DEFAULT_THREAD_COUNT;
	} else {
		fputs("too many arguments were specified, please specify one single argument for the number of balls you wish to create at most\n", stderr);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv) {
	World w;
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "test");
	handleArgs(argc, argv, &w.ballCount, &w.threadCount);
	generateWorld(&w);

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		updateWorld(&w);
		BeginDrawing();
		ClearBackground(DARKGREEN);
		DrawFPS(0, 0);
		for (uint32_t i = 0; i < w.ballCount; i++) {
			DrawCircleV(w.balls[i].pos, w.balls[i].radius, w.balls[i].col);
		}
		EndDrawing();
	}
	CloseWindow();
	exit(EXIT_SUCCESS);
}
