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
#include <cmath>

// Forward declaration
class CoordSystem;

class Vec
{
public:
  double m_x, m_y;

  Vec(double x, double y) : m_x(x), m_y(y) {}
  Vec(const Vec& other) : m_x(other.m_x), m_y(other.m_y) {}

  ~Vec()
  {
    m_x = NAN;
    m_y = NAN;
  }

  /**
   * @brief Add vector
   *
   * @param[in] other	    Second addend
   *
   * @return Sum of vectors
   */
  Vec add(const Vec& other) const;

  /**
   * @brief Subtract vector
   *
   * @param[in] other    Subtrahend
   *
   * @return Difference between vector and `other`
   */
  Vec sub(const Vec& other) const;

  /**
   * @brief Scale vector by given factor
   *
   * @param[in] scale	    Scale factor
   *
   * @return Scaled vector
   */
  Vec scale(double scale) const;

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

  /**
   * @brief Get normalized vector
   *
   * @error EINVAL    vector has length of zero
   *
   * @return Normalized vector
   */
  Vec getNormalized() const;

  /**
   * @brief Get orthogonal vector
   *
   * @return Orthogonal vector with the same length as this
   */
  Vec getOrthogonal() const;

  /**
   * @brief Get dot product of two vectors
   *
   * @param[in] first	    First operand
   * @param[in] second	  Second operand
   *
   * @return Dot product of `first` and `second`
   */
  static double dotProduct(const Vec& first, const Vec& second);

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

#endif /* vectors.h */
