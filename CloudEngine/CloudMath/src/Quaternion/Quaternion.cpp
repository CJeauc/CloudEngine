#include "CloudMath/stdafx.h"
#include "CloudMath/Tools/MathUtils.h"
#include "CloudMath/Tools/Generics.h"
#include "CloudMath/Quaternion/Quaternion.h"

#pragma warning(push)
#pragma warning(disable: 4244)

namespace CloudMath
{
	Quaternion Quaternion::Identity()
	{
		return Quaternion(0, 0, 0, 1);
	}

#pragma region Constructors & Assignment
	Quaternion::Quaternion()
		: m_x(0), m_y(0), m_z(0), m_w(1) { }

	Quaternion::Quaternion(float p_x, float p_y, float p_z, float p_w)
		: m_x(p_x), m_y(p_y), m_z(p_z), m_w(p_w) { }

	Quaternion::Quaternion(const Quaternion& p_other)
	{
		m_x = p_other.m_x;
		m_y = p_other.m_y;
		m_z = p_other.m_z;
		m_w = p_other.m_w;
	}

	Quaternion::Quaternion(const Matrix3<float>& p_matrix)
	{
		if (abs(p_matrix.Determinant() - 1) > MathTools::Generics::Epsilon)
			throw std::logic_error("Cannot convert non-super-orthogonal Matrix3 to quaternion (Determinant != 1)");

		m_w = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 + p_matrix(0, 0) + p_matrix(1, 1) + p_matrix(2, 2))) * 0.5f;
		m_x = 0;
		m_y = 0;
		m_z = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 - p_matrix(0, 0) - p_matrix(1, 1) + p_matrix(2, 2))) * 0.5f;
		m_z = _copysign(m_z, p_matrix(1, 0) - p_matrix(0, 1));
	}

	Quaternion::Quaternion(const Matrix4<float>& p_matrix)
	{
		if (abs(p_matrix.Determinant() - 1) > MathTools::Generics::Epsilon)
			throw std::logic_error("Cannot convert non-super-orthogonal Matrix4 to quaternion (Determinant != 1)");

		m_w = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 + p_matrix(0, 0) + p_matrix(1, 1) + p_matrix(2, 2))) * 0.5f;
		m_x = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 + p_matrix(0, 0) - p_matrix(1, 1) - p_matrix(2, 2))) * 0.5f;
		m_y = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 - p_matrix(0, 0) + p_matrix(1, 1) - p_matrix(2, 2))) * 0.5f;
		m_z = sqrt(MathTools::MathUtils::ToZeroIfSmaller(1 - p_matrix(0, 0) - p_matrix(1, 1) + p_matrix(2, 2))) * 0.5f;

		m_x = _copysign(m_x, p_matrix(2, 1) - p_matrix(1, 2));
		m_y = _copysign(m_y, p_matrix(0, 2) - p_matrix(2, 0));
		m_z = _copysign(m_z, p_matrix(1, 0) - p_matrix(0, 1));
	}

	Quaternion::Quaternion(const Vector3<float>& p_axis, float p_angle)
	{
		p_angle = MathTools::MathUtils::ToRadians(p_angle);

		const float halfAngle = p_angle * 0.5f;
		float quotient = (0.31830988618f * 0.5f) * halfAngle;
		if (halfAngle >= 0.0f)
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		else
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));

		float y = halfAngle - (2.0f * MathTools::Generics::Pi) * quotient;

		float sign;

		if (y > 1.570796f)
		{
			y = MathTools::Generics::Pi - y;
			sign = -1.0f;
		}
		else if (y < -1.570796f)
		{
			y = -MathTools::Generics::Pi - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}
		const float y2 = y * y;

		const float sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2
			- 0.16666667f) * y2 + 1.0f) * y;
		const float precision = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) *
			y2 - 0.5f) * y2 + 1.0f;
		const float cos = sign * precision;

		m_x = sin * p_axis.x;
		m_y = sin * p_axis.y;
		m_z = sin * p_axis.z;
		m_w = cos;
	}

	Quaternion::Quaternion(const float& p_yawZ, const float& p_pitchY, const float& p_rollX)
	{
		const float halfYaw = float(MathTools::MathUtils::ToRadians(p_yawZ)) * float(0.5);
		const float halfPitch = float(MathTools::MathUtils::ToRadians(p_pitchY)) * float(0.5);
		const float halfRoll = float(MathTools::MathUtils::ToRadians(p_rollX)) * float(0.5);
		const float cosYaw = MathTools::MathUtils::Cos(halfYaw);
		const float sinYaw = MathTools::MathUtils::Sin(halfYaw);
		const float cosPitch = MathTools::MathUtils::Cos(halfPitch);
		const float sinPitch = MathTools::MathUtils::Sin(halfPitch);
		const float cosRoll = MathTools::MathUtils::Cos(halfRoll);
		const float sinRoll = MathTools::MathUtils::Sin(halfRoll);

		m_x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
		m_y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
		m_z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
		m_w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
	}

	Quaternion::Quaternion(const Vector3f& p_eulerAngle)
	{
		const float halfYaw = float(MathTools::MathUtils::ToRadians(p_eulerAngle.z)) * float(0.5);
		const float halfPitch = float(MathTools::MathUtils::ToRadians(p_eulerAngle.y)) * float(0.5);
		const float halfRoll = float(MathTools::MathUtils::ToRadians(p_eulerAngle.x)) * float(0.5);
		const float cosYaw = MathTools::MathUtils::Cos(halfYaw);
		const float sinYaw = MathTools::MathUtils::Sin(halfYaw);
		const float cosPitch = MathTools::MathUtils::Cos(halfPitch);
		const float sinPitch = MathTools::MathUtils::Sin(halfPitch);
		const float cosRoll = MathTools::MathUtils::Cos(halfRoll);
		const float sinRoll = MathTools::MathUtils::Sin(halfRoll);

		m_x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
		m_y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
		m_z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
		m_w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
	}

