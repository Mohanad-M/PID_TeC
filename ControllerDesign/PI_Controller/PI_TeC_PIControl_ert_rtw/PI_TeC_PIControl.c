/*
 * File: PI_TeC_PIControl.c
 *
 * Code generated for Simulink model 'PI_TeC_PIControl'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Wed Jul 13 03:04:19 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_TeC_PIControl.h"
#include "PI_TeC_PIControl_private.h"

/* Block signals (default storage) */
B_PI_TeC_PIControl_T PI_TeC_PIControl_B;

/* Continuous states */
X_PI_TeC_PIControl_T PI_TeC_PIControl_X;

/* Block states (default storage) */
DW_PI_TeC_PIControl_T PI_TeC_PIControl_DW;

/* Real-time model */
RT_MODEL_PI_TeC_PIControl_T PI_TeC_PIControl_M_;
RT_MODEL_PI_TeC_PIControl_T *const PI_TeC_PIControl_M = &PI_TeC_PIControl_M_;

/* Forward declaration for local functions */
static void PI_TeC_PIC_SystemCore_release_g(codertarget_arduinobase_inter_T *obj);
static void PI_TeC_PICo_SystemCore_delete_g(codertarget_arduinobase_inter_T *obj);
static void matlabCodegenHandle_matlabCod_g(codertarget_arduinobase_inter_T *obj);
static void PI_TeC_PICon_SystemCore_release(codertarget_arduinobase_int_g_T *obj);
static void PI_TeC_PICont_SystemCore_delete(codertarget_arduinobase_int_g_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_g_T *obj);
static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_g_T *obj,
  j_codertarget_arduinobase_int_T *iobj_0);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PI_TeC_PIControl_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  PI_TeC_PIControl_step();
  PI_TeC_PIControl_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  PI_TeC_PIControl_step();
  PI_TeC_PIControl_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

static void PI_TeC_PIC_SystemCore_release_g(codertarget_arduinobase_inter_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
    MW_AnalogIn_Close(obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE);
  }
}

static void PI_TeC_PICo_SystemCore_delete_g(codertarget_arduinobase_inter_T *obj)
{
  PI_TeC_PIC_SystemCore_release_g(obj);
}

static void matlabCodegenHandle_matlabCod_g(codertarget_arduinobase_inter_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PI_TeC_PICo_SystemCore_delete_g(obj);
  }
}

static void PI_TeC_PICon_SystemCore_release(codertarget_arduinobase_int_g_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_SetDutyCycle(obj->MW_PWM_HANDLE, 0.0);
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_Close(obj->MW_PWM_HANDLE);
  }
}

static void PI_TeC_PICont_SystemCore_delete(codertarget_arduinobase_int_g_T *obj)
{
  PI_TeC_PICon_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_g_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PI_TeC_PICont_SystemCore_delete(obj);
  }
}

