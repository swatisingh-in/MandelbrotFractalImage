#ifndef ZOOMLIST_H
#define ZOOMLIST_H

#include <vector>
#include <utility>
#include "zoom.h"

using namespace std;

class zoomList
{
	double m_xCenter{0};
	double m_yCenter{0};
	double m_scale{1.0};
	int m_width{0};
	int m_height{0};
	vector<zoom> zooms;

public:
	zoomList(int width, int height);
	
	void add(const zoom &zoom);

	pair<double, double> doZoom(int x, int y);
};


#endif