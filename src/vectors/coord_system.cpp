#include "vectors/coord_system.h"

#include <cassert>
#include <cerrno>
#include <cstring>
#include <math.h>
#include "vectors/vectors.h"

#define EPS 1e-6

void CoordSystemCtor(CoordSystem* coord_system, const Point* origin,
                     const Vec* unit_x, const Vec* unit_y)
{
  assert(coord_system != NULL);
  const double cross_product = VecSignedArea(unit_x, unit_y);

  if (fabs(cross_product) < EPS)
  {
    errno = EINVAL;
    return;
  }

  memcpy(&coord_system->origin, origin, sizeof(Point));
  memcpy(&coord_system->unit_x, unit_x, sizeof(Vec));
  memcpy(&coord_system->unit_y, unit_y, sizeof(Vec));
}

void CoordSystemDtor(CoordSystem* coord_system)
{
  assert(coord_system != NULL);
  Vec empty = VEC_EMPTY;

  memcpy(&coord_system->origin, &empty, sizeof(Point));
  memcpy(&coord_system->unit_x, &empty, sizeof(Vec));
  memcpy(&coord_system->unit_y, &empty, sizeof(Vec));
}

void CoordSystemTranslate(CoordSystem* coord_system, const Vec* translation)
{
  assert(coord_system != NULL);
  assert(translation  != NULL);

  Point new_origin  = VecAdd(&coord_system->origin, translation);
  memcpy(&coord_system->origin, &new_origin, sizeof(Point));
}

void CoordSystemRotate(CoordSystem* coord_system, double angle)
{
  assert(coord_system != NULL);
  assert(isfinite(angle));

  Vec new_unit_x = VecRotate(&coord_system->unit_x, angle);
  Vec new_unit_y = VecRotate(&coord_system->unit_y, angle);

  memcpy(&coord_system->unit_x, &new_unit_x, sizeof(Vec));
  memcpy(&coord_system->unit_y, &new_unit_y, sizeof(Vec));
}

Vec CoordSystemGetOrigVector(const CoordSystem* coord_system,
                             const Vec*         vector)
{
  assert(coord_system != NULL);
  assert(vector       != NULL);

  Vec scaled_x = VecScale(&coord_system->unit_x, vector->x);
  Vec scaled_y = VecScale(&coord_system->unit_y, vector->y);
  
  return VecAdd(&scaled_x, &scaled_y);
}

Vec CoordSystemFromOrigVector(const CoordSystem* coord_system,
                              const Vec*         vector)
{
  // Use Cramer's rule to solve system of two linear equations
  // / a_00 a_01 \   / b_0 \
  // \ a_10 a_11 / = \ b_1 /
  
  const double matrix[2][2] =
    {
      { coord_system->unit_x.x, coord_system->unit_y.x},
      { coord_system->unit_x.y, coord_system->unit_y.y}
    };
  const double result[2] =
    {
      vector->x,
      vector->y
    };

  const double delta   = matrix[0][0] * matrix[1][1]
                       - matrix[0][1] * matrix[1][0];

  const double delta_x = result[0]    * matrix[1][1]
                       - matrix[0][1] * result[1];

  const double delta_y = matrix[0][0] * result[1]
                       - result[0]    * matrix[1][0];

  assert(fabs(delta) > EPS && "Invalid coordinate system");
  
  return { .x = delta_x / delta,
           .y = delta_y / delta };
}

