/*
 * File: PI_TeC_OnOff.h
 *
 * Code generated for Simulink model 'PI_TeC_OnOff'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Tue Jul 12 17:44:36 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PI_TeC_OnOff_h_
#define RTW_HEADER_PI_TeC_OnOff_h_
#include <math.h>
#include <stddef.h>
#ifndef PI_TeC_OnOff_COMMON_INCLUDES_
# define PI_TeC_OnOff_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_arduino_digitalio.h"
#include "MW_AnalogIn.h"
#endif                                 /* PI_TeC_OnOff_COMMON_INCLUDES_ */

#include "PI_TeC_OnOff_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/Analog Input' */
  codertarget_arduinobase_block_T obj_l;/* '<Root>/Digital Output' */
} DW_PI_TeC_OnOff_T;

/* Parameters (default storage) */
struct P_PI_TeC_OnOff_T_ {
  real_T LoOut_Value;                  /* Expression: 0
                                        * Referenced by: '<Root>/LoOut'
                                        */
  real_T HiOut_Value;                  /* Expression: 1
                                        * Referenced by: '<Root>/HiOut'
                                        */
  real_T AnalogInput_SampleTime;       /* Expression: -1
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  real_T Tref_Value;                   /* Expression: 50
                                        * Referenced by: '<Root>/Tref'
                                        */
  real_T biasforambeinttemperature25C002;/* Expression: 0.625
                                          * Referenced by: '<Root>/bias for ambeint temperature 25°C*0.025V'
                                          */
  real_T conversiontoC_Gain;           /* Expression: 0.04
                                        * Referenced by: '<Root>/conversion to °C'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<Root>/Switch'
                                        */
  uint16_T conversiontomillivolts_Gain;
                              /* Computed Parameter: conversiontomillivolts_Gain
                               * Referenced by: '<Root>/conversion to millivolts'
                               */
};

/* Real-time Model Data Structure */
struct tag_RTM_PI_TeC_OnOff_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_PI_TeC_OnOff_T PI_TeC_OnOff_P;

/* Block states (default storage) */
extern DW_PI_TeC_OnOff_T PI_TeC_OnOff_DW;

/* Model entry point functions */
extern void PI_TeC_OnOff_initialize(void);
extern void PI_TeC_OnOff_step(void);
extern void PI_TeC_OnOff_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PI_TeC_OnOff_T *const PI_TeC_OnOff_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PI_TeC_OnOff'
 * '<S1>'   : 'PI_TeC_OnOff/Model Info'
 */
#endif                                 /* RTW_HEADER_PI_TeC_OnOff_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
