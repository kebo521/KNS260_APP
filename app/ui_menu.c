/*****************************菜单服务******************************
//功能-------  用于处理菜单创建、执行、显示、处理
//作者-------  邓国祖
//创作时间--20150604
******************************************************************************/
#include "communal.h"



//====================================================================
//功能:   创建新的固定返回菜单(此过程需要申请内存空间)
//输入数据:pTitle 标题，pMenuText菜单显示项，tNum菜单总项数，pUnifiedFunc菜单处理的功能
//输出数据:无
//创作时间:  	20161128
//---------------------------------------------------------------
int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs)
{
	return pGuiFun->CreateMenuByStr(pTitle,tNum,pMenuText,(void*)pUnifiedFunc,TimeOutMs);
}

//====================================================================
//功能:   创建新的内存菜单(运行菜单不使用外部空间，此过程需要申请较大内存空间)
//输入数据:pTitle 标题，tNum菜单总项数，pMenuAll菜单显示与功能
//输出数据:RET_OK创建成功，RET_ERR 创建失败
//创作时间:  	20151230
//---------------------------------------------------------------
int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs)
{
	return pGuiFun->CreateMenuByStruct(pTitle,tNum,pMenuAll,TimeOutMs);
}


//====================================================================
//功能:   将链表菜单转成结构菜单(此过程需要申请内存空间，菜单的大小级数视内存而定)
//作用:   将pStrlist中的菜单内容考到结构菜单中，并释放pStrlist(由ShowFlowMenu所申请)所对应的内在空间
//输入数据:pTitle 菜单标题,pStrlist 菜单数据链(显示内容，处理方式)
//输出数据:RET_OK创建成功，RET_ERR 创建失败
//创作时间:  	20170207
//---------------------------------------------------------------
int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs)
{
	return pGuiFun->CreateMenuByList(pTitle,(void*)pMenulist,TimeOutMs);
}

//====================================================================
//功能:  向当前菜单添加其它功能键执行功能
//作用:  用于菜单需要增加额外功能
//输入数据:type 功能类型,pFunc功能执行函数，pFunTitle 功能标题。
//输出数据:无
//---------------------------------------------------------------
void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,void* pFunc,const char *pData)
{
	pGuiFun->AddCurrentMenuOtherFun(type,pFunc,pData);
}

//====================================================================
//功能:  标准SDK显示处理菜单，
//作用:  显示，并处理链表pMenuUiTable里面的菜单
//输入数据:无
//输出数据:菜单执行结果
//----------------------------------------------------------------
int APP_ShowMenuProsse(void)
{
	return pGuiFun->ShowProsseMenu();
}


int APP_ShowFixedMenu(char* pTitle,const FixedMenuUITable *pFixedMenu,void* pTagFunc)
{
	return pGuiFun->FixedMenu(pTitle,(void*)pFixedMenu,pTagFunc);
}



