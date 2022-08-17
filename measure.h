/*
 * measure.h
 *
 *  Created on: Apr 1, 2022
 *      Author: pudja
 */

#ifndef REGRESSION_ERROR_H_
#define REGRESSION_ERROR_H_

#include <stdint.h>

/* Public function prototypes */
void regr_s16_to_f32(const int16_t *s16p_src, float *f32p_dst, uint16_t u16_len);
float regr_snr_f32(float *pRef, float *pTest, uint32_t len);
float regr_mse_f32(float *pRef, float *pTest, uint32_t len);
float regr_rmse_f32(float *pRef, float *pTest, uint32_t len);
float regr_mae_f32(float *pRef, float *pTest, uint32_t len);
float regr_rsquare_f32(float *pRef, float *pTest, uint32_t len);

#endif /* REGRESSION_ERROR_H_ */
