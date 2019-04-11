#pragma once

#include <CloudMath.h>
#include <bullet/LinearMath/btVector3.h>

inline btVector3 ToBtVec(const CloudMath::Vector3f& p_vector3)
{
	return btVector3(p_vector3.x, p_vector3.y, p_vector3.z);
}

inline btQuaternion ToBtQuat(const CloudMath::Quaternion& p_quaternion)
{
	return btQuaternion(p_quaternion.GetXAxisValue(), p_quaternion.GetYAxisValue(),
	                    p_quaternion.GetZAxisValue(), p_quaternion.GetRealValue());
}

inline CloudMath::Vector3f ToVec3(const btVector3& p_vector3)
{
	return CloudMath::Vector3f(p_vector3.x(), p_vector3.y(), p_vector3.z());
}

inline CloudMath::Quaternion ToQuat(btQuaternion p_quaternion)
{
	return CloudMath::Quaternion(p_quaternion.x(), p_quaternion.y(),
	p_quaternion.z(), p_quaternion.w());
}
