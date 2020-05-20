////////////////////////////////////////////////////////////////////////////////
//自动生成文件，请勿直接修改
////////////////////////////////////////////////////////////////////////////////
//=============================================================================
//参数名称固定空间24+1，实际能正常显示的只有20Byte，后4字节异常（工具原因）----
	#define  Head_Name                     	 0     		//Len:[24   ] S全国农行
//-----------------------------------------------------------------------------
//接入模式1
	#define  ConMode				 25    		//Len:[1    ] B1
	#define  ConModeCheck			 26    		//Len:[1    ] H00
//控制超时时限 输入超时60
	#define  InputTimeOut			 27    		//Len:[1    ] B60
	#define  InputTimeOutCheck		 28    		//Len:[1    ] H00
//交易超时时限 接收数据超时   65
	#define  TradeTimeOut			 29    		//Len:[1    ] B65
	#define  TradeTimeOutCheck		 30    		//Len:[1    ] H00
//终端管理员密码  	20060101
	#define  AdminPwd			 31    		//Len:[8    ] S20060101
//固网支付操作密码 	888888
	#define  PayPwd				 40    		//Len:[6    ] S888888
//缺省中心号码序号 	1
	#define  DefCenter			 47    		//Len:[1    ] B1
	#define  DefCenterCheck         		 48    		//Len:[1    ] H00
//密码最大长度 	6
	#define  PwdMaxLen			 49    		//Len:[1    ] B6
	#define  PwdMaxLenCheck         		 50    		//Len:[1    ] H00
//网关认证密钥 
	#define  KDC				 51    		//Len:[4    ] H00000000
//应用功能版本号
	#define  AppVer				 56    		//Len:[4    ] H00000000
//来电显示标志
	#define  CidFlag				 61    		//Len:[1    ] S1
	#define  CidFlagCheck         		 62    		//Len:[1    ] H00
//预拨外线号码
	#define  PreDialNo			 63    		//Len:[12   ] H000000000000000000000000
//拨号等待时限 10
	#define  DailDelay			 76    		//Len:[1    ] B30
	#define  DailDelayCheck         		 77    		//Len:[1    ] H00
//交易提示音开关 0
	#define  TradeSwitch			 78    		//Len:[1    ] B0
	#define  TradeSwitcCheck         	 79    		//Len:[1    ] H00
//音量大小
	#define  nVolume				 80    		//Len:[1    ] B50
	#define  nVolumeCheck		 81    		//Len:[1    ] H00
//屏幕对比度 50
	#define  LcdContrast			 82    		//Len:[1    ] B50
	#define  LcdContrastCheck         	 83    		//Len:[1    ] H00
//交换机时延 1
	#define  SwitchDelay			 84    		//Len:[1    ] B1
	#define  SwitchDelayCheck         	 85    		//Len:[1    ] H00
//终端通话屏蔽 0
	#define  TalkDisable			 86    		//Len:[1    ] B0
	#define  TalkDisableCheck         	 87    		//Len:[1    ] H00
//通讯信号强度 5
	#define  SignalLevel			 88    		//Len:[1    ] B5
	#define  SignalLevelCheck         	 89    		//Len:[1    ] H00
//保存已支付账单 1
	#define  SaveBill			 90    		//Len:[1    ] B1
	#define  SaveBillCheck         		 91    		//Len:[1    ] H00
//打印浓度 20
	#define  PrintDensity			 92    		//Len:[1    ] B70
	#define  PrintDensityCheck         	 93    		//Len:[1    ] H00
//打印开关 1
	#define  PrintON				 94    		//Len:[1    ] B1
	#define  PrintONCheck         		 95    		//Len:[1    ] H00
//条码阅读开关 0
	#define  NoGunSwitch			 96    		//Len:[1    ] B0
	#define  NoGunSwitchCheck         	 97    		//Len:[1    ] H00
//密码输入方式 0
	#define  PwdType				 98    		//Len:[1    ] B0
	#define  PwdTypeCheck         		 99    		//Len:[1    ] H00
//按键音开关 0
	#define  KeySwitch			 100   		//Len:[1    ] B0
	#define  KeySwitchCheck         		 101   		//Len:[1    ] H00
//中心号码选择 0
	#define  CentDialMode			 102   		//Len:[1    ] B0
	#define  CentDialModeCheck         	 103   		//Len:[1    ] H00
//来电报号0不报 
	#define  SpeakTelNo			 104   		//Len:[1    ] B0
	#define  SpeakTelNoCheck         	 105   		//Len:[1    ] H00
//拨出信息中心号码
	#define  CallCentDialNo			 106   		//Len:[17   ] S
//接收信息中心号码
	#define  IncomeCentDialNo		 124   		//Len:[17   ] S
//预拨外线号码
	#define  PreIPDialNo			 142   		//Len:[12   ] S17909
//FSK VIP 标志 0
	#define  FskVip				 155   		//Len:[1    ] B0
	#define  FskVipCheck         		 156   		//Len:[1    ] H00
//来电更新时间 0
	#define  IncomeUpdateTime		 157   		//Len:[1    ] B0
	#define  IncomeUpdateTimeCheck		 158   		//Len:[1    ] H00
//背光时间 0
	#define  BackLight			 159   		//Len:[1    ] B30
	#define  BackLightCheck			 160   		//Len:[1    ] H00
