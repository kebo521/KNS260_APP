#ifndef _EVENMSG_
#define _EVENMSG_

typedef int (*Fun_KillThread)(HANDLE); 



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



	#define FIFO_OperatSetMsg 				pSdkFun->even->SetMsg
	#define FIFO_OperatGetMsg 				pSdkFun->even->GetMsg
	#define FIFO_OperatPeekGetMsg 			pSdkFun->even->GetMsgPeek


	#define APP_OperationKillThread 		pSdkFun->even->KillThread
	#define APP_OperationCreateThread 		pSdkFun->even->CreateThread
	#define APP_OperationLoadThread 		pSdkFun->even->LoadThread


//��ͨ�ö���
	#define TIME_ONCE		(0)			//!< ���Ϸ���
	#define TIME_INFINE		(-1)		//!< һֱ��
	#define TIME_NOWAIT		(-2)		//!< ���ȴ�
	
	/**
	 * WaitEvent�¼����Ͷ���
	 */
	enum EVENT_TYPE
	{
		EVENT_NONE		=0x00000000,	//!< ��Ч�¼�		
		EVENT_INDEX		=0x000000FF,	//!< �豸����		
		EVENT_ICC		=0x00000100,	//!< �Ӵ�ʽIC��/�ǽӴ�ʽIC��/PSAM��
		EVENT_MAG		=0x00000200,	//!< �ſ�ˢ��
		EVENT_NET		=0x00000400,	//!< ����ͨ�Žӿ�			API_NetEvent
		EVENT_SCAN		=0x00000800,	//!< ����ͷɨ��						
		EVENT_KEY		=0x00001000,	//!< ����
		EVENT_PEN		=0x00002000,	//!< ������
		EVENT_UART		=0x00004000,	//!< UART����
		EVENT_AUDIO		=0x00008000,	//!< ��Ƶͨ�Žӿ�		
		EVENT_UI		=0x00010000,	//!< ͼ���û�����ӿ�
		EVENT_SYS		=0x00020000,	//!< ϵͳ�ӿ�
		EVENT_MISC		=0x00040000,	//!< ��������ӿ�
		EVENT_PRINT		=0x00080000,	//!< ��ӡ���
		EVENT_PHONE		=0x00100000,	//!< �绰����				API_Phone_GetEvent
		EVENT_ERROR		=0x01000000,	//!< ����
		EVENT_TIMEOUT	=0x02000000,	//!< ��ʱ
		EVENT_OK  		=0x04000000,	//!< ȷ��	   ȷ��		ȷ��	��
		EVENT_CANCEL	=0x08000000,	//!< ȡ��	   ����		�˳�	��
		EVENT_QUIT		=0x10000000,	//!< �˳�
		EVENT_MASK		=0x7FFFFF00,		//!< EVENT����
	};	

	#define Set_WaitEvent 			pSdkFun->even->SetEvent
	#define Get_EventMsg 			pSdkFun->even->GetEvent
	#define Rewrite_WaitTime 		pSdkFun->even->SetEventTime
	/**
	 * �ȴ�����¼��б���
	 * 
	 * @param tTimeOutMs �ȴ���ʱʱ�䣬��λ:����
	 * @param ... �¼�����(EVENT_TYPE|EVENT_INDEX),�磺(EVENT_UART|UART_1)��ʾ����1
	 * @return �ο�{@link EVENT_TYPE}
	 *	�κ��¼� ����EVENT_ERROR|EVENT_TIMEOUT
	 * 	EVENT_UI�¼� ����EVENT_OK|EVENT_CANCEL|EVENT_QUIT
	 *  ����EVENT_TYPE ����EVENT_TYPE|EVENT_INDEX
	 */
	#define API_WaitEvent 		pSdkFun->even->WaitEvent
	
	

#endif
