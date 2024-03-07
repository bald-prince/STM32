#ifndef _PID_H_
#define _PID_H_
#include "Followline.h"
#include "timer_Drv.h"
#ifdef __cplusplus
		extern "C"{
#endif
/*****************
			
			����:Suaig
			2018-2
			�汾1.0
			2018-4-27
			�汾1.1
			�޸�һ��BUG����Ϊ����δ��ʼ����������쳣
			�޸���һ��BUG������PID_SetSampleTime�������ı�ki,kdʱ��ϵ������
			
			PS:��ֲ����arduino PID��
			��ַ:http://playground.arduino.cc/Code/PIDLibrary
			ԭ����C++д�ģ�ͨ��C��������д������ȫ������
******************/
//----------------------------------------------------------------
	//----------���������ʾ��ͼ----------------    


//                  @<---���ص��ڻ�ͷǰ��
//			                pitch++
//											��֮--
//			          (pitch_max)
//               /|\y+	��ͷ(ǰ)	-->pitch	
//(roll_max)      |
//   x+           |                      �����Ҳ�-->roll
//<---------------|----------------------   @<--���ص��ڻ����Ҳ�
//                |                         roll--
//								|                         ��֮++
//								|
//							  |
//                | 		 
//-----------------------------------


//-------------S----------------		

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;	
//�Ƿ��Զ�����
#define AUTOMATIC	1 //��ʱ���Զ�����
#define MANUAL	0		//�ֶ�
			
#define DIRECT  0  //PID������� ����������
#define REVERSE  1 //PID������ӣ�����������  �ο��յ����䣬����������ӣ��յ�������ǿ��Խ��
			
#define P_ON_M 0	//���Ƴ���(������ֳ��������߳���С��������)
#define P_ON_E 1	//����ģʽ(�г�������������)


extern uint32_t millis();
extern int16_t Pid_out_pitch;
extern int16_t Pid_out_roll;
extern uint32_t zone_Tick;

			
#define PIDmillis millis //��ȡϵͳʱ��

			
typedef double PID_type;//�����ڳ����л�PID�������ͱ���Ϊ�з���		
typedef unsigned char he;      			
typedef unsigned long Timetick;//ʱ�亯��
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
extern uint32_t tim;

#define false 0
#define true  1
			
typedef struct
{
	PID_type dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	PID_type dispKi;				//   format for display purposes
	PID_type dispKd;				//
    
	PID_type kp;                  // * (P)roportional Tuning Parameter ��������ϵ��
  PID_type ki;                  // * (I)ntegral Tuning Parameter ���ֻ���ϵ��
  PID_type kd;                  // * (D)erivative Tuning Parameter ΢�ֻ���ϵ��

	he controllerDirection;		//DIRECT  0  : PID������� ����������
															//REVERSE  1 : PID������ӣ�����������  �ο��յ����䣬����������ӣ��յ�������ǿ��Խ��
	he pOn;

  int16_t *myInput;              // * Input, Output, and Setpoint ������ָ��
  int16_t *myOutput;             //   ͨ��������ָ����ܵ���ϵ�˱�����PID
  int16_t *mySetpoint;           //   ������Ҫ����߳�����ע������ֵ
                                  //   ʹ��ָ�����ȡ����
	//Input: �ɼ�����������ΪPID���� Output:PID����õ����������DA��Dֵ��PWM�еĶ�ʱ��CCRֵ�����ڿ�������� Setpoint�����������ֵ
	Timetick lastTime;							//�ϴν�����PID�����ʱ���
	PID_type outputSum, lastInput;	//outputSum:���ڴ洢���ֻ��ڣ����ڻ�������ʷֵ��أ���Ҫ�洢��
																	//lastInput:���ڴ洢�ϴβɼ�ֵ�����ڼ����error
	Timetick SampleTime;						//PID�������ڣ���ͬ����Ч����Ƶ�ʣ�
	PID_type outMin, outMax;				//����޷�����������PID������������ֹ����ĵ��ڣ�
	
	he inAuto, pOnE;							//inAuto:��������PID����ģʽ		AUTOMATIC(1):�Զ�ģʽ���ɺ����Զ�ʵ��PID����
																	//												 		MANUAL(0):�ֶ�ģʽ ��Ҫ�Լ�ʵ��PID����
																	//pOnE:�����Ƿ�������        P_ON_M(0):���Ƴ���(������ֳ��������߳���С��������)
																	//														P_ON_E(1):����ģʽ(�г�������������)
}PID_Class,*PID_NODE;	

//extern PID_Class MY_PID_x,MY_PID_y;

/*
//������� 1,pid����ָ�룬2,�����ָ�� 3,���������ָ�� 4.����ֵָ�� 5��6��7��Kp��Ki��Kd��ֵ��8.pon�ǿ������ͣ��Ƿ����ÿ��Ƴ���,9.PID�����������
*/
void new_PID(PID_Class *mpid,int16_t* Input,int16_t* Output,int16_t* Setpoint,double Kp,double Ki,double Kd,he POn, he ControllerDirection);//��ʼ��һ���µ�PID��	
			
//���ù���ģʽ���Զ������ֶ�  1,pid����ָ�� 2.ģʽ			
void PID_SetMode(PID_Class *mpid,he Mode);			

//����PID �Ļ�������
void PID_SetTunings(PID_Class *mpid,PID_type Kp, PID_type Ki, PID_type Kd, he POn);			

//����PID�ķ���
void PID_SetControllerDirection(PID_Class *mpid,he Direction);			
//����PID�����������
void PID_SetOutputLimits(PID_Class *mpid,PID_type Min, PID_type Max);			
//��ʼ��PID
void PID_Initialize(PID_Class *mpid);

//����PID���ɹ�����һ��1����true
he PID_Compute(PID_Class *mpid);

//���ü������ڣ���λ��ms
void PID_SetSampleTime(PID_Class *mpid,Timetick NewSampleTime);
void Clear_Sum(PID_Class *mpid);
void Reset_PID(PID_Class *mpid);
#ifdef __cplusplus
}
#endif

/*
ʹ�þ���
idata PID_Class adcpid;

void main( void )
{
	
	double adcinput = 0,adcoutput = 1,setpid = 2;
	TMOD |= 0x01;
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	
	new_PID(&adcpid,&adcinput,&adcoutput,&setpid,1,1,1,P_ON_E,DIRECT);
	PID_SetMode(&adcpid,AUTOMATIC);
  while(1)
	{
		PID_Compute(&adcpid);
	}
	
	�ر�ע�⣬������ɻ�ȡϵͳʱ��ĺ���millis ��ΪPID�ǰ�ʱ��ȥ������ã�Ki��Kp,Kd��ֵҲ��ʱ��ϢϢ��أ��������ȥ��PID����Ƶ��
*/
#endif



