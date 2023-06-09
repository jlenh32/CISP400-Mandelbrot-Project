#include "ComplexPlane.h"
using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
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

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ssText;
	ssText << "Mandelbrot Set\n"
		<< "Center: (" << m_view.getCenter().x << ", " << (m_view.getCenter().y * -1) << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << (m_mouseLocation.y * -1) << ")\n"
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
	float colorScale = count * 4 - 1;
	if (colorScale < 60.0)
	{
		r = 50 * (colorScale / 60.0);
		g = 50 * (colorScale / 60.0);
		b = 75;
	}
	else if (colorScale < 120.0)
	{
		r = 255;
		g = 255 - 255 * ((colorScale - 60.0) / 60.0);
		b = 0;
	}
	else if (colorScale < 180.0)
	{
		r = 150;
		g = 100 * ((colorScale - 120.0) / 60.0);
		b = 0;
	}
	else if (colorScale < 240.0)
	{
		r = 135 - 135 * ((colorScale - 180.0) / 60.0);
		g = 0;
		b = 125;
	}
	else if (colorScale < 255.0)
	{
		r = 50 * ((colorScale - 240.0) / 60.0);
		g = 0;
		b = 50;
	}
	else
	{
		r = 0;
		g = 0;
		b = 0;
	}
}
