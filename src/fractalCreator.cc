#include "fractalCreator.h"
#include <assert.h>

fractalCreator::fractalCreator(int width, int height):m_width(width), m_height(height), m_total(0),
					m_histogram(new int[mandelBrot::MAX_ITERATION]{0}), 
					m_fractal(new int[m_width * m_height]{0}), m_bmap(m_width, m_height), m_zoomlist(m_width, m_height)
{
	m_zoomlist.add(zoom(m_width/2, m_height/2, 4.0/m_width));
}

fractalCreator::~fractalCreator()
{

}

void fractalCreator::run(string name)
{

	calculateIteration();
	calculateTotalIterations();
	calculateRangeTotals();
	drawFractal();

	writeBitmap(name);
}

void fractalCreator::calculateIteration()
{
	for(int y = 0; y < m_height; y++){
		for(int x = 0; x < m_width; x++) {
			pair <double, double> coords = m_zoomlist.doZoom(x, y);

			int iteration = mandelBrot::getIterations(coords.first, coords.second);

			m_fractal[y * m_width + x] = iteration;

			if (iteration != mandelBrot::MAX_ITERATION)
				m_histogram[iteration]++;
		}
	}
}

void fractalCreator::calculateRangeTotals()
{
	int rangeIndex = 0;

	for(int i = 0; i < mandelBrot::MAX_ITERATION; i++) {
		int pixels = m_histogram[i];

		if (i >= m_ranges[rangeIndex + 1])
			rangeIndex++;

		m_rangeTotals[rangeIndex] += pixels;
	}
}

void fractalCreator::calculateTotalIterations()
{
	for(int i = 0; i < mandelBrot::MAX_ITERATION; i++)
		m_total += m_histogram[i];
}

int fractalCreator::getRange(int iterations) const
{
	int range = 0;

	for(int i = 0; i < m_ranges.size(); i++) {
		range = i;

		if (m_ranges[i] > iterations)
			break;
	}

	range--;
	assert(range >  -1);
	assert(range < m_ranges.size());

	return range;
}

void fractalCreator::drawFractal()
{
	for(int y = 0; y < m_height; y++){
		for(int x = 0; x < m_width; x++) {

			int iteration = m_fractal[y * m_width + x];

			int range = getRange(iteration);
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB &startColor = m_colors[range];
			RGB &endColor = m_colors[range + 1];

			RGB colorDiff = endColor - startColor;

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;
			

			if (iteration != mandelBrot::MAX_ITERATION) {

				int totalPixels = 0;


				for(int i = rangeStart; i <= iteration; i++) {
					totalPixels += m_histogram[i];
				}

				red = startColor.r + colorDiff.r * double(totalPixels) / rangeTotal;
				green = startColor.g + colorDiff.g * double(totalPixels) / rangeTotal;
				blue = startColor.b + colorDiff.b * double(totalPixels) / rangeTotal;
			}

			m_bmap.setPixel(x, y, red, green, blue);

		}
	}
}

void fractalCreator::addRange(double rangeEnd, const RGB &rgb)
{
	m_ranges.push_back(rangeEnd * mandelBrot::MAX_ITERATION);
	m_colors.push_back(rgb);

	if (m_bGotFirstRange) {
		m_rangeTotals.push_back(0);
	}

	m_bGotFirstRange = true;
}

void fractalCreator::addZoom(const zoom & zoom)
{
	m_zoomlist.add(zoom);
}

void fractalCreator::writeBitmap(string filename)
{
	m_bmap.write(filename);
}
