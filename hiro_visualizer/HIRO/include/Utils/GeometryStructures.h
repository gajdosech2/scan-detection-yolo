/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_GEOMETRY_STRUCTURES_H
#define UTILS_GEOMETRY_STRUCTURES_H
#include <stdexcept>

#include <glm/glm.hpp>
#include <Utils/ExtGLM.h>
#include <Utils/Property.h>



//! Set of structures for geometry and linear algebra.
namespace geom
{
  //! Enumeration for axes of a 3 dimensional space.
  enum class Axis
  {
    x,
    y,
    z
  };

  //! Converts an Axis to the glm::vec3.
  static inline glm::vec3 AxisToVec3(const geom::Axis axis)
  {
    switch (axis)
    {
    case Axis::x:
      return glm::vec3(1.0f, 0.0f, 0.0f);
    case Axis::y:
      return glm::vec3(0.0f, 1.0f, 0.0f);
    case Axis::z:
      return glm::vec3(0.0f, 0.0f, 1.0f);
    }
    throw std::invalid_argument("Undefined axis symbol.");
  }

  //! Definition of a unit 3D vector in X axis
  const static glm::vec3 Vec3X = AxisToVec3(Axis::x);
  //! Definition of a unit 3D vector in Y axis
  const static glm::vec3 Vec3Y = AxisToVec3(Axis::y);
  //! Definition of a unit 3D vector in Z axis
  const static glm::vec3 Vec3Z = AxisToVec3(Axis::z);

  //! Converts an Axis to the glm::vec4. Homogenic (w) coordinate is zero.
  static inline glm::vec4 AxisToVec4(const geom::Axis axis)
  {
    return glm::vec4(geom::AxisToVec3(axis), 0.0f);
  }

  //! Definition of a unit 4D vector in X axis
  const static glm::vec4 Vec4X = AxisToVec4(Axis::x);
  //! Definition of a unit 4D vector in Y axis
  const static glm::vec4 Vec4Y = AxisToVec4(Axis::y);
  //! Definition of a unit 4D vector in Z axis
  const static glm::vec4 Vec4Z = AxisToVec4(Axis::z);



  //! Template line segment in an arbitrary dimension.
  template <size_t N>
  struct LineSegment
  {
    using Vec = glm::vec<N, float>;
    Vec point1;
    Vec point2;

    LineSegment() = default;

    LineSegment(const Vec &init_point1, const Vec &init_point2)
      : point1(init_point1), point2(init_point2)
    {};

    //! Returns length of line segment = distance between point1 and point2.
    float GetLength() const
    {
      return glm::distance(point1, point2);
    };

    //! Returns square length of line segment = square distance between point1 and point2.
    float GetLengthSqr() const
    {
      return glm::distance2(point1, point2);
    };

    //! Returns direction of the line as a normalized vector from point1 to point2.
    Vec GetDirection() const
    {
      return glm::normalize(point2 - point1);
    };

    //! Converts the line to the vector from point1 to point2.
    Vec ToVector() const
    {
      return point2 - point1;
    };
  };

  //! Definition of a line segment in a 2 dimensional space.
  struct LineSegment2 : public LineSegment<2>
  {
    LineSegment2() = default;

    LineSegment2(float x1, float y1, float x2, float y2)
      : LineSegment(Vec(x1, y1), Vec(x2, y2))
    { };

    LineSegment2(const Vec &init_point1, const Vec &init_point2)
      : LineSegment(init_point1, init_point2)
    {};
  };

  //! Definition of a line segment in a 3 dimensional space.
  struct LineSegment3 : public LineSegment<3>
  {
    LineSegment3() = default;

    LineSegment3(float x1, float y1, float z1, float x2, float y2, float z2)
      : LineSegment(Vec(x1, y1, z1), Vec(x2, y2, z2))
    { };

    LineSegment3(const Vec &init_point1, const Vec &init_point2)
      : LineSegment(init_point1, init_point2)
    {};
  };

