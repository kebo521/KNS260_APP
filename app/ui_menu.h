#ifndef _UI_MENU_
#define _UI_MENU_
//=======����˵��ṹ==========
typedef struct 
{//��ʾ+����
	char			*pText;		//��ʾ����
	APP_HANDLE		pFunMenu;	//������
}CMenuItemStru;


typedef struct _CMenuListPar
{//������֯�˵���
	struct _CMenuListPar *pNext;
	APP_HANDLE		pFunMenu;	//������
	int				TextLen;	//��ʾ���ݳ���
	char			Text[4];	//��ʾ����,������֧�ֵĻ� Text[0]
}CMenuListPar;

typedef int (*APP_IndexH)(char*,int); 

extern int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs);
extern int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs);
extern int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs);
typedef enum 
{
	MENU_KEY_FUN,		//���ܼ�ִ�й���
	MENU_OUT_FUN,		//�˳�ʱ��ִ�й���
	MENU_SHOW_AFT,	//���һ����ʾ
	MENU_BACK_MAP,	//����ͼƬ����
}UI_MENU_ADD_TYPE;
extern void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,APP_HANDLE pFunc,const char *pFunTitle);

extern int APP_ShowMenuProsse(void);

//===================�̶��˵�����=================================================
enum FIXED_MENU_TYPE
{
	FUN_MENU_N,	//�ղ˹��ܣ�����ĩ�˱��
	FUN_MENU_F,	//�����ܲ˵���	(char* pTitle)
	FUN_MENU_I,	//���������ܲ˵��� (char* pTitle,int index)
	FUN_MENU_G,	//�˵���		FixedMenuUITable
};	

typedef struct 
{//��ʾ+����
	char		*pText;		//��ʾ����
	void		*pFun;		//������,�� FunType ָ��(fMenuFun,APP_IndexH,FixedMenuUITable)
	int			FunType;	//FIXED_MENU_TYPE
}tMenuItemStru;

typedef struct
{
	fMenuFun 	pInFunc;		//���빦��
	fMenuFun 	pOutFunc;		//�˳�����
	char*		pMap;			//�˵�ͼƬ(��ʾͼƬ�Ͳ���ʾ����)
	u16			TimeOutS;		//�˵���ʾʱ��(��λ��)(ע:Ϊ0ʱ������ʱ)
	u16			TeamTatla;		//-�˵�������
	tMenuItemStru pItem[10];	//�˵�����,�˵�����
}FixedMenuUITable;

extern int APP_ShowFixedMenu(char* pTitle,const FixedMenuUITable *pFixedMenu,void* pTagFunc);

#endif
