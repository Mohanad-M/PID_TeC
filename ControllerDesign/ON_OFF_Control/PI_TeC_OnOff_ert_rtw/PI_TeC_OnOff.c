/*
 * File: PI_TeC_OnOff.c
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

#include "PI_TeC_OnOff.h"
#include "PI_TeC_OnOff_private.h"

/* Block states (default storage) */
DW_PI_TeC_OnOff_T PI_TeC_OnOff_DW;

/* Real-time model */
RT_MODEL_PI_TeC_OnOff_T PI_TeC_OnOff_M_;
RT_MODEL_PI_TeC_OnOff_T *const PI_TeC_OnOff_M = &PI_TeC_OnOff_M_;

/* Forward declaration for local functions */
static void PI_TeC_OnOff_SystemCore_release(codertarget_arduinobase_inter_T *obj);
static void PI_TeC_OnOf_SystemCore_delete_n(codertarget_arduinobase_inter_T *obj);
static void matlabCodegenHandle_matlabCod_n(codertarget_arduinobase_inter_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_block_T *obj);
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void PI_TeC_OnOff_SystemCore_release(codertarget_arduinobase_inter_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
    MW_AnalogIn_Close(obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE);
  }
}

static void PI_TeC_OnOf_SystemCore_delete_n(codertarget_arduinobase_inter_T *obj)
{
  PI_TeC_OnOff_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCod_n(codertarget_arduinobase_inter_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PI_TeC_OnOf_SystemCore_delete_n(obj);
  }
}

static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void PI_TeC_OnOff_step(void)
{
  uint16_T rtb_Vin_0;
  codertarget_arduinobase_inter_T *obj;
  real_T tmp;
  uint8_T tmp_0;

  /* MATLABSystem: '<Root>/Analog Input' */
  if (PI_TeC_OnOff_DW.obj.SampleTime != PI_TeC_OnOff_P.AnalogInput_SampleTime) {
    PI_TeC_OnOff_DW.obj.SampleTime = PI_TeC_OnOff_P.AnalogInput_SampleTime;
  }

  obj = &PI_TeC_OnOff_DW.obj;
  obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
  MW_AnalogInSingle_ReadResult
    (PI_TeC_OnOff_DW.obj.AnalogInDriverObj.MW_ANALOGIN_HANDLE, &rtb_Vin_0, 3);

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/HiOut'
   *  Constant: '<Root>/LoOut'
   *  Constant: '<Root>/Tref'
   *  Constant: '<Root>/bias for ambeint temperature 25°C*0.025V'
   *  Gain: '<Root>/conversion to millivolts'
   *  Gain: '<Root>/conversion to °C'
   *  MATLABSystem: '<Root>/Analog Input'
   *  Sum: '<Root>/Sum'
   *  Sum: '<Root>/Sum1'
   */
  if (PI_TeC_OnOff_P.Tref_Value - ((real_T)((uint32_T)
        PI_TeC_OnOff_P.conversiontomillivolts_Gain * rtb_Vin_0) *
       0.0001220703125 - PI_TeC_OnOff_P.biasforambeinttemperature25C002) *
      PI_TeC_OnOff_P.conversiontoC_Gain >= PI_TeC_OnOff_P.Switch_Threshold) {
    tmp = PI_TeC_OnOff_P.HiOut_Value;
  } else {
    tmp = PI_TeC_OnOff_P.LoOut_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* MATLABSystem: '<Root>/Digital Output' */
  tmp = rt_roundd_snf(tmp);
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint8_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint8_T;
  }

  writeDigitalPin(9, tmp_0);

  /* End of MATLABSystem: '<Root>/Digital Output' */
}

/* Model initialize function */
void PI_TeC_OnOff_initialize(void)
{
  {
    codertarget_arduinobase_inter_T *obj;

    /* Start for MATLABSystem: '<Root>/Analog Input' */
    PI_TeC_OnOff_DW.obj.matlabCodegenIsDeleted = true;
    PI_TeC_OnOff_DW.obj.isInitialized = 0L;
    PI_TeC_OnOff_DW.obj.SampleTime = -1.0;
    PI_TeC_OnOff_DW.obj.matlabCodegenIsDeleted = false;
    PI_TeC_OnOff_DW.obj.SampleTime = PI_TeC_OnOff_P.AnalogInput_SampleTime;
    obj = &PI_TeC_OnOff_DW.obj;
    PI_TeC_OnOff_DW.obj.isSetupComplete = false;
    PI_TeC_OnOff_DW.obj.isInitialized = 1L;
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(14UL);
    PI_TeC_OnOff_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Output' */
    PI_TeC_OnOff_DW.obj_l.matlabCodegenIsDeleted = false;
    PI_TeC_OnOff_DW.obj_l.isInitialized = 1L;
    digitalIOSetup(9, 1);
    PI_TeC_OnOff_DW.obj_l.isSetupComplete = true;
  }
}

/* Model terminate function */
void PI_TeC_OnOff_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  matlabCodegenHandle_matlabCod_n(&PI_TeC_OnOff_DW.obj);

  /* Terminate for MATLABSystem: '<Root>/Digital Output' */
  matlabCodegenHandle_matlabCodeg(&PI_TeC_OnOff_DW.obj_l);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
