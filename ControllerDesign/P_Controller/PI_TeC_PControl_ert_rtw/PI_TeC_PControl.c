/*
 * File: PI_TeC_PControl.c
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

/* Block states (default storage) */
DW_PI_TeC_PControl_T PI_TeC_PControl_DW;

/* Real-time model */
RT_MODEL_PI_TeC_PControl_T PI_TeC_PControl_M_;
RT_MODEL_PI_TeC_PControl_T *const PI_TeC_PControl_M = &PI_TeC_PControl_M_;

/* Forward declaration for local functions */
static void PI_TeC_PCo_SystemCore_release_c(codertarget_arduinobase_inter_T *obj);
static void PI_TeC_PCon_SystemCore_delete_c(codertarget_arduinobase_inter_T *obj);
static void matlabCodegenHandle_matlabCod_c(codertarget_arduinobase_inter_T *obj);
static void PI_TeC_PCont_SystemCore_release(codertarget_arduinobase_int_c_T *obj);
static void PI_TeC_PContr_SystemCore_delete(codertarget_arduinobase_int_c_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_c_T *obj);
static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_c_T *obj,
  j_codertarget_arduinobase_int_T *iobj_0);
static void PI_TeC_PCo_SystemCore_release_c(codertarget_arduinobase_inter_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
    MW_AnalogIn_Close(obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE);
  }
}

static void PI_TeC_PCon_SystemCore_delete_c(codertarget_arduinobase_inter_T *obj)
{
  PI_TeC_PCo_SystemCore_release_c(obj);
}

static void matlabCodegenHandle_matlabCod_c(codertarget_arduinobase_inter_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PI_TeC_PCon_SystemCore_delete_c(obj);
  }
}

static void PI_TeC_PCont_SystemCore_release(codertarget_arduinobase_int_c_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_SetDutyCycle(obj->MW_PWM_HANDLE, 0.0);
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_Close(obj->MW_PWM_HANDLE);
  }
}

static void PI_TeC_PContr_SystemCore_delete(codertarget_arduinobase_int_c_T *obj)
{
  PI_TeC_PCont_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_c_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PI_TeC_PContr_SystemCore_delete(obj);
  }
}

static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_c_T *obj,
  j_codertarget_arduinobase_int_T *iobj_0)
{
  iobj_0->AvailablePwmPinNames.f1 = '2';
  iobj_0->AvailablePwmPinNames.f2 = '3';
  iobj_0->AvailablePwmPinNames.f3 = '4';
  iobj_0->AvailablePwmPinNames.f4 = '5';
  iobj_0->AvailablePwmPinNames.f5 = '6';
  iobj_0->AvailablePwmPinNames.f6 = '7';
  iobj_0->AvailablePwmPinNames.f7 = '8';
  iobj_0->AvailablePwmPinNames.f8 = '9';
  iobj_0->AvailablePwmPinNames.f9[0] = '1';
  iobj_0->AvailablePwmPinNames.f9[1] = '0';
  iobj_0->AvailablePwmPinNames.f10[0] = '1';
  iobj_0->AvailablePwmPinNames.f10[1] = '1';
  iobj_0->AvailablePwmPinNames.f11[0] = '1';
  iobj_0->AvailablePwmPinNames.f11[1] = '2';
  iobj_0->AvailablePwmPinNames.f12[0] = '1';
  iobj_0->AvailablePwmPinNames.f12[1] = '3';
  obj->Hw = iobj_0;
  obj->PinPWM = 9UL;
}

