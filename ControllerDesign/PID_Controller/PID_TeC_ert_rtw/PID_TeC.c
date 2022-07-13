/*
 * File: PID_TeC.c
 *
 * Code generated for Simulink model 'PID_TeC'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Wed Jul 13 03:41:42 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PID_TeC.h"
#include "PID_TeC_private.h"

/* Block signals (default storage) */
B_PID_TeC_T PID_TeC_B;

/* Continuous states */
X_PID_TeC_T PID_TeC_X;

/* Block states (default storage) */
DW_PID_TeC_T PID_TeC_DW;

/* Real-time model */
RT_MODEL_PID_TeC_T PID_TeC_M_;
RT_MODEL_PID_TeC_T *const PID_TeC_M = &PID_TeC_M_;

/* Forward declaration for local functions */
static void PID_TeC_SystemCore_release_k(codertarget_arduinobase_inter_T *obj);
static void PID_TeC_SystemCore_delete_k(codertarget_arduinobase_inter_T *obj);
static void matlabCodegenHandle_matlabCod_k(codertarget_arduinobase_inter_T *obj);
static void PID_TeC_SystemCore_release(codertarget_arduinobase_int_k_T *obj);
static void PID_TeC_SystemCore_delete(codertarget_arduinobase_int_k_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_k_T *obj);
static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_k_T *obj,
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
  PID_TeC_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  PID_TeC_step();
  PID_TeC_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  PID_TeC_step();
  PID_TeC_derivatives();

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

static void PID_TeC_SystemCore_release_k(codertarget_arduinobase_inter_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
    MW_AnalogIn_Close(obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE);
  }
}

static void PID_TeC_SystemCore_delete_k(codertarget_arduinobase_inter_T *obj)
{
  PID_TeC_SystemCore_release_k(obj);
}

static void matlabCodegenHandle_matlabCod_k(codertarget_arduinobase_inter_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PID_TeC_SystemCore_delete_k(obj);
  }
}

static void PID_TeC_SystemCore_release(codertarget_arduinobase_int_k_T *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_SetDutyCycle(obj->MW_PWM_HANDLE, 0.0);
    obj->MW_PWM_HANDLE = MW_PWM_GetHandle(obj->PinPWM);
    MW_PWM_Close(obj->MW_PWM_HANDLE);
  }
}

static void PID_TeC_SystemCore_delete(codertarget_arduinobase_int_k_T *obj)
{
  PID_TeC_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_int_k_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    PID_TeC_SystemCore_delete(obj);
  }
}

