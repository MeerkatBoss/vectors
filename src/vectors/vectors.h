/**
 * @file vectors.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief 2D vector with double-precision floating-point coordinates
 *
 * @version 0.1
 * @date 2023-09-05
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __VECTORS_VECTORS_H
#define __VECTORS_VECTORS_H

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

// Forward declaration
class CoordSystem;

class Vec
{
public:
  double m_x, m_y;

  Vec(double x, double y) : m_x(x), m_y(y) {}
  Vec(const Vec& other) : m_x(other.m_x), m_y(other.m_y) {}

  Vec(sf::Vector2f sf_vector) : m_x(sf_vector.x), m_y(sf_vector.y) {}
  operator sf::Vector2f() const { return sf::Vector2f(m_x, m_y); }

  Vec& operator=(const Vec& other)
  {
    m_x = other.m_x;
    m_y = other.m_y;

    return *this;
  }

  ~Vec()
  {
    m_x = NAN;
    m_y = NAN;
  }

  double& operator[](size_t index)
  {
    return index % 2 == 0 ? m_x : m_y;
  }

  double operator[](size_t index) const
  {
    return index % 2 == 0 ? m_x : m_y;
  }

  /**
   * @brief Add vector
   *
   * @param[in] other	    Second addend
   *
   * @return Sum of vectors
   */
  Vec operator+(const Vec& other) const;

  Vec& operator+=(const Vec& other)
  {
    *this = *this + other;
    return *this;
  }

  /**
   * @brief Subtract vector
   *
   * @param[in] other    Subtrahend
   *
   * @return Difference between vector and `other`
   */
  Vec operator-(const Vec& other) const;

  Vec& operator-=(const Vec& other)
  {
    *this = *this - other;
    return *this;
  }

  /**
   * @brief Scale vector by given factor
   *
   * @param[in] scale	    Scale factor
   *
   * @return Scaled vector
   */
  Vec operator*(double scale) const;

  Vec& operator*=(double scale)
  {
    *this = *this * scale;
    return *this;
  }

  Vec operator-() const { return *this * (-1); }
  Vec operator+() const { return *this; }

  /**
   * @brief Scale vector by inverse of given factor
   *
   * @param[in] scale	    Scale factor
   *
   * @error EINVAL      Scale factor is zero
   *
   * @return Scaled vector
   */
  Vec operator/(double scale) const;

  Vec& operator/=(double scale)
  {
    *this = *this / scale;
    return *this;
  }

  /**
   * @brief Rotate vector around its origin by given angle
   *
   * @param[in] angle	    Angle of rotation (in radians)
   *
   * @return Rotated vector
   */
  Vec rotate(double angle) const;

  /**
   * @brief Get vector projection on another vector
   *
   * @param[in] project_on	  Vector to be projected on
   *
   * @error EINVAL    `project_on` is zero-length vector
   *
   * @return Projection on `project_on`
   */
  Vec project_on(const Vec& other) const;

  Vec operator<<(const Vec& other) const { return other.project_on(*this); }
  Vec operator>>(const Vec& other) const { return project_on(other); }

  Vec& operator<<=(const Vec& other) { return (*this = *this << other); }
  Vec& operator>>=(const Vec& other) { return (*this = *this >> other); }

  /**
   * @brief Convert vector from coordinate system coordinates
   *
   * @param[in] coords	  Coordinate system
   *
   * @return Converted vector
   */
  Vec operator<<(const CoordSystem& coords) const;

  Vec& operator<<=(const CoordSystem& coords)
  {
    return (*this = *this << coords);
  }

  /**
   * @brief Convert vector to coordinate system coordinates
   *
   * @param[in] coords	  Coordinate system
   *
   * @return Converted vector
   */
  Vec operator>>(const CoordSystem& coords) const;

  Vec& operator>>=(const CoordSystem& coords)
  {
    return (*this = *this >> coords);
  }

  /**
   * @brief Get normalized vector
   *
   * @error EINVAL    vector has length of zero
   *
   * @return Normalized vector
   */
  Vec getNormalized() const;

  Vec operator&() const { return getNormalized(); }

  /**
   * @brief Get orthogonal vector
   *
   * @return Orthogonal vector with the same length as this
   */
  Vec getOrthogonal() const;

  Vec operator~() const { return getOrthogonal(); }

  /**
   * @brief Get dot product of two vectors
   *
   * @param[in] first	    First operand
   * @param[in] second	  Second operand
   *
   * @return Dot product of `first` and `second`
   */
  static double dotProduct(const Vec& first, const Vec& second);

  double operator,(const Vec& other) const { return dotProduct(*this, other); }

  /**
   * @brief Get cross product of given vectors
   *
   * @param[in] first	    First operand
   * @param[in] second	  Second operand
   *
   * @return Cross product of `first` and `second`
   */
  static double crossProduct(const Vec& first, const Vec& second);

  /**
   * @brief Get length of vector
   *
   * @return Vector length
   */
  double length() const;

  bool operator!() const;

  /**
   * @brief Get angle (in radians) between this vector and another one
   *
   * @param[in] other	    Second operand
   *
   * @error EINVAL        this or `other` have zero length
   *
   * @return Angle (in radians) between this and `other`
   */
  double angle_with(const Vec& other) const;

  double operator^(const Vec& other) const
  {
    return angle_with(other);
  }

  double operator||(const Vec& other) const;

  /**
   * @brief Write internal representation of vector to file descriptor
   *
   * @param[in] fd	      Output file descriptor
   */
  void dump(int fd) const;

  /**
   * @brief Draw vector on target texture using given coordinate system
   *
   * @param[in]    coord_system	  Target coordinate system
   * @param[in]    width	        Width in pixels of drawn vector
   * @param[inout] render_target	Target render texture
   */
  void draw(const CoordSystem& coord_system, double width,
            sf::RenderTexture& render_target) const;

};

typedef Vec Point;

Vec operator*(double scale, const Vec& vector);

bool operator==(const Vec& first, const Vec& second);
bool operator!=(const Vec& first, const Vec& second);


#endif /* vectors.h */
