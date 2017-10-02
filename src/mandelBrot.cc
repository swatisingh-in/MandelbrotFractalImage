#include "mandelBrot.h"
#include <complex>

using namespace std;

mandelBrot::mandelBrot()
{

}

int mandelBrot::getIterations(double x, double y)
{
	complex<double> z{0};
	complex<double> c(x, y);

	int iteration = 0;

	while(iteration < MAX_ITERATION){
		z = z * z + c;

		if (abs(z) > 2)
			break;
		
		iteration++;
	}

  	return iteration;
}

mandelBrot::~mandelBrot()
{

}
