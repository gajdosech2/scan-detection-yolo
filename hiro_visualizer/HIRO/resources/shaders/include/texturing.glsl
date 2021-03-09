//! Returns texture coordinate aligned to the center of texel.
vec2 AlignToTexel(in vec2 coord, in float texel_size)
{
	return floor(coord / texel_size) * texel_size + 0.5 * texel_size;
}

//! Returns procedural checker texture parameter (0,1) for a given grid position.
float GetCheckerGridValue(in vec2 grid_coord)
{
  ivec2 igrid_coord = ivec2(grid_coord);
  return float((igrid_coord.x + igrid_coord.y) % 2);
}

//! Returns procedural checker texture parameter (0,1) for a given normalized texture coordinate.
float GetCheckerValue(in vec2 coord, in float grid_resolution)
{
  return GetCheckerGridValue(coord * grid_resolution);
}
