#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>

#include "ball.h"

typedef struct _World {
	uint32_t ballCount;
	Ball* balls;
	uint32_t threadCount;
} World;

void generateWorld(World* w);

typedef struct _AttractBallWorkArg {
	World* w;
	uint32_t tid;
	uint32_t idxStart;
	uint32_t idxEnd;
} AttractBallWorkArg;

void attractBallsWork(void* arg);  // arg is a AttractBallWorkArg*, this function is used to multithread attracting balls together for performance increase
void updateWorld(World* w);

#endif
