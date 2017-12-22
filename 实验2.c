#include<STC12C5A60S2.h>
#include<intrins.h>
#define uchar	unsigned	char//宏定义
#define uint	unsigned	int
#define	LED_PORT	P0			  //定义跑马灯连接的端口
#define KEY_PORT	P3			//定义键盘接口
sbit LED0=P0^0;
sbit LED1=P0^1;
sbit LED2=P0^2;
sbit LED3=P0^3;
sbit LED4=P0^4;
sbit LED5=P0^5;
sbit LED6=P0^6;
sbit LED7=P0^7;
unsigned char scan,read,key_num;//参考电平；读KEY_PORT口电平；检测到得键盘位数
void Delay_ms(unsigned int time);	//声明延时函数


void one(){
	uint i=1;
	while(1){
		LED0= 0;
		Delay_ms(500);
		LED2= 0;
		Delay_ms(500);
		LED0= 1;
		LED2= 1;
		break;}
		}

 
 
 
uint o;
void two()
{
	uchar temp = 0xFE,i = 0,flag = 0;
    o=8;
	while(o)
	{
		if(flag == 0)
		{
			LED_PORT = temp;
			Delay_ms(500);//延时0.5s
			//移位函数_crol_()包含在头文件intrins.h里面，在#include<intrins.h>之后，可以直接调用这个函数
			temp=_crol_(temp,1);//循环左移一位（例如：若调用函数前temp：0000 0001 ,调用函数后temp：0000 0010）
			i++;
			if(i == 7)flag = 1;			
		}
		else 
		{
			LED_PORT = temp;
			Delay_ms(500);//延时0.5s
			temp=_cror_(temp,1);//循环右移一位（例如：若调用函数前temp：0000 0001 ,调用函数后temp：1000 0000）
		    --i;
			if(i == 0)flag = 0;			
		}
		o--;
	}	
	LED_PORT=0xFF;		
}

void three(){
	uint i=2;
	while(i){
		LED0=0;
		LED1=0;
		LED2=0;
		LED3=0;
		LED4=0;
		LED5=0;
		LED6=0;
		LED7=0;
		Delay_ms(500);
		LED0=1;
		LED1=1;
		LED2=1;
		LED3=1;
		LED4=1;
		LED5=1;
		LED6=1;
		LED7=1;
		Delay_ms(500);
		i--;
}
		}
unsigned char Key_Scan() //键盘扫描程序	
{
	key_num=0;
	KEY_PORT=0xfe;//从下面数起第一行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(50);//延迟一段时间，消斗，
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0) // 若真的有键按下，再进行判断哪个按键按下
				{
					switch(scan)
						{
							case 0x70:key_num=16;break;
							case 0xb0:key_num=15;break;
							case 0xd0:key_num=14;break;
							case 0xe0:key_num=13;break;						
						}
					while(scan!=0xf0)//松手检测
					{
						while(scan != 0xf0)//松手消抖检测
						{
							Delay_ms(50);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(50);
						read=KEY_PORT;
						scan=read&0xf0;
					}
				}

		}

	KEY_PORT=0xfd;//从下面数起第二行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(50);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
			{
				switch(scan)
				{
					case 0x70:key_num=12;break;
					case 0xb0:key_num=11;break;
					case 0xd0:key_num=10;break;
					case 0xe0:key_num=9;break;						
				}
					while(scan!=0xf0)
					{
						while(scan != 0xf0)
						{
							Delay_ms(50);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(50);
						read=KEY_PORT;
						scan=read&0xf0;
					}
		    }

		}


    KEY_PORT=0xfb;//从下面数起第三行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(50);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
				{
					switch(scan)
						{
							case 0x70:key_num=8;break;
							case 0xb0:key_num=7;break;
							case 0xd0:key_num=6;break;
							case 0xe0:key_num=5;break;						
						}
						while(scan!=0xf0)
						{
							while(scan != 0xf0)
							{
								Delay_ms(50);
								read=KEY_PORT;
								scan=read&0xf0;				
							}
							Delay_ms(50);
							read=KEY_PORT;
							scan=read&0xf0;
						}
				}

		}


    KEY_PORT=0xf7;//从下面数起第四行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(50);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
				{
					switch(scan)
						{
							case 0x70:key_num=4;break;
							case 0xb0:three();break;
							case 0xd0:two();break;
							case 0xe0:one();break;						
						}
					while(scan!=0xf0)
					{
						while(scan != 0xf0)
						{
							Delay_ms(70);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(50);
						read=KEY_PORT;
						scan=read&0xf0;
					}
				}

		}
	return(key_num);
}

void main()
{
	P0=0xff;
	while (1)
	  {
	     Key_Scan();
}
		
}


void Delay_ms(uint time)
{
	uint i,j;
	for(i = 0;i < time;i ++)
		for(j = 0;j < 930;j ++);
}
