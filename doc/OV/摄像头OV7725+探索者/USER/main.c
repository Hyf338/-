#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"  
#include "usart2.h"  
#include "timer.h" 
#include "ov7670.h" 
#include "dcmi.h" 
#include "sram.h"
//ALIENTEK ̽����STM32F407������ ʵ��35
//����ͷ ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

extern u8 ov_sta;

void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta)//��֡�жϸ��£�
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//����ʾ�������õ���Ļ����
		else if(lcddev.id==0X5510||lcddev.id==0X5310)LCD_Set_Window((lcddev.width-320)/2,(lcddev.height-240)/2,320,240);//����ʾ�������õ���Ļ����
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK_H;
		for(j=0;j<76800;j++)
		{
			OV7670_RCK_L;
			color=OV7670_DATA;	//������
			OV7670_RCK_H; 
			color<<=8;  
			OV7670_RCK_L;
			color|=OV7670_DATA;	//������
			OV7670_RCK_H; 
			LCD->LCD_RAM=color;    
		}   							  
 		ov_sta=0;					//����֡�жϱ�
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽��
		LED1=!LED1;		
	} 
}
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
	TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
	FSMC_SRAM_Init();
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"OV7670 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2018/8/18");

	
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(30,130,240,16,16,"OV7670 ERR");
		delay_ms(200);
		LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
		LED0=!LED0;
	}

	LCD_ShowString(30,130,200,16,16,"OV7670 OK");  		
	delay_ms(1500);	 	   
				  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
	OV7725_Window_Set(320,240 ,1);	//���ô��� ��ʱ��0���У���
	
  	OV7670_CS=0;					
	LCD_Clear(BLACK);
 	while(1)
	{	
		camera_refresh();//������ʾ

		static int i=0;
		i++;
		if(i==15)//DS0��˸.
		{
			i=0;
			LED0=!LED0;
 		}
	}	   

}
