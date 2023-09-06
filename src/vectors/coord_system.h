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

struct CoordSystem
{
  Point origin;
  Vec   unit_x;
  Vec   unit_y;
};

#define COORD_SYSTEM_EMPTY                                                     \
  {                                                                            \
    .origin = VEC_EMPTY, .unit_x = VEC_EMPTY, .unit_y = VEC_EMPTY              \
  }

/**
 * @brief Initialize coordinate system
 *
 * @param[out] coord_system	    Initialized coordinate system
 * @param[in]  origin	          Origin point of coordinate system
 * @param[in]  unit_x	          Unit vector of x axis
 * @param[in]  unit_y	          Unit vector of y axis
 *
 * @error EINVAL      unit_x and unit_y are collinear vectors
 */
void CoordSystemCtor(CoordSystem* coord_system, const Point* origin,
                     const Vec* unit_x, const Vec* unit_y);

/**
 * @brief Deinitialize coordinate system
 *
 * @param[out] coord_system	    Destroyed coordinate system
 */
void CoordSystemDtor(CoordSystem* coord_system);

/**
 * @brief Translate coordinate system by given vector
 *
 * @param[inout] coord_system       Translated coordinate system
 * @param[in]    translation	      Translation vector (with coordinates in
 *                                          independent coordinate system)
 */
void CoordSystemTranslate(CoordSystem* coord_system, const Vec* translation);

/**
 * @brief Rotate coordinate system around its origin
 * 
 * @param[inout] coord_system       Rotated coordinate system
 * @param[in] 	 angle              Rotation angle (in radians)
 */
void CoordSystemRotate(CoordSystem* coord_system, double angle);

/**
 * @brief Get original (coordinate-system-independent) coordinates of a vector
 *
 * @param[in] coord_system	        Target coordinate system
 * @param[in] vector	              Vector with coordinates expressed in terms
 *                                    of coordinate system unit vectors
 *
 * @return Vector with coordinate-system-independent coordinates
 */
Vec CoordSystemGetOrigVector(const CoordSystem* coord_system,
                             const Vec*         vector);

/**
 * @brief Get coordinates of vector in given coordinate system
 *
 * @param[in] coord_system	        Target coordinate system
 * @param[in] vector	              Vector with coordinate-system-independent
 *                                    coordinates
 *
 * @return Vector with coordinates expressed in terms of coordinate system
 *           unit vectors
 */
Vec CoordSystemFromOrigVector(const CoordSystem* coord_system,
                              const Vec*         vector);

#endif /* coord_system.h */
