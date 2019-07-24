#include <PrecompiledHeaders.h>

#include "Line3D.h"
#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	Line3D::Line3D(double x1, double y1, double z1, double x2, double y2, double z2){
		a = x2 - x1;
		b = y2 - y1;
		c = z2 - z1;

		x0 = x1;
		y0 = y1;
		z0 = z1;
	}

	Line3D::~Line3D(){

	}

	void Line3D::getLineFromXComponent(double value, double* vector){
		double t;
		vector[0] = value;
		if(a == 0){
			vector[1] = y0;
			vector[2] = z0;
			return;
		}
		t = (value - x0) / a;
		vector[1] = b * t + y0;
		vector[2] = c * t + z0;
	}

	void Line3D::getLineFromYComponent(double value, double* vector){
		double t;
		vector[1] = value;
		if(b == 0){
			vector[0] = x0;
			vector[2] = z0;
			return;
		}
		t = (value - y0) / b;
		vector[0] = a * t + x0;
		vector[2] = c * t + z0;
	}

	void Line3D::getLineFromZComponent(double value, double* vector){
		double t;
		vector[2] = value;
		if(c == 0){
			vector[0] = x0;
			vector[1] = y0;
			return;
		}
		t = (value - z0) / c;
		vector[0] = a * t + x0;
		vector[1] = b * t + y0;
	}

	bool Line3D::intersectsBox(double x, double y, double z, double width, double height, double depth){
		double point[3];

		// Bottom face.
		getLineFromZComponent(z + depth, point);
		if(Utils::isInRect((float) point[0], (float) point[1], (float) x, (float) y, (float) x + (float) width, (float) y + (float) height)) return true;

		// Top face.
		getLineFromZComponent(z, point);
		if(Utils::isInRect((float) point[0], (float) point[1], (float) x, (float) y, (float) x + (float) width, (float) y + (float) height)) return true;

		// Front face.
		getLineFromYComponent(y + height, point);
		if(Utils::isInRect((float) point[0], (float) point[2], (float) x, (float) z, (float) x + (float) width, (float) z + (float) depth)) return true;

		// Back face.
		getLineFromYComponent(y, point);
		if(Utils::isInRect((float) point[0], (float) point[2], (float) x, (float) z, (float) x + (float) width, (float) z + (float) depth)) return true;

		// Left face.
		getLineFromXComponent(x, point);
		if(Utils::isInRect((float) point[1], (float) point[2], (float) y, (float) z, (float) y + (float) height, (float) z + (float) depth)) return true;

		return false;
	}
}