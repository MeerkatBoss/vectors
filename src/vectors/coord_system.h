/**
 * @file coord_system.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief Coordinate system for drawing vectors
 *
 * @version 0.1
 * @date 2023-09-06
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __VECTORS_COORD_SYSTEM_H
#define __VECTORS_COORD_SYSTEM_H

#include "vectors/vectors.h"

class CoordSystem
{
private:
  Point m_origin;
  Vec   m_unit_x;
  Vec   m_unit_y;

public:
  CoordSystem(Point origin, Vec unit_x, Vec unit_y)
      : m_origin(origin), m_unit_x(unit_x), m_unit_y(unit_y)
  {
  }

  ~CoordSystem() {}

  const Point& getOrigin() const { return m_origin; };
  const Vec&   getUnitX() const { return m_unit_x; };
  const Vec&   getUnitY() const { return m_unit_y; };

  /**
   * @brief Translate coordinate system by given vector
   *
   * @param[in]    translation	      Translation vector (with coordinates in
   *                                          independent coordinate system)
   */
  void translate(const Vec& translation);

  CoordSystem& operator+=(const Vec& translation)
  {
    translate(translation);
    return *this;
  }

  /**
   * @brief Rotate coordinate system around its origin
   *
   * @param[in] 	 angle              Rotation angle (in radians)
   */
  void rotate(double angle);

  /**
   * @brief Scale all unit vectors by given scale factor
   *
   * @param[in] scale	              Scale factor
   */
  void scale(double scale);

  CoordSystem& operator*=(double scale)
  {
    this->scale(scale);
    return *this;
  }

  /**
   * @brief Get original (coordinate-system-independent) coordinates of a vector
   *
   * @param[in] vector	              Vector with coordinates expressed in terms
   *                                    of coordinate system unit vectors
   *
   * @return Vector with coordinate-system-independent coordinates
   */
  Vec getOrigVector(const Vec& vector) const;

  Vec operator>>(const Vec& vector) const
  {
    return getOrigVector(vector);
  }

  /**
   * @brief Get coordinates of vector in coordinate system
   *
   * @param[in] vector	              Vector with coordinate-system-independent
   *                                    coordinates
   *
   * @return Vector with coordinates expressed in terms of coordinate system
   *           unit vectors
   */
  Vec fromOrigVector(const Vec& vector) const;

  Vec operator<<(const Vec& vector) const
  {
    return fromOrigVector(vector);
  }
};

#endif /* coord_system.h */
