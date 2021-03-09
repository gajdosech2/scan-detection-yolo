#ifndef COGS_META_DATA_SERIALIZER_H
#define COGS_META_DATA_SERIALIZER_H

#include <Utils/Serializer.h>
#include <Utils/Serializables.h>

#include <COGS/API.h>
#include <COGS/MetaData.h>



namespace cogs
{

  class CameraSpaceSerializable
  {
    friend class cereal::access;

  public:
    utils::GlmVec3Serializable forward;
    utils::GlmVec3Serializable up;
    utils::GlmVec3Serializable right;

  private:
    template <class Archive>
    void serialize(Archive &ar);
  };

  class TransformationSerializable
  {
    friend class cereal::access;

  public:
    utils::GlmVec3Serializable translation;
    utils::GlmQuatSerializable rotation;
    float scaling;

  private:
    template <class Archive>
    void serialize(Archive &ar);
  };



  class ResolutionSerializable
  {
    friend class cereal::access;

  public:
    size_t width;
    size_t height;

    ResolutionSerializable() : ResolutionSerializable(glm::uvec2()) {}
    explicit ResolutionSerializable(const glm::uvec2 &v) : width(v.x), height(v.y) {}

    glm::uvec2 ToUvec2() const { return glm::uvec2(width, height); }

  private:
    template <class Archive>
    void serialize(Archive &ar);
  };



  class CameraParamsSerializable
  {
    friend class cereal::access;

  public:
    ResolutionSerializable resolution;
    utils::GlmVec3Serializable position;
    utils::GlmVec3Serializable forward;
    utils::GlmVec3Serializable up;
    utils::GlmVec3Serializable right;
    float fx, fy, cx, cy;
    float k1 = 0.0f, k2 = 0.0f, k3 = 0.0f,
          p1 = 0.0f, p2 = 0.0f;

  private:
    template <class Archive>
    void serialize(Archive &ar);
  };



  class MetaDataSerializable
  {
    friend class cereal::access;

  public:
    MetaDataSerializable() = default;
    explicit MetaDataSerializable(const MetaData &data);

    MetaData To() const;

  private:
    template <class Archive>
    void serialize(Archive &ar);

    std::string units = "";
    CameraSpaceSerializable camera_space;
    TransformationSerializable transformation;
    CameraParamsSerializable camera_params;
  };



  /*!
    \brief MetaDataSerializer - serialize read and write cogs::MetaData.
  */
  class COGS_API MetaDataSerializer
    : public utils::Serializer<cogs::MetaData, cogs::MetaDataSerializable>
  {
  public:
    explicit MetaDataSerializer()
      : Serializer("pcl_metadata")
    {
    }
  };


  template <class Archive>
  void cogs::CameraSpaceSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(forward),
      CEREAL_NVP(up),
      CEREAL_NVP(right)
    );
  }


  template <class Archive>
  void cogs::TransformationSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(translation),
      CEREAL_NVP(rotation),
      CEREAL_NVP(scaling)
    );
  }

  template <class Archive>
  void cogs::ResolutionSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(width),
      CEREAL_NVP(height)
    );
  }

  template <class Archive>
  void cogs::CameraParamsSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(resolution),
      CEREAL_NVP(position),
      CEREAL_NVP(forward),
      CEREAL_NVP(up),
      CEREAL_NVP(right),
      CEREAL_NVP(fx),
      CEREAL_NVP(fy),
      CEREAL_NVP(cx),
      CEREAL_NVP(cy),
      CEREAL_NVP(k1),
      CEREAL_NVP(k2),
      CEREAL_NVP(k3),
      CEREAL_NVP(p1),
      CEREAL_NVP(p2)
    );
  }

  template <class Archive>
  void cogs::MetaDataSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(units),
      CEREAL_NVP(camera_space),
      CEREAL_NVP(transformation),
      CEREAL_NVP(camera_params)
    );
  }

}

#endif /* !COGS_META_DATA_SERIALIZER_H */