  //! Template line in an arbitrary dimension.
  template <size_t N>
  struct Line
  {
    using Vec = glm::vec<N, float>;
    Vec point, direction;
    Line() = default;
    Line(const Vec &_point, const Vec &_direction)
      : point(_point), direction(glm::normalize(_direction))
    {};
  };

  //! Definition of a line in a 2 dimensional space.
  using Line2 = Line<2>;

  //! Definition of a line in a 3 dimensional space.
  using Line3 = Line<3>;



  //! Template ray in an arbitrary dimension.
  template <size_t N>
  struct Ray
  {
    using Vec = glm::vec<N, float>;
    Vec origin;
    Vec direction;

    Ray() = default;
    Ray(const Vec &init_origin, const Vec &init_direction)
      : origin(init_origin), direction(init_direction)
    {};
  };

  //! Definition of a ray in a 2 dimensional space.
  using Ray2 = Ray<2>;

  //! Definition of a ray in a 3 dimensional space.
  using Ray3 = Ray<3>;

  //! Template spheroid of in an arbitrary dimension.
  template <int N, typename T>
  struct TSphere
  {
    glm::vec<N, T> center = glm::vec<N, T>(0);
    T radius = 0;
    TSphere() = default;
    TSphere(const glm::vec<N, T> &_center, const T _radius)
      : center(_center), radius(_radius)
    {};
    T GetDiameter() const
    {
      return static_cast<T>(2) * radius;
    };
    void SetDiameter(T value)
    {
      radius = value / static_cast<T>(2);
    };
  };

  //! Definition of a float type circle.
  using Circle = TSphere<2, float>;

  //! Definition of a float type sphere.
  using Sphere = TSphere<3, float>;

  //! Template triangle  in an arbitrary dimension.
  template <size_t D>
  struct TTriangle
  {
    using Vec = glm::vec<D, float>;

    Vec points[3];

    //! Returns point with a specified index. Calling Triangle[0] is equivalent to Triangle.points[0].
    Vec &operator[](size_t point_id)
    {
      if (point_id >= D)
      {
        throw std::invalid_argument("Triangle index out of range.");
      }
      return points[point_id];
    }

    //! Returns point with a specified index. Calling Triangle[0] is equivalent to Triangle.points[0].
    const Vec &operator[](size_t point_id) const
    {
      if (point_id >= D)
      {
        throw std::invalid_argument("Triangle index out of range.");
      }
      return points[point_id];
    }

    //! Returns a centroid of the three triangle points.
    Vec GetCentroid() const
    {
      return (points[0] + points[1] + points[2]) / 3.0f;
    }
  };

  //! Definition of a 2 dimensional triangle.
  struct Triangle2 : public TTriangle<2>
  {
    Triangle2() = default;

    Triangle2(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2)
    {
      points[0] = p0;
      points[1] = p1;
      points[2] = p2;
    };
  };

  //! Definition of a 3 dimensional triangle.
  struct Triangle3 : public TTriangle<3>
  {
    Triangle3() = default;

    Triangle3(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2)
    {
      points[0] = p0;
      points[1] = p1;
      points[2] = p2;
    };

    //! Calculates a normal vector of a triangle using counter-clockwise order.
    glm::vec3 GetNormal() const
    {
      return glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
    }
  };



  //! Template rectangle in an arbitrary dimension.
  template <typename T>
  struct TRect
  {
    using Vec2 = glm::tvec2<T>;

    Vec2 position = Vec2((T)0);
    Vec2 position2 = Vec2((T)0);

    TRect() : x(this), y(this), width(this), height(this), x2(this), y2(this), size(this) {};
    TRect(const T x1, const T y1, const T x2, const T y2) : TRect()
    {
      Set(x1, y1, x2, y2);
    };
    TRect(const Vec2 &point1, const Vec2 &point2) : TRect()
    {
      Set(point1, point2);
    };

