#pragma once
#include "LSRender.h"
#include "Logging.hpp"
class LinePrediction
{
public:

	static struct LineInfo_t
	{
		SpellData*data;
	};

	LinePrediction()
	{

	}
	float Length(RVector3&vec)
	{
		return (float)sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}

	void Normalize(RVector3&vec)
	{
		float length = Length(vec);
		if (length != 0)
		{
			float inv = 1.0f / length;
			vec.x *= inv;
			vec.y *= inv;
			vec.z *= inv;
		}
	}
	
	RVector3 Calculate(Obj_AI_Base * target, float range, float missilespeed, float casttime);



	~LinePrediction()
	{
	}

private:


};

class CirclePrediction
{
public:



	float Length(RVector3&vec)
	{
		return (float)sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}

	void Normalize(RVector3&vec)
	{
		float length = Length(vec);
		if (length != 0)
		{
			float inv = 1.0f / length;
			vec.x *= inv;
			vec.y *= inv;
			vec.z *= inv;
		}
	}

	RVector3 Calculate(Obj_AI_Base * target, float range, float missilespeed, float radius, float casttime);

	CirclePrediction()
	{
	}

	~CirclePrediction()
	{
	}

private:


	

};

class Prediction
{


public:
	Prediction();
	~Prediction();

	Prediction(LinePrediction* pred)
	{
		LinePred = pred;
	}
	Prediction(CirclePrediction* pred)
	{
		CircPred = pred;
	}

	enum CollisionType
	{
		Minion
	};
	bool BoundBox(D3DXVECTOR2 cursorPos, D3DXVECTOR2 Pos, D3DXVECTOR2 Size)
	{
		return Pos.x >= cursorPos.x - Size.x && Pos.x <= cursorPos.x + Size.x && Pos.y >= cursorPos.y - Size.y && Pos.y <= cursorPos.y + Size.y /*sol*/ &&  cursorPos.x >= Pos.x /*üst*/ && cursorPos.y >= Pos.y;
	}
	 bool PointInLineSegment(D3DXVECTOR2 segmentStart, D3DXVECTOR2 segmentEnd, D3DXVECTOR2 point)
	{
		
		auto crossproduct = (point.y - segmentStart.y) * (segmentEnd.x - segmentStart.x) - (point.x - segmentStart.x) * (segmentEnd.y - segmentStart.y);
		if (abs(crossproduct) > 2)
		{
			return false;
		}

		auto dotproduct = (point.x - segmentStart.x) * (segmentEnd.x - segmentStart.x) + (point.y - segmentStart.y) * (segmentEnd.y - segmentStart.y);
		if (dotproduct < 0)
		{
			return false;
		}

		auto squaredlengthba = (segmentEnd.x - segmentStart.x) * (segmentEnd.x - segmentStart.x) + (segmentEnd.y - segmentStart.y) * (segmentEnd.y - segmentStart.y);
		if (dotproduct > squaredlengthba)
		{
			return false;
		}

		return true;
	}
	  bool PointOnLineSegment(D3DXVECTOR2 pt1, D3DXVECTOR2 pt2, D3DXVECTOR2 pt, double epsilon = 0.001)
	 {
		 if (pt.x - std::fmax(pt1.x, pt2.x) > epsilon ||
			std::fmin(pt1.x, pt2.x) - pt.x > epsilon ||
			 pt.y - std::fmax(pt1.y, pt2.y) > epsilon ||
			 std::fmin(pt1.y, pt2.y) - pt.y > epsilon)
			 return false;

		 if (abs(pt2.x - pt1.x) < epsilon)
			 return abs(pt1.x - pt.x) < epsilon || abs(pt2.x - pt.x) < epsilon;
		 if (abs(pt2.y - pt1.y) < epsilon)
			 return abs(pt1.y - pt.y) < epsilon || abs(pt2.y - pt.y) < epsilon;

		 double x = pt1.x + (pt.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y);
		 double y = pt1.y + (pt.x - pt1.x) * (pt2.y - pt1.y) / (pt2.x - pt1.x);

		 return abs(pt.x - x) < epsilon || abs(pt.y - y) < epsilon;
	 }

	bool IsCollisioned(CollisionType type ,RVector3 vec,float radius)
	{
		auto local = ObjectManager::GetPlayer();
		switch (type)
		{
		case Minion:
		{
			for (GameObject*minion : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies))
			{ 
				
				
				auto base = (Obj_AI_Base*)minion;
				auto basecord = base->GetPosition();//LinePred->Calculate(base);
			


				RVector3 pt1,pt2,pt;
				if (!render.r3dWorldToScreen(&basecord, &pt))
					continue;

				render.r3dWorldToScreen(&local->GetPosition(), &pt1);
				render.r3dWorldToScreen(&vec, &pt2);
#ifdef linepred
				render.DrawLine(pt.x, pt.y, pt2.x, pt2.y, 10, D3DCOLOR_ARGB(255, 255, 20, 147));
				render.DrawLine(pt2.x, pt2.y, pt1.x, pt1.y, 10, D3DCOLOR_ARGB(255, 255, 165, 0));
#endif

				if (PointOnLineSegment(D3DXVECTOR2(pt1.x,pt1.y), D3DXVECTOR2(pt2.x,pt2.y), D3DXVECTOR2(pt.x,pt.y),radius))
				{
					return true;
				}
				


			}
			break;
		}
		}

		return false;
	}

	LinePrediction* LinePred;
	CirclePrediction* CircPred;
};

