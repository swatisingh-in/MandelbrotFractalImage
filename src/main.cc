#include <iostream>
#include <random>
#include <cstdint>
#include "fractalCreator.h"
#include "zoom.h"

using namespace std;

int main(int argc, char const *argv[])
{
	fractalCreator fractalcreator(800, 600);

	fractalcreator.addRange(0.0, RGB(0, 0, 0));
	fractalcreator.addRange(0.3, RGB(255, 0, 0));
	fractalcreator.addRange(0.5, RGB(255, 255, 0));
	fractalcreator.addRange(1.0, RGB(255, 255, 255));

	fractalcreator.addZoom(zoom(295, 202, 0.1));
	fractalcreator.addZoom(zoom(312, 304, 0.1));
	fractalcreator.run("test.bmp");

	cout << "Finished!!!" << endl;
	return 0;
}