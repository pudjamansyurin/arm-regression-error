/*
 * measure.h
 *
 *  Created on: Apr 1, 2022
 *      Author: pudja
 */

#ifndef ARM_REGRESSION_ERROR_H_
#define ARM_REGRESSION_ERROR_H_

#include <stdint.h>

/* Public function prototypes */
void arm_s16_to_f32(const int16_t *s16p_src, float *f32p_dst, uint16_t u16_len);
float arm_snr_f32(float *pRef, float *pTest, uint32_t len);
float arm_mse_f32(float *pRef, float *pTest, uint32_t len);
float arm_rmse_f32(float *pRef, float *pTest, uint32_t len);
float arm_mae_f32(float *pRef, float *pTest, uint32_t len);
float arm_rsquare_f32(float *pRef, float *pTest, uint32_t len);

#endif /* ARM_REGRESSION_ERROR_H_ */