    void SetSize(const Vec2 &new_size)
    {
      position2 = position + new_size;
    }

    TRect(const Vec2 &top_left_origin, const T size_width, const T size_height) : TRect()
    {
      position = top_left_origin;
      SetSize(Vec2(size_width, size_height));
    };

    void Set(const TRect &rect)
    {
      Set(rect.position, rect.position + rect.size);
    };
    void Set(const T t_x1, const T t_y1, const T t_x2, const T t_y2)
    {
      position.x = glm::min(t_x1, t_x2);
      position.y = glm::min(t_y1, t_y2);
      position2.x = glm::max(t_x1, t_x2);
      position2.y = glm::max(t_y1, t_y2);
    };
    void Set(const Vec2 &point1, const Vec2 &point2)
    {
      Set(point1.x, point1.y, point2.x, point2.y);
    };

    Vec2 GetSize() const
    {
      return position2 - position;
    }
    T GetX() const
    {
      return position.x;
    };
    T GetY() const
    {
      return position.y;
    };
    T GetWidth() const
    {
      return GetSize().x;
    };
    T GetHeight() const
    {
      return GetSize().y;
    };
    T GetX2() const
    {
      return position.x + GetSize().x;
    };
    T GetY2() const
    {
      return position.y + GetSize().y;
    };

    void SetX(const T value)
    {
      position.x = value;
    };
    void SetY(const T value)
    {
      position.y = value;
    };
    void SetWidth(const T value)
    {
      position2.x = position.x + value;
    };
    void SetHeight(const T value)
    {
      position2.y = position.y + value;
    };
    void SetX2(const T value)
    {
      position2.x = value;
    };
    void SetY2(const T value)
    {
      position2.y = value;
    };

    Vec2 Center(void) const
    {
      return (position + position2) / (T)2;
    };
    bool Contains(const Vec2 &point) const
    {
      return point.x >= position.x && point.x < GetX2() && point.y >= position.y && point.y < GetY2();
    }
    T Area(void) const
    {
      return (position2.x - position.x) * (position2.y - position.y);
    }

    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetX, &TRect<T>::SetX> x;
    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetY, &TRect<T>::SetY> y;
    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetWidth, &TRect<T>::SetWidth> width;
    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetHeight, &TRect<T>::SetHeight> height;
    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetX2, &TRect<T>::SetX2> x2;
    utils::PropertyByValue<TRect<T>, T, &TRect<T>::GetY2, &TRect<T>::SetY2> y2;
    utils::Property<TRect<T>, Vec2, &TRect<T>::GetSize, &TRect<T>::SetSize> size;
  };

  //! Definition of a float type rectangle.
  using Rect = TRect<float>;

  //! Definition of an integer type rectangle.
  using IRect = TRect<int>;

  //! Definition of an unsigned integer type rectangle.
  using URect = TRect<unsigned>;



  //! Template axis aligned bounding box in an arbitrary dimension.
  template <int dimensions, typename Type>
  struct TAabb
  {
    using Vec = glm::vec<dimensions, Type, glm::highp>;
    Vec min = Vec(std::numeric_limits<Type>::max());
    Vec max = Vec(std::numeric_limits<Type>::lowest());

    TAabb() {};
    TAabb(const Vec &corner1, const Vec &corner2)
    {
      min = (glm::min)(corner1, corner2);
      max = (glm::max)(corner1, corner2);
    };

    //! Returns sizing vector.
    Vec GetSize() const
    {
      return max - min;
    }

    //! Returns center point of bounding box.
    Vec GetCenter() const
    {
      return min + GetSize() / Type(2);
    }

    //! Returns square size of diagonal.
    float GetDiagonalSqr() const
    {
      return (glm::distance2)(min, max);
    }

    //! Returns size of diagonal.
    float GetDiagonal() const
    {
      return (glm::distance)(min, max);
    }

