////////////////////////////////////////////////////////////////////////////////
//�Զ������ļ�������ֱ���޸�
////////////////////////////////////////////////////////////////////////////////
//=============================================================================
//�������ƹ̶��ռ�24+1��ʵ����������ʾ��ֻ��20Byte����4�ֽ��쳣������ԭ��----
	#define  Head_Name                     	 0     		//Len:[24   ] Sȫ��ũ��
//-----------------------------------------------------------------------------
//����ģʽ1
	#define  ConMode				 25    		//Len:[1    ] B1
	#define  ConModeCheck			 26    		//Len:[1    ] H00
//���Ƴ�ʱʱ�� ���볬ʱ60
	#define  InputTimeOut			 27    		//Len:[1    ] B60
	#define  InputTimeOutCheck		 28    		//Len:[1    ] H00
//���׳�ʱʱ�� �������ݳ�ʱ   65
	#define  TradeTimeOut			 29    		//Len:[1    ] B65
	#define  TradeTimeOutCheck		 30    		//Len:[1    ] H00
//�ն˹���Ա����  	20060101
	#define  AdminPwd			 31    		//Len:[8    ] S20060101
//����֧���������� 	888888
	#define  PayPwd				 40    		//Len:[6    ] S888888
//ȱʡ���ĺ������ 	1
	#define  DefCenter			 47    		//Len:[1    ] B1
	#define  DefCenterCheck         		 48    		//Len:[1    ] H00
//������󳤶� 	6
	#define  PwdMaxLen			 49    		//Len:[1    ] B6
	#define  PwdMaxLenCheck         		 50    		//Len:[1    ] H00
//������֤��Կ 
	#define  KDC				 51    		//Len:[4    ] H00000000
//Ӧ�ù��ܰ汾��
	#define  AppVer				 56    		//Len:[4    ] H00000000
//������ʾ��־
	#define  CidFlag				 61    		//Len:[1    ] S1
	#define  CidFlagCheck         		 62    		//Len:[1    ] H00
//Ԥ�����ߺ���
	#define  PreDialNo			 63    		//Len:[12   ] H000000000000000000000000
//���ŵȴ�ʱ�� 10
	#define  DailDelay			 76    		//Len:[1    ] B30
	#define  DailDelayCheck         		 77    		//Len:[1    ] H00
//������ʾ������ 0
	#define  TradeSwitch			 78    		//Len:[1    ] B0
	#define  TradeSwitcCheck         	 79    		//Len:[1    ] H00
//������С
	#define  nVolume				 80    		//Len:[1    ] B50
	#define  nVolumeCheck		 81    		//Len:[1    ] H00
//��Ļ�Աȶ� 50
	#define  LcdContrast			 82    		//Len:[1    ] B50
	#define  LcdContrastCheck         	 83    		//Len:[1    ] H00
//������ʱ�� 1
	#define  SwitchDelay			 84    		//Len:[1    ] B1
	#define  SwitchDelayCheck         	 85    		//Len:[1    ] H00
//�ն�ͨ������ 0
	#define  TalkDisable			 86    		//Len:[1    ] B0
	#define  TalkDisableCheck         	 87    		//Len:[1    ] H00
//ͨѶ�ź�ǿ�� 5
	#define  SignalLevel			 88    		//Len:[1    ] B5
	#define  SignalLevelCheck         	 89    		//Len:[1    ] H00
//������֧���˵� 1
	#define  SaveBill			 90    		//Len:[1    ] B1
	#define  SaveBillCheck         		 91    		//Len:[1    ] H00
//��ӡŨ�� 20
	#define  PrintDensity			 92    		//Len:[1    ] B70
	#define  PrintDensityCheck         	 93    		//Len:[1    ] H00
//��ӡ���� 1
	#define  PrintON				 94    		//Len:[1    ] B1
	#define  PrintONCheck         		 95    		//Len:[1    ] H00
//�����Ķ����� 0
	#define  NoGunSwitch			 96    		//Len:[1    ] B0
	#define  NoGunSwitchCheck         	 97    		//Len:[1    ] H00
//�������뷽ʽ 0
	#define  PwdType				 98    		//Len:[1    ] B0
	#define  PwdTypeCheck         		 99    		//Len:[1    ] H00
//���������� 0
	#define  KeySwitch			 100   		//Len:[1    ] B0
	#define  KeySwitchCheck         		 101   		//Len:[1    ] H00
//���ĺ���ѡ�� 0
	#define  CentDialMode			 102   		//Len:[1    ] B0
	#define  CentDialModeCheck         	 103   		//Len:[1    ] H00
//���籨��0���� 
	#define  SpeakTelNo			 104   		//Len:[1    ] B0
	#define  SpeakTelNoCheck         	 105   		//Len:[1    ] H00
//������Ϣ���ĺ���
	#define  CallCentDialNo			 106   		//Len:[17   ] S
//������Ϣ���ĺ���
	#define  IncomeCentDialNo		 124   		//Len:[17   ] S
//Ԥ�����ߺ���
	#define  PreIPDialNo			 142   		//Len:[12   ] S17909
//FSK VIP ��־ 0
	#define  FskVip				 155   		//Len:[1    ] B0
	#define  FskVipCheck         		 156   		//Len:[1    ] H00
//�������ʱ�� 0
	#define  IncomeUpdateTime		 157   		//Len:[1    ] B0
	#define  IncomeUpdateTimeCheck		 158   		//Len:[1    ] H00
//����ʱ�� 0
	#define  BackLight			 159   		//Len:[1    ] B30
	#define  BackLightCheck			 160   		//Len:[1    ] H00
