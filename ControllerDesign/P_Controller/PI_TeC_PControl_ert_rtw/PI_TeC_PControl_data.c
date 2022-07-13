/*
 * File: PI_TeC_PControl_data.c
 *
 * Code generated for Simulink model 'PI_TeC_PControl'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Wed Jul 13 02:20:24 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_TeC_PControl.h"
#include "PI_TeC_PControl_private.h"

/* Block parameters (default storage) */
P_PI_TeC_PControl_T PI_TeC_PControl_P = {
  /* Expression: -1
   * Referenced by: '<Root>/Analog Input'
   */
  -1.0,

  /* Expression: 50
   * Referenced by: '<Root>/Tref'
   */
  50.0,

  /* Expression: 0.625
   * Referenced by: '<Root>/bias for ambeint temperature 25°C*0.025V'
   */
  0.625,

  /* Expression: 0.04
   * Referenced by: '<Root>/conversion to °C'
   */
  0.04,

  /* Expression: 100
   * Referenced by: '<Root>/Kp'
   */
  100.0,

  /* Expression: 255
   * Referenced by: '<Root>/Saturation'
   */
  255.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation'
   */
  0.0,

  /* Computed Parameter: conversiontomillivolts_Gain
   * Referenced by: '<Root>/conversion to millivolts'
   */
  40039U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
