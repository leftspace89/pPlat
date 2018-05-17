#include "stdafx.h"
#include "Prediction.h"


Prediction::Prediction()
{
}


Prediction::~Prediction()
{
}

 RVector3 LinePrediction::Calculate(Obj_AI_Base * target,float range,float missilespeed,float casttime)
{
	float t = RVector3((target->GetPosition() - ObjectManager::GetPlayer()->GetPosition())).Length() /missilespeed;
	t += casttime;
	auto aim = *target->GetAIManager_Client();
          	auto comm = aim->GetActor();
	auto veloc =  *comm->GetVelocity();
	veloc.y = 0;
	RVector3 orientation = veloc.Normalize();//target->GetAllShield->vVelocity.Normalized();
											 //Normalize(orientation);
	if (!target->IsValidTarget(range))
		return RVector3(0, 0, 0);

	if ( veloc.x == 0  && veloc.z ==0 )
	{
		//ENGINE_MSG("GetServerPosition %f %f %f\n", orientation.x, orientation.y, orientation.z);
		//Beep(2000,200);
		
		return target->GetServerPosition();
	}
	int pcolor = 0xFF0000;
	lol::r3dDrawCircle.Call(&target->GetPosition(), 300, &pcolor, 0, 0, 0, 1);

	RVector3 result = target->GetPosition() + *target->GetCharData()->GetMoveSpeed() * orientation * t;

	D3DCOLOR predcolor = D3DCOLOR_ARGB(255, 0, 0, 255);
	RVector3 predict2d, local2d;
	render.r3dWorldToScreen(&result, &predict2d);
	render.r3dWorldToScreen(&target->GetPosition(), &local2d);
	render.DrawLine(local2d.x, local2d.y, predict2d.x, predict2d.y, 5, predcolor);

	if (result.Distance(ObjectManager::GetPlayer()->GetPosition()) > range)
		return RVector3(0, 0, 0);



	//ENGINE_MSG("result %f %f %f : time : %f\n", orientation.x, orientation.y, orientation.z,t);

	return result;
}

 RVector3 CirclePrediction::Calculate(Obj_AI_Base * target, float range, float missilespeed,float radius, float casttime)
 {


	 auto aim = *target->GetAIManager_Client();
	 auto comm = aim->GetActor();
	 auto veloc = *comm->GetVelocity();
	 veloc.y = 0;
	 RVector3 orientation = veloc.Normalize();//target->GetAllShield->vVelocity.Normalized();
											  //Normalize(orientation);
	 if (!target->IsValidTarget(range))
		 return RVector3(0, 0, 0);

	 if (veloc.x == 0 && veloc.z == 0)
	 {
		 return target->GetServerPosition();
	 }

	 RVector3 result = target->GetPosition() + *target->GetCharData()->GetMoveSpeed() * orientation  * casttime;
	
	 int pcolor = 0x0000FF;
	 lol::r3dDrawCircle.Call(&result, radius, &pcolor, 0, 0, 0, 1);

	 return result;
 }
