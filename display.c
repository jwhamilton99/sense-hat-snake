#include "sense.h"
#include <stdio.h>
#include <unistd.h>
#include "snake.h"

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF000
#define GREEN 0x0F00

pi_framebuffer_t *fb = NULL;

void openDisplay(void) {
   fb = getFrameBuffer();
}

void closeDisplay(void) {
   clearDisplay();
   freeFrameBuffer(fb);
}

void displaySnake(int pieces[][2], int snakeColor) {
	sense_fb_bitmap_t *bm = fb->bitmap;
	for(int i = 0; pieces[i][0] != -1; i++) {
		int color = snakeColor;
		if(i == 0) {
			color = GREEN;
		}
		bm->pixel[pieces[i][0]][pieces[i][1]] = color;
	}
}

void displayFood(int x, int y) {
	sense_fb_bitmap_t *bm = fb->bitmap;
	bm->pixel[x][y] = RED;
}

void clearDisplay(void) {
   clearFrameBuffer(fb,BLACK);
}