//闪断时间 0
	#define  FlashTime			 161   		//Len:[1    ] B0
	#define  FlashTimeCheck			 162   		//Len:[1    ] H00
//是否mute 0
	#define  mute				 163   		//Len:[1    ] B0
	#define  muteCheck         		 164   		//Len:[1    ] H00
//dtmf 电平 0
	#define  Dtmf_Level			 165   		//Len:[1    ] B0
	#define  Dtmf_LevelCheck         	 166   		//Len:[1    ] H00
//客服显示 
	#define  CustoServiInfo			 167   		//Len:[32   ] S正在呼叫客户服务中心
//客服电话 
	#define  CustoServiceDialNo		 200   		//Len:[16   ] S95599
//ctsi连接超时设置
	#define  FskOverTime			 217   		//Len:[1    ] B0
	#define  FskOverTimeCheck         	 218   		//Len:[1    ] H00
//快捷键绑定菜单
	#define  FuncKeyMenuTrade		 219   		//Len:[3    ] S000
//IC卡降级控制(0能降级)--深圳行要求有降级功能（所有为0），其它非0
	#define  IcNoRelegation			 223   		//Len:[1    ] B0
	#define  IcNoRelegationCheck         	 224   		//Len:[1    ] H00
//ACK等待时间
	#define  AckWaitTime			 225   		//Len:[1    ] B3
	#define  AckWaitTimeCheck         	 226   		//Len:[1    ] H00
//来电制式选择
	#define  incomemode			 227   		//Len:[1    ] B0
	#define  incomemodeCheck         	 228   		//Len:[1    ] H00
//通信方式
	#define  CommMode			 229   		//Len:[1    ] S1
	#define  CommModeCheck         		 230   		//Len:[1    ] H00
//接入IP		
	#define  ServerIp			 231   		//Len:[50   ] S10.12.40.40
//接入端口		
	#define  ServerPort			 282   		//Len:[6    ] S3071
//接入用户名		
	#define  GprsUserName			 289   		//Len:[65   ] Sgdtest1
//接入密码		
	#define  GprsPassword			 355   		//Len:[65   ] Sgd#*12345678
//接入点		
	#define  GprsApn				 421   		//Len:[50   ] SGDABC.SJCS.GDAPN
//电信呼叫号码		
	#define  CallNumber			 472   		//Len:[20   ] S
//TPDU信---贵州:6000410000 ,广东:6000220000,其它:6000210000
	#define  Tpdu				 493   		//Len:[5    ] H6000220000
//滚动条缺省信息		
	#define  ScroMsg				 499   		//Len:[200  ] S欢迎使用农行智付通业务
//外部认证密钥		
	#define  QualifyMainKey			 700   		//Len:[32   ] S
//密钥索引		
	#define  PsamKdcIndex			 733   		//Len:[2    ] S
//卡片状态		
	#define  PsamSta				 736   		//Len:[1    ] S
	#define  PsamStaCheck         		 737   		//Len:[1    ] H00
//农总行PC下载通讯密钥(Ksort[1]+Kindex[1]+Klen[1]+Kdata[16]+KMAC[4])
	#define  PTK_PC				 738   		//Len:[24   ] H000010000102030405060708090A0B0C0D0E0F00000000
//长连接使能		
	#define  OnLineEn			 763   		//Len:[1    ] B0
	#define  OnLineEnCheck         		 764   		//Len:[1    ] H00
//------------------MODEM参数设置----------------
//信号发送强度	
	#define  MsignalLevel			 765   		//Len:[1    ] H05
	#define  MsignalLevelCheck         	 766   		//Len:[1    ] H00
//DTMF拨号时间		
	#define  Mdialtime			 767   		//Len:[1    ] H64
	#define  MdialtimeCheck         		 768   		//Len:[1    ] H00
//检测拨号音时间单位10ms		
	#define  Mchkdialtime			 769   		//Len:[1    ] H8C
	#define  MchkdialCheck         		 770   		//Len:[1    ] H00
//检测应答音时间单位10ms	
	#define  Mchkacktime			 771   		//Len:[1    ] H14
	#define  MchkacktimeCheck         	 772   		//Len:[1    ] H00
//AT命令串		
	#define  Matcmd				 773   		//Len:[64   ] S
//强制延时,默认为关	
	#define  CheckDialSwitch			 838   		//Len:[1    ] B0
	#define  CheckDialSwitchCheck         	 839   		//Len:[1    ] H00
//是否添加P,默认为关	
	#define  CheckAddDialP			 840   		//Len:[1    ] B0
	#define  CheckAddDialPCheck         	 841   		//Len:[1    ] H00
//========================校验参数（格式固定不变3+16+8）=============================			
//结束标记	
	#define  CheckEnd			 842   		//Len:[3    ] SEND
//参数标记（）	
	#define  FLAG_NAME			 846   		//Len:[16   ] SKSPT-KN-MK2-U002
//参数版本日期	
	#define  VER_DATE			 863   		//Len:[8    ] S20171106
//==================================================================================
// 参数Flash区域:总共空间=0x10000字节
//               已用空间=0x00368字节 [1%]
//               剩余空间=0x0FC98字节 [98%]
//==================================================================================