    //! Checks if point is included in range of bounding box.
    bool IsIncluded(const Vec &point) const
    {
      for (int i = 0; i < dimensions; i++)
      {
        if (point[i] < min[i] || point[i] > max[i])
        {
          return false;
        }
      }
      return true;
    }

    //! Checks if this bounding box is inside other Aabb.
    bool IsInside(const TAabb &aabb) const
    {
      return aabb.IsIncluded(min) && aabb.IsIncluded(max);
    }

    //! Enlarges aabb so that it covers also defined point.
    void Include(const Vec &point)
    {
      min = glm::min(min, point);
      max = glm::max(max, point);
    };

    //! Enlarges aabb so that it covers also area of specified aabb.
    void Include(const TAabb<dimensions, Type> &aabb)
    {
      min = glm::min(min, aabb.min);
      max = glm::max(max, aabb.max);
    };

    //! Checks if structure is valid. Invalid structure may have max < min.
    bool IsValid() const
    {
      return glm::all(glm::lessThan(min, max));
    }

    //! Returns smaller bounding box computed as an intersection.
    TAabb<dimensions, Type> GetIntersection(const TAabb<dimensions, Type> &aabb) const
    {
      TAabb<dimensions, Type> result;

      result.min = glm::max(min, aabb.min);
      result.max = glm::min(max, aabb.max);

      return result;
    }

    //! Checks if aabb has an intersection with defined bounding box.
    bool AreIntersected(const TAabb<dimensions, Type> &aabb) const
    {
      return
        aabb.min.x < max.x && min.x < aabb.max.x
        && aabb.min.y < max.y && min.y < aabb.max.y
        && aabb.min.z < max.z && min.z < aabb.max.z;
    }

    //! Returns volume of bounding box.
    Type Volume()
    {
      Vec dim = max - min;
      Type result = dim[0];
      for (unsigned char i = 1; i < dimensions; i++)
      {
        result *= dim[i];
      }
      return result;
    }

    //! Resets min and max to init values
    void Clear()
    {
      min = Vec(std::numeric_limits<Type>::max());
      max = Vec(std::numeric_limits<Type>::lowest());
    }

    //! Inflate in all directions.
    void Inflate(float d)
    {
      min -= d;
      max += d;
    }

    TAabb<dimensions, Type> &operator+=(const TAabb<dimensions, Type> &other)
    {
      min += other.min;
      max += other.max;
      return *this;
    };

    TAabb<dimensions, Type> &operator+=(const Type &other)
    {
      min += other;
      max += other;
      return *this;
    };

    TAabb<dimensions, Type> &operator+=(const Vec &vector)
    {
      min += vector;
      max += vector;
      return *this;
    };

    TAabb<dimensions, Type> &operator-=(const TAabb<dimensions, Type> &other)
    {
      min -= other.min;
      max -= other.max;
      return *this;
    };

    TAabb<dimensions, Type> &operator-=(const Type &other)
    {
      min -= other;
      max -= other;
      return *this;
    };

    TAabb<dimensions, Type> &operator-=(const Vec &vector)
    {
      min -= vector;
      max -= vector;
      return *this;
    };

    TAabb<dimensions, Type> &operator*=(const Type &factor)
    {
      min *= factor;
      max *= factor;
      return *this;
    };

    TAabb<dimensions, Type> &operator*(const Type &factor)
    {
      min *= factor;
      max *= factor;
      return *this;
    };

    TAabb<dimensions, Type> &operator*=(const Vec &vector)
    {
      min *= vector;
      max *= vector;
      return *this;
    };

    TAabb<dimensions, Type> &operator/=(const Type &divisor)
    {
      min /= divisor;
      max /= divisor;
      return *this;
    };

    TAabb<dimensions, Type> &operator/(const Type &divisor)
    {
      min /= divisor;
      max /= divisor;
      return *this;
    };

