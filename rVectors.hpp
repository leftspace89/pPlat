#pragma once
#ifndef RVECTOR
#define RVECTOR
class RVector3 : public D3DXVECTOR3
{
public:
	RVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	RVector3(D3DXVECTOR3 vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	RVector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	RVector3(float X, float Z)
	{
		x = X;
		y = 0;
		z = Z;
	}

	float Length()
	{
		return (float)sqrt((x * x) + (y * y) + (z * z));
	}
	float Distance(RVector3 b)
	{
		RVector3 vector = RVector3(x - b.x, y - b.y, z - b.z);
		return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}
	D3DXVECTOR3 Normalize()
	{
		float length = Length();
		if (length != 0)
		{
			float inv = 1.0f / length;
			x *= inv;
			y *= inv;
			z *= inv;
		}
		return D3DXVECTOR3(x, y, z);
	}
	RVector3 perpendicularTo()
	{
		return RVector3(z, y, -x);
	}

	RVector3 To2D()
	{
		return RVector3(x, z,0);
	}


};
#endif // kuçu korumasý