#pragma endregion

#pragma region Tests & Comparisons

	bool Quaternion::IsIdentity() const
	{
		return m_w == 1.f && Length() == 1.f;
	}

	bool Quaternion::IsPure() const
	{
		return m_w == 0.f && (m_x != 0.f || m_y != 0.f || m_z != 0.f);
	}

	bool Quaternion::IsNormalized() const
	{
		return abs(Length() - 1.0f) < MathTools::Generics::Epsilon;
	}

	bool Quaternion::operator==(const Quaternion& p_otherQuat) const
	{
		return m_x == p_otherQuat.m_x &&
			m_y == p_otherQuat.m_y &&
			m_z == p_otherQuat.m_z &&
			m_w == p_otherQuat.m_w;
	}

	bool Quaternion::operator!=(const Quaternion& p_otherQuat) const
	{
		return m_x != p_otherQuat.m_x ||
			m_y != p_otherQuat.m_y ||
			m_z != p_otherQuat.m_z ||
			m_w != p_otherQuat.m_w;
	}
#pragma endregion

#pragma region Arithmetic Operations

#pragma region Add
	Quaternion Quaternion::operator+(const Quaternion& p_otherQuat) const
	{
		return Quaternion(m_x + p_otherQuat.m_x, m_y + p_otherQuat.m_y,
		                  m_z + p_otherQuat.m_z, m_w + p_otherQuat.m_w);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& p_otherQuat)
	{
		m_x += p_otherQuat.m_x;
		m_y += p_otherQuat.m_y;
		m_z += p_otherQuat.m_z;
		m_w += p_otherQuat.m_w;
		return *this;
	}

#pragma endregion

#pragma region Substract
	Quaternion Quaternion::operator-(const Quaternion& p_otherQuat) const
	{
		return Quaternion(m_x - p_otherQuat.m_x, m_y - p_otherQuat.m_y,
		                  m_z - p_otherQuat.m_z, m_w - p_otherQuat.m_w);
	}

	Quaternion& Quaternion::operator-=(const Quaternion& p_otherQuat)
	{
		m_x -= p_otherQuat.m_x;
		m_y -= p_otherQuat.m_y;
		m_z -= p_otherQuat.m_z;
		m_w -= p_otherQuat.m_w;

		return *this;
	}
#pragma endregion

