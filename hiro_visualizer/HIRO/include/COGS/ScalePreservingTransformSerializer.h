/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_SCALE_PRESERVING_TRANSFORM_SERIALIZER_H
#define COGS_SCALE_PRESERVING_TRANSFORM_SERIALIZER_H

#include <Utils/Serializer.h>
#include <Utils/Serializables.h>

#include <COGS/API.h>
#include <COGS/ScalePreservingTransform.h>


namespace cogs
{

  class COGS_API ScalePreservingTransformSerializable
  {
  public:
    ScalePreservingTransformSerializable() = default;
    ScalePreservingTransformSerializable(const ScalePreservingTransform &);

    ScalePreservingTransform To() const;

    friend class cereal::access;

  public:
    utils::GlmVec3Serializable translation;
    utils::GlmQuatSerializable rotation;

  private:
    template <class Archive>
    void serialize(Archive &ar);
  };

  /*!
    \brief ScalePreservingTransformSerializer - serialize read and write cogs::ScalePreservingTransform.
  */
  class COGS_API ScalePreservingTransformSerializer
    : public utils::Serializer<cogs::ScalePreservingTransform, cogs::ScalePreservingTransformSerializable>
  {
  public:
    explicit ScalePreservingTransformSerializer()
      : Serializer("transformation")
    {
    }
  };


  template <class Archive>
  void cogs::ScalePreservingTransformSerializable::serialize(Archive &ar)
  {
    ar(
      CEREAL_NVP(translation),
      CEREAL_NVP(rotation)
    );
  }

}

#endif /* !COGS_SCALE_PRESERVING_TRANSFORM_SERIALIZER_H */