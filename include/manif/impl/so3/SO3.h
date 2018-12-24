#ifndef _MANIF_MANIF_SO3_H_
#define _MANIF_MANIF_SO3_H_

#include "manif/impl/so3/SO3_base.h"

namespace manif {

// Forward declare for type traits specialization

template <typename _Scalar> struct SO3;
template <typename _Scalar> struct SO3Tangent;

namespace internal {

//! Traits specialization
template <typename _Scalar>
struct traits<SO3<_Scalar>>
{
  using Scalar = _Scalar;

  using LieGroup = SO3<_Scalar>;
  using Tangent  = SO3Tangent<_Scalar>;

  using Base = SO3Base<SO3<_Scalar>>;

  static constexpr int Dim     = LieGroupProperties<Base>::Dim;
  static constexpr int DoF     = LieGroupProperties<Base>::DoF;
  static constexpr int RepSize = 4;

  using DataType       = Eigen::Matrix<Scalar, RepSize, 1>;
  using Jacobian       = Eigen::Matrix<Scalar, DoF, DoF>;
  using Transformation = Eigen::Matrix<Scalar, 4, 4>;
  using Rotation       = Eigen::Matrix<Scalar, Dim, Dim>;
  using Vector         = Eigen::Matrix<Scalar, DoF, 1>;
};

} /* namespace internal */
} /* namespace manif */

namespace manif {

////////////////
///          ///
/// LieGroup ///
///          ///
////////////////

/**
 * @brief Represents an element of SO3.
 */
template <typename _Scalar>
struct SO3 : SO3Base<SO3<_Scalar>>
{
private:

  using Base = SO3Base<SO3<_Scalar>>;
  using Type = SO3<_Scalar>;

  using QuaternionDataType = Eigen::Quaternion<_Scalar>;

public:

  MANIF_COMPLETE_GROUP_TYPEDEF
  MANIF_INHERIT_GROUP_API

  using Base::quat;

  SO3()  = default;
  ~SO3() = default;

  SO3(const DataType& d);

  /**
   * @brief Constructor given a quaternion.
   */
  SO3(const QuaternionDataType& q);

  /**
   * @brief Constructor given the quaternion's coefficients.
   */
  SO3(const Scalar x, const Scalar y,
      const Scalar z, const Scalar w);

  /**
   * @brief Constructor given an angle axis.
   */
  SO3(const Eigen::AngleAxis<Scalar>& angle_axis);

  /**
   * @brief Constructor given Euler angles.
   */
  SO3(const Scalar roll, const Scalar pitch,
      const Scalar yaw);

  const DataType& coeffs() const;

protected:

  friend class LieGroupBase<SO3<Scalar>>;
  DataType& coeffs_nonconst();

  DataType data_;
};

MANIF_EXTRA_GROUP_TYPEDEF(SO3)

template <typename _Scalar>
SO3<_Scalar>::SO3(const DataType& d)
  : data_(d)
{
  //
}

template <typename _Scalar>
SO3<_Scalar>::SO3(const QuaternionDataType& q)
  : data_(q.coeffs())
{
  //
}

template <typename _Scalar>
SO3<_Scalar>::SO3(const Scalar x, const Scalar y,
                  const Scalar z, const Scalar w)
  : data_(x, y, z, w)
{
  //
}

template <typename _Scalar>
SO3<_Scalar>::SO3(const Eigen::AngleAxis<Scalar>& angle_axis)
  : SO3(QuaternionDataType(angle_axis).coeffs())
{

}

template <typename _Scalar>
SO3<_Scalar>::SO3(const Scalar roll,
                  const Scalar pitch,
                  const Scalar yaw)
  : SO3(Eigen::AngleAxis<Scalar>(yaw,   Eigen::Matrix<Scalar, 3, 1>::UnitZ()) *
        Eigen::AngleAxis<Scalar>(pitch, Eigen::Matrix<Scalar, 3, 1>::UnitY()) *
        Eigen::AngleAxis<Scalar>(roll,  Eigen::Matrix<Scalar, 3, 1>::UnitX())  )
{
  //
}

template <typename _Scalar>
typename SO3<_Scalar>::DataType&
SO3<_Scalar>::coeffs_nonconst()
{
  return data_;
}

template <typename _Scalar>
const typename SO3<_Scalar>::DataType&
SO3<_Scalar>::coeffs() const
{
  return data_;
}

} /* namespace manif */

#endif /* _MANIF_MANIF_SO3_H_ */
