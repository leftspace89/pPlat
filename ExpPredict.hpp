#pragma once
#ifndef EXPREDICT
#define EXPREDICT

enum  Hitchance
{
	VeryLow,
	Medium,
	High,
	VeryHigh,
	Collision,
	OutOfRange,
	Impossible
};
enum  SkillType
{
	Line,
	Circle,
};
class PredictionInput
{
public:
	float Speed;

	float Radius;

	 float Delay;

	float Range;

	 Obj_AI_Base* Target;

	 SkillType SkillType_ = SkillType::Line;

	 RVector3 _from;
};

class PredictionOutput
{
public:
	PredictionInput Input;

	Hitchance Hitchance_ = Hitchance::VeryLow;

	RVector3 MousePosition;

	RVector3 TargetPosition;

	RVector3 CollisionPoint;
	PredictionOutput(PredictionInput in,RVector3 mpos,RVector3 tpos, Hitchance hit)
	{
		this->Input = in;
		this->Hitchance_ = hit;
		this->MousePosition = mpos;
		this->TargetPosition = tpos;
	}

};

class ExpPrediction
{
public:
#ifdef xp
	public static PredictionOutput GetPrediction(PredictionInput input, bool includePing=false)
	{
		PredictionOutput result = new PredictionOutput();

		if (!input.Target.IsValidTarget(float.MaxValue, input.From))
		{
			result.Hitchance = Hitchance::Impossible;
			return result;
		}



		if (Vector2.Distance(input.Target.WorldPosition, input.From) > input.Range * 1.4f)
		{
			result.Input = input;
			result.Hitchance = Hitchance.OutOfRange;
			return result;
		}

		//TODO: Check immobile & dashing

		result = GetStandardPrediction(input);

		if (Math.Abs(input.Range - float.MaxValue) > float.Epsilon)
		{
			if (result.Hitchance >= Hitchance.High
				&& Vector2.Distance(input.From, input.Target.WorldPosition) > input.Range * input.Radius * 3 / 4) //Use ScreenPosition instead?
			{
				result.Hitchance = Hitchance.Medium;
			}

			if (Vector2.Distance(input.From, result.TargetPosition) > input.Range + (input.SkillType == SkillType.Circle ? input.Radius : 0))
			{
				result.Hitchance = Hitchance.OutOfRange;
			}

			if (Vector2.Distance(input.From, result.MousePosition) > input.Range)
			{
				if (result.Hitchance != Hitchance.OutOfRange)
				{
					result.MousePosition = input.From + input.Range * (result.TargetPosition - input.From).Normalized;
				}
				else
				{
					result.Hitchance = Hitchance.OutOfRange;
				}
			}
		}

		if (input.CollidesWith != 0)
		{
			auto colResult = CollisionSolver.CheckThickLineCollision(input.From, result.MousePosition, input.Radius, input.CollidesWith);

			if (colResult.IsColliding)
			{
				result.CollisionPoint = colResult.CollisionPoint;

				result.Hitchance = Hitchance.Collision;
			}
		}

		result.MousePosition = result.MousePosition.WorldToScreen();

		return result;
	}

	
#endif
	static PredictionOutput GetStandardPrediction(PredictionInput input)
	{
		auto aibase = *input.Target->GetAIManager_Client();
		auto velocityV = *aibase->GetVelocity();
		auto velocity = velocityV.To2D();

		auto speed = velocity.Length();

		auto xDir = velocity.x == 0 ? 100 : velocity.x > 0 ? 1 : -100;
		auto yDir = velocity.y == 0 ? 100: velocity.y > 0 ? 1 : -100;
		auto dirVector = RVector3(xDir, yDir,0);

		auto extendedPos = RVector3(input.Target->GetPosition() + dirVector).To2D();

		auto result = GetPositionOnDirection(input, extendedPos, speed);

		return result;
}
	struct MovementColl
	{
		float t1;
		RVector3* second;
	};