static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_g_T *obj,
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
void PI_TeC_PIControl_step(void)
{
  uint16_T rtb_Vin_0;
  codertarget_arduinobase_inter_T *obj;
  codertarget_arduinobase_int_g_T *obj_0;
  real_T u0;
  if (rtmIsMajorTimeStep(PI_TeC_PIControl_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&PI_TeC_PIControl_M->solverInfo,
                          ((PI_TeC_PIControl_M->Timing.clockTick0+1)*
      PI_TeC_PIControl_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PI_TeC_PIControl_M)) {
    PI_TeC_PIControl_M->Timing.t[0] = rtsiGetT(&PI_TeC_PIControl_M->solverInfo);
  }

  /* MATLABSystem: '<Root>/Analog Input' */
  if (PI_TeC_PIControl_DW.obj_h.SampleTime !=
      PI_TeC_PIControl_P.AnalogInput_SampleTime) {
    PI_TeC_PIControl_DW.obj_h.SampleTime =
      PI_TeC_PIControl_P.AnalogInput_SampleTime;
  }

  obj = &PI_TeC_PIControl_DW.obj_h;
  obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
  MW_AnalogInSingle_ReadResult
    (PI_TeC_PIControl_DW.obj_h.AnalogInDriverObj.MW_ANALOGIN_HANDLE, &rtb_Vin_0,
     3);

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Tref'
   *  Constant: '<Root>/bias for ambeint temperature 25°C*0.025V'
   *  Gain: '<Root>/conversion to millivolts'
   *  Gain: '<Root>/conversion to °C'
   *  MATLABSystem: '<Root>/Analog Input'
   *  Sum: '<Root>/Sum'
   */
  PI_TeC_PIControl_B.error = PI_TeC_PIControl_P.Tref_Value - ((real_T)((uint32_T)
    PI_TeC_PIControl_P.conversiontomillivolts_Gain * rtb_Vin_0) *
    0.0001220703125 - PI_TeC_PIControl_P.biasforambeinttemperature25C002) *
    PI_TeC_PIControl_P.conversiontoC_Gain;

  /* MATLABSystem: '<Root>/PWM' */
  obj_0 = &PI_TeC_PIControl_DW.obj;
  obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PI_TeC_PIControl_DW.obj.PinPWM);

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<Root>/Ki'
   *  Gain: '<Root>/Kp'
   *  Integrator: '<Root>/Integrator'
   */
  u0 = PI_TeC_PIControl_P.Kp_Gain * PI_TeC_PIControl_B.error +
    PI_TeC_PIControl_P.Ki_Gain * PI_TeC_PIControl_X.Integrator_CSTATE;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > PI_TeC_PIControl_P.Saturation_UpperSat) {
    u0 = PI_TeC_PIControl_P.Saturation_UpperSat;
  } else {
    if (u0 < PI_TeC_PIControl_P.Saturation_LowerSat) {
      u0 = PI_TeC_PIControl_P.Saturation_LowerSat;
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

  MW_PWM_SetDutyCycle(PI_TeC_PIControl_DW.obj.MW_PWM_HANDLE, u0);
  if (rtmIsMajorTimeStep(PI_TeC_PIControl_M)) {
    rt_ertODEUpdateContinuousStates(&PI_TeC_PIControl_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++PI_TeC_PIControl_M->Timing.clockTick0;
    PI_TeC_PIControl_M->Timing.t[0] = rtsiGetSolverStopTime
      (&PI_TeC_PIControl_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      PI_TeC_PIControl_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PI_TeC_PIControl_derivatives(void)
{
  XDot_PI_TeC_PIControl_T *_rtXdot;
  _rtXdot = ((XDot_PI_TeC_PIControl_T *) PI_TeC_PIControl_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = PI_TeC_PIControl_B.error;
}

/* Model initialize function */
void PI_TeC_PIControl_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PI_TeC_PIControl_M->solverInfo,
                          &PI_TeC_PIControl_M->Timing.simTimeStep);
    rtsiSetTPtr(&PI_TeC_PIControl_M->solverInfo, &rtmGetTPtr(PI_TeC_PIControl_M));
    rtsiSetStepSizePtr(&PI_TeC_PIControl_M->solverInfo,
                       &PI_TeC_PIControl_M->Timing.stepSize0);
    rtsiSetdXPtr(&PI_TeC_PIControl_M->solverInfo, &PI_TeC_PIControl_M->derivs);
    rtsiSetContStatesPtr(&PI_TeC_PIControl_M->solverInfo, (real_T **)
                         &PI_TeC_PIControl_M->contStates);
    rtsiSetNumContStatesPtr(&PI_TeC_PIControl_M->solverInfo,
      &PI_TeC_PIControl_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PI_TeC_PIControl_M->solverInfo,
      &PI_TeC_PIControl_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PI_TeC_PIControl_M->solverInfo,
      &PI_TeC_PIControl_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PI_TeC_PIControl_M->solverInfo,
      &PI_TeC_PIControl_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PI_TeC_PIControl_M->solverInfo, (&rtmGetErrorStatus
      (PI_TeC_PIControl_M)));
    rtsiSetRTModelPtr(&PI_TeC_PIControl_M->solverInfo, PI_TeC_PIControl_M);
  }

  rtsiSetSimTimeStep(&PI_TeC_PIControl_M->solverInfo, MAJOR_TIME_STEP);
  PI_TeC_PIControl_M->intgData.y = PI_TeC_PIControl_M->odeY;
  PI_TeC_PIControl_M->intgData.f[0] = PI_TeC_PIControl_M->odeF[0];
  PI_TeC_PIControl_M->intgData.f[1] = PI_TeC_PIControl_M->odeF[1];
  PI_TeC_PIControl_M->intgData.f[2] = PI_TeC_PIControl_M->odeF[2];
  PI_TeC_PIControl_M->contStates = ((X_PI_TeC_PIControl_T *) &PI_TeC_PIControl_X);
  rtsiSetSolverData(&PI_TeC_PIControl_M->solverInfo, (void *)
                    &PI_TeC_PIControl_M->intgData);
  rtsiSetSolverName(&PI_TeC_PIControl_M->solverInfo,"ode3");
  rtmSetTPtr(PI_TeC_PIControl_M, &PI_TeC_PIControl_M->Timing.tArray[0]);
  PI_TeC_PIControl_M->Timing.stepSize0 = 0.2;

  {
    codertarget_arduinobase_inter_T *obj;
    codertarget_arduinobase_int_g_T *obj_0;

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    PI_TeC_PIControl_X.Integrator_CSTATE = PI_TeC_PIControl_P.Integrator_IC;

    /* Start for MATLABSystem: '<Root>/Analog Input' */
    PI_TeC_PIControl_DW.obj_h.matlabCodegenIsDeleted = true;
    PI_TeC_PIControl_DW.obj_h.isInitialized = 0L;
    PI_TeC_PIControl_DW.obj_h.SampleTime = -1.0;
    PI_TeC_PIControl_DW.obj_h.matlabCodegenIsDeleted = false;
    PI_TeC_PIControl_DW.obj_h.SampleTime =
      PI_TeC_PIControl_P.AnalogInput_SampleTime;
    obj = &PI_TeC_PIControl_DW.obj_h;
    PI_TeC_PIControl_DW.obj_h.isSetupComplete = false;
    PI_TeC_PIControl_DW.obj_h.isInitialized = 1L;
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(14UL);
    PI_TeC_PIControl_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/PWM' */
    PI_TeC_PIControl_DW.obj.matlabCodegenIsDeleted = true;
    PI_TeC_PIControl_DW.obj.isInitialized = 0L;
    PI_TeC_PIControl_DW.obj.matlabCodegenIsDeleted = false;
    arduino_PWMOutput_set_pinNumber(&PI_TeC_PIControl_DW.obj,
      &PI_TeC_PIControl_DW.gobj_2);
    obj_0 = &PI_TeC_PIControl_DW.obj;
    PI_TeC_PIControl_DW.obj.isSetupComplete = false;
    PI_TeC_PIControl_DW.obj.isInitialized = 1L;
    obj_0->MW_PWM_HANDLE = MW_PWM_Open(PI_TeC_PIControl_DW.obj.PinPWM, 0.0, 0.0);
    obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PI_TeC_PIControl_DW.obj.PinPWM);
    MW_PWM_Start(PI_TeC_PIControl_DW.obj.MW_PWM_HANDLE);
    PI_TeC_PIControl_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void PI_TeC_PIControl_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  matlabCodegenHandle_matlabCod_g(&PI_TeC_PIControl_DW.obj_h);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  matlabCodegenHandle_matlabCodeg(&PI_TeC_PIControl_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