    TAabb<dimensions, Type> &operator/=(const Vec &vector)
    {
      min /= vector;
      max /= vector;
      return *this;
    };

  };

  //! Two dimensional axis aligned bounding box.
  using Aabb2 = TAabb<2, float>;

  //! Three dimensional axis aligned bounding box.
  using Aabb3 = TAabb<3, float>;



  //! Definition of a 3 dimensional plane.
  struct Plane
  {
    //! Distance from the origin in the direction of a normal.
    float distance{ 0.0f };
    //! Orientation of the plane.
    glm::vec3 normal{ 0.0f, 0.0f, 1.0f };

    Plane() = default;
    Plane(const glm::vec3 &origin, const glm::vec3 &normal)
    {
      this->normal = glm::normalize(normal);
      this->distance = -glm::dot(normal, -origin);
    };
    bool operator==(const Plane &other) const
    {
      return (this->distance == other.distance) && (this->normal == other.normal);
    };
    bool operator!=(const Plane &other) const
    {
      return !(*this == other);
    };
  };



  //! Definition of a 3 dimensional half-plane.
  struct HalfPlane
  {
    //! Line representing border of the half-plane.
    Line3 border;
    //! Direction of a plane.
    glm::vec3 direction{ glm::vec3(0.0f, 0.0f, 1.0f) };

    HalfPlane() = default;
    HalfPlane(const Line3 &border_line, const glm::vec3 &halfplane_direction)
    {
      this->border = border_line;
      this->direction = halfplane_direction;
    }
  };



  //! Definition of a 3 dimensional capsule.
  struct Capsule
  {
    //! Central line of a capsule.
    LineSegment3 central;
    //! Distance of a capsule surface from the central line.
    float radius{ 1.0f };

    Capsule() = default;

    Capsule(const LineSegment3 &line_segment, float init_radius)
      : central(line_segment), radius(init_radius)
    {};

    Capsule(const glm::vec3 &point1, const glm::vec3 &point2, float init_radius)
      : central(point1, point2), radius(init_radius)
    {};
  };



  //! Definition of a 3 dimensional capsule with different radiuses at each end.
  struct ConicalCapsule
  {
    //! Central line of a capsule.
    LineSegment3 central;
    //! Distance of a capsule surface from the point1 of a central line.
    float radius1{ 1.0f };
    //! Distance of a capsule surface from the point2 of a central line.
    float radius2{ 1.0f };

    ConicalCapsule() = default;

    ConicalCapsule(const LineSegment3 &line_segment, float init_radius1, const float init_radius2)
      : central(line_segment), radius1(init_radius1), radius2(init_radius2)
    {};

    ConicalCapsule(const glm::vec3 point1, const float init_radius1, const glm::vec3 point2, const float init_radius2)
      : central(point1, point2), radius1(init_radius1), radius2(init_radius2)
    {};

    /*!
      \brief
        Returns a radius in the specific central part of a capsule.
      \param factor
        Interpolation parameter over central. Value 0 returns radius1 and 1 returns radius2.
    */
    float GetInterpolatedRadius(float factor) const
    {
      factor = glm_ext::Clamp01(factor);
      return (1.f - factor) * radius1 + factor * radius2;
    };
  };



  //! Definition of abstract k-DOP bounding volume structure.
  class KDop
  {
  public:

    KDop() = delete;

    //! Set k-dop so that it covers all specified points.
    void Set(const glm::vec3 *points, const size_t num_of_points)
    {
      for (size_t i = 0; i < num_of_points; i++)
      {
        for (size_t j = 0; j < axes.size(); j++)
        {
          const auto t = glm::dot(points[i], axes[j].direction);
          axes[j].min = std::min(axes[j].min, t);
          axes[j].max = std::max(axes[j].max, t);
        }
      }
    }

    //! Checks if all
    bool IsValid() const
    {
      return !axes.empty() && std_ext::AllOf(axes, [](const auto & a) { return a.IsValid(); });
    }

