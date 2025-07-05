#include "utils.h"

int32_t randRange(int32_t min, int32_t max) {
	return min + (rand() % (max - min));
}

double randRangeFloat(double min, double max) {
	return min + ((rand() / (double)(RAND_MAX)) * (max - min));
}
