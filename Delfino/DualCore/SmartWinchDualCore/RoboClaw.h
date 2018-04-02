#ifndef RoboClaw_h
#define RoboClaw_h


#include "includes.h"
#include <stdarg.h>
#include "buffered_serial_C.h"

#define _SS_VERSION 16
#define RoboClaw_Address 0x80
/******************************************************************************
* Definitions
******************************************************************************/
enum 
{
	M1FORWARD = 0,
	M1BACKWARD = 1,
	SETMINMB = 2,
	SETMAXMB = 3,
	M2FORWARD = 4,
	M2BACKWARD = 5,
	M17BIT = 6,
	M27BIT = 7,
	MIXEDFORWARD = 8,
	MIXEDBACKWARD = 9,
	MIXEDRIGHT = 10,
	MIXEDLEFT = 11,
	MIXEDFB = 12,
	MIXEDLR = 13,
	GETM1ENC = 16,
	GETM2ENC = 17,
	GETM1SPEED = 18,
	GETM2SPEED = 19,
	RESETENC = 20,
	GETVERSION = 21,
	SETM1ENCCOUNT = 22,
	SETM2ENCCOUNT = 23,
	GETMBATT = 24,
	GETLBATT = 25,
	SETMINLB = 26,
	SETMAXLB = 27,
	SETM1PID = 28,
	SETM2PID = 29,
	GETM1ISPEED = 30,
	GETM2ISPEED = 31,
	M1DUTY = 32,
	M2DUTY = 33,
	MIXEDDUTY = 34,
	M1SPEED = 35,
	M2SPEED = 36,
	MIXEDSPEED = 37,
	M1SPEEDACCEL = 38,
	M2SPEEDACCEL = 39,
	MIXEDSPEEDACCEL = 40,
	M1SPEEDDIST = 41,
	M2SPEEDDIST = 42,
	MIXEDSPEEDDIST = 43,
	M1SPEEDACCELDIST = 44,
	M2SPEEDACCELDIST = 45,
	MIXEDSPEEDACCELDIST = 46,
	GETBUFFERS = 47,
	GETPWMS = 48,
	GETCURRENTS = 49,
	MIXEDSPEED2ACCEL = 50,
	MIXEDSPEED2ACCELDIST = 51,
	M1DUTYACCEL = 52,
	M2DUTYACCEL = 53,
	MIXEDDUTYACCEL = 54,
	READM1PID = 55,
	READM2PID = 56,
	SETMAINVOLTAGES = 57,
	SETLOGICVOLTAGES = 58,
	GETMINMAXMAINVOLTAGES = 59,
	GETMINMAXLOGICVOLTAGES = 60,
	SETM1POSPID = 61,
	SETM2POSPID = 62,
	READM1POSPID = 63,
	READM2POSPID = 64,
	M1SPEEDACCELDECCELPOS = 65,
	M2SPEEDACCELDECCELPOS = 66,
	MIXEDSPEEDACCELDECCELPOS = 67,
	SETM1DEFAULTACCEL = 68,
	SETM2DEFAULTACCEL = 69,
	SETPINFUNCTIONS = 74,
	GETPINFUNCTIONS = 75,
	SETDEADBAND	= 76,
	GETDEADBAND	= 77,
	GETENCODERS = 78,
	GETISPEEDS = 79,
	RESTOREDEFAULTS = 80,
	GETTEMP = 82,
	GETTEMP2 = 83,	//Only valid on some models
	GETERROR = 90,
	GETENCODERMODE = 91,
	SETM1ENCODERMODE = 92,
	SETM2ENCODERMODE = 93,
	WRITENVM = 94,
	READNVM = 95,	//Reloads values from Flash into Ram
	SETCONFIG = 98,
	GETCONFIG = 99,
	SETM1MAXCURRENT = 133,
	SETM2MAXCURRENT = 134,
	GETM1MAXCURRENT = 135,
	GETM2MAXCURRENT = 136,
	SETPWMMODE = 148,
	GETPWMMODE = 149,
	FLAGBOOTLOADER = 255 //Only available via USB communications
};	

