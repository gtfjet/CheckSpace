#include <stdio.h>
#include <math.h>
#include <windows.h>
#define PI 3.14159265359
#define NUMP 10
#define RADIUS 10

double X[NUMP], Y[NUMP], U[NUMP], V[NUMP], F[NUMP], G[NUMP];

double dist(int i, int j) {
	return(sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j])));
}

void step(double k, double dt) {
	double d;
	for(int i=0; i<NUMP; i++) {
		F[i] = 0;
		G[i] = 0;
		for(int j=0; j<NUMP; j++) {
			if(i==j) {
				d = X[i];
				if(d < RADIUS) { F[i] += (RADIUS-d); }
				d = Y[i];
				if(d < RADIUS) { G[i] += (RADIUS-d); }
				d = 1920 - X[i];
				if(d < RADIUS) { F[i] -= (RADIUS-d); }
				d = 1080 - Y[i];
				if(d < RADIUS) { G[i] -= (RADIUS-d); }
			} else {
				d = dist(i,j);
 				if(d < 2*RADIUS) {
					F[i] += (2*RADIUS-d)*(X[i]-X[j])/d;
					G[i] += (2*RADIUS-d)*(Y[i]-Y[j])/d;
				} 
			}
		}
	}
	for(int i=0; i<NUMP; i++) {
		U[i] += k*F[i]*dt;
		V[i] += k*G[i]*dt;
		X[i] += U[i]*dt;
		Y[i] += V[i]*dt;
	}
}

void draw(HDC hdc, HDC hdcMem) {
	double x[360],  y[360];
	for(int i=0; i<NUMP; i++) {
		for(int theta=0; theta<360; theta++) {
			x[theta] = X[i] + RADIUS*sin(theta*PI/180);
			y[theta] = Y[i] + RADIUS*cos(theta*PI/180);
			SetPixelV(hdc, x[theta], y[theta], RGB(0,255,0)); 
		}
	}
	BitBlt(hdc, 0, 0, 1920, 1080, hdcMem, 0, 0, SRCCOPY);
}

void main(){
	int count=0;
	HDC hdc    = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP bm = CreateCompatibleBitmap(hdc, 1920, 1080);
	SelectObject(hdcMem, bm);
	for(int i=0; i<NUMP; i++) {
		X[i] = 30*(i%50);
		Y[i] = i > 50 ? 500 : 1000;
		U[i] = 5;
		V[i] = -10;
	}	
	while(1) {
		count++;
		step(10,0.001);
		if(count%1000==0) { draw(hdc,hdcMem); }
	}
}