/* Model step function */
void PI_TeC_PControl_step(void)
{
  uint16_T rtb_Vin_0;
  codertarget_arduinobase_inter_T *obj;
  codertarget_arduinobase_int_c_T *obj_0;
  real_T u0;

  /* MATLABSystem: '<Root>/Analog Input' */
  if (PI_TeC_PControl_DW.obj_h.SampleTime !=
      PI_TeC_PControl_P.AnalogInput_SampleTime) {
    PI_TeC_PControl_DW.obj_h.SampleTime =
      PI_TeC_PControl_P.AnalogInput_SampleTime;
  }

  obj = &PI_TeC_PControl_DW.obj_h;
  obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
  MW_AnalogInSingle_ReadResult
    (PI_TeC_PControl_DW.obj_h.AnalogInDriverObj.MW_ANALOGIN_HANDLE, &rtb_Vin_0,
     3);

  /* MATLABSystem: '<Root>/PWM' */
  obj_0 = &PI_TeC_PControl_DW.obj;
  obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PI_TeC_PControl_DW.obj.PinPWM);

  /* Gain: '<Root>/Kp' incorporates:
   *  Constant: '<Root>/Tref'
   *  Constant: '<Root>/bias for ambeint temperature 25°C*0.025V'
   *  Gain: '<Root>/conversion to millivolts'
   *  Gain: '<Root>/conversion to °C'
   *  MATLABSystem: '<Root>/Analog Input'
   *  Sum: '<Root>/Sum'
   *  Sum: '<Root>/Sum1'
   */
  u0 = (PI_TeC_PControl_P.Tref_Value - ((real_T)((uint32_T)
          PI_TeC_PControl_P.conversiontomillivolts_Gain * rtb_Vin_0) *
         0.0001220703125 - PI_TeC_PControl_P.biasforambeinttemperature25C002) *
        PI_TeC_PControl_P.conversiontoC_Gain) * PI_TeC_PControl_P.Kp_Gain;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > PI_TeC_PControl_P.Saturation_UpperSat) {
    u0 = PI_TeC_PControl_P.Saturation_UpperSat;
  } else {
    if (u0 < PI_TeC_PControl_P.Saturation_LowerSat) {
      u0 = PI_TeC_PControl_P.Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* MATLABSystem: '<Root>/PWM' */
  if (!(u0 < 255.0)) {
    u0 = 255.0;
  }

  if (!(u0 > 0.0)) {
    u0 = 0.0;
  }

  MW_PWM_SetDutyCycle(PI_TeC_PControl_DW.obj.MW_PWM_HANDLE, u0);
}

/* Model initialize function */
void PI_TeC_PControl_initialize(void)
{
  {
    codertarget_arduinobase_inter_T *obj;
    codertarget_arduinobase_int_c_T *obj_0;

    /* Start for MATLABSystem: '<Root>/Analog Input' */
    PI_TeC_PControl_DW.obj_h.matlabCodegenIsDeleted = true;
    PI_TeC_PControl_DW.obj_h.isInitialized = 0L;
    PI_TeC_PControl_DW.obj_h.SampleTime = -1.0;
    PI_TeC_PControl_DW.obj_h.matlabCodegenIsDeleted = false;
    PI_TeC_PControl_DW.obj_h.SampleTime =
      PI_TeC_PControl_P.AnalogInput_SampleTime;
    obj = &PI_TeC_PControl_DW.obj_h;
    PI_TeC_PControl_DW.obj_h.isSetupComplete = false;
    PI_TeC_PControl_DW.obj_h.isInitialized = 1L;
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(14UL);
    PI_TeC_PControl_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/PWM' */
    PI_TeC_PControl_DW.obj.matlabCodegenIsDeleted = true;
    PI_TeC_PControl_DW.obj.isInitialized = 0L;
    PI_TeC_PControl_DW.obj.matlabCodegenIsDeleted = false;
    arduino_PWMOutput_set_pinNumber(&PI_TeC_PControl_DW.obj,
      &PI_TeC_PControl_DW.gobj_2);
    obj_0 = &PI_TeC_PControl_DW.obj;
    PI_TeC_PControl_DW.obj.isSetupComplete = false;
    PI_TeC_PControl_DW.obj.isInitialized = 1L;
    obj_0->MW_PWM_HANDLE = MW_PWM_Open(PI_TeC_PControl_DW.obj.PinPWM, 0.0, 0.0);
    obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PI_TeC_PControl_DW.obj.PinPWM);
    MW_PWM_Start(PI_TeC_PControl_DW.obj.MW_PWM_HANDLE);
    PI_TeC_PControl_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void PI_TeC_PControl_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  matlabCodegenHandle_matlabCod_c(&PI_TeC_PControl_DW.obj_h);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  matlabCodegenHandle_matlabCodeg(&PI_TeC_PControl_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