	static MovementColl VectorMovementCollision(
		RVector3 startPoint1,
		RVector3 endPoint1,
		float v1,
		RVector3 startPoint2,
		float v2,
		float delay = 0)
	{
		float sP1x = startPoint1.x,
			sP1y = startPoint1.y,
			eP1x = endPoint1.x,
			eP1y = endPoint1.y,
			sP2x = startPoint2.x,
			sP2y = startPoint2.y;

		float d = eP1x - sP1x, e = eP1y - sP1y;
		float dist = (float)sqrt(d * d + e * e), t1 = NAN;
		float S = abs(dist) > FLT_EPSILON ? v1 * d / dist : 0,
			K = (abs(dist) > FLT_EPSILON) ? v1 * e / dist : 0;

		float r = sP2x - sP1x, j = sP2y - sP1y;
		auto c = r * r + j * j;

		if (dist > 0)
		{
			if (abs(v1 -FLT_MAX) < FLT_EPSILON)
			{
				auto t = dist / v1;
				t1 = v2 * t >= 0 ? t : NAN;
			}
			else if (abs(v2 - FLT_MAX) < FLT_EPSILON)
			{
				t1 = 0;
			}
			else
			{
				float a = S * S + K * K - v2 * v2, b = -r * S - j * K;

				if (abs(a) < FLT_EPSILON)
				{
					if (abs(b) < FLT_EPSILON)
					{
						t1 = (abs(c) < FLT_EPSILON) ? 0 :NAN;
					}
					else
					{
						auto t = -c / (2 * b);
						t1 = (v2 * t >= 0) ? t : NAN;
					}
				}
				else
				{
					auto sqr = b * b - a * c;
					if (sqr >= 0)
					{
						auto nom = (float)sqrt(sqr);
						auto t = (-nom - b) / a;
						t1 = v2 * t >= 0 ? t :NAN;
						t = (nom - b) / a;
						auto t2 = (v2 * t >= 0) ? t : NAN;

						if (!isnan(t2) && !isnan(t1))
						{
							if (t1 >= delay && t2 >= delay)
							{
								t1 = min(t1, t2);
							}
							else if (t2 >= delay)
							{
								t1 = t2;
							}
						}
					}
				}
			}
		}
		else if (abs(dist) <FLT_EPSILON)
		{
			t1 = 0;
		}

		return MovementColl{ t1, (!isnan(t1)) ? new RVector3(sP1x + S * t1, sP1y + K * t1,0) : new RVector3() };
	}
	static PredictionOutput GetPositionOnDirection(PredictionInput input, RVector3 extendedPosition, float targetSpeed)
	{
		auto aibase = *input.Target->GetAIManager_Client();
		auto velocityV = *aibase->GetVelocity();
		auto velocity = velocityV.To2D();
		if (velocity == RVector3(0, 0, 0))
		{
			return PredictionOutput(
				input,
				input.Target->GetPosition(),
				input.Target->GetPosition(),
				Hitchance::VeryHigh
			);
		}

		if (abs(input.Speed - FLT_MAX) < FLT_EPSILON)
		{
			auto distance = input.Delay * targetSpeed - input.Radius;

			auto a = input.Target->GetPosition().To2D();
			auto b = extendedPosition;
			auto vectorDist = a.Distance(b);
			auto direction = RVector3((b - a)).Normalize();
			auto unitPos = a + direction * distance;

			return  PredictionOutput(

				input,
				unitPos,
				unitPos,
				Hitchance::High
			);
		}

		if (abs(input.Speed - FLT_MAX) > FLT_EPSILON)
		{
			auto distance = input.Delay * targetSpeed - input.Radius;

			auto a = input.Target->GetPosition().To2D();
			auto b = extendedPosition;
			auto time = a.Distance(b) / targetSpeed;
			auto direction = RVector3(RVector3((b - a)).Normalize());
			auto c = a - targetSpeed * time * direction;

			auto solution = VectorMovementCollision(c, b, targetSpeed, input._from, input.Speed, time);
			auto tSol = (float)solution.t1;
			auto pos =	solution.second;

			if (*pos != RVector3(0,0,0) && tSol >= time && tSol <= time * 2)
			{
				auto p = RVector3(*pos + input.Radius * direction);

				return  PredictionOutput(
					  input,
					  p,
					  *pos,
					  Hitchance::High
				);
			}
		}

		return  PredictionOutput(
			  input,
			  extendedPosition,
			 extendedPosition,
			  Hitchance::Medium
		);
	}
};
#endif