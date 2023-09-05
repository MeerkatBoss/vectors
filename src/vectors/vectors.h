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

#include <cmath>

struct Vec
{
  double x, y;
};

typedef Vec Point;

#define VEC_EMPTY                                                              \
  {                                                                            \
    .x = NAN, .y = NAN                                                         \
  }

/**
 * @brief Initialize Vec struct
 *
 * @param[out] vector	  Initialized struct
 * @param[in]  x	      Vector x coordinate
 * @param[in]  y	      Vector y coordinate
 *
 */
void VecCtor(Vec* vector, double x, double y);

/**
 * @brief Deinitialize Vec struct
 *
 * @param[out] vector	  Deinitialized struct
 *
 */
void VecDtor(Vec* vector);

/**
 * @brief Get sum of vectors
 *
 * @param[in] first	    First addend
 * @param[in] second	  Second addend
 *
 * @return Sum of `first` and `second`
 */
Vec VecAdd(const Vec* first, const Vec* second);

/**
 * @brief Get difference of vectors
 *
 * @param[in] first	    Minuend
 * @param[in] second    Subtrahend
 *
 * @return Difference of `first` and `second`
 */
Vec VecSub(const Vec* first, const Vec* second);

/**
 * @brief Scale vector by given factor
 *
 * @param[in] vector	  Vector to be scaled
 * @param[in] scale	    Scale factor
 *
 * @return Scaled vector
 */
Vec VecScale(const Vec* vector, double scale);

/**
 * @brief Rotate vector around its origin by given angle
 *
 * @param[in] vector	  Vector to be rotated
 * @param[in] angle	    Angle of rotation (in radians)
 *
 * @return Rotated vector
 */
Vec VecRotate(const Vec* vector, double angle);

/**
 * @brief Get vector projection of one vector on another
 *
 * @param[in] project_on	  Vector to be projected on
 * @param[in] projected	    Projected vector
 *
 * @error EINVAL    project_on is zero-length vector
 *
 * @return Projection of `projected` on `project_on`
 */
Vec VecProject(const Vec* project_on, const Vec* projected);

/**
 * @brief Get dot product of two vectors
 *
 * @param[in] first	    First operand
 * @param[in] second	  Second operand
 *
 * @return Dot product of `first` and `second`
 */
double VecDotProduct(const Vec* first, const Vec* second);

/**
 * @brief Get signed area of a parallelogram based on given vectors
 *
 * @param[in] first	    First operand
 * @param[in] second	  Second operand
 *
 * @return Signed area of `first` and `second`
 */
double VecSignedArea(const Vec* first, const Vec* second);

/**
 * @brief Get length of vector
 *
 * @param[in] vector	  Target vector for length calculation
 *
 * @return Length of `vector`
 */
double VecLength(const Vec* vector);

/**
 * @brief Get angle (in radians) between vectors
 *
 * @param[in] first	    First operand
 * @param[in] second	  Second operand
 *
 * @error EINVAL    `first` or `second` is zero-length vector
 *
 * @return Angle (in radians) between `first` and `second`
 */
double VecAngle(const Vec* first, const Vec* second);

/**
 * @brief Write internal representation of vector to file descriptor
 *
 * @param[in] vector	  Vector to be printed
 * @param[in] fd	      Output file descriptor
 */
void VecDump(const Vec* vector, int fd);

#endif /* vectors.h */
