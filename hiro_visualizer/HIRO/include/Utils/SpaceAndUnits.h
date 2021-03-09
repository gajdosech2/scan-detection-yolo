#ifndef UTILS_SPACE_AND_UNITS_H
#define UTILS_SPACE_AND_UNITS_H
#undef snprintf
#include <nlohmann/json.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Utils/GeometryStructures.h>


namespace utils
{
  const uint8_t BASIS_DEFINITION_VERSION = 1;
  const uint8_t SPACE_DEFINITION_VERSION = 2;

  //! Distance measurement units.
  enum class Units : uint8_t
  {
    km,  //!< kilometer
    m,   //!< meter
    dm,  //!< decimeter
    cm,  //!< centimeter
    mm,  //!< millimeter
    um,  //!< micrometer
    nm,  //!< nanometer
    mi,  //!< mile
    ft,  //!< feet
    in,  //!< inch
  };

  //! String names for a specific unit.
  struct UnitNames
  {
    UnitNames(const std::string &sg, const std::string &pl, const std::string &ab)
      : singular(sg), plural(pl), abbrev(ab) {};
    std::string singular;
    std::string plural;
    std::string abbrev;
  };

  //! Gets ratio that describes relation between two provided units. target_value = source_value * ratio.
  static inline float GetUnitConversionRatio(utils::Units source_units, utils::Units target_units)
  {
    static const std::map<Units, float> unit_scale
    {
      { Units::km, 0.001f },
      { Units::m, 1.0f },
      { Units::dm, 10.0f },
      { Units::cm, 100.0f },
      { Units::mm, 1'000.0f },
      { Units::um, 1'000'000.0f },
      { Units::nm, 1'000'000'000.0f },
      { Units::mi, 0.0006213712f },
      { Units::ft, 3.280839935991f },
      { Units::in, 39.37007923189f },
    };
    const auto src_unit_scale = unit_scale.at(source_units);
    const auto tar_unit_scale = unit_scale.at(target_units);
    return tar_unit_scale / src_unit_scale;
  }

  //! Gets ratio that describes relation between two provided unit: target_value = source_value * ratio.
  static inline const UnitNames &GetUnitName(utils::Units unit)
  {
    static const std::map<Units, UnitNames> unit_names
    {
      { Units::km, {"kilometer", "kilometers", "km"} },
      { Units::m, {"meter", "meters", "m"} },
      { Units::dm, {"decimeter", "decimeters", "dm"} },
      { Units::cm, {"centimeter", "centimeters", "cm"} },
      { Units::mm, {"millimeter", "millimeters", "mm"} },
      { Units::um, {"micrometer", "micrometers", "um" } },
      { Units::nm, {"nanometer", "nanometers", "nm" } },
      { Units::mi, {"mile", "miles", "mi" } },
      { Units::ft, {"foot", "feet", "ft" } },
      { Units::in, {"inch", "inches", "in" } },
    };
    return unit_names.at(unit);
  }

  //! Base axis.
  enum class BaseAxis : uint8_t
  {
    positive_x,
    positive_y,
    positive_z,
    negative_x,
    negative_y,
    negative_z
  };

  //! Converts base axis x,y,z hints to 0,1,2 respectively.
  static inline size_t BaseAxisToId(BaseAxis axis)
  {
    switch (axis)
    {
    case utils::BaseAxis::positive_x:
    case utils::BaseAxis::negative_x:
      return 0;
    case utils::BaseAxis::positive_y:
    case utils::BaseAxis::negative_y:
      return 1;
    case utils::BaseAxis::positive_z:
    case utils::BaseAxis::negative_z:
      return 2;
    }
    return {};
  }

  //! Converts base axis positive,negative hints to 1,-1 respectively.
  static inline float BaseAxisToSign(BaseAxis axis)
  {
    switch (axis)
    {
    case utils::BaseAxis::positive_x:
    case utils::BaseAxis::positive_y:
    case utils::BaseAxis::positive_z:
      return 1.0f;
    case utils::BaseAxis::negative_x:
    case utils::BaseAxis::negative_y:
    case utils::BaseAxis::negative_z:
      return -1.0f;
    }
    return {};
  }


  //! Converts base axis to vec3.
  static inline glm::vec3 BaseAxisToVec3(BaseAxis axis)
  {
    switch (axis)
    {
    case utils::BaseAxis::positive_x:
      return geom::AxisToVec3(geom::Axis::x);
    case utils::BaseAxis::positive_y:
      return geom::AxisToVec3(geom::Axis::y);
    case utils::BaseAxis::positive_z:
      return geom::AxisToVec3(geom::Axis::z);
    case utils::BaseAxis::negative_x:
      return -geom::AxisToVec3(geom::Axis::x);
    case utils::BaseAxis::negative_y:
      return -geom::AxisToVec3(geom::Axis::y);
    case utils::BaseAxis::negative_z:
      return -geom::AxisToVec3(geom::Axis::z);
    }
    return {};
  }

  //! Converts base axis to vec4, with possible custom w element value.
  static inline glm::vec4 BaseAxisToVec4(BaseAxis axis, float w = 0.0f)
  {
    return {BaseAxisToVec3(axis), w};
  }

  static inline bool AreCollinear(BaseAxis axis_a, BaseAxis axis_b)
  {
    const auto vec_a = BaseAxisToVec3(axis_a);
    const auto vec_b = BaseAxisToVec3(axis_b);

    std::optional<float> div = std::nullopt;
    for (glm::length_t i = 0; i < 3; ++i)
    {
      if (glm_ext::AreEqual(vec_b[i], 0.0f))
      {
        if (glm_ext::AreEqual(vec_a[i], 0.0f))
        {
          continue;
        }
        else
        {
          return false;
        }
      }
      else
      {
        float this_div = vec_a[i] / vec_b[i];
        if (div.has_value() && !glm_ext::AreEqual(*div, this_div))
        {
          return false;
        }
        div = this_div;
      }
    }
    return true;
  }

  //! Which hand to use.
  enum class Handedness : uint8_t
  {
    left,
    right
  };

  //! Definition of an arbitrary basis.
  struct BasisDefinition
  {
    std::string id{ "custom" };
    BaseAxis up{ BaseAxis::positive_y };
    BaseAxis forward{ BaseAxis::positive_z };
    Handedness handedness{ Handedness::right };

    BasisDefinition() = default;

    BasisDefinition(BaseAxis t_up, BaseAxis t_forward, Handedness t_handedness)
      : up(t_up), forward(t_forward), handedness(t_handedness)
    {
    };

    //! Creates a basis matrix that defines this space.
    glm::mat3 CreateBasisMat3() const
    {
      const auto src_up = BaseAxisToVec3(up);
      const auto src_fwd = BaseAxisToVec3(forward);
      const auto src_cr = handedness == Handedness::right ? glm::cross(src_up, src_fwd) : glm::cross(src_fwd, src_up);
      return glm::mat3(src_cr, src_up, src_fwd);
    }

    //! Creates a basis matrix that defines this space.
    glm::mat4 CreateBasisMat4() const
    {
      return glm::mat4(CreateBasisMat3());
    }

    //! Creates transformation matrix that defines transition from this basis to the target_basis.
    glm::mat3 MakeTransform3To(const BasisDefinition &target_basis) const
    {
      if (*this == target_basis)
      {
        return {};
      }
      const auto src_basis = CreateBasisMat3();
      const auto tar_basis = target_basis.CreateBasisMat3();
      return tar_basis * glm::inverse(src_basis);
    }

    //! Creates transformation matrix that defines transition from this basis to the target_basis.
    glm::mat4 MakeTransform4To(const BasisDefinition &target_basis) const
    {
      return { MakeTransform3To(target_basis) };
    }

    //! Creates transformation matrix for this basis, from transformation in other basis.
    glm::mat4 Convert(
      const glm::mat4 &other_transform, const BasisDefinition &other_basis) const
    {
      if (*this == other_basis)
      {
        return other_transform;
      }
      const auto to_other_space = MakeTransform4To(other_basis);
      return glm::inverse(to_other_space) * other_transform * to_other_space;
    }

    bool operator ==(BasisDefinition const &b) const
    {
      return up == b.up && forward == b.forward && handedness == b.handedness;
    }

    bool operator !=(BasisDefinition const &b) const
    {
      return !operator==(b);
    }

    //! Converts this to nlohmann::json structure.
    virtual void Serialize(nlohmann::json &json) const
    {
      json["id"] = id;
      json["up"] = glm_ext::to_string(BaseAxisToVec3(up));
      json["forward"] = glm_ext::to_string(BaseAxisToVec3(forward));
      json["handedness"] = handedness == Handedness::left ? "left" : "right";
    }

    //! Convert this to JSON string.
    std::string ToString() const
    {
      nlohmann::json j;
      Serialize(j);
      return j.dump();
    }

    virtual void Serialize(std::ostream &outs) const
    {
      std_ext::Write<uint8_t>(BASIS_DEFINITION_VERSION, outs);
      std_ext::WriteString(id, outs);
      std_ext::Write(static_cast<uint8_t>(up), outs);
      std_ext::Write(static_cast<uint8_t>(forward), outs);
      std_ext::Write(static_cast<uint8_t>(handedness), outs);
    }

    virtual bool Deserialize(std::istream &in)
    {
      const auto version = std_ext::Read<uint8_t>(in);
      if (version > BASIS_DEFINITION_VERSION)
      {
        return false;
      }
      if (version >= 1)
      {
        id = std_ext::ReadString(in);
      }
      up = static_cast<BaseAxis>(std_ext::Read<uint8_t>(in));
      forward = static_cast<BaseAxis>(std_ext::Read<uint8_t>(in));
      handedness = static_cast<Handedness>(std_ext::Read<uint8_t>(in));
      return true;
    }
  };

  //! Defines logical categories of spaces. Only spaces within same categories can be converted onto one another directly.
  enum class SpaceCategory : uint8_t
  {
    custom,
    camera,
    marker,
  };

  inline std::string SpaceCategoryToString(SpaceCategory categ)
  {
    switch (categ)
    {
    case SpaceCategory::custom:
      return "custom";
    case SpaceCategory::camera:
      return "camera";
    case SpaceCategory::marker:
      return "marker";
    }
    return "";
  }

//! Definition of an arbitrary space.
  struct SpaceDefinition : public BasisDefinition
  {
    SpaceDefinition() = default;

    SpaceDefinition(Units t_units, BaseAxis t_up,  BaseAxis t_forward, Handedness t_handedness)
      : BasisDefinition(t_up, t_forward, t_handedness), units(t_units)
    {
    };

    SpaceCategory category{ SpaceCategory::custom };
    Units units{ Units::mm };

    //! Creates transformation matrix that defines transition from this space to the target_space.
    glm::mat3 MakeTransform3To(const SpaceDefinition &target_space) const
    {
      if (*this == target_space)
      {
        return {};
      }
      const auto unit_conversion_ratio = GetUnitConversionRatio(units, target_space.units);
      const glm::mat3 space_scaling = glm::scale({}, glm::vec3(unit_conversion_ratio));
      return space_scaling * BasisDefinition::MakeTransform3To(target_space);
    }

    //! Creates transformation matrix that defines transition from this space to the target_space.
    glm::mat4 MakeTransform4To(const SpaceDefinition &target_space) const
    {
      return { MakeTransform3To(target_space) };
    }

    using BasisDefinition::Convert;

    //! Creates transformation matrix for this space, from transformation created for other space.
    glm::mat4 Convert(
      const glm::mat4 &other_transform, const SpaceDefinition &other_space) const
    {
      if (*this == other_space)
      {
        return other_transform;
      }
      const auto to_other_space = MakeTransform4To(other_space);
      return glm::inverse(to_other_space) * other_transform * to_other_space;
    }

    bool operator ==(SpaceDefinition const &b) const
    {
      return units == b.units && category == b.category && BasisDefinition::operator==(b);
    }

    bool operator !=(SpaceDefinition const &b) const
    {
      return !operator==(b);
    }

    //! Converts this to nlohmann::json structure.
    virtual void Serialize(nlohmann::json &json) const
    {
      BasisDefinition::Serialize(json);
      json["category"] = SpaceCategoryToString(category);
      json["units"] = GetUnitName(units).abbrev;
    }

    virtual void Serialize(std::ostream &outs) const override
    {
      BasisDefinition::Serialize(outs);
      std_ext::Write<uint8_t>(SPACE_DEFINITION_VERSION, outs);
      std_ext::Write(static_cast<uint8_t>(units), outs);
      std_ext::Write(static_cast<uint8_t>(category), outs);
    }

    virtual bool Deserialize(std::istream &ins) override
    {
      if (!BasisDefinition::Deserialize(ins))
      {
        return false;
      }
      const auto version = std_ext::Read<uint8_t>(ins);
      if (version > SPACE_DEFINITION_VERSION)
      {
        return false;
      }
      if (version == 0)
      {
        id = std_ext::ReadString(ins);
      }
      units = static_cast<Units>(std_ext::Read<uint8_t>(ins));
      if (version >= 2)
      {
        category = static_cast<SpaceCategory>(std_ext::Read<uint8_t>(ins));
      }
      return true;
    }
  };



  const SpaceDefinition PHOXI_MARKER_SPACE = []()
  {
    SpaceDefinition space;
    space.id = "PhoXi Marker";
    space.category = SpaceCategory::marker;
    space.up = BaseAxis::positive_z;
    space.forward = BaseAxis::negative_x;
    space.units = Units::mm;
    space.handedness = Handedness::right;
    return space;
  }
  ();

  const SpaceDefinition COGS_MARKER_SPACE = []()
  {
    SpaceDefinition space;
    space.id = "COGS Marker";
    space.category = SpaceCategory::marker;
    space.up = BaseAxis::positive_y;
    space.forward = BaseAxis::positive_z;
    space.units = Units::m;
    space.handedness = Handedness::right;
    return space;
  }
  ();

  const SpaceDefinition PHOXI_CAMERA_SPACE = []()
  {
    SpaceDefinition space;
    space.id = "PhoXi Camera";
    space.category = SpaceCategory::camera;
    space.up = BaseAxis::negative_y;
    space.forward = BaseAxis::positive_z;
    space.units = Units::mm;
    space.handedness = Handedness::right;
    return space;
  }
  ();

  const SpaceDefinition COGS_CAMERA_SPACE = []()
  {
    SpaceDefinition space;
    space.id = "COGS Camera";
    space.category = SpaceCategory::camera;
    space.up = BaseAxis::positive_y;
    space.forward = BaseAxis::negative_z;
    space.units = Units::m;
    space.handedness = Handedness::right;
    return space;
  }
  ();

  const std::map<std::string, SpaceDefinition> SPACE_DEFINITION_OF_ID =
  {
    {PHOXI_MARKER_SPACE.id, PHOXI_MARKER_SPACE},
    {PHOXI_CAMERA_SPACE.id, PHOXI_CAMERA_SPACE},
    {COGS_MARKER_SPACE.id, COGS_MARKER_SPACE},
    {COGS_CAMERA_SPACE.id, COGS_CAMERA_SPACE}
  };

}
#endif /* !UTILS_SPACE_AND_UNITS_H */