#pragma region Multiply
	float Quaternion::DotProduct(const Quaternion& p_otherQuat) const
	{
		return (m_x * p_otherQuat.m_x +
			m_y * p_otherQuat.m_y +
			m_z * p_otherQuat.m_z +
			m_w * p_otherQuat.m_w);
	}

	float Quaternion::DotProduct(const Quaternion& p_left, const Quaternion& p_right)
	{
		return (p_left.m_x * p_right.m_x +
			p_left.m_y * p_right.m_y +
			p_left.m_z * p_right.m_z +
			p_left.m_w * p_right.m_w);
	}

	float Quaternion::operator|(const Quaternion& p_otherQuat) const
	{
		return (m_x * p_otherQuat.m_x +
			m_y * p_otherQuat.m_y +
			m_z * p_otherQuat.m_z +
			m_w * p_otherQuat.m_w);
	}

	Quaternion Quaternion::operator*(const float p_scale) const
	{
		Quaternion result(*this);

		result.m_x *= p_scale;
		result.m_y *= p_scale;
		result.m_z *= p_scale;
		result.m_w *= p_scale;

		return result;
	}

	Quaternion& Quaternion::operator*=(const float p_scale)
	{
		m_x *= p_scale;
		m_y *= p_scale;
		m_z *= p_scale;
		m_w *= p_scale;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& p_otherQuat) const
	{
		return Quaternion(
			m_w * p_otherQuat.m_x + m_x * p_otherQuat.m_w + m_y * p_otherQuat.m_z - m_z * p_otherQuat.m_y,
			m_w * p_otherQuat.m_y - m_x * p_otherQuat.m_z + m_y * p_otherQuat.m_w + m_z * p_otherQuat.m_x,
			m_w * p_otherQuat.m_z + m_x * p_otherQuat.m_y - m_y * p_otherQuat.m_x + m_z * p_otherQuat.m_w,
			m_w * p_otherQuat.m_w - m_x * p_otherQuat.m_x - m_y * p_otherQuat.m_y - m_z * p_otherQuat.m_z);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& p_otherQuat)
	{
		return (*this = *this * p_otherQuat);
	}

	Vector3<float> Quaternion::operator*(const Vector3<float>& p_toMultiply) const
	{
		const float num = m_x * 2.0f;
		const float num2 = m_y * 2.0f;
		const float num3 = m_z * 2.0f;
		const float num4 = m_x * num;
		const float num5 = m_y * num2;
		const float num6 = m_z * num3;
		const float num7 = m_x * num2;
		const float num8 = m_x * num3;
		const float num9 = m_y * num3;
		const float num10 = m_w * num;
		const float num11 = m_w * num2;
		const float num12 = m_w * num3;

		Vector3<float> result;
		result.x = (1.f - (num5 + num6)) * p_toMultiply.x + (num7 - num12) * p_toMultiply.y + (num8 + num11) *
			p_toMultiply.z;
		result.y = (num7 + num12) * p_toMultiply.x + (1.f - (num4 + num6)) * p_toMultiply.y + (num9 - num10) *
			p_toMultiply.z;
		result.z = (num8 - num11) * p_toMultiply.x + (num9 + num10) * p_toMultiply.y + (1.f - (num4 + num5)) *
			p_toMultiply.z;
		return result;
	}

	Matrix3<float> Quaternion::operator*(const Matrix3<float>& p_multiply) const
	{
		return (ToMatrix3() * p_multiply);
	}

#pragma endregion

#pragma region Divide
	Quaternion& Quaternion::operator/=(const float p_scale)
	{
		if (p_scale == 0)
			throw std::logic_error("Division by 0");

		const float reciprocate = 1.0f / p_scale;
		m_x *= reciprocate;
		m_y *= reciprocate;
		m_z *= reciprocate;
		m_w *= reciprocate;

		return *this;
	}

	Quaternion Quaternion::operator/(const float p_scale) const
	{
		return (Quaternion(*this) /= p_scale);
	}

#pragma endregion

#pragma endregion

