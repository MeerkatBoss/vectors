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

Vec Vec::add(const Vec& other) const
{
  return Vec(m_x + other.m_x,
             m_y + other.m_y);
}

Vec Vec::sub(const Vec& other) const
{
  return Vec(m_x - other.m_x,
             m_y - other.m_y);
}

Vec Vec::scale(double scale) const
{
  return Vec(scale * m_x,
             scale * m_y);
}

Vec Vec::rotate(double angle) const
{
  const double sine   = sin(angle);
  const double cosine = cos(angle);

  return Vec(cosine * m_x - sine   * m_y,
             sine   * m_x + cosine * m_y);
}

Vec Vec::project_on(const Vec& other) const
{
  const double dot_product = Vec::dotProduct(other, *this);
  const double other_len   = other.length();

  if (fabs(other_len) < EPS)
  {
    errno = EINVAL;
    return Vec(NAN, NAN);
  }

  return other.scale(dot_product / other_len);
}

Vec Vec::getNormalized() const
{
  if (fabs(length()) < EPS)
  {
    errno = EINVAL;
    return Vec(NAN, NAN);
  }

  return scale(1.0/length());
}

Vec Vec::getOrthogonal() const
{
  return Vec(-m_y, m_x);
}

double Vec::dotProduct(const Vec& first, const Vec& second)
{
  return first.m_x * second.m_x
       + first.m_y * second.m_y;
}

double Vec::crossProduct(const Vec& first, const Vec& second)
{
  return first.m_x * second.m_y
       - first.m_y * second.m_x;
}

double Vec::length() const
{
  return hypot(m_x, m_y);
}

double Vec::angle_with(const Vec& other) const
{
  const double first_len  = length();
  const double second_len = other.length();

  if (fabs(first_len * second_len) < EPS)
  {
    errno = EINVAL;
    return NAN;
  }

  const double cosine = Vec::dotProduct(*this, other) / (first_len*second_len);
  assert(fabs(cosine) < 1);

  return acos(cosine);
}

void Vec::dump(int fd) const
{
  dprintf(fd, "Vec { x=%lg, y=%lg }\n", m_x, m_y);
}

void Vec::draw(const CoordSystem& coord_system, double width,
          sf::RenderTexture& render_target) const
{
  const double arrow_head_length = 8*width;
  const double arrow_head_width  = 4*width;

  // Transition to texture-relative coordinates
  const Vec target_vector = coord_system.getOrigVector(*this);
  const double target_len = target_vector.length();

  // If target vector has zero length
  if (fabs(target_len) < EPS)
  {
    // Do not draw vector
    return;
  }

  // Create target-vector-relative coordinate system
  const Vec norm = target_vector.getNormalized();
  const Vec orth = norm.getOrthogonal();

  // Get base points
  const Vec   head_margin = norm.scale(arrow_head_length / 2);
  const Point head_end    = coord_system.getOrigin().add(target_vector);
  const Point head_start  = head_end.sub(head_margin);
  Point       line_start  = coord_system.getOrigin();

  // If target vector is longer than half of arrow-head
  if (target_len > arrow_head_length / 2)
  {
    // Draw arrow line
    const Vec line_half_width = orth.scale(width / 2);

    const Point tail_left  = line_start.sub(line_half_width);
    const Point tail_right = line_start.add(line_half_width);
    const Point head_left  = head_start.sub(line_half_width);
    const Point head_right = head_start.add(line_half_width);

    const sf::Vertex vertex_array[] = {
      sf::Vertex(sf::Vector2f( tail_left.m_x,  tail_left.m_y), sf::Color::Black),
      sf::Vertex(sf::Vector2f(tail_right.m_x, tail_right.m_y), sf::Color::Black),
      sf::Vertex(sf::Vector2f(head_right.m_x, head_right.m_y), sf::Color::Black),
      sf::Vertex(sf::Vector2f( head_left.m_x,  head_left.m_y), sf::Color::Black)
    };

    render_target.draw(vertex_array, 4, sf::TriangleStrip);
  }

  // Draw arrow head
  const Vec head_half_width = orth.scale(arrow_head_width / 2);
  const Vec head_vec_len    = norm.scale(arrow_head_length);

  const Point head_back  = head_end.sub(head_vec_len);
  const Point head_left  = head_back.sub(head_half_width);
  const Point head_right = head_back.add(head_half_width);

  const sf::Vertex vertex_array[] = {
    sf::Vertex(sf::Vector2f( head_left.m_x,  head_left.m_y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(  head_end.m_x,   head_end.m_y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(head_start.m_x, head_start.m_y), sf::Color::Black),
    sf::Vertex(sf::Vector2f(head_right.m_x, head_right.m_y), sf::Color::Black),
  };

  render_target.draw(vertex_array, 4, sf::TriangleStrip);
}
