#include "CameraMouse.h"

#include <cmath>
#include <iostream>

#include "../ThirdParty/glut.h"

using namespace std;

CameraMouse::CameraMouse()
:	mf_Distance(10.0f)
,	mf_Theta(0.0f)
,	mf_Phi(3.141592f/16.0f)
,	mb_ZoomActivated(false)
,	mb_RotateActvated(false)
{}

void CameraMouse::RefreshCamera(float DeltaT)
{
	mo_Position.X() = mf_Distance * cos(mf_Phi) * sin(mf_Theta);
	mo_Position.Y() = mf_Distance * sin(mf_Phi);
	mo_Position.Z() = mf_Distance * cos(mf_Phi) * cos(mf_Theta);

	gluLookAt(	mo_Position.X(),mo_Position.Y(),mo_Position.Z(),
				0,0,0,
				0,1,0);
}

void CameraMouse::RefreshPosition(int as32_X, int as32_Y)
{
	if(mb_ZoomActivated || mb_RotateActvated)
	{
		int s32_DeltaX = as32_X - ms32_X;
		int s32_DeltaY = as32_Y - ms32_Y;

		ms32_X = as32_X;
		ms32_Y = as32_Y;

		if(mb_ZoomActivated)
		{
			mf_Distance += s32_DeltaY/20.0f;

			if(mf_Distance < 4)
			{
				mf_Distance = 4;
			}
			else if(mf_Distance > 30)
			{
				mf_Distance = 30;
			}
		}

		if(mb_RotateActvated)
		{
			mf_Phi += s32_DeltaY/200.0f;
			mf_Theta -= s32_DeltaX/100.0f;

			if(mf_Phi > 3.141592f/2.0f)
			{
				mf_Phi = 3.141592f/2.0f;
			}
			else if(mf_Phi < -3.141592f/2.0f)
			{
				mf_Phi = -3.141592f/2.0f;
			}
		}
	}
}

void CameraMouse::RefreshState(int as32_Button, int as32_State, int as32_X, int as32_Y)
{
	//cout << "Refresh State" << endl;
	if(as32_Button == GLUT_LEFT_BUTTON)
	{
		if(as32_State == GLUT_DOWN)
		{
			mb_RotateActvated = true;
			ms32_X = as32_X;
			ms32_Y = as32_Y;
		}
		else if (as32_State == GLUT_UP)
		{
			mb_RotateActvated = false;
		}
	}
	else if(as32_Button == GLUT_RIGHT_BUTTON)
	{
		if(as32_State == GLUT_DOWN)
		{
			mb_ZoomActivated = true;
			ms32_X = as32_X;
			ms32_Y = as32_Y;
		}
		else if(as32_State == GLUT_UP)
		{
			mb_ZoomActivated = false;
		}
	}
}

CameraMouse::~CameraMouse()
{
}
