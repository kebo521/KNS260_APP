#ifndef _EVENMSG_
#define _EVENMSG_



	typedef enum
	{
		EVEN_ID_KEY_DOWN, 
		EVEN_ID_SCAN,
		EVEN_ID_NOTIFY_NSG,
		EVEN_ID_UART_RECV,
		EVEN_ID_WIFI_MSG,
		EVEN_ID_TIME_OUT,
		EVEN_ID_SHOW_UI,
		EVEN_ID_FUNTION_OUT, 
		EVEN_ID_NO_SERVICE 
	} EVEN_MSG_STATE;
	//◎通用定义
	#define TIME_ONCE		(0)			//!< 马上返回
	#define TIME_INFINE		(-1)		//!< 一直等
	#define TIME_NOWAIT		(-2)		//!< 不等待
		
	/**
	 * WaitEvent事件类型定义
	 */
	enum EVENT_TYPE
	{
		EVENT_NONE		=0x00000000,	//!< 无效事件		
		EVENT_INDEX 	=0x000000FF,	//!< 设备索引		
		EVENT_ICC		=0x00000100,	//!< 接触式IC卡/非接触式IC卡/PSAM卡
		EVENT_MAG		=0x00000200,	//!< 磁卡刷卡
		EVENT_NET		=0x00000400,	//!< 网络通信接口			API_NetEvent
		EVENT_SCAN		=0x00000800,	//!< 摄像头扫码 					
		EVENT_KEY		=0x00001000,	//!< 按键
		EVENT_PEN		=0x00002000,	//!< 触摸屏
		EVENT_UART		=0x00004000,	//!< UART串口
		EVENT_AUDIO 	=0x00008000,	//!< 音频通信接口		
		EVENT_UI		=0x00010000,	//!< 图形用户界面接口
		EVENT_SYS		=0x00020000,	//!< 系统接口
		EVENT_MISC		=0x00040000,	//!< 其他杂项接口
		EVENT_PRINT 	=0x00080000,	//!< 打印完成
		EVENT_PHONE 	=0x00100000,	//!< 电话功能				API_Phone_GetEvent
		EVENT_ERROR 	=0x01000000,	//!< 错误
		EVENT_TIMEOUT	=0x02000000,	//!< 超时
		EVENT_OK		=0x04000000,	//!< 确认	   确认 	确认	是
		EVENT_CANCEL	=0x08000000,	//!< 取消	   返回 	退出	否
		EVENT_QUIT		=0x10000000,	//!< 退出
		EVENT_MASK		=0x7FFFFF00,		//!< EVENT掩码
	};	

	typedef struct	
	{
		char Mask[4];	// "Even"
		void (*Init)(void); //int pshared, unsigned int value
		void (*DeInit)(void);
		void (*SetMsg)(u16,u16);
		int (*GetMsg)(u16*,u16*);
		int (*GetMsgPeek)(u16*,u16*);
		
		void (*SetEvent)(int,u32);
		void (*SetEventTime)(int );
		u32  (*WaitEvent)(int,...);
	}API_Even_Def;
	extern API_Even_Def*		pEventFun;		//字库资源

	#define FIFO_OperatSetMsg 		pEventFun->SetMsg
	#define FIFO_OperatGetMsg 		pEventFun->GetMsg
	#define FIFO_OperatPeekGetMsg 	pEventFun->GetMsgPeek
	#define Set_WaitEvent 			pEventFun->SetEvent
	#define Rewrite_WaitTime 		pEventFun->SetEventTime
	/**
	 * 等待相关事件列表触发
	 * 
	 * @param tTimeOutMs 等待超时时间，单位:毫秒
	 * @param ... 事件类型(EVENT_TYPE|EVENT_INDEX),如：(EVENT_UART|UART_1)表示串口1
	 * @return 参考{@link EVENT_TYPE}
	 *	任何事件 返回EVENT_ERROR|EVENT_TIMEOUT
	 * 	EVENT_UI事件 返回EVENT_OK|EVENT_CANCEL|EVENT_QUIT
	 *  其它EVENT_TYPE 返回EVENT_TYPE|EVENT_INDEX
	 */
	#define API_WaitEvent 		pEventFun->WaitEvent
	
	

#endif
