//====================================================================
/*****************************С�ں�******************************
//����------- �ں˴���ṹ��ǰ�ļ�����?--------
//����-------  �˹���
//����ʱ��--20140724
******************************************************************************/
#ifndef G_SMALL_KERNEL
#define G_SMALL_KERNEL
#ifdef __cplusplus
extern "C" {
#endif
//typedef 	void (*VOID_HANDLE)(char*); 
//#define	NULL				(0)
//#ifndef PFUNC
//typedef void (*PFUNC)(void);	
//#endif
//==================ͷ�ļ�����==================================================
//  ��������,�����ʼ����ִ��
extern void gKernelHandles(void);

//����������ڵ�ǰ�����.(NewFunc����Ϊ��)
extern void gLoadingFunctional(PFUNC NewFunc);

//�ڵ�ǰ���������һ��������������֮ǰ����ִ�У�
//ֱ��ȡ����ռ����(�����ڱ����ʼ������ִ�ж�Ӧ��������).(NewFunc����Ϊ��)
extern void gTaskStackFunctional(PFUNC NewFunc);

//�ڵ�ǰ���������һ����ռ������ռ���񽫴��������ִ�У�ֱ���Ƴ�����ռ����.(NewFunc����Ϊ��)
extern void gSeizeFunctional(PFUNC pTarget,PFUNC NewFunc);

// �������������ǰ����ִ��.(NewFunc����Ϊ��)
extern void gReplaceFunctional(PFUNC NewFunc);

// �Ƴ�һ�����е�����(�κ�����),��pTargetΪ��ʱ���Ƴ���ǰ����(�Ƴ�������)
extern void gRemoveFunctional(PFUNC pTarget);

//�ں˶�ʱ��
extern void gKernel_sleep(int timeMs);

//�ں˶�ʱ��(��ʱ��仹��ִ����������)
extern int gKernelTimes(R_PFUNC pRfunc);

extern void gEndKernel(void);




#ifdef __cplusplus
}
#endif

#endif
