#include "ball.h"

#include <raylib.h>
#include <raymath.h>

#include "utils.h"

const unsigned int MIN_RADIUS = 8;
const unsigned int MAX_RADIUS = 16;

void NepVector2Add(Vector2* result, Vector2* a, Vector2* b) {
	result->x = a->x + b->x;
	result->y = a->y + b->y;
}

void NepVector2Substract(Vector2* result, Vector2* a, Vector2* b) {
	result->x = a->x - b->x;
	result->y = a->y - b->y;
}

void NepVector2Scale(Vector2* result, Vector2* vec, double scale) {
	result->x = vec->x * scale;
	result->y = vec->y * scale;
}

double NepVector2LengthSqr(Vector2* vector) {
	return vector->x * vector->x + vector->y * vector->y;
}

void generateBall(Ball* b) {
	b->radius = randRange(MIN_RADIUS, MAX_RADIUS);
	b->pos = (Vector2){randRangeFloat(0.f + b->radius, GetScreenWidth() - b->radius), randRangeFloat(0.f + b->radius, GetScreenHeight() - b->radius)};
	b->vel = (Vector2){randRangeFloat(-0.2f, 0.2f), randRangeFloat(-0.2f, 0.2f)};
	b->col = GetColor(rand() << 1 | 0x000000FF);
}

void finishUpdateBall(Ball* b) {
	b->pos = b->resultPos;
}

void updateBallTS(Ball* b) {
	NepVector2Add(&b->pos, &b->pos, &b->vel);
	uint32_t curWidth = GetScreenWidth();
	uint32_t curHeight = GetScreenHeight();
	bool xBorderCollide = false;
	bool yBorderCollide = false;
	b->resultPos = b->pos;
	if (b->pos.x < 0.0 + b->radius) {
		xBorderCollide = true;
		b->resultPos.x = b->radius;
	}
	if (b->pos.x > curWidth - b->radius) {
		xBorderCollide = true;
		b->resultPos.x = curWidth - b->radius;
	}
	if (b->pos.y < 0.0 + b->radius) {
		yBorderCollide = true;
		b->resultPos.y = b->radius;
	}
	if (b->pos.y > curHeight - b->radius) {
		yBorderCollide = true;
		b->resultPos.y = curHeight - b->radius;
	}
	if (xBorderCollide) b->vel.x *= -1.0;
	if (yBorderCollide) b->vel.y *= -1.0;
}

const double G = 1;
const double MIN_MAGSQ = 64.0;
/*
void attractBalls(Ball* ba, Ball* bb) {
	Vector2 dir = Vector2Subtract(bb->pos, ba->pos);
	double mag_sq = fmax(Vector2LengthSqr(dir), MIN_MAGSQ);
	double mag = sqrtf(mag_sq);
	double f = G * (bb->radius / (mag_sq * mag));
	ba->vel = Vector2Add(ba->vel, Vector2Scale(dir, f));
}
*/

void attractBalls(Ball* ba, Ball* bb) {
	Vector2 dir;
	NepVector2Substract(&dir, &bb->pos, &ba->pos);
	double dirLenSq = NepVector2LengthSqr(&dir);
	double magSq;
	if(dirLenSq < MIN_MAGSQ) {
		magSq = MIN_MAGSQ;
	} else {
		magSq = dirLenSq;
	}
	double mag = sqrtf(magSq);
	double f = G * (bb->radius / (magSq * mag));
	NepVector2Scale(&dir, &dir, f);
	NepVector2Add(&ba->vel, &ba->vel, &dir);
}