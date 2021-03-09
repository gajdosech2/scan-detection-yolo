
//! Calculates rotation quaternion from rotation axis and angle in radians.
vec4 QuatFromAxisAngle(in vec3 axis, in float angle)
{
	vec4 qr;
	float half_angle = (angle * 0.5);
	qr.x = axis.x * sin(half_angle);
	qr.y = axis.y * sin(half_angle);
	qr.z = axis.z * sin(half_angle);
	qr.w = cos(half_angle);
	return qr;
}

//! Creates quaternion rotation from vector a to vertor b.
vec4 QuatBetweenNormalizedVectors(in vec3 a, in vec3 b)
{
	return QuatFromAxisAngle(normalize(cross(a, b)), acos(dot(a, b)));
}

//! Rotates point using rotation quaternion.
vec3 RotateByQuat(in vec3 point, in vec4 quat)
{
	vec4 qr_conj = QuatConjugate(quat);
	vec4 q_pos = vec4(point, 0.0);
	vec4 q_tmp = QuatMultiply(quat, q_pos);
	vec4 qr = QuatMultiply(q_tmp, qr_conj);
	return vec3(qr.x, qr.y, qr.z);
}

//! Returns identity quaternion.
vec4 QuatIdentity()
{
	return vec4(0.0, 0.0, 0.0, 1.0);
}

//! Calculates the conjugate of a quaternion.
vec4 QuatConjugate(in vec4 q)
{
	return vec4(-q.x, -q.y, -q.z, q.w);
}

//! Calculates quaternion multiplication.
vec4 QuatMultiply(in vec4 q1, in vec4 q2)
{
	vec4 qr;
	qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	return qr;
}

//! Calculates inverse quaternion.
vec4 QuatInverse(in vec4 q)
{
	return QuatConjugate(q) / dot(q, q);
}

//! Interpolates two quaternions lineary by parameter t.
vec4 QuatLerp(in vec4 q1, in vec4 q2, in float t)
{
	return normalize(q1 * (1.0 - t) + q2 * t);
}

//! Interpolates two quaternions sphericaly by parameter t.
vec4 QuatSlerp(in vec4 q1, in vec4 q2, in float t)
{
	vec4 q3;
	float dot_p = dot(q1, q2);

	//if (dot_p < 0), q1 and q2 are more than 90 degrees apart,
	//so we can invert one to reduce spinning
	if (dot_p < 0.0)
	{
		dot_p = -dot_p;
		q3 = -q2;
	}
  else
  {
		q3 = q2;
	}

	if (dot_p < (1.0 - FLT_EPSILON))
	{
		float angle = acos(dot_p);
		return (q1 * sin(angle * (1.0 - t)) + q3 * sin(angle * t)) / sin(angle);
	}
  else
  {
		// if the angle is small, use linear interpolation
		return QuatLerp(q1, q3, t);
	}
}

//! Raises quaternion to the power of p.
vec4 QuatPow(in vec4 q, in float p)
{
	//Raising to the power of 0 should yield 1
	//Needed to prevent a division by 0 error later on
	if(yp > -FLT_EPSILON && p < FLT_EPSILON){
		return vec4(0.0, 0.0, 0.0, 1.0);
	}

	//To deal with non-unit quaternions
	float magnitude = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);

	//Equivalent to raising a real number to a power
	//Needed to prevent a division by 0 error later on
	if(abs(q.w / magnitude) > 1.0 - FLT_EPSILON && abs(q.w / magnitude) < 1.0 + FLT_EPSILON){
		return vec4(0.0, 0.0, 0.0, pow(q.w, p));
	}

	float Angle = acos(q.w / magnitude);
	float NewAngle = Angle * p;
	float Div = sin(NewAngle) / sin(Angle);
	float Mag = pow(magnitude, p - 1.0);

	return vec4(q.x * Div * Mag, q.y * Div * Mag, q.z * Div * Mag, cos(NewAngle) * magnitude * Mag);
}

//! Converts Rotation matrix to rotation quaternion.
vec4 MatToQuat(in mat3 m)
{
	float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
	float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
	float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
	float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0) * 0.5;
	float mult = 0.25f / biggestVal;

	vec4 Result;
	switch(biggestIndex)
	{
	case 0:
		Result.w = biggestVal;
		Result.x = (m[1][2] - m[2][1]) * mult;
		Result.y = (m[2][0] - m[0][2]) * mult;
		Result.z = (m[0][1] - m[1][0]) * mult;
		break;
	case 1:
		Result.w = (m[1][2] - m[2][1]) * mult;
		Result.x = biggestVal;
		Result.y = (m[0][1] + m[1][0]) * mult;
		Result.z = (m[2][0] + m[0][2]) * mult;
		break;
	case 2:
		Result.w = (m[2][0] - m[0][2]) * mult;
		Result.x = (m[0][1] + m[1][0]) * mult;
		Result.y = biggestVal;
		Result.z = (m[1][2] + m[2][1]) * mult;
		break;
	case 3:
		Result.w = (m[0][1] - m[1][0]) * mult;
		Result.x = (m[2][0] + m[0][2]) * mult;
		Result.y = (m[1][2] + m[2][1]) * mult;
		Result.z = biggestVal;
		break;

	default:
		break;
	}
	return Result;
}
