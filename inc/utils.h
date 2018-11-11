/**
 * @file utils.h
 *
 * @brief Mathematic utilitary functions.
 *
 * @date 11/2018
 */

#ifndef __UTILS_H__
#define __UTILS_H__

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Maps an integer value from one scale to another.
 *
 * @param former_value Value in former scale.
 * @param former_min   Former scale minimum value.
 * @param former_max   Former scale maximum value.
 * @param new_min      New scale minimum value.
 * @param new_max      New scale maximum value.
 *
 * @return Value in new scale
 */
float map(float former_value, float former_min, float former_max, float new_min, float new_max);

#endif  // __UTILS_H__
