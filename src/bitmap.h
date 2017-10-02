#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <cstdint>

using namespace std;

class bitmap
{
private:
	int m_height{0};
	int m_width{0};
	unique_ptr<uint8_t[]> m_pPixels;

public:
	bitmap(int width, int height);
	bool write(string filename);
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
	~bitmap();
};


#endif