#ifndef CAMERA_MOUSE_H_
#define CAMERA_MOUSE_H_

#include "Camera.h"

class CameraMouse : public Camera
{
public:

	CameraMouse();
	virtual ~CameraMouse();

	virtual void RefreshCamera(float DeltaT);

	void RefreshPosition(int as32_X, int as32_Y);
	void RefreshState(int as32_Button, int as32_State, int as32_X, int as32_Y);

protected:

	float	mf_Distance;//Distance from the lookat target
	float	mf_Theta;	//Rotation on the y axis
	float	mf_Phi;		//Rotation on the z axis

	bool	mb_ZoomActivated;
	bool	mb_RotateActvated;

	int		ms32_X; //Mouse coords
	int		ms32_Y;

private:
};

#endif //CAMERA_MOUSE_H_
