#include "vectors/coord_system.h"

#include <cassert>
#include <cerrno>
#include <cstring>
#include <math.h>
#include "vectors/vectors.h"

#define EPS 1e-6

void CoordSystem::translate(const Vec& translation)
{
  m_origin += translation;
}

void CoordSystem::rotate(double angle)
{
  assert(isfinite(angle));

  m_unit_x = m_unit_x.rotate(angle);
  m_unit_y = m_unit_y.rotate(angle);
}

Vec CoordSystem::getOrigVector(const Vec& vector) const
{
  return m_unit_x * vector.m_x
       + m_unit_y * vector.m_y;
}

Vec CoordSystem::fromOrigVector(const Vec& vector) const
{
  // Use Cramer's rule to solve system of two linear equations
  // / a_00 a_01 \   / b_0 \
  // \ a_10 a_11 / = \ b_1 /
  
  const double matrix[2][2] =
    {
      { m_unit_x.m_x, m_unit_y.m_x},
      { m_unit_x.m_y, m_unit_y.m_y}
    };
  const double result[2] =
    {
      vector.m_x,
      vector.m_y
    };

  const double delta   = matrix[0][0] * matrix[1][1]
                       - matrix[0][1] * matrix[1][0];

  const double delta_x = result[0]    * matrix[1][1]
                       - matrix[0][1] * result[1];

  const double delta_y = matrix[0][0] * result[1]
                       - result[0]    * matrix[1][0];

  assert(fabs(delta) > EPS && "Invalid coordinate system");
  
  return Vec(delta_x / delta,
             delta_y / delta);
}

