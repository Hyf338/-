/*******************************************************************************
*  Copyright (C) 2010 - All Rights Reserved
*		
* ��������:	��ɼ���
* ��Ȩ����: ��ɵ���	
* ��������:	2012��8��18�� 
* ������ʷ:	2012��8��18���װ�
* Version:  1.0 
* Demo �Ա���ַ��http://store.taobao.com/shop/view_shop.htm?asker=wangwang&shop_nick=qifeidianzi
**********************************************************************************************************************************************
����������������������������������������������������������������������������������������������������������������������������������������������
����������������������һ������������������������������������������������������������һ����������������������������һһһһһһһ��������������
������һһһһ��һһһһһһ������������һһһһһһһһ�������������������ą�����һһ������һ������������������һһһһ����һһһ������������
������������һ������һ��һ������������һһһһ�ą���һ����һһ������������һһһһһһһһһһһ������������������������һһһһ��������������
�������ą���һ��������������������������������������һ��һһ��������������һһ����һһ������һһ������������������������һһ������������������
������һ����һһһһһһһһһһһ������������������һһ������������������һһһһһһһһһһ������������һһһһһһһһһһһһһһһ������
������һһһһһ����һһ��һ����������������������һһһһһ��������������һһ����һһ������һ������������һһ����������һһ������һһ��������
��������������һ��һ��һ��һ������������������������һ����һһ������������һһһһһһһһһһ��������������������������һһ������������������
����һһһ��������һһһ��һ������������������������һһ����������������������������һ��������������һ������������������һһ������������������
������������һ����������һһ��������������������������һһһһһһ������������������һһһһһһһһһ������������������һһ������������������
��������һһһ������һһһһ����������������������������һһһһһ��������������������һһһһһһһ��������������һһһһ��������������������
����������������������������������������������������������������������������������������������������������������������������������������������
**********************************************************************************************************************************************/


#ifndef __SYS_H
#define __SYS_H	 
#include <stm32f10x.h>

//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����
/////////////////////////////////////////////////////////////////
//Ex_NVIC_Configר�ö���
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //�½��ش���
#define RTIR   2  //�����ش���
/////////////////////////////////////////////////////////////////
//JTAGģʽ���ö���
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

/////////////////////////////////////////////////////////////////  
//void BKP_Write(u8 reg,u16 dat);	//д��󱸼Ĵ���
void Stm32_Clock_Init(u8 PLL);  //ʱ�ӳ�ʼ��  
void Sys_Soft_Reset(void);      //ϵͳ����λ
void Sys_Standby(void);         //����ģʽ 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//����ƫ�Ƶ�ַ
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//����NVIC����
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//�ⲿ�ж����ú���(ֻ��GPIOA~G)
void JTAG_Set(u8 mode);
#endif