    //! Checks if the k-dop has an intersection with other k-dop.
    bool AreIntersected(const KDop &other)
    {
      for (size_t i = 0; i < axes.size(); i++)
      {
        if (axes[i].min > other.axes[i].max || axes[i].max < other.axes[i].min)
        {
          return false;
        }
      }
      return true;
    }

    //! Checks if point is included in range of k-dop.
    bool IsIncluded(const glm::vec3 &point)
    {
      for (auto &axis : axes)
      {
        auto t = glm::dot(point, axis.direction);
        if (axis.min > t || axis.max < t)
        {
          return false;
        }
      }
      return true;
    }

  protected:

    KDop(const std::vector<glm::vec3> &dirs)
    {
      axes.resize(dirs.size());
      for (size_t i = 0; i < dirs.size(); i++)
      {
        axes[i].direction = glm::normalize(dirs[i]);
      }
    };

  private:

    struct PrincipalAxis
    {
      glm::vec3 direction;
      float min{ std::numeric_limits<float>::max() };
      float max{ std::numeric_limits<float>::min() };
      bool IsValid() const
      {
        return glm_ext::IsLequal(min, max);
      }
    };

    std::vector<PrincipalAxis> axes;
  };

  //! Directions that define default KDOP_3.
  const static std::vector<glm::vec3> KDOP_3_DIRECTIONS
  {
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 0.0, 1.0),
  };
  //! Directions that define default KDOP_4.
  const static std::vector<glm::vec3> KDOP_4_DIRECTIONS
  {
    glm::vec3(1.0, 1.0, 1.0),
    glm::vec3(1.0, 1.0, -1.0),
    glm::vec3(1.0, -1.0, 1.0),
    glm::vec3(1.0, -1.0, -1.0)
  };
  //! Directions that define default KDOP_7.
  const static std::vector<glm::vec3> KDOP_7_DIRECTIONS
  {
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 0.0, 1.0),

    glm::vec3(1.0, 1.0, 1.0),
    glm::vec3(1.0, 1.0, -1.0),
    glm::vec3(1.0, -1.0, 1.0),
    glm::vec3(1.0, -1.0, -1.0)
  };
  //! Directions that define default KDOP_13.
  const static std::vector<glm::vec3> KDOP_13_DIRECTIONS
  {
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 0.0, 1.0),

    glm::vec3(1.0, 1.0, 1.0),
    glm::vec3(1.0, 1.0, -1.0),
    glm::vec3(1.0, -1.0, 1.0),
    glm::vec3(1.0, -1.0, -1.0),

    glm::vec3(0.0, 1.0, 1.0),
    glm::vec3(0.0, 1.0, -1.0),
    glm::vec3(1.0, 0.0, 1.0),
    glm::vec3(1.0, 0.0, -1.0),
    glm::vec3(1.0, 1.0, 0.0),
    glm::vec3(1.0, -1.0, 0.0),
  };

  //! k-DOP bounding volume structure with 3 principal axes. It is essentially AABB.
  class KDop3 : public KDop
  {
  public:
    KDop3() : KDop(KDOP_3_DIRECTIONS)
    {
    };
  };

  //! k-DOP bounding volume structure with 4 principal axes.
  class KDop4 : public KDop
  {
  public:
    KDop4() : KDop(KDOP_4_DIRECTIONS)
    {
    };
  };

  //! k-DOP bounding volume structure with 7 principal axes.
  class KDop7 : public KDop
  {
  public:
    KDop7() : KDop(KDOP_7_DIRECTIONS)
    {
    };
  };

  //! k-DOP bounding volume structure with 13 principal axes.
  class KDop13 : public KDop
  {
  public:
    KDop13() : KDop(KDOP_13_DIRECTIONS)
    {
    };
  };
}

#endif /* !UTILS_GEOMETRY_STRUCTURES_H */