#pragma region Quaternion Operations

	Quaternion& Quaternion::Normalize()
	{
		const float length = this->Length();

		if (length != 0)
			return *this /= length;

		return *this;
	}

	Quaternion Quaternion::Normalize(const Quaternion& p_quaternion)
	{
		Quaternion result(p_quaternion);
		return result.Normalize();
	}

	float Quaternion::Length() const
	{
		return MathTools::MathUtils::SquareRootF(LengthSquare());
	}

	float Quaternion::LengthSquare() const
	{
		return (m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	float Quaternion::GetAngle() const
	{
		return 2.f * MathTools::MathUtils::Arccos(m_w);
	}

	Quaternion& Quaternion::Inverse()
	{
		const float norm = LengthSquare();
		Conjugate();

		if (norm == 0)
			throw std::logic_error("Division by 0");

		return *this /= norm;
	}

	Quaternion Quaternion::Inverse(const Quaternion& p_quaternion)
	{
		Quaternion result(p_quaternion);
		return result.Inverse();;
	}

	Quaternion Quaternion::Conjugate(const Quaternion& p_quaternion)
	{
		Quaternion result(p_quaternion);
		return result.Conjugate();
	}

	Quaternion& Quaternion::Conjugate()
	{
		m_x *= -1;
		m_y *= -1;
		m_z *= -1;
		return *this;
	}

	Quaternion& Quaternion::Square()
	{
		return *this *= *this;
	}

	Quaternion Quaternion::Square(const Quaternion& p_quaternion)
	{
		Quaternion result(p_quaternion);
		return result.Square();
	}

	void Quaternion::GetAxisAndAngle(Vector3<float>& p_axis, float& p_angle) const
	{
		p_angle = GetAngle();
		p_axis = GetRotationAxis();
	}

	Vector3<float> Quaternion::GetAxisZ() const
	{
		return RotateVector(Vector3<float>(0.f, 0.f, 1.f));
	}

	Vector3<float> Quaternion::GetAxisY() const
	{
		return RotateVector(Vector3<float>(0.f, 1.f, 0.f));
	}

	Vector3<float> Quaternion::GetAxisX() const
	{
		return RotateVector(Vector3<float>(1.f, 0.f, 0.f));
	}

	Vector3<float> Quaternion::GetForwardVector() const
	{
		return GetAxisZ();
	}

	Vector3<float> Quaternion::GetRightVector() const
	{
		return GetAxisX();
	}

	Vector3<float> Quaternion::GetUpVector() const
	{
		return GetAxisY();
	}

	Vector3<float> Quaternion::GetRotationAxis() const
	{
		const float S = MathTools::MathUtils::SquareRoot(std::max(1.f - (m_w * m_w), 0.f));

		if (S >= MathTools::Generics::Epsilon)
		{
			return Vector3<float>(m_x / S, m_y / S, m_z / S);
		}

		return Vector3<float>(1.f, 0.f, 0.f);
	}

	float Quaternion::AngularDistance(const Quaternion& p_other) const
	{
		const float innerProd = (*this | p_other);
		return MathTools::MathUtils::Arccos((2 * innerProd * innerProd) - 1.f);
	}

	float Quaternion::GetXAxisValue() const
	{
		return m_x;
	}

	float Quaternion::GetYAxisValue() const
	{
		return m_y;
	}

	float Quaternion::GetZAxisValue() const
	{
		return m_z;
	}

	float Quaternion::GetRealValue() const
	{
		return m_w;
	}

	void Quaternion::SetXAxisValue(float p_xValue)
	{
		m_x = p_xValue;
	}

	void Quaternion::SetYAxisValue(float p_yValue)
	{
		m_y = p_yValue;
	}

	void Quaternion::SetZAxisValue(float p_zValue)
	{
		m_z = p_zValue;
	}

	void Quaternion::SetRealValue(float p_realValue)
	{
		m_w = p_realValue;
	}

	Quaternion Quaternion::Lerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha)
	{
		if (!p_first.IsNormalized())
			p_first.Normalize();
		if (!p_second.IsNormalized())
			p_second.Normalize();

		const Quaternion src = p_first * (1.0f - p_alpha);
		const Quaternion dst = p_second * p_alpha;

		Quaternion q = src + dst;
		return q;
	}

	Quaternion Quaternion::Slerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha)
	{
		if (!p_first.IsNormalized())
			p_first.Normalize();
		if (!p_second.IsNormalized())
			p_second.Normalize();

		bool inverseSecond = false;
		float dotProductResult = p_first | p_second;
		Quaternion temp;
		if (dotProductResult < 0.0f)
		{
			inverseSecond = true;
			dotProductResult *= -1;
			temp = p_second * -1.f;
		}

		if (dotProductResult > 0.9998)
		{
			Quaternion result = p_first + ((inverseSecond ? temp : p_second) - p_first) * p_alpha;
			result.Normalize();
			return result;
		}

		const float angleBetweenTwoQuats = MathTools::MathUtils::Arccos(dotProductResult);
		const float angleBetweenFirstAndDot = angleBetweenTwoQuats * p_alpha;
		const float sinusAngleBetweenFirstAndDot = MathTools::MathUtils::Sin(angleBetweenFirstAndDot);
		const float sinusAngleBetweenTowQuats = MathTools::MathUtils::Sin(angleBetweenTwoQuats);

		const float sinusFirst = MathTools::MathUtils::Cos(angleBetweenFirstAndDot) - dotProductResult *
			sinusAngleBetweenFirstAndDot / sinusAngleBetweenTowQuats;
		const float sinusSecond = sinusAngleBetweenFirstAndDot / sinusAngleBetweenTowQuats;
		if (inverseSecond)
		{
			return (p_first * sinusFirst) + (temp * sinusSecond);
		}
		return (p_first * sinusFirst) + (p_second * sinusSecond);
	}

	Quaternion Quaternion::Nlerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha)
	{
		Quaternion calculated(Lerp(p_first, p_second, p_alpha));
		calculated.Normalize();
		return calculated;
	}

	Vector3<float> Quaternion::RotateRelativeToPivot(const Vector3<float>& p_position,
	                                                 const Vector3<float>& p_pivot) const
	{
		Vector3<float> toRotate = p_position - p_pivot;
		return this->RotateVector(toRotate);
	}

	Vector3<float> Quaternion::RotateRelativeToPivot(const Vector3<float>& p_position, const Vector3<float>& p_pivot,
	                                                 const Vector3<float>& p_eulerAngles)
	{
		Quaternion quat = Quaternion(Vector3<float>(0, 1, 0), p_eulerAngles.y) *
			Quaternion(Vector3<float>(1, 0, 0), p_eulerAngles.x) *
			Quaternion(Vector3<float>(0, 0, 1), p_eulerAngles.z);

		Vector3<float> toRotate = p_position - p_pivot;
		return quat.RotateVector(toRotate);
	}

	Vector3<float> Quaternion::RotateRelativeToPivot(const Vector3<float>& p_position, const Vector3<float>& p_pivot,
	                                                 Quaternion& p_quaternion)
	{
		Vector3<float> toRotate = p_position - p_pivot;
		return p_quaternion.RotateVector(toRotate);
	}

	Vector3<float> Quaternion::RotateVector(const Vector3<float>& p_toRotate) const
	{
		const Vector3<float> quaternion(m_x, m_y, m_z);
		const Vector3<float> T = Vector3<float>::CrossProduct(quaternion, p_toRotate) * 2.0f;
		const Vector3<float> result = p_toRotate + (T * m_w) + Vector3<float>::CrossProduct(quaternion, T);
		return result;
	}
