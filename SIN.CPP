#include<conio.h>
#include <windows.h>
#include<stdio.h>
#include<math.h>
#pragma comment(lib,"mp411.lib")
#include"mp411.h"
#define f 360
HANDLE hDevice0=INVALID_HANDLE_VALUE;  //硬件操作句柄
//HANDLE hDevice1=INVALID_HANDLE_VALUE;  //硬件操作句柄
void main()
{
	//获得411硬件操作句柄
	hDevice0=MP411_OpenDevice(0); //创建设备驱动句柄，设备号为0
//	hDevice1=MP411_OpenDevice(1); //创建设备驱动句柄，设备号为1
	long y=0;
	float amp=0.2,Kp=0.1,error=0,acc_goal=0.3;
	float V_goal=0.75*acc_goal;
	float temp_data[10];
	int j=0;
	//long check=1;
	double s=0.0;
	long int t=0;  //AD用参数
	double m=0.0,max=0;
	FILE* stream;  //文件指针
	stream = fopen("2.txt", "w");
	MP411_DA_Mode(hDevice0,1,0);
	MP411_DA_Data(hDevice0,0,2048);
	getch();
	while(!kbhit())
	{
			t=MP411_AD(hDevice0,0,2,0,50);  //AD读取电压值
			m=(t-2048)*5.0/2048;
			for(int tim=0;tim<f;tim++)
			{
				y=long(2048+amp*1500.0*sin(tim*3.14*7/180));   //DA输出sin函数
				//	check=MP411_DA_Data(hDevice0,0,y);
				MP411_DA_Data(hDevice0,1,y);
				s=(y-2048)*5.0/2048.0;
				//printf("DA输出：数字量=%ld,电压为%.4fV\n",y,s);
				fprintf(stream,"DA检测：数字量=%ld,电压为%.4fV\n",y,s);
				
				if(tim==0)
					temp_data[j]=m;
				else 
				{
					if(m>temp_data[j])
						temp_data[j]=m;
				}
				
				if(tim==(f-1))
				{
					max+=temp_data[j];
					j++;
				}
				if(j==3)
				{
					j=0;
					max=max/3.0;
					printf("max检测：数字量=%f\n",max);
					error=max-V_goal;
					max=0;					
					/*if(error>=0.05)
						amp=amp+0.05;
					if(error<=-0.05)
						amp=amp-0.05;*/
					if(fabs(error)>=0.02)
						amp=amp+Kp*error;

				}
				//max=max/3;
				//printf("AD检测：数字量=%ld,电压为%.4fV\n",t,m);
				//if(tim==0)max=m;
				//else max=(m<max?m:max);
			}
		
		
		//if(amp<0)
			//amp=0;
		//printf("amp检测：数字量=%f\n",amp);
		


	}

	getch();	//退出<br>
	MP411_CloseDevice(hDevice0); //关闭操作句柄
//	MP411_CloseDevice(hDevice1); //关闭操作句柄<br>
}
