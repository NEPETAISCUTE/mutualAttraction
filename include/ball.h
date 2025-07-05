#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <stdint.h>

typedef struct _Ball {
	Vector2 pos;
	Vector2 vel;
	Color col;
	uint32_t radius;
} Ball;

void generateBall(Ball* b);
void updateBall(Ball* b);
void attractBalls(Ball* ba, Ball* bb);

#endif
