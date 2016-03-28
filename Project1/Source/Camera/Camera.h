#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Foundation/Vector3.h"

class Camera
{
public:

	virtual void	RefreshCamera(float DeltaT) = 0;

	void			SetPosition(const Vector3& ao_Position);
	Vector3			GetPosition() const;

	void			SetLookAt(const Vector3& ao_LookAt);
	Vector3			GetLookAt() const;

protected:

	Vector3 mo_Position;
	Vector3 mo_LookAt;
};

inline void Camera::SetPosition(const Vector3& ao_Position)
{
	mo_Position = ao_Position;
}

inline Vector3 Camera::GetPosition() const
{
	return mo_Position;
}

inline void Camera::SetLookAt(const Vector3& ao_LookAt)
{
	mo_LookAt = ao_LookAt;
}

inline Vector3 Camera::GetLookAt() const
{
	return mo_LookAt;
}



#endif //CAMERA_H_
