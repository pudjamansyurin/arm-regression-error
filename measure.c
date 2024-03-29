/*
 * measure.c
 *
 *  Created on: Apr 1, 2022
 *      Author: pudja
 */

#include "measure.h"
#include <math.h>

/* Private function */
static uint8_t is_nan(void *value)
{
    return (*(int*) value == 0x7FC00000);
}

/* Public function definitions */
/**
 * @brief Convert S16 to F32 format
 * @param s16p_src Pointer to S16 data
 * @param f32p_dst Pointer to F32 data
 * @param u16_len Data length
 */
void regr_s16_to_f32(const int16_t *s16p_src, float *f32p_dst, uint16_t u16_len)
{
    uint16_t u16_i;

    for (u16_i = 0; u16_i < u16_len; u16_i++) {
        f32p_dst[u16_i] = (float) s16p_src[u16_i];
    }
}

/**
 * @brief Calculate Signal to Noise Ratio (SNR) of two array
 * @param pRef Pointer to reference buffer
 * @param pTest Pointer to test buffer
 * @param len Length of the buffer
 * @return SNR value (in dB)
 */
float regr_snr_f32(float *pRef, float *pTest, uint32_t len)
{
    float EnergySignal = 0.0;
    float EnergyError = 0.0;
    float SNR;
    uint32_t i;

    for (i = 0; i < len; i++) {
        /* Checking for a NAN value in pRef array */
        if (is_nan(&pRef[i]))
            return (0);

        /* Checking for a NAN value in pTest array */
        if (is_nan(&pTest[i]))
            return (0);

        /* Sum of Energy Signal & Errors */
        EnergySignal += pRef[i] * pRef[i];
        EnergyError += (pRef[i] - pTest[i]) * (pRef[i] - pTest[i]);
    }

    /* Checking for a NAN value in EnergyError */
    if (is_nan(&EnergyError))
        return (0);

    /* Convert to dB */
    SNR = 10 * log10(EnergySignal / EnergyError);

    return (SNR);
}

/**
 * @brief Calculate Mean Square Error (MSE) of two array
 * @param pRef Pointer to reference buffer
 * @param pTest Pointer to test buffer
 * @param len Length of the buffer
 * @return MSE value
 */
float regr_mse_f32(float *pRef, float *pTest, uint32_t len)
{
    float EnergyError = 0.0;
    float MSE;
    uint32_t i;

    for (i = 0; i < len; i++) {
        /* Checking for a NAN value in pRef array */
        if (is_nan(&pRef[i]))
            return (0);

        /* Checking for a NAN value in pTest array */
        if (is_nan(&pTest[i]))
            return (0);

        /* Sum of square errors */
        EnergyError += (pRef[i] - pTest[i]) * (pRef[i] - pTest[i]);
    }

    /* Checking for a NAN value in EnergyError */
    if (is_nan(&EnergyError))
        return (0);

    /* Average the errors */
    MSE = EnergyError / len;

    return (MSE);

}

/**
 * @brief Calculate Root Mean Square Error (RMSE) of two array
 * @param pRef Pointer to reference buffer
 * @param pTest Pointer to test buffer
 * @param len Length of the buffer
 * @return RMSE value
 */
float regr_rmse_f32(float *pRef, float *pTest, uint32_t len)
{
    float MSE;
    float RMSE;

    /* Calculate MSE */
    MSE = regr_mse_f32(pRef, pTest, len);

    /* Checking for a NAN value */
    if (is_nan(&MSE))
        return (0);

    /* Square root */
    RMSE = sqrtf(MSE);

    return (RMSE);

}

/**
 * @brief Calculate Mean Absolute Error (MAE) of two array
 * @param pRef Pointer to reference buffer
 * @param pTest Pointer to test buffer
 * @param len Length of the buffer
 * @return MAE value
 */
float regr_mae_f32(float *pRef, float *pTest, uint32_t len)
{
    float EnergyError = 0.0;
    float MAE;
    uint32_t i;

    for (i = 0; i < len; i++) {
        /* Checking for a NAN value in pRef array */
        if (is_nan(&pRef[i]))
            return (0);

        /* Checking for a NAN value in pTest array */
        if (is_nan(&pTest[i]))
            return (0);

        /* Sum of absolute errors */
        EnergyError += fabsf(pRef[i] - pTest[i]);
    }

    /* Checking for a NAN value in EnergyError */
    if (is_nan(&EnergyError))
        return (0);

    /* Average the errors */
    MAE = EnergyError / len;

    return (MAE);

}

/**
 * @brief Calculate R-Square (R2) or Coefficient Determination of two array
 * @param pRef Pointer to reference buffer
 * @param pTest Pointer to test buffer
 * @param len Length of the buffer
 * @return R-Square value
 */
float regr_rsquare_f32(float *pRef, float *pTest, uint32_t len)
{
    float RSS = 0.0;
    float TSS = 0.0;
    float mean = 0.0;
    float R2;
    uint32_t i;

    /* Find reference signal mean */
    for (i = 0; i < len; i++) {
        mean += pRef[i];
    }
    mean /= len;

    for (i = 0; i < len; i++) {
        /* Checking for a NAN value in pRef array */
        if (is_nan(&pRef[i]))
            return (0);

        /* Checking for a NAN value in pTest array */
        if (is_nan(&pTest[i]))
            return (0);

        /* Sum of squares */
        RSS += (pRef[i] - pTest[i]) * (pRef[i] - pTest[i]);
        TSS += (pRef[i] - mean) * (pRef[i] - mean);
    }

    /* Checking for a NAN value in Sum of Squares of Residuals */
    if (is_nan(&RSS))
        return (0);

    /* Checking for a NAN value in Total Sum of Squares */
    if (is_nan(&TSS))
        return (0);

    /* Calculate R-Square */
    R2 = 1.0f - (RSS / TSS);

    return (R2);
}