static void arduino_PWMOutput_set_pinNumber(codertarget_arduinobase_int_k_T *obj,
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
void PID_TeC_step(void)
{
  if (rtmIsMajorTimeStep(PID_TeC_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&PID_TeC_M->solverInfo,((PID_TeC_M->Timing.clockTick0+
      1)*PID_TeC_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PID_TeC_M)) {
    PID_TeC_M->Timing.t[0] = rtsiGetT(&PID_TeC_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T lastTime;
    uint16_T rtb_Vin_0;
    codertarget_arduinobase_inter_T *obj;
    codertarget_arduinobase_int_k_T *obj_0;
    real_T rtb_error;

    /* MATLABSystem: '<Root>/Analog Input' */
    if (PID_TeC_DW.obj_h.SampleTime != PID_TeC_P.AnalogInput_SampleTime) {
      PID_TeC_DW.obj_h.SampleTime = PID_TeC_P.AnalogInput_SampleTime;
    }

    obj = &PID_TeC_DW.obj_h;
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle(14UL);
    MW_AnalogInSingle_ReadResult
      (PID_TeC_DW.obj_h.AnalogInDriverObj.MW_ANALOGIN_HANDLE, &rtb_Vin_0, 3);

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Tref'
     *  Constant: '<Root>/bias for ambeint temperature 25°C*0.025V'
     *  Gain: '<Root>/conversion to millivolts'
     *  Gain: '<Root>/conversion to °C'
     *  MATLABSystem: '<Root>/Analog Input'
     *  Sum: '<Root>/Sum'
     */
    PID_TeC_B.error = PID_TeC_P.Tref_Value - ((real_T)((uint32_T)
      PID_TeC_P.conversiontomillivolts_Gain * rtb_Vin_0) * 0.0001220703125 -
      PID_TeC_P.biasforambeinttemperature25C002) * PID_TeC_P.conversiontoC_Gain;

    /* Derivative: '<Root>/Derivative' */
    rtb_error = PID_TeC_M->Timing.t[0];
    if ((PID_TeC_DW.TimeStampA >= rtb_error) && (PID_TeC_DW.TimeStampB >=
         rtb_error)) {
      rtb_error = 0.0;
    } else {
      lastTime = PID_TeC_DW.TimeStampA;
      lastU = &PID_TeC_DW.LastUAtTimeA;
      if (PID_TeC_DW.TimeStampA < PID_TeC_DW.TimeStampB) {
        if (PID_TeC_DW.TimeStampB < rtb_error) {
          lastTime = PID_TeC_DW.TimeStampB;
          lastU = &PID_TeC_DW.LastUAtTimeB;
        }
      } else {
        if (PID_TeC_DW.TimeStampA >= rtb_error) {
          lastTime = PID_TeC_DW.TimeStampB;
          lastU = &PID_TeC_DW.LastUAtTimeB;
        }
      }

      rtb_error = (PID_TeC_B.error - *lastU) / (rtb_error - lastTime);
    }

    /* End of Derivative: '<Root>/Derivative' */

    /* MATLABSystem: '<Root>/PWM' */
    obj_0 = &PID_TeC_DW.obj;
    obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PID_TeC_DW.obj.PinPWM);

    /* Sum: '<Root>/Sum2' incorporates:
     *  Gain: '<Root>/Kd'
     *  Gain: '<Root>/Ki'
     *  Gain: '<Root>/Kp'
     *  Integrator: '<Root>/Integrator'
     */
    rtb_error = (PID_TeC_P.Kd_Gain * rtb_error + PID_TeC_P.Kp_Gain *
                 PID_TeC_B.error) + PID_TeC_P.Ki_Gain *
      PID_TeC_X.Integrator_CSTATE;

    /* Saturate: '<Root>/Saturation' */
    if (rtb_error > PID_TeC_P.Saturation_UpperSat) {
      rtb_error = PID_TeC_P.Saturation_UpperSat;
    } else {
      if (rtb_error < PID_TeC_P.Saturation_LowerSat) {
        rtb_error = PID_TeC_P.Saturation_LowerSat;
      }
    }

    /* End of Saturate: '<Root>/Saturation' */

    /* MATLABSystem: '<Root>/PWM' */
    if (!(rtb_error < 255.0)) {
      rtb_error = 255.0;
    }

    if (!(rtb_error > 0.0)) {
      rtb_error = 0.0;
    }

    MW_PWM_SetDutyCycle(PID_TeC_DW.obj.MW_PWM_HANDLE, rtb_error);
  }

  if (rtmIsMajorTimeStep(PID_TeC_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative' */
    if (PID_TeC_DW.TimeStampA == (rtInf)) {
      PID_TeC_DW.TimeStampA = PID_TeC_M->Timing.t[0];
      lastU = &PID_TeC_DW.LastUAtTimeA;
    } else if (PID_TeC_DW.TimeStampB == (rtInf)) {
      PID_TeC_DW.TimeStampB = PID_TeC_M->Timing.t[0];
      lastU = &PID_TeC_DW.LastUAtTimeB;
    } else if (PID_TeC_DW.TimeStampA < PID_TeC_DW.TimeStampB) {
      PID_TeC_DW.TimeStampA = PID_TeC_M->Timing.t[0];
      lastU = &PID_TeC_DW.LastUAtTimeA;
    } else {
      PID_TeC_DW.TimeStampB = PID_TeC_M->Timing.t[0];
      lastU = &PID_TeC_DW.LastUAtTimeB;
    }

    *lastU = PID_TeC_B.error;

    /* End of Update for Derivative: '<Root>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PID_TeC_M)) {
    rt_ertODEUpdateContinuousStates(&PID_TeC_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++PID_TeC_M->Timing.clockTick0;
    PID_TeC_M->Timing.t[0] = rtsiGetSolverStopTime(&PID_TeC_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      PID_TeC_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PID_TeC_derivatives(void)
{
  XDot_PID_TeC_T *_rtXdot;
  _rtXdot = ((XDot_PID_TeC_T *) PID_TeC_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = PID_TeC_B.error;
}

/* Model initialize function */
void PID_TeC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PID_TeC_M->solverInfo, &PID_TeC_M->Timing.simTimeStep);
    rtsiSetTPtr(&PID_TeC_M->solverInfo, &rtmGetTPtr(PID_TeC_M));
    rtsiSetStepSizePtr(&PID_TeC_M->solverInfo, &PID_TeC_M->Timing.stepSize0);
    rtsiSetdXPtr(&PID_TeC_M->solverInfo, &PID_TeC_M->derivs);
    rtsiSetContStatesPtr(&PID_TeC_M->solverInfo, (real_T **)
                         &PID_TeC_M->contStates);
    rtsiSetNumContStatesPtr(&PID_TeC_M->solverInfo,
      &PID_TeC_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PID_TeC_M->solverInfo,
      &PID_TeC_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PID_TeC_M->solverInfo,
      &PID_TeC_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PID_TeC_M->solverInfo,
      &PID_TeC_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PID_TeC_M->solverInfo, (&rtmGetErrorStatus(PID_TeC_M)));
    rtsiSetRTModelPtr(&PID_TeC_M->solverInfo, PID_TeC_M);
  }

  rtsiSetSimTimeStep(&PID_TeC_M->solverInfo, MAJOR_TIME_STEP);
  PID_TeC_M->intgData.y = PID_TeC_M->odeY;
  PID_TeC_M->intgData.f[0] = PID_TeC_M->odeF[0];
  PID_TeC_M->intgData.f[1] = PID_TeC_M->odeF[1];
  PID_TeC_M->intgData.f[2] = PID_TeC_M->odeF[2];
  PID_TeC_M->contStates = ((X_PID_TeC_T *) &PID_TeC_X);
  rtsiSetSolverData(&PID_TeC_M->solverInfo, (void *)&PID_TeC_M->intgData);
  rtsiSetSolverName(&PID_TeC_M->solverInfo,"ode3");
  rtmSetTPtr(PID_TeC_M, &PID_TeC_M->Timing.tArray[0]);
  PID_TeC_M->Timing.stepSize0 = 0.2;

  {
    codertarget_arduinobase_inter_T *obj;
    codertarget_arduinobase_int_k_T *obj_0;

    /* InitializeConditions for Derivative: '<Root>/Derivative' */
    PID_TeC_DW.TimeStampA = (rtInf);
    PID_TeC_DW.TimeStampB = (rtInf);

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    PID_TeC_X.Integrator_CSTATE = PID_TeC_P.Integrator_IC;

    /* Start for MATLABSystem: '<Root>/Analog Input' */
    PID_TeC_DW.obj_h.matlabCodegenIsDeleted = true;
    PID_TeC_DW.obj_h.isInitialized = 0L;
    PID_TeC_DW.obj_h.SampleTime = -1.0;
    PID_TeC_DW.obj_h.matlabCodegenIsDeleted = false;
    PID_TeC_DW.obj_h.SampleTime = PID_TeC_P.AnalogInput_SampleTime;
    obj = &PID_TeC_DW.obj_h;
    PID_TeC_DW.obj_h.isSetupComplete = false;
    PID_TeC_DW.obj_h.isInitialized = 1L;
    obj->AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open(14UL);
    PID_TeC_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/PWM' */
    PID_TeC_DW.obj.matlabCodegenIsDeleted = true;
    PID_TeC_DW.obj.isInitialized = 0L;
    PID_TeC_DW.obj.matlabCodegenIsDeleted = false;
    arduino_PWMOutput_set_pinNumber(&PID_TeC_DW.obj, &PID_TeC_DW.gobj_2);
    obj_0 = &PID_TeC_DW.obj;
    PID_TeC_DW.obj.isSetupComplete = false;
    PID_TeC_DW.obj.isInitialized = 1L;
    obj_0->MW_PWM_HANDLE = MW_PWM_Open(PID_TeC_DW.obj.PinPWM, 0.0, 0.0);
    obj_0->MW_PWM_HANDLE = MW_PWM_GetHandle(PID_TeC_DW.obj.PinPWM);
    MW_PWM_Start(PID_TeC_DW.obj.MW_PWM_HANDLE);
    PID_TeC_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void PID_TeC_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  matlabCodegenHandle_matlabCod_k(&PID_TeC_DW.obj_h);

  /* Terminate for MATLABSystem: '<Root>/PWM' */
  matlabCodegenHandle_matlabCodeg(&PID_TeC_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
