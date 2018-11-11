/**
 * @file utils.c
 *
 * @brief Mathematic utilitary functions.
 */

#include "utils.h"

/*****************************************
 * Public Function Body Definitions
 *****************************************/

float map(float former_value, float former_min, float former_max, float new_min, float new_max) {
    float new_value;

    new_value = (former_value - former_min) * (new_max - new_min);
    new_value /= (former_max - former_min);
    new_value += new_min;

    return new_value;
}
