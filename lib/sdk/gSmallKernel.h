//====================================================================
/*****************************小内核******************************
//功能------- 内核处理结构与前文件定义?--------
//作者-------  邓国祖
//创作时间--20140724
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
//==================头文件定义==================================================
//  多任务处理,任务初始化后执行
extern void gKernelHandles(void);

//添加新任务于当前任务后.(NewFunc不能为空)
extern void gLoadingFunctional(PFUNC NewFunc);

//在当前任务上添加一个衍生新任务但替之前任务执行，
//直到取消抢占任务(可用于保存初始化任务，执行对应的新任务).(NewFunc不能为空)
extern void gTaskStackFunctional(PFUNC NewFunc);

//在当前任务上添加一个抢占任务，抢占任务将代替旧任务执行，直到移除此抢占任务.(NewFunc不能为空)
extern void gSeizeFunctional(PFUNC pTarget,PFUNC NewFunc);

// 用新任务替代当前任务执行.(NewFunc不能为空)
extern void gReplaceFunctional(PFUNC NewFunc);

// 移除一个已有的任务(任何任务),当pTarget为空时，移除当前任务(移除任务本身)
extern void gRemoveFunctional(PFUNC pTarget);

//内核定时器
extern void gKernel_sleep(int timeMs);

//内核定时器(定时其间还在执行其它任务)
extern int gKernelTimes(R_PFUNC pRfunc);

extern void gEndKernel(void);




#ifdef __cplusplus
}
#endif

#endif
