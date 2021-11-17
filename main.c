#include <stdio.h>
#include <sense.h>
#include "snake.h"
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <time.h>

#define BLACK 0x0000
#define RED 0xF000
#define WHITE 0xFFFF
#define SCREENWIDTH 8
#define SCREENHEIGHT 8

int xInc = 1;
int yInc = 0;

int cacheXInc = 1;
int cacheYInc = 0;

int snakeColor = WHITE;

int foodX, foodY;

int dead = 0;

int len = 1;

void handler(unsigned int code) {
	switch(code) {
		case KEY_RIGHT:
			if(cacheYInc != -1) {
				yInc = 1;
				xInc = 0;
			}
			break;
		case KEY_LEFT:
			if(cacheYInc != 1) {
				yInc = -1;
				xInc = 0;
			}
			break;
		case KEY_UP:
			if(cacheXInc != 1) {
				xInc = -1;
				yInc = 0;
			}
			break;
		case KEY_DOWN:
			if(cacheXInc != -1) {
				xInc = 1;
				yInc = 0;
			}
			break;
	}
}

int pieces[65][2] = {
	{4, 4},
	{-1, -1}
};

void die() {
	dead = 1;
	snakeColor = RED;
}

void pushToStartOfArray(int x[2], int arr[][2]) {
	for(int i = len-1; i >= 0; i--) {
		if(x[0] == arr[i][0] && x[1] == arr[i][1]) { die(); break;}
		arr[i+1][0] = arr[i][0];
		arr[i+1][1] = arr[i][1];
	}
		arr[0][0] = x[0];
		arr[0][1] = x[1];
		arr[len][0] = -1;
		arr[len][1] = -1;
}

void makeNewFoodLocation(void);

void updateSnake() {
	int newHead[2] = {(pieces[0][0]+xInc), (pieces[0][1]+yInc)};

	if(newHead[0] == -1) {
		newHead[0] = SCREENWIDTH-1;
	} else if(newHead[0] == SCREENWIDTH) {
		newHead[0] = 0;
	}

	if(newHead[1] == -1) {
		newHead[1] = SCREENHEIGHT-1;
	} else if(newHead[1] == SCREENHEIGHT) {
		newHead[1] = 0;
	}

	if(newHead[0] == foodX && newHead[1] == foodY) {
		len++;
		makeNewFoodLocation();
	}

	pushToStartOfArray(newHead, pieces);
}

void makeNewFoodLocation() {
	foodX = (rand()%SCREENWIDTH);
	foodY = (rand()%SCREENHEIGHT);
}

int main(void) {
	srand(time(NULL));
	openDisplay();
	openJoystick();
	makeNewFoodLocation();
	int tick = 0;
	while(!dead) {
		checkJoystick(handler, 1);
		if(tick == 200) {
			cacheXInc = xInc;
			cacheYInc = yInc;
			tick = 0;
			clearDisplay();
			displaySnake(pieces, snakeColor);
			displayFood(foodX, foodY);
			updateSnake();
		}
		tick++;
	}
	clearDisplay();
	displaySnake(pieces, snakeColor);
	displayFood(foodX, foodY);
	sleep(2);

	closeDisplay();
	closeJoystick();
	return 0;
}
