
//! Mapps float value in range <0-1> to rainbow colors.
vec3 ValToColorRainbow(in float value)
 {
 	if (value < 0.0){
 		return vec3(0.0);
 	}
	if (value >= 0.0 && value < 0.2)
	{
		value = value / 0.2;
		return vec3(0.0, value, 1.0);
	}
	else if (value >= 0.2 && value < 0.4)
	{
		value = (value - 0.2) / 0.2;
		return vec3(0.0, 1.0, 1.0 - value);
	}
	else if (value >= 0.4 && value < 0.6)
	{
		value = (value - 0.4) / 0.2;
		return vec3(value, 1.0, 0.0);
	}
	else if (value >= 0.6 && value < 0.8)
	{
		value = (value - 0.6) / 0.2;
		return vec3(1.0, 1.0 - value, 0.0);
	}
	else if (value >= 0.8 && value <= 1.0)
	{
		value = (value - 0.8) / 0.2;
		return vec3(1.0, 0.0, value);
	}
	else if (value > 1.0)
	{
		return vec3(1.0, 1.0, 1.0);
	}
  else
  {
		return vec3(1.0, 0.0, 0.0);
	}
 };

 //! Mapps float value to pseudo-random colors.
 vec3 ValToColorRandom(in float value)
 {
 	if (value < 0.0){
 		return vec3(0.0);
 	}
	if (value > 1.0)
	{
		return vec3(1.0);
	}
	return vec3(
		Random(value + 1.0), Random(value + 3.59), Random(value + 6.7)
	);
 };
