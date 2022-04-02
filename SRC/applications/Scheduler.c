#include "Scheduler.h"


u32 test_dT_1000hz[3],test_rT[6];

static void Loop_1000Hz(void)	//1msִ��һ��
{
//	test_dT_1000hz[0] = test_dT_1000hz[1];
//	test_rT[3] = test_dT_1000hz[1] = GetSysTime_us ();
//	test_dT_1000hz[2] = (u32)(test_dT_1000hz[1] - test_dT_1000hz[0]) ;
////////////////////////////////////////////////////////////////////////	
	
////////////////////////////////////////////////////////////////////////	
//	test_rT[4]= GetSysTime_us ();
//	test_rT[5] = (u32)(test_rT[4] - test_rT[3]) ;	
}

static void Loop_500Hz(void)	//2msִ��һ��
{	
	mearm_control();
	
}

static void Loop_200Hz(void)	//5msִ��һ��
{

}

static void Loop_100Hz(void)	//10msִ��һ��
{
//			test_rT[0]= GetSysTime_us ();
////////////////////////////////////////////////////////////////////////	
//	

//	
////////////////////////////////////////////////////////////////////////		
//			test_rT[1]= GetSysTime_us ();
//			test_rT[2] = (u32)(test_rT[1] - test_rT[0]) ;	
				
}

static void Loop_50Hz(void)	//20msִ��һ��
{	
}

static void Loop_20Hz(void)	//50msִ��һ��
{
	
	
}

static void Loop_10Hz(void)	//100msִ��һ��
{
	
//	oled_show();
}

static void Loop_2Hz(void)	//500msִ��һ��
{


}

//ϵͳ�������ã�������ִͬ��Ƶ�ʵġ��̡߳�
static sched_task_t sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_200Hz , 200,  0, 0},
	{Loop_100Hz , 100,  0, 0},
	{Loop_50Hz  ,  50,  0, 0},
	{Loop_20Hz  ,  20,  0, 0},
	{Loop_10Hz  ,  10,  0, 0},
	{Loop_2Hz   ,   2,  0, 0},
};
//�������鳤�ȣ��ж��߳�����
#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	//��ʼ�������
	for(index=0;index < TASK_NUM;index++)
	{
		//����ÿ���������ʱ������
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz;
		//�������Ϊ1��Ҳ����1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}
//��������ŵ�main������while(1)�У���ͣ�ж��Ƿ����߳�Ӧ��ִ��
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��
	
	for(index=0;index < TASK_NUM;index++)
	{
		//��ȡϵͳ��ǰʱ�䣬��λMS
		uint32_t tnow = SysTick_GetTick();
		//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{			
				//�����̵߳�ִ��ʱ�䣬������һ���ж�
			sched_tasks[index].last_run = tnow;
			//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
			sched_tasks[index].task_func();
			 			
		}
			
	}
}

	

