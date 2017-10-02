#ifndef FRACTALCREATOR_H
#define FRACTALCREATOR_H

#include <iostream>
#include <math.h>
#include <vector>
#include "mandelBrot.h"
#include "bitmap.h"
#include "RGB.h"
#include "zoomList.h"
#include "zoom.h"

using namespace std;

class fractalCreator
{
	int m_width;
	int m_height;
	int m_total;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	bitmap m_bmap;
	zoomList m_zoomlist;
	vector<int> m_ranges;
	vector<RGB> m_colors;
	vector<int> m_rangeTotals;
	bool m_bGotFirstRange{false};

private:
	void calculateIteration();
	void calculateTotalIterations();
	void drawFractal();
	void writeBitmap(string filename);
	int getRange(int iterations) const;

public:
	fractalCreator(int width, int height);
	void run(string name);
	void addZoom(const zoom & zoom);
	void addRange(double rangeEnd, const RGB &rgb);
	void calculateRangeTotals();
	~fractalCreator();
	
};

#endif