#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace Utils
{

	struct Color
	{
		float r, g, b, a;
		Color(float R, float G, float B, float A):
		r(R),
			g(G),
			b(B),
			a(A)
		{
		}

		Color():
		r(0.0f),
			g(0.0f),
			b(0.0f),
			a(0.0f)
		{

		}
	};

}
#endif