int16_t RoboClaw_library_version();
bool RoboClaw_ForwardM1(uint16_t address, uint16_t speed);
bool RoboClaw_BackwardM1(uint16_t address, uint16_t speed);
bool RoboClaw_SetMinVoltageMainBattery(uint16_t address, uint16_t voltage);
bool RoboClaw_SetMaxVoltageMainBattery(uint16_t address, uint16_t voltage);
bool RoboClaw_ForwardM2(uint16_t address, uint16_t speed);
bool RoboClaw_BackwardM2(uint16_t address, uint16_t speed);
bool RoboClaw_ForwardBackwardM1(uint16_t address, uint16_t speed);
bool RoboClaw_ForwardBackwardM2(uint16_t address, uint16_t speed);
bool RoboClaw_ForwardMixed(uint16_t address, uint16_t speed);
bool RoboClaw_BackwardMixed(uint16_t address, uint16_t speed);
bool RoboClaw_TurnRightMixed(uint16_t address, uint16_t speed);
bool RoboClaw_TurnLeftMixed(uint16_t address, uint16_t speed);
bool RoboClaw_ForwardBackwardMixed(uint16_t address, uint16_t speed);
bool RoboClaw_LeftRightMixed(uint16_t address, uint16_t speed);
int32_t RoboClaw_ReadEncM1(uint16_t address, uint16_t *status,bool *valid);
uint32_t RoboClaw_ReadEncM2(uint16_t address, uint16_t *status,bool *valid);
bool RoboClaw_SetEncM1(uint16_t address, int32_t val);
bool RoboClaw_SetEncM2(uint16_t address, int32_t val);
uint32_t RoboClaw_ReadSpeedM1(uint16_t address, uint16_t *status,bool *valid);
uint32_t RoboClaw_ReadSpeedM2(uint16_t address, uint16_t *status,bool *valid);
bool RoboClaw_ResetEncoders(uint16_t address);
bool RoboClaw_ReadVersion(uint16_t address,char *version);
uint16_t RoboClaw_ReadMainBatteryVoltage(uint16_t address,bool *valid);
uint16_t RoboClaw_ReadLogicBatteryVoltage(uint16_t address,bool *valid);
bool RoboClaw_SetMinVoltageLogicBattery(uint16_t address, uint16_t voltage);
bool RoboClaw_SetMaxVoltageLogicBattery(uint16_t address, uint16_t voltage);
bool RoboClaw_SetM1VelocityPID(uint16_t address, float Kp, float Ki, float Kd, uint32_t qpps);
bool RoboClaw_SetM2VelocityPID(uint16_t address, float Kp, float Ki, float Kd, uint32_t qpps);
uint32_t RoboClaw_ReadISpeedM1(uint16_t address,uint16_t *status,bool *valid);
uint32_t RoboClaw_ReadISpeedM2(uint16_t address,uint16_t *status,bool *valid);
bool RoboClaw_DutyM1(uint16_t address, uint16_t duty);
bool RoboClaw_DutyM2(uint16_t address, uint16_t duty);
bool RoboClaw_DutyM1M2(uint16_t address, uint16_t duty1, uint16_t duty2);
bool RoboClaw_SpeedM1(uint16_t address, uint32_t speed);
bool RoboClaw_SpeedM2(uint16_t address, uint32_t speed);
bool RoboClaw_SpeedM1M2(uint16_t address, uint32_t speed1, uint32_t speed2);
bool RoboClaw_SpeedAccelM1(uint16_t address, uint32_t accel, uint32_t speed);
bool RoboClaw_SpeedAccelM2(uint16_t address, uint32_t accel, uint32_t speed);
bool RoboClaw_SpeedAccelM1M2(uint16_t address, uint32_t accel, uint32_t speed1, uint32_t speed2);
bool RoboClaw_SpeedDistanceM1(uint16_t address, uint32_t speed, uint32_t distance, uint16_t flag);
bool RoboClaw_SpeedDistanceM2(uint16_t address, uint32_t speed, uint32_t distance, uint16_t flag);
bool RoboClaw_SpeedDistanceM1M2(uint16_t address, uint32_t speed1, uint32_t distance1, uint32_t speed2, uint32_t distance2, uint16_t flag);
bool RoboClaw_SpeedAccelDistanceM1(uint16_t address, uint32_t accel, uint32_t speed, uint32_t distance, uint16_t flag);
bool RoboClaw_SpeedAccelDistanceM2(uint16_t address, uint32_t accel, uint32_t speed, uint32_t distance, uint16_t flag);
bool RoboClaw_SpeedAccelDistanceM1M2(uint16_t address, uint32_t accel, uint32_t speed1, uint32_t distance1, uint32_t speed2, uint32_t distance2, uint16_t flag);
bool RoboClaw_ReadBuffers(uint16_t address, uint16_t *depth1, uint16_t *depth2);
bool RoboClaw_ReadPWMs(uint16_t address, int16_t *pwm1, int16_t *pwm2);
bool RoboClaw_ReadCurrents(uint16_t address, int16_t *current1, int16_t *current2);
bool RoboClaw_SpeedAccelM1M2_2(uint16_t address, uint32_t accel1, uint32_t speed1, uint32_t accel2, uint32_t speed2);
bool RoboClaw_SpeedAccelDistanceM1M2_2(uint16_t address, uint32_t accel1, uint32_t speed1, uint32_t distance1, uint32_t accel2, uint32_t speed2, uint32_t distance2, uint16_t flag);
bool RoboClaw_DutyAccelM1(uint16_t address, uint16_t duty, uint32_t accel);
bool RoboClaw_DutyAccelM2(uint16_t address, uint16_t duty, uint32_t accel);
bool RoboClaw_DutyAccelM1M2(uint16_t address, uint16_t duty1, uint32_t accel1, uint16_t duty2, uint32_t accel2);
bool RoboClaw_ReadM1VelocityPID(uint16_t address,float *Kp_fp,float *Ki_fp,float *Kd_fp,uint32_t *qpps);
bool RoboClaw_ReadM2VelocityPID(uint16_t address,float *Kp_fp,float *Ki_fp,float *Kd_fp,uint32_t *qpps);
bool RoboClaw_SetMainVoltages(uint16_t address,uint16_t min,uint16_t max);
bool RoboClaw_SetLogicVoltages(uint16_t address,uint16_t min,uint16_t max);
bool RoboClaw_ReadMinMaxMainVoltages(uint16_t address,uint16_t *min,uint16_t *max);
bool RoboClaw_ReadMinMaxLogicVoltages(uint16_t address,uint16_t *min,uint16_t *max);
bool RoboClaw_SetM1PositionPID(uint16_t address,float kp,float ki,float kd,uint32_t kiMax,uint32_t deadzone,uint32_t min,uint32_t max);
bool RoboClaw_SetM2PositionPID(uint16_t address,float kp,float ki,float kd,uint32_t kiMax,uint32_t deadzone,uint32_t min,uint32_t max);
bool RoboClaw_ReadM1PositionPID(uint16_t address,float *Kp,float *Ki,float *Kd,uint32_t *KiMax,uint32_t *DeadZone,uint32_t *Min,uint32_t *Max);
bool RoboClaw_ReadM2PositionPID(uint16_t address,float *Kp,float *Ki,float *Kd,uint32_t *KiMax,uint32_t *DeadZone,uint32_t *Min,uint32_t *Max);
bool RoboClaw_SpeedAccelDeccelPositionM1(uint16_t address,uint32_t accel,uint32_t speed,uint32_t deccel,uint32_t position,uint16_t flag);
bool RoboClaw_SpeedAccelDeccelPositionM2(uint16_t address,uint32_t accel,uint32_t speed,uint32_t deccel,uint32_t position,uint16_t flag);
bool RoboClaw_SpeedAccelDeccelPositionM1M2(uint16_t address,uint32_t accel1,uint32_t speed1,uint32_t deccel1,uint32_t position1,uint32_t accel2,uint32_t speed2,uint32_t deccel2,uint32_t position2,uint16_t flag);
bool RoboClaw_SetM1DefaultAccel(uint16_t address, uint32_t accel);
bool RoboClaw_SetM2DefaultAccel(uint16_t address, uint32_t accel);
bool RoboClaw_SetPinFunctions(uint16_t address, uint16_t S3mode, uint16_t S4mode, uint16_t S5mode);
bool RoboClaw_GetPinFunctions(uint16_t address, uint16_t *S3mode, uint16_t *S4mode, uint16_t *S5mode);
bool RoboClaw_SetDeadBand(uint16_t address, uint16_t Min, uint16_t Max);
bool RoboClaw_GetDeadBand(uint16_t address, uint16_t *Min, uint16_t *Max);
bool RoboClaw_ReadEncoders(uint16_t address,uint32_t *enc1,uint32_t *enc2);
bool RoboClaw_ReadISpeeds(uint16_t address,uint32_t *ispeed1,uint32_t *ispeed2);
bool RoboClaw_RestoreDefaults(uint16_t address);
bool RoboClaw_ReadTemp(uint16_t address, uint16_t *temp);
bool RoboClaw_ReadTemp2(uint16_t address, uint16_t *temp);
uint16_t RoboClaw_ReadError(uint16_t address,bool *valid);
bool RoboClaw_ReadEncoderModes(uint16_t address, uint16_t *M1mode, uint16_t *M2mode);
bool RoboClaw_SetM1EncoderMode(uint16_t address,uint16_t mode);
bool RoboClaw_SetM2EncoderMode(uint16_t address,uint16_t mode);
bool RoboClaw_WriteNVM(uint16_t address);
bool RoboClaw_ReadNVM(uint16_t address);
bool RoboClaw_SetConfig(uint16_t address, uint16_t config);
bool RoboClaw_GetConfig(uint16_t address, uint16_t *config);
bool RoboClaw_SetM1MaxCurrent(uint16_t address,uint32_t max);
bool RoboClaw_SetM2MaxCurrent(uint16_t address,uint32_t max);
bool RoboClaw_ReadM1MaxCurrent(uint16_t address,uint32_t *max);
bool RoboClaw_ReadM2MaxCurrent(uint16_t address,uint32_t *max);
bool RoboClaw_SetPWMMode(uint16_t address, uint16_t mode);
bool RoboClaw_GetPWMMode(uint16_t address, uint16_t *mode);
#endif
