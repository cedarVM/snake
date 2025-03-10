#include "ssw.h"

#define uint unsigned int
#define uchar unsigned char

float FISR(float n) { // this is not my code
	float xhalf = 0.5f * n;
	int i = *(int*)&n;            // store floating-point bits in integer
	i = 0x5f375a85 - (i >> 1);    // initial guess for Newton's method
	n = *(float*)&i;              // convert new bits into float
	n = n*(1.5f - xhalf*n*n);     // One round of Newton's method
	return n;
} // this is not my code

int adjpow(uint n) {
int p;
char i = sizeof(p)*8-1;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

XGCValues mask_values;
Pixmap snake_mask;
GC mask_gc;

void drawcurve(unsigned long rgb, uint *x, uint *y, uchar n, int sec, int size, Pixmap *board, GC *boardgc) {
struct exposepoint *context = (struct exposepoint *)Exposure();

snake_mask = XCreatePixmap(context[0].dis, context[0].win, WW(0), WH(0), 1);
mask_gc = XCreateGC(context[0].dis, snake_mask, 0, &mask_values);
XSetForeground(context[0].dis, mask_gc, 1);
XSetBackground(context[0].dis, mask_gc, 0);

float xslice[n + 1];
float yslice[n + 1];
float t, tc, totx, toty;
tc = (float)1.0/adjpow(size);
int xc;
int yc;

	for (t = 0; (uint)t==0; t+=tc) {
	xslice[0] = 1;
	yslice[0] = 1;
	xc = 1;
		while (xc < n) {
		xslice[xc] = t * xslice[xc - 1] * (n - xc) / xc;
		yslice[xc] = xslice[xc];
		xc++;
		}
	xc = 0;
		while (xc < n) {
		xslice[xc]*=x[xc];
		yslice[xc]*=y[xc];
		xc++;
		}
	totx=xslice[n - 1];
	toty=yslice[n - 1];
	xc = 0;
		while (xc < n - 1) {
			for (yc = 0; yc < n - xc - 1; yc++) {
			xslice[xc]*=(1 - t);
			yslice[xc]*=(1 - t);
			}
		totx+=xslice[xc];
		toty+=yslice[xc];
		xc++;
		}

		xc = -1*sec/2;
		while (xc < sec/2 + 1) {
		yc = (sec*sec/4-xc*xc)*FISR(sec*sec/4-xc*xc);
		// RegionFill((uint)(totx+xc), (uint)(toty-yc), 1, (uint)(2*yc), rgb, win);
		XFillRectangle(context[0].dis, snake_mask, mask_gc, (uint)(totx+xc), (uint)(toty-yc), 1, (uint)(2*yc));
		xc++;
		}

	XSetClipMask(context[0].dis, *boardgc, snake_mask); // boardgc
	XSetForeground(context[0].dis, *boardgc, rgb); // boardgc
	XFillRectangle(context[0].dis, *board, *boardgc, 0, 0, WW(0), WH(0)); // board, boardgc
	XSetClipMask(context[0].dis, *boardgc, 0); // last arg None // boardgc

	}
}
