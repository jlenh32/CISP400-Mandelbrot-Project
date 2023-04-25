#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

class ComplexPlane
{
	public: 
		ComplexPlane(float aspectRatio);
		void zoomIn();
		void zoomOut();
		void setCenter(Vector2f coord);
		View getView();
		void setMouseLocation(Vector2f coord);
		void loadText(Vector2f coord);
		size_t countIterations(Vector2f coord);
		void iteratorsToRGB(size_t count, Uint&& r, Uint&& g, Uint&& b);
	private:
		Vector2f m_mouseLocation;
		View m_view;
		int m_zoomCount;
		float m_aspectRatio;
		int width;
		int height;
};
