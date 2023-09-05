#include "vectors/vectors.h"

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <math.h>

#include "vectors.h"

#define EPS 1e-6

void VecCtor(Vec* vector, double x, double y)
{
  vector->x = x;
  vector->y = y;
}

void VecDtor(Vec* vector)
{
  vector->x = NAN;
  vector->y = NAN;
}

Vec VecAdd(const Vec* first, const Vec* second)
{
  return {first->x + second->x,
          first->y + second->y};
}

Vec VecSub(const Vec* first, const Vec* second)
{
  return {first->x - second->x,
          first->y - second->y};
}

Vec VecScale(const Vec* vector, double scale)
{
  return {scale * vector->x,
          scale * vector->y};
}

Vec VecRotate(const Vec* vector, double angle)
{
  const double sine   = sin(angle);
  const double cosine = cos(angle);

  return {cosine * vector->x - sine   * vector->y,
          sine   * vector->x + cosine * vector->y};
}

Vec VecProject(const Vec* project_on, const Vec* projected)
{
  const double dot_product = VecDotProduct(project_on, projected);
  const double target_len  = VecLength(project_on);

  if (fabs(target_len) < EPS)
  {
    errno = EINVAL;
    return VEC_EMPTY;
  }

  return VecScale(project_on, dot_product / target_len);
}

double VecSignedArea(const Vec* first, const Vec* second)
{
  return first->x * second->y
       - first->y * second->x;
}

double VecDotProduct(const Vec* first, const Vec* second)
{
  return first->x * second->x
       + first->y * second->y;
}

double VecLength(const Vec* vector)
{
  return hypot(vector->x, vector->y);
}

double VecAngle(const Vec* first, const Vec* second)
{
  const double first_len  = VecLength(first);
  const double second_len = VecLength(second);

  if (fabs(first_len * second_len) < EPS)
  {
    errno = EINVAL;
    return NAN;
  }

  const double cosine = VecDotProduct(first, second) / (first_len * second_len);
  assert(fabs(cosine) < 1);

  return acos(cosine);
}

void VecDump(const Vec* vector, int fd)
{
  dprintf(fd, "Vec { x=%lg, y=%lg }\n", vector->x, vector->y);
}
