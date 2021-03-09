#define PI 3.1415926
#define HALF_PI 1.5707963
#define TWO_PI 6.283184
#define FLT_MAX 3.402823466e+38
#define FLT_EPSILON 1.192092896e-07

//! Returns pseudo-random value using a given seed.
float Random(in vec2 seed)
{
  return fract(sin(dot(seed, vec2(12.9898, 78.233))) * 43758.5453);
}

//! Returns pseudo-random value using a given seed.
float Random(in float seed)
{
  return fract(sin(seed) * 43758.5453);
}

//! Clamps the value to defined interval.
float Clamp(in float value, in float min_val, in float max_val)
{
  // original glsl function clamp may be numericaly instable?
	return min(max(value, min_val), max_val);
}

//! Clamps each component of vector to defined interval.
vec4 Clamp(in vec4 value, in vec4 min_val, in vec4 max_val)
{
	return vec4(
    Clamp(value.x, min_val.x, max_val.x),
		Clamp(value.y, min_val.y, max_val.y),
		Clamp(value.z, min_val.z, max_val.z),
		Clamp(value.w, min_val.w, max_val.w)
  );
}

//! Clamps the value to interval <0, 1>.
float Clamp01(in float val)
{
	return clamp(val, 0.0, 1.0);
};

//! Returns square distance between two points.
float Distance2(in vec3 point1, in vec3 point2)
{
	return pow(point1.x-point2.x, 2) + pow(point1.y-point2.y, 2) + pow(point1.z-point2.z, 2);
};

//! Returns a normal vector of the triangle defined by three points ordered in a counter-clockwise fashion.
vec3 GetNormalCCW(in vec3 pos1, in vec3 pos2, in vec3 pos3)
{
	vec3 v1 = pos1 - pos2;
  vec3 v2 = pos1 - pos3;
  return normalize(cross(v1, v2));
}

//! Returns non-oriented angle between two vectors in radians - within interval <0, PI>.
float GetAngle(in vec3 vector1, in vec3 vector2)
{
  const float dot_product = clamp(dot(vector1, vector2), -1.0, 1.0);
  return acos(dot_product);
}

//! Returns oriented angle in radians - within interval <-PI, PI>.
float GetOrientAngle(in vec3 vector1, in vec3 vector2, in vec3 ref_axis)
{
  float angle = GetAngle(vector1, vector2);
  if (dot(ref_axis, cross(vector1, vector2)) < 0.0)
    angle = -angle;
  return angle;
}

//! Calculates rotation matrix from rotation axis and angle in radians.
mat4 RotationMatrix(in vec3 axis, in float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                               0.0,                               0.0,                               1.0);
}

//! Checks if the value is neither Inf nor NaN.
bool IsValid(in float value)
{
	return !(isinf(value) || isnan(value));
}

//! Checks if all vector components are neither Inf nor NaN.
bool IsValid(in vec2 vector)
{
	for (int i = 0; i < 2; i++){
		if (isinf(vector[i]) || isnan(vector[i]))
			return false;
	}
	return true;
}

//! Checks if all vector components are neither Inf nor NaN.
bool IsValid(in vec3 vector)
{
	for (int i = 0; i < 3; i++){
		if (isinf(vector[i]) || isnan(vector[i]))
			return false;
	}
	return true;
}

//! Checks if all vector components are neither Inf nor NaN.
bool IsValid(in vec4 vector)
{
	for (int i = 0; i < 4; i++){
		if (isinf(vector[i]) || isnan(vector[i]))
			return false;
	}
	return true;
}

//! Calculates line parameter for finding intersection between line and plane.
float GetIntersectionParameter(in vec3 line_point, in vec3 line_direction, in vec3 plane_point, in vec3 plane_normal)
{
	float plane_distance = dot(plane_normal, plane_point);
	float dot_p = dot(plane_normal, line_direction);
	float t = (plane_distance - dot(plane_normal, line_point)) / dot_p;
	return t;
}

//! Calculates intersection point between line and plane.
vec3 GetIntersection(in vec3 line_point, in vec3 line_direction, in vec3 plane_point, in vec3 plane_normal)
{
	float t = GetIntersectionParameter(line_point, line_direction, plane_point, plane_normal);
	vec3 result = line_point + line_direction * t;
	return result;
}

//! Projects vector on a plane.
vec3 ProjectVecOnPlane(in vec3 vector, in vec3 plane_normal)
{
	return normalize(vector - (plane_normal * dot(vector, plane_normal)));
}