//����ʱ�� 0
	#define  FlashTime			 161   		//Len:[1    ] B0
	#define  FlashTimeCheck			 162   		//Len:[1    ] H00
//�Ƿ�mute 0
	#define  mute				 163   		//Len:[1    ] B0
	#define  muteCheck         		 164   		//Len:[1    ] H00
//dtmf ��ƽ 0
	#define  Dtmf_Level			 165   		//Len:[1    ] B0
	#define  Dtmf_LevelCheck         	 166   		//Len:[1    ] H00
//�ͷ���ʾ 
	#define  CustoServiInfo			 167   		//Len:[32   ] S���ں��пͻ���������
//�ͷ��绰 
	#define  CustoServiceDialNo		 200   		//Len:[16   ] S95599
//ctsi���ӳ�ʱ����
	#define  FskOverTime			 217   		//Len:[1    ] B0
	#define  FskOverTimeCheck         	 218   		//Len:[1    ] H00
//��ݼ��󶨲˵�
	#define  FuncKeyMenuTrade		 219   		//Len:[3    ] S000
//IC����������(0�ܽ���)--������Ҫ���н������ܣ�����Ϊ0����������0
	#define  IcNoRelegation			 223   		//Len:[1    ] B0
	#define  IcNoRelegationCheck         	 224   		//Len:[1    ] H00
//ACK�ȴ�ʱ��
	#define  AckWaitTime			 225   		//Len:[1    ] B3
	#define  AckWaitTimeCheck         	 226   		//Len:[1    ] H00
//������ʽѡ��
	#define  incomemode			 227   		//Len:[1    ] B0
	#define  incomemodeCheck         	 228   		//Len:[1    ] H00
//ͨ�ŷ�ʽ
	#define  CommMode			 229   		//Len:[1    ] S1
	#define  CommModeCheck         		 230   		//Len:[1    ] H00
//����IP		
	#define  ServerIp			 231   		//Len:[50   ] S10.12.40.40
//����˿�		
	#define  ServerPort			 282   		//Len:[6    ] S3071
//�����û���		
	#define  GprsUserName			 289   		//Len:[65   ] Sgdtest1
//��������		
	#define  GprsPassword			 355   		//Len:[65   ] Sgd#*12345678
//�����		
	#define  GprsApn				 421   		//Len:[50   ] SGDABC.SJCS.GDAPN
//���ź��к���		
	#define  CallNumber			 472   		//Len:[20   ] S
//TPDU��---����:6000410000 ,�㶫:6000220000,����:6000210000
	#define  Tpdu				 493   		//Len:[5    ] H6000220000
//������ȱʡ��Ϣ		
	#define  ScroMsg				 499   		//Len:[200  ] S��ӭʹ��ũ���Ǹ�ͨҵ��
//�ⲿ��֤��Կ		
	#define  QualifyMainKey			 700   		//Len:[32   ] S
//��Կ����		
	#define  PsamKdcIndex			 733   		//Len:[2    ] S
//��Ƭ״̬		
	#define  PsamSta				 736   		//Len:[1    ] S
	#define  PsamStaCheck         		 737   		//Len:[1    ] H00
//ũ����PC����ͨѶ��Կ(Ksort[1]+Kindex[1]+Klen[1]+Kdata[16]+KMAC[4])
	#define  PTK_PC				 738   		//Len:[24   ] H000010000102030405060708090A0B0C0D0E0F00000000
//������ʹ��		
	#define  OnLineEn			 763   		//Len:[1    ] B0
	#define  OnLineEnCheck         		 764   		//Len:[1    ] H00
//------------------MODEM��������----------------
//�źŷ���ǿ��	
	#define  MsignalLevel			 765   		//Len:[1    ] H05
	#define  MsignalLevelCheck         	 766   		//Len:[1    ] H00
//DTMF����ʱ��		
	#define  Mdialtime			 767   		//Len:[1    ] H64
	#define  MdialtimeCheck         		 768   		//Len:[1    ] H00
//��Ⲧ����ʱ�䵥λ10ms		
	#define  Mchkdialtime			 769   		//Len:[1    ] H8C
	#define  MchkdialCheck         		 770   		//Len:[1    ] H00
//���Ӧ����ʱ�䵥λ10ms	
	#define  Mchkacktime			 771   		//Len:[1    ] H14
	#define  MchkacktimeCheck         	 772   		//Len:[1    ] H00
//AT���		
	#define  Matcmd				 773   		//Len:[64   ] S
//ǿ����ʱ,Ĭ��Ϊ��	
	#define  CheckDialSwitch			 838   		//Len:[1    ] B0
	#define  CheckDialSwitchCheck         	 839   		//Len:[1    ] H00
//�Ƿ����P,Ĭ��Ϊ��	
	#define  CheckAddDialP			 840   		//Len:[1    ] B0
	#define  CheckAddDialPCheck         	 841   		//Len:[1    ] H00
//========================У���������ʽ�̶�����3+16+8��=============================			
//�������	
	#define  CheckEnd			 842   		//Len:[3    ] SEND
//������ǣ���	
	#define  FLAG_NAME			 846   		//Len:[16   ] SKSPT-KN-MK2-U002
//�����汾����	
	#define  VER_DATE			 863   		//Len:[8    ] S20171106
//==================================================================================
// ����Flash����:�ܹ��ռ�=0x10000�ֽ�
//               ���ÿռ�=0x00368�ֽ� [1%]
//               ʣ��ռ�=0x0FC98�ֽ� [98%]
//==================================================================================
