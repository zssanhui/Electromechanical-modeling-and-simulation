

//opem MP411
extern "C" HANDLE __declspec(dllimport)  __stdcall MP411_OpenDevice(long dev_num);
//close device
extern "C" long __declspec(dllimport)  __stdcall MP411_CloseDevice(HANDLE hDevice1);


//********************************************
//get board info
//model or type in *bStr
extern "C" long __declspec(dllimport)  __stdcall MP411_Info(HANDLE hDevice,char *modle);


//****************************************************************************
//for AD

//*****************************************************************
//sam a single channel with average times=naver
//ch=0-15 , selected input
//gain: selected input range, 0,1,2 via: 5/10/B5 V
//sidi: not using by MP411
//return data=0-4095, 12bit ad data, if -1 error
//naver: average times, =0-100, if 0 aver times=1
extern "C" long __declspec(dllimport)  __stdcall MP411_AD(HANDLE hDevice1,long ch,long gain,long sidi,long naver);

//*****************************************************************
//sam multi channel from stch to endch
//gain: selected input range, 0,1,2 via: 5/10/B5 V
//sidi: not using by MP411
//return 0 ok, if -1 error
//*addata is long addata[16], is return ad data, addata[0] stch's data,addata[1] (stch+1)'s data, 
extern "C" long __declspec(dllimport)  __stdcall MP411_AD_Scan(HANDLE hDevice1,long stch,long endch,long gain,long sidi,long *addata);




//end AD

//****************************************************************************
//DIO
//get 16bit DI data, data return by MP411_DI
extern "C" long __declspec(dllimport)  __stdcall MP411_DI(HANDLE hDevice1);
//set 16bit DO data=dodata
extern "C" long __declspec(dllimport)  __stdcall MP411_DO(HANDLE hDevice1,long dodata);

//****************************************************************************
//counter
///start counter 
//cmode=0: set cnt is counter mode
//     =1: set Freq. measuring mode
extern "C" long __declspec(dllimport)  __stdcall MP411_CNT_RUN(HANDLE hDevice1,long cmode);

//read cnt data 
//return if -1 : cnt overflow
//*timer_state, using at Freq mode, =1 1S timer not end  / =0: end
extern "C" long __declspec(dllimport)  __stdcall MP411_CNT_RD(HANDLE hDevice1, long *timer_state);

//**********************************************************************************
//da
//set da data
//dch=0:da channel0 /1:da channel 1
//dadata=0-4095: 12bit DA data
extern "C" long __declspec(dllimport)  __stdcall MP411_DA_Data(HANDLE hDevice1,long dch,long dadata);

//set DA Mode
//dgs: 0: out 0-10V / 1: +/-5V
extern "C" long __declspec(dllexport)  __stdcall MP411_DA_Mode(HANDLE hDevice1,long dgs0,long dgs1);



//**********************************************************************************
//read a byte from hardware
extern "C" long __declspec(dllimport)  __stdcall MP411_inb(HANDLE hdevice,int adr);
//read a word from hardware
extern "C" long __declspec(dllimport)  __stdcall MP411_inw(HANDLE hdevice,int adr);
//write byte
extern "C" long __declspec(dllimport)  __stdcall MP411_outb(HANDLE hdevice,long adr,long data1);
//write word
extern "C" long __declspec(dllimport)  __stdcall MP411_outw(HANDLE hdevice,long adr,long data1);
////////////////////////end
