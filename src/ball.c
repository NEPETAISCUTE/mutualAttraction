#include "ball.h"

#include <raylib.h>
#include <raymath.h>

#include "utils.h"

const unsigned int MIN_RADIUS = 8;
const unsigned int MAX_RADIUS = 16;

void generateBall(Ball* b) {
	b->radius = randRange(MIN_RADIUS, MAX_RADIUS);
	b->pos = (Vector2){randRangeFloat(0.f + b->radius, GetScreenWidth() - b->radius), randRangeFloat(0.f + b->radius, GetScreenHeight() - b->radius)};
	b->vel = (Vector2){randRangeFloat(-0.2f, 0.2f), randRangeFloat(-0.2f, 0.2f)};
	b->col = GetColor(rand() << 1 | 0x000000FF);
}

void updateBall(Ball* b) {
	b->pos = Vector2Add(b->pos, b->vel);
	uint32_t curWidth = GetScreenWidth();
	uint32_t curHeight = GetScreenHeight();
	bool xBorderCollide = false;
	bool yBorderCollide = false;
	if (b->pos.x < 0.f + b->radius) {
		xBorderCollide = true;
		b->pos.x = b->radius;
	}
	if (b->pos.x > curWidth - b->radius) {
		xBorderCollide = true;
		b->pos.x = curWidth - b->radius;
	}
	if (b->pos.y < 0.f + b->radius) {
		yBorderCollide = true;
		b->pos.y = b->radius;
	}
	if (b->pos.y > curHeight - b->radius) {
		yBorderCollide = true;
		b->pos.y = curHeight - b->radius;
	}
	if (xBorderCollide) b->vel.x *= -1;
	if (yBorderCollide) b->vel.y *= -1;
}

const double G = 1;
const double MIN_MAGSQ = 64.0;
void attractBalls(Ball* ba, Ball* bb) {
	Vector2 dir = Vector2Subtract(bb->pos, ba->pos);
	double mag_sq = fmax(Vector2LengthSqr(dir), MIN_MAGSQ);
	double mag = sqrtf(mag_sq);
	double f = G * (bb->radius / (mag_sq * mag));
	ba->vel = Vector2Add(ba->vel, Vector2Scale(dir, f));
}