#pragma endregion

#pragma region Conversions
	Vector3<float> Quaternion::ToEuler() const
	{
		// roll (x-axis rotation)
		const float sinr_cosp = +2.0f * (m_w * m_x + m_y * m_z);
		const float cosr_cosp = +1.0f - 2.0f * (m_x * m_x + m_y * m_y);
		const float roll = MathTools::MathUtils::Arctan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		float pitch = 0.f;
		const float sinp = +2.0f * (m_w * m_y - m_z * m_x);
		if (fabs(sinp) >= 1)
			pitch = static_cast<float>(copysign(MathTools::Generics::Pi / 2.0f, sinp));
			// use 90 degrees if out of range
		else
			pitch = MathTools::MathUtils::Arcsin(sinp);

		// yaw (z-axis rotation)
		const float siny_cosp = +2.0f * (m_w * m_z + m_x * m_y);
		const float cosy_cosp = +1.0f - 2.0f * (m_y * m_y + m_z * m_z);
		const float yaw = MathTools::MathUtils::Arctan2(siny_cosp, cosy_cosp);

		return {
			MathTools::MathUtils::ToDegrees(roll), MathTools::MathUtils::ToDegrees(pitch),
			MathTools::MathUtils::ToDegrees(yaw)
		};
	}

	std::string Quaternion::ToString() const
	{
		return std::string(IsNormalized() ? "Quaternion is Normalized\n" : "Quaternion is not Normalized\n") +
			"Scalar: " + std::to_string(m_w) + ", Vector: " + std::to_string(m_x) + "i " + std::to_string(m_y) + "j " +
			std::to_string(m_z) + "k";
	}

	std::string Quaternion::ToString(const Quaternion& p_quaternion)
	{
		return p_quaternion.ToString();
	}

	Matrix3<float> Quaternion::ToMatrix3() const
	{
		if (!this->IsNormalized())
			throw std::logic_error("Cannot convert non-normalized quaternions to Matrix4");

		float y2 = m_y * m_y;
		float wz = m_w * m_z;
		float x2 = m_x * m_x;
		float z2 = m_z * m_z;
		float xz = m_x * m_z;
		float yz = m_y * m_z;
		float xy = m_x * m_y;
		float wy = m_w * m_y;
		float wx = m_w * m_x;

		Matrix3<float> converted;
		converted.elements[0] = 1.0f - (2 * y2) - (2 * z2);
		converted.elements[3] = (2 * xy) - (2 * wz);
		converted.elements[6] = (2 * xz) + (2 * wy);
		converted.elements[1] = (2 * xy) + (2 * wz);
		converted.elements[4] = 1.0f - (2 * x2) - (2 * z2);
		converted.elements[7] = (2 * yz) - (2 * wx);
		converted.elements[2] = (2 * xz) - (2 * wy);
		converted.elements[5] = (2 * yz) + (2 * wx);
		converted.elements[8] = 1.0f - (2 * x2) - (2 * y2);
		return converted;
	}

	Matrix4<float> Quaternion::ToMatrix4() const
	{
		if (!this->IsNormalized())
			throw std::logic_error("Cannot convert non-normalized quaternions to Matrix4");

		float y2 = m_y * m_y;
		float wz = m_w * m_z;
		float x2 = m_x * m_x;
		float z2 = m_z * m_z;
		float xz = m_x * m_z;
		float yz = m_y * m_z;
		float xy = m_x * m_y;
		float wy = m_w * m_y;
		float wx = m_w * m_x;

		Matrix4<float> converted;
		converted.elements[0] = 1.0f - (2 * y2) - (2 * z2);
		converted.elements[4] = (2 * xy) - (2 * wz);
		converted.elements[8] = (2 * xz) + (2 * wy);
		converted.elements[12] = 0;
		converted.elements[1] = (2 * xy) + (2 * wz);
		converted.elements[5] = 1.0f - (2 * x2) - (2 * z2);
		converted.elements[9] = (2 * yz) - (2 * wx);
		converted.elements[13] = 0;
		converted.elements[2] = (2 * xz) - (2 * wy);
		converted.elements[6] = (2 * yz) + (2 * wx);
		converted.elements[10] = 1.0f - (2 * x2) - (2 * y2);
		converted.elements[14] = 0;
		converted.elements[3] = 0;
		converted.elements[7] = 0;
		converted.elements[11] = 0;
		converted.elements[15] = 1;
		return converted;
	}

#pragma endregion
	std::ostream& operator<<(std::ostream& p_stream, const Quaternion& p_quaternion)
	{
		p_stream << (p_quaternion.IsNormalized() ? "Quaternion is Normalized\n" : "Quaternion is not Normalized\n");
		p_stream << "Scalar: " << p_quaternion.GetRealValue() << ", Vector: " << p_quaternion.GetXAxisValue() << "i " <<
			p_quaternion.GetYAxisValue() << "j " << p_quaternion.GetZAxisValue() << "k";
		return p_stream;
	}
}

#pragma warning(pop)
