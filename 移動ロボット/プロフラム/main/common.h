// **************************************************
// *** common.h (���ʕϐ��C���ʒ萔)              ***
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

// �^�C�}�[�J�n 011: CK2=0, CK1=1, CK0=1 -> ��/8192, pp.463
#define  START_FEED  OCT_ITU3.TCR.BIT.CKS= 3;
// �^�C�}�[��~ 000: CK2=0, CK1=0, CK0=0 -> pp.463
#define   STOP_FEED  OCT_ITU3.TCR.BIT.CKS= 0;

// �G���R�[�_�J�E���g�J�n
#define  START_ENCO_COUNT  HEX_ITU.TSTR.BIT.STR0= 1; HEX_ITU.TSTR.BIT.STR1= 1; HEX_ITU.TSTR.BIT.STR2= 1;
// �G���R�[�_�J�E���g��~
#define  STOP_ENCO_COUNT   HEX_ITU.TSTR.BIT.STR0= 0; HEX_ITU.TSTR.BIT.STR1= 0; HEX_ITU.TSTR.BIT.STR2= 0;

// --- Photo reflector ---
#define  Photo_1  P5.DR.BIT.B0  // 1�ԍ�
#define  Photo_2  P5.DR.BIT.B1  // 2�Ԗ�
#define  Photo_3  P5.DR.BIT.B2  // 3�Ԗ�
#define  Photo_4  P5.DR.BIT.B3  // 4�Ԗ�

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

// --- �T���v�����O�^�C�� ---
#define  SampTime   20      // [ms]
#define  RsampTime   0.02f  // [s]

// --- �ő�f�[�^�� ---
#define  MaxDataNum  1001  // �ő厞�� = MaxDataNum*SampTime[ms]

// --- ���W�n�̕ϐ� ---
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
	float  d;  // ����
	float  v;  // ���x

} ki_stateType;


// --- kinematics shared type ---
typedef struct{
	float  W;  // �{�̂̉���
	float  r;  // �ԗ֔��a
    
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

	float  WPulse2Rad;  // �ϊ��W�� enco[pulse] -> angle[rad]
	float  Tr;          // ������

	int    timeFlag;    // plan �̏I���t���O

	int    enco_dir[Jnum];      // �G���R�[�_�̉�]����
	int    tmp_enco_val[Jnum];  // �G���R�[�_�J�E���g�p���ϐ�

	int    pwm[Jnum];      // ���[�^��PWM�l�i�ő�l=Max_duty�j
	int    mot_dir[Jnum];  // ���[�^�̉�]����, jikken6�� LD, RD�̑���
 
	float  start_present_d[Jnum];  // ���{�b�g�̌��݈ʒu
 
	ct_stateType  data[Jnum][MaxDataNum];  // �f�[�^�Z�[�u�p�ϐ�
    
} ct_sharedType;

#endif
