#include "ComplexPlane.h"
using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float xVal = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float yVal = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(xVal, yVal);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float xVal = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float yVal = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(xVal, yVal);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ssText;
	ssText << "Mandelbrot Set\n"
		<< "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
		<< "Left-click to zoom in\n"
		<< "Right-click to zoom out";

	text.setString(ssText.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	size_t coordIter = 0;
	complex<double> z(0, 0);
	complex<double> c(coord.x, coord.y);
	for (int i = 0; i < MAX_ITER && abs(z) < 2.0; i++)
	{
		z = z * z + c;
		coordIter++;
	}

	return coordIter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	size_t colorScale = count * 4 - 1;
	if (colorScale < 60)
	{
		r = 255;
		g = 255 * (colorScale / 60.0);
		b = 0;
	}
	else if (colorScale < 120)
	{
		r = 255 - 255 * ((colorScale - 60.0) / 60.0)
		g = 255;
		b = 0;
	}
	else if (colorScale < 180)
	{
		r = 0;
		g = 255;
		b = 255 * ((colorScale - 120.0) / 60.0)
	}
}