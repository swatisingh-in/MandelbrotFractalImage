#ifndef MANDELBROT_H
#define MANDELBROT_H

class mandelBrot
{
public:
	static const int MAX_ITERATION{1000};
public:
	mandelBrot();
	~mandelBrot();

	static int getIterations(double x, double y);
	
};

#endif