#pragma once

namespace Mewtle{
	class Line3D{
		double x0 = 0, y0 = 0, z0 = 0;
		double a = 0, b = 0, c = 0;

	public :
		Line3D(double x1, double y1, double z1, double x2, double y2, double z2);
		~Line3D();

		void getLineFromXComponent(double value, double* vector);
		void getLineFromYComponent(double value, double* vector);
		void getLineFromZComponent(double value, double* vector);

		bool intersectsBox(double x, double y, double z, double width, double height, double depth);
	};
}