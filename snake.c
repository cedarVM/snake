#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ssw.h"
#include "bezier.h"

#include <time.h>
 
#include <X11/Xlib.h>

int main() {
int seed, add;
seed = (int)&add;
srand(seed);
struct cache c;
char xsnake[255];
char ysnake[255];
int xsnak[255];
int ysnak[255];
char dir = 3;
int i, j, secsize;
xsnake[0] = 19;
ysnake[0] = 15;
xsnake[1] = 20;
ysnake[1] = 15;
xsnake[2] = 0;
ysnake[2] = 0;
char xp = rand()%38 + 1;
char yp = rand()%28 + 1;

struct timespec init, end;

XI(0, "Snek", "Snek", 1440, 1080, 0, 0, 0);

struct exposepoint *context = (struct exposepoint *)Exposure();

XGCValues lol;
Pixmap board = XCreatePixmap(context[0].dis, context[0].win, WW(0), WH(0), 24);
GC boardgc = XCreateGC(context[0].dis, board, 0, &lol);

secsize = WW(0)/40;

	while (1) {
	secsize = WW(0)/40;
	XSetForeground(context[0].dis, boardgc, RGB(0,0,0));
	XFillRectangle(context[0].dis, board, boardgc, 0, 0, WW(0), WH(0));
	XSetForeground(context[0].dis, boardgc, RGB(255,255,255));
	XDrawRectangle(context[0].dis, board, boardgc, secsize, secsize, WW(0)-2*secsize, WW(0)*3/4-2*secsize);
	XFillRectangle(context[0].dis, board, boardgc, xp*secsize, yp*secsize, secsize, secsize);

		while (Pend(0)) {
		Eve(&c, 0);
			if (c.t == 1) {
			break;
			}
		}

		if (c.t==1) {
			if (c.txt==65362&&dir!=0&&dir!=2) {
			dir = 0;
			}
			if (c.txt==65363&&dir!=1&&dir!=3) {
			dir = 1;
			}
			if (c.txt==65364&&dir!=0&&dir!=2) {
			dir = 2;
			}
			if (c.txt==65361&&dir!=1&&dir!=3) {
			dir = 3;
			}
			if (c.txt==' ') {
				while (1) {
				Eve(&c, 0);
					if (c.txt==' ') {
					break;
					}
				}
			}

		}

		clock_gettime(CLOCK_MONOTONIC, &init);

		i = 2;
		
		while (xsnake[i]) {
		i++;
		}

		while (i - 1) {
		i--;
		xsnake[i] = xsnake[i - 1];
		ysnake[i] = ysnake[i - 1];
		}

		if (dir==0) {
		ysnake[0]--;
		}
		if (dir==1) {
		xsnake[0]++;
		}
		if (dir==2) {
		ysnake[0]++;
		}
		if (dir==3) {
		xsnake[0]--;
		}

		if (!xsnake[0]||!ysnake[0]||xsnake[0]>38||ysnake[0]>28) {
		goto gg;
		}

		i = 2;

		while (xsnake[i]) {
		i++;
		}

		j = i;

		while (i) {
			if (xsnake[0]==xsnake[i]&&ysnake[0]==ysnake[i]) {
			goto gg;
			}
		i--;
		}

		if (xsnake[0]==xp&&ysnake[0]==yp) {
			while (i < j) {
				xp = rand()%38 + 1;
				yp = rand()%28 + 1;
				i = 0;
				while (xsnake[i++]) {
					if (xsnake[i]==xp&&ysnake[i]==yp) {
					break;
					}
				}
				
			}
				
		i = 2;
			while (xsnake[i]) {
			i++;
			}
		xsnake[i] = xsnake[i - 1];
		ysnake[i] = ysnake[i - 1];
		xsnake[i + 1] = 0;
		ysnake[i + 1] = 0;
		}
		
		for (i = 0; xsnake[i]; i++) {
		xsnak[i] = xsnake[i] * secsize;
		ysnak[i] = ysnake[i] * secsize;
		}

	xsnak[i + 1] = 0;
	ysnak[i + 1] = 0;

		for (i = 0; xsnake[i]; i++) {
		xsnak[i]+=secsize/2;
		ysnak[i]+=secsize/2;
		}

	drawcurve(RGB(0, 255, 255), xsnak, ysnak, i, secsize, (i*secsize)>>1, &board, &boardgc);
	XCopyArea(context[0].dis, board, context[0].win, context[0].gc, 0, 0, WW(0), WH(0), 0, 0);
	XFlush(context[0].dis);
	clock_gettime(CLOCK_MONOTONIC, &end);
		//if (end - init > 50000) {
		//printf("Gettin rough\n");
		//}
		while ( (end.tv_sec - init.tv_sec) * 1000 + (end.tv_nsec - init.tv_nsec)/1000000 < 60 - i * 3) {
		//printf("had overtime: end: %d\n", end - init);
		clock_gettime(CLOCK_MONOTONIC, &end);
		}
	}
gg:
Clean(0);
XX(0);
}
