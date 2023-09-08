#include "vectors/vectors.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <math.h>

#include "vectors/coord_system.h"

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

Vec VecNormalize(const Vec* vector)
{
  const double length = VecLength(vector);

  if (fabs(length) < EPS)
  {
    errno = EINVAL;
    return VEC_EMPTY;
  }

  return VecScale(vector, 1.0/length);
}

Vec VecGetOrthogonal(const Vec* vector)
{
  return { .x = -vector->y,
           .y =  vector->x };
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

void VecDraw(const Vec* vector, const CoordSystem* coord_system,
             double width, sf::RenderTexture* render_target)
{
  assert(vector        != NULL);
  assert(coord_system  != NULL);
  assert(render_target != NULL);

  const double arrow_head_length = 8*width;
  const double arrow_head_width  = 4*width;
  
  // Transition to texture-relative coordinates
  const Vec target_vector = CoordSystemGetOrigVector(coord_system, vector);
  const double target_len = VecLength(&target_vector);

  // If target vector has zero length
  if (fabs(target_len) < EPS)
  {
    // Do not draw vector
    return;
  }

  // Create target-vector-relative coordinate system
  const Vec norm = VecNormalize(&target_vector);
  const Vec orth = VecGetOrthogonal(&norm);

  // Get line-head connection point
  const Vec   head_margin = VecScale(&norm, arrow_head_length / 2);
  const Point head_end    = VecAdd(&coord_system->origin, &target_vector);
  const Point head_start  = VecSub(&head_end, &head_margin);
  Point       line_start  = VEC_EMPTY;
  memcpy(&line_start, &coord_system->origin, sizeof(Point));

  // If target vector is longer than half of arrow-head
  if (target_len > arrow_head_length / 2)
  {
    // Draw arrow line
    const Vec line_half_width = VecScale(&orth, width / 2);

    const Point tail_left  = VecSub(&line_start, &line_half_width);
    const Point tail_right = VecAdd(&line_start, &line_half_width);
    const Point head_left  = VecSub(&head_start, &line_half_width);
    const Point head_right = VecAdd(&head_start, &line_half_width);

    const sf::Vertex vertex_array[] = {
      sf::Vertex(sf::Vector2f( tail_left.x,  tail_left.y), sf::Color::Black),
      sf::Vertex(sf::Vector2f(tail_right.x, tail_right.y), sf::Color::Black),
      sf::Vertex(sf::Vector2f(head_right.x, head_right.y), sf::Color::Black),
      sf::Vertex(sf::Vector2f( head_left.x,  head_left.y), sf::Color::Black)
    };

    render_target->draw(vertex_array, 4, sf::TriangleStrip);
  }

  // Draw arrow head
  const Vec head_half_width = VecScale(&orth, arrow_head_width / 2);
  const Vec head_vec_len    = VecScale(&norm, arrow_head_length);

  const Point head_back  = VecSub(&head_end, &head_vec_len);
  const Point head_left  = VecSub(&head_back, &head_half_width);
  const Point head_right = VecAdd(&head_back, &head_half_width);
  
  const sf::Vertex vertex_array[] = {
    sf::Vertex(sf::Vector2f( head_left.x,  head_left.y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(  head_end.x,   head_end.y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(head_start.x, head_start.y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(head_right.x, head_right.y), sf::Color::Black),
  };

  render_target->draw(vertex_array, 4, sf::TriangleStrip);
}
