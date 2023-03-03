// **************************************************
// *** common.h (共通変数，共通定数)              ***
// ***                        produced by Y. Mori ***
// ***	      special thanks to A. Ruike, S. Kido ***
// **************************************************

#ifndef __COMMON_H
#define __COMMON_H

#include <math.h>

// **************
// *** For H8 ***
// **************

// --- motor ---
#define  MOTOR_0_CW		P4.DR.BIT.B0= 1; P4.DR.BIT.B2= 0;
#define  MOTOR_0_CCW	P4.DR.BIT.B0= 0; P4.DR.BIT.B2= 1;
#define  MOTOR_0_RUN	P4.DR.BIT.B0= 0; P4.DR.BIT.B2= 0;
#define  MOTOR_0_BREAK	P4.DR.BIT.B0= 1; P4.DR.BIT.B2= 1;
#define  MOTOR_0_DUTY	OCT_ITU0.TCORB

#define  MOTOR_1_CW		P4.DR.BIT.B1= 1; P4.DR.BIT.B3= 0;
#define  MOTOR_1_CCW	P4.DR.BIT.B1= 0; P4.DR.BIT.B3= 1;
#define  MOTOR_1_RUN	P4.DR.BIT.B1= 0; P4.DR.BIT.B3= 0;
#define  MOTOR_1_BREAK	P4.DR.BIT.B1= 1; P4.DR.BIT.B3= 1;
#define  MOTOR_1_DUTY	OCT_ITU1.TCORB

// タイマー開始 011: CK2=0, CK1=1, CK0=1 -> φ/8192, pp.463
#define  START_FEED  OCT_ITU3.TCR.BIT.CKS= 3;
// タイマー停止 000: CK2=0, CK1=0, CK0=0 -> pp.463
#define   STOP_FEED  OCT_ITU3.TCR.BIT.CKS= 0;

// エンコーダカウント開始
#define  START_ENCO_COUNT  HEX_ITU.TSTR.BIT.STR0= 1; HEX_ITU.TSTR.BIT.STR1= 1; HEX_ITU.TSTR.BIT.STR2= 1;
// エンコーダカウント停止
#define  STOP_ENCO_COUNT   HEX_ITU.TSTR.BIT.STR0= 0; HEX_ITU.TSTR.BIT.STR1= 0; HEX_ITU.TSTR.BIT.STR2= 0;

// --- Photo reflector ---
#define  Photo_1  P5.DR.BIT.B0  // 1番左
#define  Photo_2  P5.DR.BIT.B1  // 2番目
#define  Photo_3  P5.DR.BIT.B2  // 3番目
#define  Photo_4  P5.DR.BIT.B3  // 4番目

#define  Black  0
#define  White  1

// --- Motor ---
#define  Max_duty    250
#define  Limit_duty  250
#define  Ratio_duty (Max_duty/Limit_duty)

// --- Feedback control ---
#define  STOP   0
#define  ENCO   1
#define  PHOTO  2


// ************************
// *** Common Parameter ***
// ************************

// --- サンプリングタイム ---
#define  SampTime   20      // [ms]
#define  RsampTime   0.02f  // [s]

// --- 最大データ数 ---
#define  MaxDataNum  1001  // 最大時間 = MaxDataNum*SampTime[ms]

// --- 座標系の変数 ---
#define  CoordsNum  3
#define  X    0
#define  Y    1
#define  Tht  2

// --- Joint Number ---
#define  Jnum  2
#define  LW  0  //  Left wheel
#define  RW  1  // Right wheel

#define  PI  3.141592654f


// ***********************
// *** For Kinemtatics ***
// ***********************

// --- Input Variables ---
#define  InputNum  2
#define  DDis  0  // dot Dis
#define  DTht  1  // dot Tht


// --- state type ---
typedef struct{
	float  d;  // 距離
	float  v;  // 速度

} ki_stateType;


// --- kinematics shared type ---
typedef struct{
	float  W;  // 本体の横幅
	float  r;  // 車輪半径
    
	ki_stateType  traj[Jnum][MaxDataNum];
    
	float  in[InputNum][MaxDataNum];
    
} ki_sharedType;


// **********************
// *** For Controller ***
// **********************
#define  Rad2Deg  57.29578f   // Rad to Deg
#define  Deg2Rad  0.0174533f  // Deg to Rad

// --- for time.h ---
#define  Stopped   0
#define  UntilInc  1
#define  Reached   1

// --- Output Variables ---
#define  OutputNum  2
#define  DLW  0  // Dot LW_Angle
#define  DRW  1  // Dot RW_Angle


// --- encoder count type ---
typedef struct{
	int  d, delta;  // pos, delta

} ct_eCountType;


// --- encoder type ---
typedef struct{
	ct_eCountType  present, last;

} ct_encoType;


// --- state type ---
typedef struct{
	float  d; 
	float  v; 

} ct_stateType;


// --- gain type ---
typedef struct{              
	float  kp, kd;  // for PD controller
    
} ct_gainType;


// --- joint type ---
typedef struct{
	ct_stateType  present, last;    
	ct_gainType   gain;
	float         delta;
    
} ct_jntType; 


// --- time type ---
typedef struct{
	int  val;       //      val: now value
	int  startVal;  // startVal: begin time
	int  stopVal;   //  stopVal: end time
	int  inc;       //      inc: stop or move

} ct_timeType;


// --- control shared type ---
typedef struct{
	ct_jntType    jnt[Jnum];
	ct_encoType   enco[Jnum];
	ct_timeType   dTime;

	float  WPulse2Rad;  // 変換係数 enco[pulse] -> angle[rad]
	float  Tr;          // 減速比

	int    timeFlag;    // plan の終了フラグ

	int    enco_dir[Jnum];      // エンコーダの回転方向
	int    tmp_enco_val[Jnum];  // エンコーダカウント用仮変数

	int    pwm[Jnum];      // モータのPWM値（最大値=Max_duty）
	int    mot_dir[Jnum];  // モータの回転方向, jikken6の LD, RDの代わり
 
	float  start_present_d[Jnum];  // ロボットの現在位置
 
	ct_stateType  data[Jnum][MaxDataNum];  // データセーブ用変数
    
} ct_sharedType;

#endif
