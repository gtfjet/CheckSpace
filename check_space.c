#include <stdio.h>
#include <math.h>
#include <windows.h>
#define PI 3.14159265359
#define NUMP 100
#define RADIUS 10

double X[NUMP], Y[NUMP];

void draw(HDC h) {
	double x[360],  y[360];
	for(int i=0; i<NUMP; i++) {
		for(int theta=0; theta<360; theta++) {
			x[theta] = X[i] + RADIUS*sin(theta*PI/180);
			y[theta] = Y[i] + RADIUS*cos(theta*PI/180);
			SetPixelV(h, x[theta], y[theta], RGB(0,255,0)); 
		}
	}
}

void main(){
	HDC hdc = GetDC(NULL);
	for(int i=0; i<NUMP; i++) {
		X[i] = 20*i;
		Y[i] = 500;
	}
	while(1) { draw(hdc); }
}

