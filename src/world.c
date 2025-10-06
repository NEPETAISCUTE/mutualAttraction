#include "world.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void generateWorld(World* w) {
	w->balls = malloc(w->ballCount * sizeof(Ball));
	if (!w->balls) {
		fputs("An error occured when allocating memory for the balls, please try freeing up memory and trying again\n", stderr);
		exit(EXIT_FAILURE);
	}
	for (uint32_t i = 0; i < w->ballCount; i++) {
		generateBall(&w->balls[i]);
	}
}

const uint32_t MAX_THREAD_COUNT = 128;
void attractBallsWork(void* arg) {
	AttractBallWorkArg* warg = (AttractBallWorkArg*)arg;
	for (uint32_t i = warg->idxStart; i < warg->idxEnd; i++) {
		updateBallTS(&warg->w->balls[i]);
	}
	for (uint32_t i = warg->idxStart; i < warg->idxEnd; i++) {
		for (uint32_t j = 0; j < warg->w->ballCount; j++) {
			if (i == j) continue;
			attractBalls(&warg->w->balls[i], &warg->w->balls[j]);
		}
	}
}

double timeRecord[100];
size_t timeRecordIdx = 0;
size_t timesRecorded = 0;

void updateWorld(World* w) {
	pthread_t threads[MAX_THREAD_COUNT];
	AttractBallWorkArg args[MAX_THREAD_COUNT];

	double timeStart = GetTime();
	for (uint32_t i = 0; i < w->threadCount; i++) {
		args[i].w = w;
		args[i].tid = i;
		args[i].idxStart = i * (w->ballCount / w->threadCount);
		if (i == w->threadCount - 1 && w->ballCount % w->threadCount != 0)
			args[i].idxEnd = (i + 1) * (w->ballCount / w->threadCount) + (w->ballCount % w->threadCount);
		else
			args[i].idxEnd = (i + 1) * (w->ballCount / w->threadCount);
		pthread_create(&threads[i], NULL, (void*)attractBallsWork, &args[i]);
	}

	for (uint32_t i = 0; i < w->threadCount; i++) {
		pthread_join(threads[i], NULL);
	}

	for(uint32_t i = 0; i < w->ballCount; i++) {
		finishUpdateBall(&w->balls[i]);
	}
	double timeEnd = GetTime();
	timeRecord[timeRecordIdx++] = timeEnd - timeStart;
	if(timeRecordIdx >= 100) timeRecordIdx = 0;
	timesRecorded++;

	if(timesRecorded >= 100) {
		double sum = 0.0;
		for(size_t i = 0; i < 100; i++) {
			sum += timeRecord[i];
		}
		sum /= 100;
		printf("average: %f\n", sum);
	}
	/*
	for (uint32_t i = 0; i < w->ballCount; i++) {
		for (uint32_t j = 0; j < w->ballCount; j++) {
			if (i == j) continue;
			attractBalls(&w->balls[i], &w->balls[j]);
		}
	}
	double testTime = GetTime() - timeStart;
	if (w->steps == 128) {
		double average = 0.0;
		for (uint32_t i = 0; i < 128; i++) {
			average += data[i];
		}
		average /= 128;
		printf("%lf\n", average);
		w->steps = 0;
	}
	data[w->steps] = testTime;
	w->steps++;
	*/
}
