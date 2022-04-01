# ARM Regression Error Calculator

## How to use the module

#### **`main.c`**

```c
#include "arm_regression_error/measure.h"

#define BUF_SZ  (5)

int main(void)
{
  float pReff[BUF_SZ] = { 0.1, 0.2, 0.3, 0.4, 0.5 };
  float pTest[BUF_SZ] = { 0.15, 0.21, 0.34, 0.46, 0.52 };
  float value;

  /* Super loop */
  while(1) {
    /* Calculate SNR (in dB) */
    value = arm_snr_f32(pReff, pTest, BUF_SZ);

    /* Calculate MSE */
    value = arm_mse_f32(pReff, pTest, BUF_SZ);

    /* Calculate RMSE */
    value = arm_rmse_f32(pReff, pTest, BUF_SZ);
    
    /* Calculate MAE */
    value = arm_mae_f32(pReff, pTest, BUF_SZ);

    /* Calculate R-Square */
    value = arm_rsquare_f32(pReff, pTest, BUF_SZ);
  }
}
```