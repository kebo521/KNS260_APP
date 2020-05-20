/*****************************�˵�����******************************
//����-------  ���ڴ���˵�������ִ�С���ʾ������
//����-------  �˹���
//����ʱ��--20150604
******************************************************************************/
#include "communal.h"



//====================================================================
//����:   �����µĹ̶����ز˵�(�˹�����Ҫ�����ڴ�ռ�)
//��������:pTitle ���⣬pMenuText�˵���ʾ�tNum�˵���������pUnifiedFunc�˵�����Ĺ���
//�������:��
//����ʱ��:  	20161128
//---------------------------------------------------------------
int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs)
{
	return pGuiFun->CreateMenuByStr(pTitle,tNum,pMenuText,pUnifiedFunc,TimeOutMs);
}

//====================================================================
//����:   �����µ��ڴ�˵�(���в˵���ʹ���ⲿ�ռ䣬�˹�����Ҫ����ϴ��ڴ�ռ�)
//��������:pTitle ���⣬tNum�˵���������pMenuAll�˵���ʾ�빦��
//�������:RET_OK�����ɹ���RET_ERR ����ʧ��
//����ʱ��:  	20151230
//---------------------------------------------------------------
int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs)
{
	return pGuiFun->CreateMenuByStruct(pTitle,tNum,pMenuAll,TimeOutMs);
}


//====================================================================
//����:   ������˵�ת�ɽṹ�˵�(�˹�����Ҫ�����ڴ�ռ䣬�˵��Ĵ�С�������ڴ����)
//����:   ��pStrlist�еĲ˵����ݿ����ṹ�˵��У����ͷ�pStrlist(��ShowFlowMenu������)����Ӧ�����ڿռ�
//��������:pTitle �˵�����,pStrlist �˵�������(��ʾ���ݣ�����ʽ)
//�������:RET_OK�����ɹ���RET_ERR ����ʧ��
//����ʱ��:  	20170207
//---------------------------------------------------------------
int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs)
{
	return pGuiFun->CreateMenuByList(pTitle,pMenulist,TimeOutMs);
}

//====================================================================
//����:  ��ǰ�˵�����������ܼ�ִ�й���
//����:  ���ڲ˵���Ҫ���Ӷ��⹦��
//��������:type ��������,pFunc����ִ�к�����pFunTitle ���ܱ��⡣
//�������:��
//---------------------------------------------------------------
void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,APP_HANDLE pFunc,const char *pFunTitle)
{
	pGuiFun->AddCurrentMenuOtherFun(type,pFunc,pFunTitle);
}

//====================================================================
//����:  ��׼SDK��ʾ����˵���
//����:  ��ʾ������������pMenuUiTable����Ĳ˵�
//��������:��
//�������:�˵�ִ�н��
//----------------------------------------------------------------
int APP_ShowMenuProsse(void)
{
	return pGuiFun->ShowProsseMenu();
}


int APP_ShowFixedMenu(char* pTitle,const FixedMenuUITable *pFixedMenu,void* pTagFunc)
{
	return pGuiFun->FixedMenu(pTitle,pFixedMenu,pTagFunc);
}



