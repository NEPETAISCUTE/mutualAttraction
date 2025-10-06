#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <stdint.h>

typedef struct _Ball {
	Vector2 pos;
	Vector2 resultPos;
	Vector2 vel;
	Vector2 resultVel;
	Color col;
	uint32_t radius;
} Ball;

void generateBall(Ball* b);
void finishUpdateBall(Ball* b);
void updateBallTS(Ball* b);
void attractBalls(Ball* ba, Ball* bb);

#endif
