/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LS1C101_H_
#define LS1C101_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////  ��������  /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
typedef unsigned char       	INT8U;
typedef signed char				INT8S;
typedef unsigned short      	INT16U;
typedef signed short        	INT16S;
typedef unsigned int         	INT32U;//32λ
typedef signed int           	INT32S;
typedef unsigned long       	INT64U;//64λ
typedef signed long         	INT64S;
typedef float					FP32;
typedef float					FP64;

typedef unsigned char 		    BOOL;

#define NO_INIT 				volatile

/******************************************************************************
 * 
 */
#define UNCACHED_MEMORY_ADDR 	0xa0000000
#define UNCACHED_TO_PHYS(x)     ((x) & 0x1fffffff)
#define PHYS_TO_UNCACHED(x)     ((x) | UNCACHED_MEMORY_ADDR)

#define IRAM_BASEADDR			PHYS_TO_UNCACHED(0x00000000)            //iram
#define DRAM_BASEADDR			PHYS_TO_UNCACHED(0x00001000)            //dram
#define SPI_FLASH_BASEADDR		PHYS_TO_UNCACHED(0x1e000000)            //spi_flash
#define FLASH_BASEADDR			PHYS_TO_UNCACHED(0x1f000000)            //on-chip flash
#define BOOT_ADDR				PHYS_TO_UNCACHED(0x1fc00000)            //spi_flash/on-chip flash
#define FLASH_REG_BASEADDR		PHYS_TO_UNCACHED(0x1fe60000)            //flash regs
#define SPI_REG_BASEADDR		PHYS_TO_UNCACHED(0x1fe70000)            //spi regs
#define UART0_BASEADDR  		PHYS_TO_UNCACHED(0x1fe80000)            //uart0
#define UART1_BASEADDR			PHYS_TO_UNCACHED(0x1fe88000)            //uart1
#define UART2_BASEADDR			PHYS_TO_UNCACHED(0x1fe8c000)            //uart2
#define I2C_BASEADDR			PHYS_TO_UNCACHED(0x1fe90000)            //i2c
#define REGS_BASEADDR			PHYS_TO_UNCACHED(0x1fea0000)            //Interrupt_Regs_Baseadd
#define PMU_BASEADDR			PHYS_TO_UNCACHED(0x1feb0000)            //PMU
#define TSENSOR_BASEADDR		PHYS_TO_UNCACHED(0x1feb4000)            //tsensor
#define RTC_BASEADDR			PHYS_TO_UNCACHED(0x1feb8000)            //rtc
#define DMA_BASEADDR		    PHYS_TO_UNCACHED(0x1fec0000)            //DMA
#define VPWM_BASEADDR		    PHYS_TO_UNCACHED(0x1fec0020)            //vpwm
#define TIMER_BASEADDR		    PHYS_TO_UNCACHED(0x1fed0000)            //timer

/********************************PMU REGS********************************/
#define PMU_ChipCtrl  	       *(volatile unsigned int *)(PMU_BASEADDR+0x00)    //ȫ������
#define PMU_CmdSts  	       *(volatile unsigned int *)(PMU_BASEADDR+0x04)    //������״̬
#define PMU_Count   	       *(volatile unsigned int *)(PMU_BASEADDR+0x08)    //ʱ�������
#define PMU_Compare  	       *(volatile unsigned int *)(PMU_BASEADDR+0x0c)    //����ʱ������
#define PMU_IOSEL0    	       *(volatile unsigned int *)(PMU_BASEADDR+0x10)    //IO����ѡ��0
#define PMU_IOSEL1  	       *(volatile unsigned int *)(PMU_BASEADDR+0x14)    //IO����ѡ��1
#define PMU_IOSEL2   	       *(volatile unsigned int *)(PMU_BASEADDR+0x18)    //IO����ѡ��2
#define PMU_IOSEL3 		       *(volatile unsigned int *)(PMU_BASEADDR+0x1c)    //IO����ѡ��3
#define PMU_ExintEn 	       *(volatile unsigned int *)(PMU_BASEADDR+0x20)    //�ⲿ�ж�ʹ��
#define PMU_ExintPol           *(volatile unsigned int *)(PMU_BASEADDR+0x24)    //�ⲿ�жϼ���
#define PMU_ExintEdge          *(volatile unsigned int *)(PMU_BASEADDR+0x28)    //�ⲿ�жϱ���
#define PMU_ExintSrc           *(volatile unsigned int *)(PMU_BASEADDR+0x2c)    //�ⲿ�ж�״̬
#define PMU_ExintCLr           *(volatile unsigned int *)(PMU_BASEADDR+0x2c)    //�ⲿ�ж�״̬
#define PMU_WdtCfg             *(volatile unsigned int *)(PMU_BASEADDR+0x30)    //���Ź�����
#define PMU_WdtFeed            *(volatile unsigned int *)(PMU_BASEADDR+0x34)    //���Ź�����
#define PMU_PowerCfg 	       *(volatile unsigned int *)(PMU_BASEADDR+0x38)    //��Դ����
#define PMU_GPIOA_OE 	       *(volatile unsigned int *)(PMU_BASEADDR+0x40)    //GPIOA���ʹ��
#define PMU_GPIOA_O		       *(volatile unsigned int *)(PMU_BASEADDR+0x44)    //GPIOA�����ƽ
#define PMU_GPIOA_I		       *(volatile unsigned int *)(PMU_BASEADDR+0x48)    //GPIOA�����ƽ
#define PMU_GPIOB_OE 	       *(volatile unsigned int *)(PMU_BASEADDR+0x50)    //GPIOB���ʹ��
#define PMU_GPIOB_O		       *(volatile unsigned int *)(PMU_BASEADDR+0x54)    //GPIOB�����ƽ
#define PMU_GPIOB_I		       *(volatile unsigned int *)(PMU_BASEADDR+0x58)    //GPIOB�����ƽ
#define PMU_Pulse0 		       *(volatile unsigned int *)(PMU_BASEADDR+0x60)    //�����������0
#define PMU_Pulse1 		       *(volatile unsigned int *)(PMU_BASEADDR+0x64)    //�����������1
#define PMU_UserDAT 	       *(volatile unsigned int *)(PMU_BASEADDR+0x68)    //�û�����
#define PMU_AdcCtrl 	       *(volatile unsigned int *)(PMU_BASEADDR+0x6c)    //ADC����
#define PMU_AdcDat  	       *(volatile unsigned int *)(PMU_BASEADDR+0x70)    //ADC����
#define PMU_GPIOBit(i) 	       *(volatile unsigned char *)(PMU_BASEADDR+0x80+i)   //GPIOλ����

#define PMU_CommandW           *(volatile unsigned int *) (PMU_BASEADDR+0x3c)   //Commandд�˿�

/***************************INTERRUPT REGS******************************/
#define INT_EN	               *(volatile unsigned char *)(REGS_BASEADDR+0x00)     //�ж�ʹ�ܼĴ���
#define INT_EGDE               *(volatile unsigned char *)(REGS_BASEADDR+0x01)     //�жϱ��ؼĴ���
#define INT_POL                *(volatile unsigned char *)(REGS_BASEADDR+0x02)     //�жϼ��ԼĴ���
#define INT_CLR                *(volatile unsigned char *)(REGS_BASEADDR+0x03)     //�ж�����Ĵ���
#define INT_SET                *(volatile unsigned char *)(REGS_BASEADDR+0x04)     //�ж���λ�Ĵ���
#define INT_OUT                *(volatile unsigned char *)(REGS_BASEADDR+0x05)     //�ж�����Ĵ���
#define INT_SRPROT             *(volatile unsigned char *)(REGS_BASEADDR+0x06)     //����״̬�������Ĵ�

/*******************************TIMER REGS*********************************/
#define TIMER_CFG  	 	       *(volatile unsigned int *)(TIMER_BASEADDR+0x00)   //���üĴ���
#define TIMER_CNT		       *(volatile unsigned int *)(TIMER_BASEADDR+0x04)   //����ֵ�Ĵ���
#define TIMER_CMP		       *(volatile unsigned int *)(TIMER_BASEADDR+0x08)   //�Ƚ�ֵ�Ĵ���
#define TIMER_STP              *(volatile unsigned int *)(TIMER_BASEADDR+0x0C)   //����ֵ�Ĵ���

/*******************************I2C REGS********************************/
#define IIC_PRERL	           *(volatile unsigned char *)(I2C_BASEADDR+0x00)     //��Ƶֵ���ֽڼĴ���
#define IIC_PRERH 	           *(volatile unsigned char *)(I2C_BASEADDR+0x01)     //��Ƶֵ���ֽڼĴ���
#define IIC_CTR   	           *(volatile unsigned char *)(I2C_BASEADDR+0x02)     //���ƼĴ���
#define IIC_DR   	           *(volatile unsigned char *)(I2C_BASEADDR+0x03)     //���ݼĴ���
#define IIC_CR		           *(volatile unsigned char *)(I2C_BASEADDR+0x04)     //����Ĵ���
#define IIC_SR		           *(volatile unsigned char *)(I2C_BASEADDR+0x04)     //״̬�Ĵ���
#define IIC_BLTOP		       *(volatile unsigned char *)(I2C_BASEADDR+0x05)     //��������ʱ��Ĵ���
#define IIC_SADDR	           *(volatile unsigned char *)(I2C_BASEADDR+0x07)     //��ģʽ��ַ�Ĵ���

/*******************************SPI REGS********************************/
#define SPI_SPCR		       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x00) //���ƼĴ���
#define SPI_SPSR		       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x01) //״̬�Ĵ���
#define SPI_TxFIFO		       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x02) //���ݼĴ���
#define SPI_RxFIFO		       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x02) //���ݼĴ���
#define SPI_SPER		       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x03) //�ⲿ�Ĵ���
#define SPI_SFC_PARAM	       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x04) //�������ƼĴ���
#define SPI_SFC_SOFTCS	       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x05) //Ƭѡ���ƼĴ���
#define SPI_SFC_TIMING	       *(volatile unsigned char *)(SPI_REG_BASEADDR+0x06) //ʱ����ƼĴ���

/*****************************UART0 REGS********************************/
#define Uart0_TxData           *(volatile unsigned char *)(UART0_BASEADDR+0x00)   //�������ݼĴ���
#define Uart0_RxData           *(volatile unsigned char *)(UART0_BASEADDR+0x00)   //�������ݼĴ���
#define Uart0_IER              *(volatile unsigned char *)(UART0_BASEADDR+0x01)   //�ж�ʹ�ܼĴ���
#define Uart0_IIR   	       *(volatile unsigned char *)(UART0_BASEADDR+0x02)   //�ж�״̬�Ĵ�
#define Uart0_FCR   	       *(volatile unsigned char *)(UART0_BASEADDR+0x02)	//FIFO���ƼĴ���
#define Uart0_LCR   	       *(volatile unsigned char *)(UART0_BASEADDR+0x03)   //��·���ƼĴ���
#define Uart0_SAMPLE_CTRL      *(volatile unsigned char *)(UART0_BASEADDR+0x04)   //bit���ڻ��ֺͲ������ƼĴ���
#define Uart0_LSR  	           *(volatile unsigned char *)(UART0_BASEADDR+0x05)   //��·״̬�Ĵ���
#define Uart0_TF_CNT   	       *(volatile unsigned char *)(UART0_BASEADDR+0x06)   //���Ͷ������ݴ���
#define Uart0_STATUS   	       *(volatile unsigned char *)(UART0_BASEADDR+0x07)   //״̬�Ĵ���

#define Uart0_DL_L   	       *(volatile unsigned char *)(UART0_BASEADDR+0x00)   //��Ƶֵ���ֽڼĴ���
#define Uart0_DL_H   	       *(volatile unsigned char *)(UART0_BASEADDR+0x01)   //��Ƶֵ���ֽڼĴ���
#define Uart0_DL_D   	       *(volatile unsigned char *)(UART0_BASEADDR+0x02)   //��ƵֵС���Ĵ���

/*****************************UART1 REGS********************************/
#define Uart1_TxData           *(volatile unsigned char *)(UART1_BASEADDR+0x00)   //�������ݼĴ���
#define Uart1_RxData           *(volatile unsigned char *)(UART1_BASEADDR+0x00)   //�������ݼĴ���
#define Uart1_IER              *(volatile unsigned char *)(UART1_BASEADDR+0x01)   //�ж�ʹ�ܼĴ���
#define Uart1_IIR   	       *(volatile unsigned char *)(UART1_BASEADDR+0x02)   //�ж�״̬�Ĵ�
#define Uart1_FCR   	       *(volatile unsigned char *)(UART1_BASEADDR+0x02)	  //FIFO���ƼĴ���
#define Uart1_LCR   	       *(volatile unsigned char *)(UART1_BASEADDR+0x03)   //��·���ƼĴ���
#define Uart1_SAMPLE_CTRL      *(volatile unsigned char *)(UART1_BASEADDR+0x04)   //bit���ڻ��ֺͲ������ƼĴ���
#define Uart1_LSR  	           *(volatile unsigned char *)(UART1_BASEADDR+0x05)   //��·״̬�Ĵ���
#define Uart1_TF_CNT   	       *(volatile unsigned char *)(UART1_BASEADDR+0x06)   //���Ͷ������ݴ���
#define Uart1_STATUS   	       *(volatile unsigned char *)(UART1_BASEADDR+0x07)   //״̬�Ĵ���

#define Uart1_DL_L   	       *(volatile unsigned char *)(UART1_BASEADDR+0x00)   //��Ƶֵ���ֽڼĴ���
#define Uart1_DL_H   	       *(volatile unsigned char *)(UART1_BASEADDR+0x01)   //��Ƶֵ���ֽڼĴ���
#define Uart1_DL_D   	       *(volatile unsigned char *)(UART1_BASEADDR+0x02)   //��ƵֵС���Ĵ���

/*****************************UART2 REGS********************************/
#define Uart2_TxData           *(volatile unsigned char *)(UART2_BASEADDR+0x00)   //�������ݼĴ���
#define Uart2_RxData           *(volatile unsigned char *)(UART2_BASEADDR+0x00)   //�������ݼĴ���
#define Uart2_IER              *(volatile unsigned char *)(UART2_BASEADDR+0x01)   //�ж�ʹ�ܼĴ���
#define Uart2_IIR   	       *(volatile unsigned char *)(UART2_BASEADDR+0x02)   //�ж�״̬�Ĵ�
#define Uart2_FCR   	       *(volatile unsigned char *)(UART2_BASEADDR+0x02)	//FIFO���ƼĴ���
#define Uart2_LCR   	       *(volatile unsigned char *)(UART2_BASEADDR+0x03)   //��·���ƼĴ���
#define Uart2_SAMPLE_CTRL      *(volatile unsigned char *)(UART2_BASEADDR+0x04)   //bit���ڻ��ֺͲ������ƼĴ���
#define Uart2_LSR  	           *(volatile unsigned char *)(UART2_BASEADDR+0x05)   //��·״̬�Ĵ���
#define Uart2_TF_CNT   	       *(volatile unsigned char *)(UART2_BASEADDR+0x06)   //���Ͷ������ݴ���
#define Uart2_STATUS   	       *(volatile unsigned char *)(UART2_BASEADDR+0x07)   //״̬�Ĵ���

#define Uart2_DL_L       	   *(volatile unsigned char *)(UART2_BASEADDR+0x00)   //��Ƶֵ���ֽڼĴ���
#define Uart2_DL_H      	   *(volatile unsigned char *)(UART2_BASEADDR+0x01)   //��Ƶֵ���ֽڼĴ���
#define Uart2_DL_D      	   *(volatile unsigned char *)(UART2_BASEADDR+0x02)   //��ƵֵС���Ĵ���

/*****************************RTC REGS**********************************/
#define RTC_FREQ   	           *(volatile unsigned int *)(RTC_BASEADDR+0x00)    //��Ƶֵ�Ĵ���
#define RTC_CFG   	           *(volatile unsigned int *)(RTC_BASEADDR+0x04)    //���üĴ���
#define RTC_RTC0   	           *(volatile unsigned int *)(RTC_BASEADDR+0x08)    //ʱ��ֵ�Ĵ���0
#define RTC_RTC1   	           *(volatile unsigned int *)(RTC_BASEADDR+0x0c)    //ʱ��ֵ�Ĵ���1

/*****************************DMA REGS**********************************/
#define DMA_SOURCE             *(volatile unsigned int *)(DMA_BASEADDR+0x00)    //DMA����Դ��ַд�˿�
#define DMA_COUNT              *(volatile unsigned int *)(DMA_BASEADDR+0x04)    //DMA�������ݳ��ȶ�д�˿�
#define DMA_CMD_STATUS         *(volatile unsigned int *)(DMA_BASEADDR+0x08)    //�����״̬�Ĵ���
#define DMA_INT_STATUS         *(volatile unsigned int *)(DMA_BASEADDR+0x0c)    //�жϺ�״̬�Ĵ���
#define DMA_SOURCE0   	       *(volatile unsigned int *)(DMA_BASEADDR+0x10)    //���������0��Դ��ַ����
#define DMA_SOURCE1  	       *(volatile unsigned int *)(DMA_BASEADDR+0x14)    //���������1��Դ��ַ����
#define DMA_COUNT0 	           *(volatile unsigned int *)(DMA_BASEADDR+0x18)    //���������0��DMA���Ȳ���
#define DMA_COUNT1 	           *(volatile unsigned int *)(DMA_BASEADDR+0x1c)    //���������1��DMA���Ȳ���

/*****************************VPWM REGS**********************************/
#define VPWM_CFG   	           *(volatile unsigned int *)(VPWM_BASEADDR+0x00)   //�㷨����
#define VPWM_WPORT_STATUS      *(volatile unsigned int *)(VPWM_BASEADDR+0x08)   //����д�˿�״̬
#define VPWM_WPORT 	           *(volatile unsigned int *)(VPWM_BASEADDR+0x0c)   //����д�˿�

/*****************************TSENSOR REGS**********************************/
#define TS_CTRL                *(volatile unsigned int *)(TSENSOR_BASEADDR+0x00) //���ƼĴ���
#define TS_STAT          	   *(volatile unsigned int *)(TSENSOR_BASEADDR+0x04) //״̬�Ĵ���
#define TS_OSCCFG         	   *(volatile unsigned int *)(TSENSOR_BASEADDR+0x08) //�������üĴ���
#define TS_POLLTIM             *(volatile unsigned int *)(TSENSOR_BASEADDR+0x0c) //ɨ��ʱ��Ĵ���
#define TS_DIFFTHRES           *(volatile unsigned int *)(TSENSOR_BASEADDR+0x10) //���췧ֵ�Ĵ���
#define TS_CNTMAX   	       *(volatile unsigned int *)(TSENSOR_BASEADDR+0x14) //������ֵ
#define TS_CNTMIN 	           *(volatile unsigned int *)(TSENSOR_BASEADDR+0x18) //��С����ֵ
#define TS_CNTLOW 	           *(volatile unsigned int *)(TSENSOR_BASEADDR+0x1c) //�ڶ�С����ֵ
#define TS_CNTADJ(a)           *(volatile unsigned int *)(TSENSOR_BASEADDR+0x40+a*4) //��������ֵ
#define TS_CNTRES(a)           *(volatile unsigned int *)(TSENSOR_BASEADDR+0x80+a*4) //�������

/*****************************FLASH REGS********************************/
#define FLASH_CMD_REG	       *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x00)   //����Ĵ���
#define FLASH_CAH_REG		   *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x04)   //���ܵ�ַ�Ͻ�Ĵ���
#define FLASH_CAL_REG		   *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x08)   //���ܵ�ַ�½�Ĵ���
#define FLASH_VRF_REG		   *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x10)   //����Ч��Ĵ���
#define FLASH_STS_REG		   *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x14)   //״̬�Ĵ���
#define FLASH_PET_REG		   *(volatile unsigned int *)(FLASH_REG_BASEADDR+0x18)   //��дʱ��Ĵ���

/*****************************GPIO Functional selection************************/
#define GPIO_FUN               0x0
#define GPIO_MAIN              0x1
#define GPIO_FIRST             0x2
#define GPIO_SECOND            0x3

/******************************************************************************
 * bit mark
 */
#define bit(x)                  (1ul << x)

#define WDT_SET(time)     	   { PMU_WdtCfg = (((~time)<<16) | time);\
							     PMU_WdtFeed = 0xa55a55aa; }

#define WDT_FEED 	     	   { PMU_WdtFeed = 0xa55a55aa; }

////////////////////////////  PMU_ChipCtrl  /////////////////////////////////
typedef struct
{
	INT32U	c32k_trim	:4;
	INT32U	c32k_speed 	:1;
	INT32U	c32k_sel	:1;
	INT32U	osc8m_en	:1;
	INT32U	c8m_sel 	:1;
	INT32U	clkup_dly	:2;
	INT32U	input_hold	:1;
	INT32U	fast_ram	:1;
	INT32U	tsensor_off	:1;
	INT32U	rtc_off		:1;
	INT32U	uart2_off	:1;
	INT32U	dram_pd		:1;
	INT32U	adc_on		:1;
	INT32U	adci0_ien	:1;
	INT32U	adci_pd		:1;
	INT32U	adci_pu		:1;
	INT32U	adc_en	    :4;
	INT32U	batdet_sel	:2;
	INT32U	spi_start	:1;
	INT32U	compact_mem	:1;
	INT32U	soft_flag   :4;
}PMU_ChipCtrlStruct;

#define spPMU_ChipCtrl         ((volatile PMU_ChipCtrlStruct *)(PMU_BASEADDR))

#define WriteKeyReg(LeftData,ReghtData)\
{\
	unsigned char GlobalIntFlag = IsGlobalIntOpen();\
 	DisableInt();\
	LeftData     = ReghtData;\
	if(GlobalIntFlag){\
		EnableInt();\
	}\
}

/*
 *  �Ĵ��� Read/Write ����
 */
/*
 * 8 Bits
 */
#define READ_REG8(Addr)			(*(volatile unsigned char*)(Addr))
#define WRITE_REG8(Addr, Val)	(*(volatile unsigned char*)(Addr) = (Val))
#define OR_REG8(Addr, Val)		(*(volatile unsigned char*)(Addr) |= (Val))
#define AND_REG8(Addr, Val)	    (*(volatile unsigned char*)(Addr) &= (Val))

/*
 * 16 Bits
 */
#define READ_REG16(Addr) 		(*(volatile unsigned short*)(Addr))
#define WRITE_REG16(Addr, Val)	(*(volatile unsigned short*)(Addr) = (Val))
#define OR_REG16(Addr, Val)	    (*(volatile unsigned short*)(Addr) |= (Val))
#define AND_REG16(Addr, Val)	(*(volatile unsigned short*)(Addr) &= (Val))

/*
 * 32 Bits
 */
#define READ_REG32(Addr) 		(*(volatile unsigned int*)(Addr))
#define WRITE_REG32(Addr, Val)	(*(volatile unsigned int*)(Addr) = (Val))
#define OR_REG32(Addr, Val)	    (*(volatile unsigned int*)(Addr) |= (Val))
#define AND_REG32(Addr, Val)	(*(volatile unsigned int*)(Addr) &= (Val))

/******************************************************************************
 * use for delay slot
 */
void static inline ls1x_sync(void)
{
    __asm__ volatile ("sync");
}

#define LS1X_SYNC   do { __asm__ volatile ("sync"); } while (0)

/**********************************************************************************************
 * ��ַ�ռ�ֲ�
 **********************************************************************************************/

#define LS1C101_IRAM_ADDR          0xA0000000      // - ֻ������ȡָ
#define LS1C101_IRAM_SIZE          0x1000          // - IRAM ��С = 4K

#define LS1C101_DRAM_ADDR          0xA0001000      // - ֻ������ȡָ
#define LS1C101_DRAM_SIZE          0x1000          // - IRAM ��С = 4K

#define LS1C101_SPIFLASH_ADDR      0xBE000000      // SPI Flash ����ַ
#define LS1C101_FLASH_ADDR         0xBF000000      // On-chip Flash ����ַ

#define LS1C101_BOOT_ADDR          0xBFC00000      // Boot from SPI Flash or On-chip Flash

#define LS1C101_FLASH_BASE         0xBFE60000      // Flash ���ƼĴ�������ַ
#define LS1C101_SPI_BASE           0xBFE70000      // SPI ���ƼĴ�������ַ
#define LS1C101_UART0_BASE         0xBFE80000      // UART0 ����ַ
#define LS1C101_UART1_BASE         0xBFE88000      // UART1 ����ַ
#define LS1C101_UART2_BASE         0xBFE8C000      // UART2 ����ַ
#define LS1C101_I2C_BASE           0xBFE90000      // I2C ����ַ

#define LS1C101_INTC_BASE          0xBFEA0000      // �жϿ��ƼĴ�������ַ
#define LS1C101_PMU_BASE           0xBFEB0000      // ��Դ����Ԫ�Ĵ�������ַ
#define LS1C101_TSENSOR_BASE       0xBFEB4000      // �����������Ĵ�������ַ
#define LS1C101_RTC_BASE           0xBFEB8000      // ʵʱʱ�ӼĴ�������ַ
#define LS1C101_DMA_BASE           0xBFEC0000      // DMA �Ĵ�������ַ
#define LS1C101_VPWM_BASE          0xBFEC0020      // VPWM �Ĵ�������ַ
#define LS1C101_TIMER_BASE         0xBFED0000      // ��ʱ���Ĵ�������ַ

/**********************************************************************************************
 * ��Դ����Ԫ
 **********************************************************************************************/

typedef struct ls1c101_PMU
{
    volatile unsigned int ChipCtrl;             // 0x00 ȫ������
    volatile unsigned int CmdSts;               // 0x04 ������״̬
    volatile unsigned int Count;                // 0x08 ʱ�������
    volatile unsigned int Compare;              // 0x0c ����ʱ������
    volatile unsigned int IOSEL0;               // 0x10 IO����ѡ�� 0
    volatile unsigned int IOSEL1;               // 0x14 IO����ѡ�� 1
    volatile unsigned int IOSEL2;               // 0x18 IO����ѡ�� 2
    volatile unsigned int IOSEL3;               // 0x1c IO����ѡ�� 3
    volatile unsigned int ExIntEn;              // 0x20 �ⲿ�ж�ʹ��
    volatile unsigned int ExIntPol;             // 0x24 �ⲿ�жϼ���
    volatile unsigned int ExIntEdge;            // 0x28 �ⲿ�жϱ���
    volatile unsigned int ExIntSrc;             // 0x2c �ⲿ�ж�״̬
    volatile unsigned int WdtCfg;               // 0x30 ���Ź�����
    volatile unsigned int WdtFeed;              // 0x34 ι��
    volatile unsigned int PowerCfg;             // 0x38 ��Դ����
    volatile unsigned int CommandW;             // 0x3C XXX datasheet��û����������Ĵ���, == CmdSts?
    volatile unsigned int GPIOA_OE;             // 0x40 GPIOA ���ʹ��
    volatile unsigned int GPIOA_O;              // 0x44 GPIOA ���
    volatile unsigned int GPIOA_I;              // 0x48 GPIOA ����
    volatile unsigned int rsv1;                 // 0x4C
    volatile unsigned int GPIOB_OE;             // 0x50 GPIOB ���ʹ��
    volatile unsigned int GPIOB_O;              // 0x54 GPIOB ���
    volatile unsigned int GPIOB_I;              // 0x58 GPIOB ����
    volatile unsigned int rsv2;                 // 0x5C
    volatile unsigned int Pulse0;               // 0x60 ����������� 0
    volatile unsigned int Pulse1;               // 0x64 ����������� 1
    volatile unsigned int UserDat;              // 0x68 �û�����
    volatile unsigned int AdcCtrl;              // 0x6c ADC ����
    volatile unsigned int AdcDat;               // 0x70 ADC ����
    volatile unsigned int rsv3[3];              // 0x74/0x78/0x7C
    volatile unsigned char GPIOBit[0x40];       // 0x80~0xbf GPIO λ����
} HW_PMU_t;

extern HW_PMU_t *g_pmu;

/*
 * ChipCtrl оƬȫ������
 */
#define CHIPCTRL_SOFTFLAG_MASK          (0xF<<28)           /* ��д�����־λ */
#define CHIPCTRL_SOFTFLAG_SHIFT         28
#define CHIPCTRL_SPI_START              bit(26)             /* SPI ��������ѡ��: 1=8us; 0=256us */
#define CHIPCTRL_BATDET_SEL_MASK        (0x3<<24)           /* �����źż��ѡ�� */
#define CHIPCTRL_BATDET_SEL_SHIFT       24
#define CHIPCTRL_BATDET_SEL_ADCI0       (0<<24)
#define CHIPCTRL_BATDET_SEL_ADCI1       (1<<24)
#define CHIPCTRL_BATDET_SEL_GPIO00      (2<<24)
#define CHIPCTRL_BATDET_SEL_GPIO01      (3<<24)
#define CHIPCTRL_ADCI7_EN               bit(23)             /* ADC_I[7] ģ������ʹ�� */
#define CHIPCTRL_ADCI6_EN               bit(22)             /* =0: ��������, �ɸ���ΪGPIO */
#define CHIPCTRL_ADCI5_EN               bit(21)             /* =1: ģ������ */
#define CHIPCTRL_ADCI4_EN               bit(20)
#define CHIPCTRL_ADCI0_PU               bit(19)             /* ADC_I[0] 400K����, 0=�ر�, 1=�� */
#define CHIPCTRL_ADCI0_PD               bit(18)             /* ADC_I[0] 400K����, 0=�ر�, 1=�� */
#define CHIPCTRL_ADCI0_IEN              bit(17)             /* ADC_I[0] ��������ʹ��, 0=�ر�,������ģ���ź�, 1=��,�����������ź� */
#define CHIPCTRL_ADC_POWER              bit(16)             /* ADC ��Դ, 0=�Զ���, 1=���� */
#define CHIPCTRL_DRAM_POWER             bit(15)             /* DRAM ��Դ, 0=����,����ʱ��������Ҫ����, 1=��CPUͬʱ���µ� */
#define CHIPCTRL_UART2_OFF              bit(14)             /* 1=�ض� */
#define CHIPCTRL_RTC_OFF                bit(13)             /* 1=�ض� */
#define CHIPCTRL_TSENSOR_OFF            bit(12)             /* 1=�ض� */
#define CHIPCTRL_FAST_RAM               bit(11)             /* 1=RAM ���ʼ��� */
#define CHIPCTRL_INPUT_HOLD             bit(10)             /* ���뱣��: GPIO */
#define CHIPCTRL_CLKUP_DELAY_MASK       (0x3<<8)            /* ���پ�����������ʹ�õ��ӳ� */
#define CHIPCTRL_CLKUP_DELAY_SHIFT      8
#define CHIPCTRL_CLKUP_DELAY_5140       (0<<8)
#define CHIPCTRL_CLKUP_DELAY_480        (1<<8)
#define CHIPCTRL_CLKUP_DELAY_1460       (2<<8)
#define CHIPCTRL_CLKUP_DELAY_2440       (3<<8)
#define CHIPCTRL_8M_SEL                 bit(7)              /* 8M ʱ��ѡ��, 0=�ڲ�, 1=�ⲿ */
#define CHIPCTRL_8M_EN                  bit(6)              /* ���پ�������ʹ�� */
#define CHIPCTRL_32K_SEL                bit(5)              /* 32K ʱ��ѡ��, 0=�ڲ�, 1=�ⲿ */
#define CHIPCTRL_32K_SPEED              bit(4)              /* �ڲ� 32K OSC �ٶ�, 1: 1K, 0: 32K */
#define CHIPCTRL_32K_TRIM_MASK          0xF                 /* �ڲ�32K OSC Trimming ֵ */

/*
 * CmdSts ������״̬
 */
#define CMDSR_8M_FAIL                   bit(31)             /* RO 8M �ⲿʱ��ʧЧ, 1=ʧЧ */
#define CMDSR_8M_SEL                    bit(30)             /* RO 8M ʱ��ѡ��, 1=�ⲿʱ�� */
#define CMDSR_32K_FAIL                  bit(29)             /* RO 32K �ⲿʱ��ʧЧ, 1=ʧЧ */
#define CMDSR_32K_SEL                   bit(28)             /* RO 32K ʱ��ѡ��, 1=�ⲿʱ�� */
#define CMDSR_RSTSRC_MASK               (0x3<<26)           /* RO ��λ��Դ */
#define CMDSR_RSTSRC_SHIFT              26
#define CMDSR_RSTSRC_OUT                0                   /* �ⲿ��λ */
#define CMDSR_RSTSRC_DOG0               1                   /* ���Ź���λ */
#define CMDSR_RSTSRC_DOG1               2                   /* ���Ź���λ */
#define CMDSR_RSTSRC_WAKE               3                   /* ���߻��� */
#define CMDSR_EXINTEN                   bit(25)             /* �ⲿ�ж�ʹ��, 1=��Ч */
#define CMDSR_INTSRC_MASK               (0x1FF<<16)         /* bit[24:16] RO �ж�״̬ */
#define CMDSR_INTSRC_SHIFT              16                  /* XXX �����жϺ��Ӧλ=1, ��CommandW�Ĵ�����Ӧλд1����ж� */
#define CMDSR_INTSRC_EXTINT             bit(24)
#define CMDSR_INTSRC_ADC                bit(23)
#define CMDSR_INTSRC_RTC                bit(22)
#define CMDSR_INTSRC_8MFAIL             bit(21)
#define CMDSR_INTSRC_32KFAIL            bit(20)
#define CMDSR_INTSRC_BATFAIL            bit(19)
#define CMDSR_INTSRC_UART2              bit(18)
#define CMDSR_INTSRC_TOUCH              bit(17)
#define CMDSR_INTSRC_WAKE               bit(16)
#define CMDSR_INTEN_MASK                (0xFF<<8)           /* bit[15:8] �ж�ʹ��, ÿһλ��Ӧһ���ж�Դ*/
#define CMDSR_INTEN_SHIFT               8
#define CMDSR_INTEN_ADC                 bit(15)
#define CMDSR_INTEN_RTC                 bit(14)
#define CMDSR_INTEN_8MFAIL              bit(13)
#define CMDSR_INTEN_32KFAIL             bit(12)
#define CMDSR_INTEN_BATFAIL             bit(11)
#define CMDSR_INTEN_UART2               bit(10)
#define CMDSR_INTEN_TOUCH               bit(9)
#define CMDSR_INTEN_WAKE                bit(8)
#define CMDSR_WAKE_EN                   bit(7)              /* ��ʱ����ʹ��, 0=�ر�, 1=�� */
#define CMDSR_SLEEP_EN                  bit(0)              /* RO ��������״̬. ����ֵΪ1��ʾ������, ��CommandW[0]д1��رմ�����ϵͳ */

/*
 * Count ʱ�������
 */
#define COUNT_MASK                      0x000FFFFF          /* bit[19:0] ÿ1/256�� +1 */

/*
 * Compare ����ʱ������
 */
#define COMPARE_MASK                    0x000FFFFF          /* bit[19:0] ����ֵ�� Count ����� WakeEn Ϊ 1ʱ���������¼� */

/*
 * IOSEL0~3 GPIO ����ѡ��.
 * ��128λ, �ɵ͵���ÿ 2 λ����һ�� GPIO �ĸ�λ״̬, ��λ�ڼ�������������ΪGPIO ����.
 */
#define IOSEL_GPIO                      0
#define IOSEL_MAIN                      1
#define IOSEL_MUX1                      2
#define IOSEL_MUX2                      3

/*
 * ExIntEn �ⲿ�ж�ʹ��
 *
 * bit[0:7]   ��ӦGPIO0~GPIO7
 * bit[8:15]  ��ӦGPIO16~GPIO23
 * bit[16:23] ��ӦGPIO32~GPIO39
 * bit[24:31] ��ӦGPIO48~GPIO55
 */

/*
 * ExIntPol �ⲿ�жϼ���
 *
 * ��Ӧ��ϵͬ��, 0=�ߵ�ƽ/��������Ч
 */

/*
 * ExIntEdge �ⲿ�жϱ���
 *
 * ��Ӧ��ϵͬ��, 0=��ƽģʽ, 1=����ģʽ
 */

/*
 * ExIntSrc �ⲿ�ж�״̬
 *
 * ��Ӧ��ϵͬ��, д1���?
 */

/*
 * WdtCfg ���Ź�����
 */
#define WDTCFG_HI_MASK                  0xFFFF0000          /* bit[31:16], ��ֵ���ڵ�16λȡ�� */
#define WDTCFG_HI_SHIFT                 16
#define WDTCFG_LO_MASK                  0x0000FFFF          /* bit[15:0], ���Ź���λ�ȴ�ʱ��, ����Ϊ��λ. ���λΪ��У��λ */

/*
 * WdtFeed ι��
 */
#define WDTFEED_FOOD                    0xA55A55AA          /* ι��ֵ */

/*
 * PowerCfg ��Դ����
 *
 * XXX �������޸�
 */

/*
 * GPIOA_OE/GPIOB_OE ���ʹ��
 *
 * 0=����; 1=���
 */

/*
 * GPIOA_O/GPIOB_O ���
 *
 * 0=�͵�ƽ, 1=�ߵ�ƽ. ����״̬ʱд1, ��ʾ��������Ҫ���뱣��.
 */

/*
 * GPIOA_I/GPIOB_I ����
 *
 * 0=�͵�ƽ, 1=�ߵ�ƽ
 */

/*
 * Pulse0/Pulse1 �����������
 *
 * XXX �ı�ʱ�ӻ��Ƶϵ��ʱӦ���ȹر�, �ٴ�.
 */
#define PULSE_ENABLE                    bit(17)             /* �������ʹ��. 0=�ر�, ����ΪGPIO����, 1=����,���ռ�ձ�50%���� */
#define PULSE_CLK_SEL                   bit(16)             /* ʱ��Դѡ��. 0=32K, 1=8M */
#define PULSE_MASK                      0x0000FFFF          /* �����Ƶϵ�� */

/*
 * UserDat �û�����
 *
 * XXX ��λ�������������
 */

/*
 * AdcCtrl ADC ����
 */
#define ADCCTRL_RUN                     bit(8)              /* �������β���. д1����, �������Զ����; ����ADC�ж� */
#define ADCCTRL_DIV                     bit(4)              /* ʱ�ӷ�Ƶѡ��. 0=2��Ƶ, 1=4��Ƶ */
#define ADCCTRL_SEL_MASK                0x07                /* ͨ��ѡ�� */
#define ADCCTRL_SEL_ADCI0               0
#define ADCCTRL_SEL_ADCI1               1
#define ADCCTRL_SEL_VCORE               2
#define ADCCTRL_SEL_1V                  3
#define ADCCTRL_SEL_ADCI4               4
#define ADCCTRL_SEL_ADCI5               5
#define ADCCTRL_SEL_ADCI6               6
#define ADCCTRL_SEL_ADCI7               7

/*
 * AdcDat ADC ����
 */
#define ADCDAT_MASK                     0x0FFF              /* 12λ��Чλ */

/*
 * GPIOBit[0x40] GPIO λ���ʶ˿�
 *
 * ÿ���ֽڶ�Ӧһ���˿�
 */
#define GPIOBIT_OE                      bit(1)              /* GPIO����. 0=����, 1=��� */
#define GPIOBIT_VAL                     bit(0)

/**********************************************************************************************
 * �жϹ���
 **********************************************************************************************/

typedef struct ls1c101_INTC
{
    volatile unsigned char en;                  // 0x00 �ж�ʹ�ܼĴ���. 1=�ж�ʹ��
    volatile unsigned char edge;                // 0x01 �жϱ��ؼĴ���. 1=���ش���, 0=��ƽ����
    volatile unsigned char pol;                 // 0x02 �жϼ��ԼĴ���. 1=�ߵ�ƽ/�����ش���
    volatile unsigned char clr;                 // 0x03 �ж�����Ĵ���. д1����ж�״̬
    volatile unsigned char set;                 // 0x04 �ж���λ�Ĵ���. д1���жϴ���ģʽ���ж�״̬, XXX ���ڲ���
    volatile unsigned char out;                 // 0x05 �ж�����Ĵ���. 1=�жϴ���
    volatile unsigned char srprot;              // 0x06 ����״̬�������Ĵ���
} HW_INTC_t;

/*
 * �ж϶�Ӧλ��
 */
#define INTC_DMA                bit(7)          /* DMA �ж�λ */
#define INTC_VPWM               bit(6)          /* VPWM �ж�λ */
#define INTC_SPI                bit(5)          /* SPI �ж�λ */
#define INTC_FLASH              bit(4)          /* Flash �ж�λ */
#define INTC_UART0              bit(3)          /* UART0 �ж�λ */
#define INTC_UART1              bit(2)          /* UART1 �ж�λ */
#define INTC_I2C                bit(1)          /* I2C �ж�λ */
#define INTC_TIMER              bit(0)          /* ��ʱ���ж�λ */

/*
 * SRPROT ����״̬�������Ĵ���
 */
#define SRPROT_ADDR_CHECK       bit(7)          /* ��ַ���ʹ��. 1=���е�ַ���, ���������δ����ĵ�ַʱ����NMI�ж�,
                                                 * ���˼Ĵ�������д�� 0x00, 0x5A, 0xA5 �򿪴�λдʹ��. */
#define SRPROT_EJTAG_LOCK       bit(5)          /* RO EJTAG ����, 1=EJTAG������ */
#define SRPROT_OPT_LOCK         bit(4)          /* RO OTP ����, 1=OPT���򱻽��� */
#define SRPROT_NEW_PKG          bit(3)          /* RO �·�װģʽ */
#define SRPROT_EJTAG_FUNC       bit(2)          /* RO EJTAG ����. 1=�ɸ���ΪGPIO */
#define SRPROT_INSTALL_MODE     bit(1)          /* RO ��װģʽ. 1=��װģʽ */
#define SRPROT_BOOT_SPI         bit(0)          /* RO SPI ����. 1=��ǰ��SPI���� */

/**********************************************************************************************
 * Ƭ�� Flash
 **********************************************************************************************/

#define FLASH_PAGE_COUNT        1024
#define FLASH_PAGE_SIZE         128
#define FLASH_BYTES             (1024*128)
#define FLASH_OPT_ADDR          0xBF020000

typedef struct ls1c101_FLASH
{
    volatile unsigned int cmd;                  // 0x00 ����Ĵ���
    volatile unsigned int cah;                  // 0x04 ���ܵ�ַ�Ͻ�Ĵ���
    volatile unsigned int cal;                  // 0x08 ���ܵ�ַ�½�Ĵ���
    volatile unsigned int rsv;                  // 0x0C
    volatile unsigned int vrf;                  // 0x10 ����У��Ĵ���: ��У������
    volatile unsigned int sts;                  // 0x14 ״̬�Ĵ���
    volatile unsigned int pet;                  // 0x18 ��дʱ��Ĵ���
} HW_FLASH_t;

/*
 * CMD ����Ĵ���
 */
#define FLASH_CMD_CMD_MASK      (0xF<<28)       /* RW ���� */
#define FLASH_CMD_CMD_SHIFT     28
#define FLASH_CMD_VERIFY        (1<<28)         /* 4��b0001 ����У�� */
#define FLASH_CMD_CLR_INT       (3<<28)         /* 4��b0011 ���ж� */
#define FLASH_CMD_PAGE_LATCH    (4<<28)         /* 4��b0100 ��page_latch */
#define FLASH_CMD_UPD_OPT       (9<<28)         /* 4��b1001 �������򱣻� */
#define FLASH_CMD_ERASE         (10<<28)        /* 4��b1010 ����Ŀ��ҳ */
#define FLASH_CMD_SLEEP         (12<<28)        /* 4��b1100 ��������ģʽ */
#define FLASH_CMD_WRITE         (14<<28)        /* 4��b1110 ���Ŀ��ҳ */
#define FLASH_CMD_UPD_KEY       (15<<28)        /* 4��b1111 ������Կ */

#define FLASH_CMD_PAGEADDR_MASK 0x0003FFFF      /* �������̵�Ŀ��ҳ��ַ, 128k���� */

/*
 * CAH ���ܵ�ַ�Ͻ�Ĵ���
 */
#define FLASH_CADDR_HI_MASK     0x0003FFFF      /* ���ܷ�Χ���Ͻ��ַ */

/*
 * CAL ���ܵ�ַ�½�Ĵ���
 */
#define FLASH_CADDR_LO_MASK     0x0003FFFF      /* ���ܷ�Χ���½��ַ */

/*
 * STS ״̬�Ĵ���
 */
#define FLASH_SR_NO_PERMISSION  bit(3)          /* RO ��Ȩ��, ��ʾ��һ�β�����Ȩ�� */
#define FLASH_SR_PE_END         bit(2)          /* RO ��д���� */
#define FLASH_SR_VERIFY_END     bit(1)          /* RO У����� */
#define FLASH_SR_VERIFY_OK      bit(0)          /* RO У����ȷ */

/*
 * PET ��дʱ��Ĵ���
 */
#define FLASH_PET_INTEN_NOPER   bit(17)         /* no_permission �ж�ʹ�� */
#define FLASH_PET_INTEN_PEEND   bit(16)         /* pe_end �ж�ʹ�� */

#define FLASH_PET_ETIME_MASK    (7<<3)          /* ����ʱ��. ��8Mʱ�Ӽ���, Ĭ�ϲ���ʱ��2.5ms */
#define FLASH_PET_ETIME_SHIFT   3
#define FLASH_PET_ETIME_15      (0<<3)          /* 0:1.5ms */
#define FLASH_PET_ETIME_20      (1<<3)          /* 1:2.0ms */
#define FLASH_PET_ETIME_25      (2<<3)          /* 2:2.5ms */
#define FLASH_PET_ETIME_30      (3<<3)          /* 3:3.0ms */
#define FLASH_PET_ETIME_35      (4<<3)          /* 4:3.5ms */
#define FLASH_PET_ETIME_40      (5<<3)          /* 5:4.0ms */
#define FLASH_PET_ETIME_45      (6<<3)          /* 6:4.5ms */
#define FLASH_PET_ETIME_50      (7<<3)          /* 7:5.0ms */

#define FLASH_PET_PTIME_MASK    7               /* ���ʱ��. ��8Mʱ�Ӽ���, Ĭ�ϱ��ʱ��2.5ms */
#define FLASH_PET_PTIME_SHIFT   3
#define FLASH_PET_PTIME_15      0               /* 0:1.5ms */
#define FLASH_PET_PTIME_20      1               /* 1:2.0ms */
#define FLASH_PET_PTIME_25      2               /* 2:2.5ms */
#define FLASH_PET_PTIME_30      3               /* 3:3.0ms */
#define FLASH_PET_PTIME_35      4               /* 4:3.5ms */
#define FLASH_PET_PTIME_40      5               /* 5:4.0ms */
#define FLASH_PET_PTIME_45      6               /* 6:4.5ms */
#define FLASH_PET_PTIME_50      7               /* 7:5.0ms */

/**********************************************************************************************
 * ��ʱ��
 **********************************************************************************************/

typedef struct ls1c101_TIMER
{
    volatile unsigned int cfg;                  // 0x00 ���üĴ���
    volatile unsigned int cnt;                  // 0x04 ����ֵ�Ĵ���
    volatile unsigned int cmp;                  // 0x08 �Ƚ�ֵ�Ĵ���
    volatile unsigned int step;                 // 0x0c ����ֵ�Ĵ���
} HW_TIMER_t;

/*
 * CFG ���üĴ���, �õ� 8M ʱ��
 */
#define TIMER_CFG_INT_SR        bit(8)          /* �ж�״̬/���ж�. 1=���ж�, д1���ж� */
#define TIMER_CFG_PERIODIC      bit(2)          /* 1=���ڴ��� */
#define TIMER_CFG_INT_EN        bit(1)          /* 1=�ж�ʹ�� */
#define TIMER_CFG_START         bit(0)          /* 1=����ʹ��, ��ʱ�����޸� CNT/CMP/STP ��ֵ */

/**********************************************************************************************
 * I2C ������
 **********************************************************************************************/

typedef struct ls1c101_IIC
{
    volatile unsigned char prerlo;              // 0x00 ��Ƶֵ���ֽڼĴ���
    volatile unsigned char prerhi;              // 0x01 ��Ƶֵ���ֽڼĴ���
    volatile unsigned char ctrl;                // 0x02 ���ƼĴ���
    volatile unsigned char data;                // 0x03 ���ݼĴ���
    union
	{
    	volatile unsigned char cmd;             // 0x04 ����Ĵ���
    	volatile unsigned char sr;              // 0x04 ״̬�Ĵ���
	} CMDSR;
    volatile unsigned char blt;                 // 0x05 ��������ʱ��Ĵ���
    volatile unsigned char rsv;                 // 0x06
    volatile unsigned char saddr;               // 0x07 ��ģʽ��ַ�Ĵ���
} HW_IIC_t;

/*
 * PRERH �� PRERL ��ͬ��ɷ�Ƶֵ PRER, ������� SCL Ƶ��Ϊ: clkin / (4*(PRER+1))
 */

/*
 * CTL ���ƼĴ���
 */
#define IIC_CTRL_EN             bit(7)          /* ģ�鹤��ʹ��. 1=��������ģʽ, 0=�Է�Ƶֵ�Ĵ������в��� */
#define IIC_CTRL_IEN            bit(6)          /* 1=�ж�ʹ��  */
#define IIC_CTRL_MS             bit(5)          /* ����ģʽѡ��. 0=���豸, 1=���豸 */
#define IIC_CTRL_TXRDY          bit(4)          /* "���豸"��������׼����: 1=Ҫ���͵�������д��data. �Զ����� */
#define IIC_CTRL_RXRDY          bit(3)          /* "���豸"���������Ѷ���: 1=data�������ѱ�����. �Զ����� */
#define IIC_CTRL_BUSLOCK_CHECK  bit(1)          /* 1=��������״̬���ʹ��: ʱ��buslock_top */
#define IIC_CTRL_SLAVE_ATUORST  bit(0)          /* 1=��������ʱ���豸�Զ���λ״̬��ʹ�� */

/*
 * DATA ���ݼĴ���
 *
 * д��ʱΪ����������, ����ʱΪ�յ�������
 */

/*
 * CMD ����Ĵ���
 */
#define IIC_CMD_STA             bit(7)          /* 1="���豸"����"���俪ʼ����" */
#define IIC_CMD_STO             bit(6)          /* 1="���豸"����"�����������" */
#define IIC_CMD_RD              bit(5)          /* 1="���豸"��һ�δ���Ϊ���߶����� */
#define IIC_CMD_WR              bit(4)          /* 1="���豸"��һ�δ���Ϊ����д���� */
#define IIC_CMD_ACK             bit(3)          /* ���豸Ӧ��. 1=��һ�ζ����ݷ���ʱӦ��NACK, ������������� */
#define IIC_CMD_RECOVER         bit(2)          /* ���������ָ�����. 1="���豸"������� */
#define IIC_CMD_IACK            bit(0)          /* �ж�Ӧ��. д1���ж� */

/*
 * SR ״̬�Ĵ���
 */
#define IIC_SR_RXACK            bit(7)          /* 0=�յ�Ӧ��, 1=�յ�NACK */
#define IIC_SR_BUSY             bit(6)          /* 1=����æ״̬ */
#define IIC_SR_ALOST            bit(5)          /* 1="���豸"ʧȥ���߿���Ȩ */
#define IIC_SR_SLAVE_ADDRESSED  bit(4)          /* 1="���豸"��Ѱַ�ɹ� */
#define IIC_SR_SLAVE_RW         bit(3)          /* 0="���豸"����, 1="���豸"��д */
#define IIC_SR_BUSLOCK          bit(2)          /* 1=�������� */
#define IIC_SR_TXIP             bit(1)          /* 1="���豸"���ڴ��� */
#define IIC_SR_INT_FLAG         bit(0)          /* �жϱ�־λ. 1=������1���ֽڻ�"���豸"��ʧ����Ȩ */

/*
 * SADDR ��ģʽ��ַ�Ĵ���
 */
#define IIC_SADDR_MASK          0x7F            /* ���豸��ַ */

/**********************************************************************************************
 * SPI ������
 **********************************************************************************************/

typedef struct ls1c101_SPI
{
    volatile unsigned char ctrl;                // 0x00 ���ƼĴ���
    volatile unsigned char sr;                  // 0x01 ״̬�Ĵ���
    volatile unsigned char data;                // 0x02 ���ݼĴ���
    volatile unsigned char er;                  // 0x03 �ⲿ�Ĵ���
    volatile unsigned char param;               // 0x04 �������ƼĴ���
    volatile unsigned char cs;                  // 0x05 Ƭѡ�Ĵ���
    volatile unsigned char timing;              // 0x06 ʱ����ƼĴ���
} HW_SPI_t;

/*
 * CTRL ���ƼĴ���
 */
#define SPI_CTRL_INT_EN         bit(7)          /* 1=�ж�ʹ�� */
#define SPI_CTRL_EN             bit(6)          /* 1=ϵͳ����ʹ�� */
#define SPI_CTRL_MASTER         bit(4)          /* 1=master ģʽ, 0=slave ģʽ */
#define SPI_CTRL_CPOL           bit(3)          /* ʱ�Ӽ���, ��ʾ��ʱ��ʱ CLK �ĵ�ƽ. 1=�ߵ�ƽ, 0=�͵�ƽ */
#define SPI_CTRL_CPHA           bit(2)          /* ʱ����λ, 0=��λ��ͬ, 1=��λ�෴ */
#define SPI_CTRL_SPR_MASK       0x03            /* ʱ�ӷ�Ƶλ, �� SPER һ��ʹ�� */

/*
 * SR ״̬�Ĵ���
 */
#define SPI_SR_INT_FLAG         bit(7)          /* 1=���ж�, д1���� */
#define SPI_SR_WCOL             bit(6)          /* "д�Ĵ���"�����־λ, 1=���, д1���� */
#define SPI_SR_BUSY             bit(4)          /* 1=������æ */
#define SPI_SR_WFFULL           bit(3)          /* 1="д�Ĵ���"����־ */
#define SPI_SR_WFEMPTY          bit(2)          /* 1="д�Ĵ���"�ձ�־ */
#define SPI_SR_RFFULL           bit(1)          /* 1="���Ĵ���"����־ */
#define SPI_SR_RFEMPTY          bit(0)          /* 1="���Ĵ���"�ձ�־ */

/*
 * SPER �ⲿ�Ĵ���
 *
 */
#define SPI_ER_INT_CNT_MASK     0xC0            /* ��������ֽں��ж� */
#define SPI_ER_INT_CNT_SHIFT    6
#define SPI_ER_INT_1BYTES       0
#define SPI_ER_INT_2BYTES       1
#define SPI_ER_INT_3BYTES       2
#define SPI_ER_INT_4BYTES       3
#define SPI_ER_MODE             bit(2)          /* �ӿ�ģʽ. 0:�����뷢��ʱ��ͬ��, 1:�����뷢��ʱ���������� */
#define SPI_ER_SPRE_MASK        0x07            /* ʱ�ӷ�Ƶλ. ��SPR һ���趨��Ƶ���� */
#define SPI_ER_SPRE_2           0               /* 4��b0000 */
#define SPI_ER_SPRE_4           1               /* 4��b0001 */
#define SPI_ER_SPRE_16          2               /* 4��b0010 */
#define SPI_ER_SPRE_32          3               /* 4��b0011 */
#define SPI_ER_SPRE_8           4               /* 4��b0100 */
#define SPI_ER_SPRE_64          5               /* 4��b0101 */
#define SPI_ER_SPRE_128         6               /* 4��b0110 */
#define SPI_ER_SPRE_256         7               /* 4��b0111 */
#define SPI_ER_SPRE_512         8               /* 4��b1000 */
#define SPI_ER_SPRE_1024        9               /* 4��b1001 */
#define SPI_ER_SPRE_2048        10              /* 4��b1010 */
#define SPI_ER_SPRE_4096        11              /* 4��b1011 */

/*
 * PARAM �������ƼĴ���
 */
#define SPI_PARAM_CLKDIV_MASK   0xF0            /* ʱ�ӷ�Ƶ��ѡ��: ��{spre,spr}�����ͬ */
#define SPI_PARAM_DUALIO        bit(3)          /* ˫IO ģʽ, ���ȼ�����fast_read */
#define SPI_PARAM_FASTREAD      bit(2)          /* ���ٶ�ģʽ */
#define SPI_PARAM_BURST_EN      bit(1)          /* SPI Flash ֧��������ַ��ģʽ */
#define SPI_PARAM_MEMORY_EN     bit(0)          /* SPI Flash ��ʹ��. 0=��ͨ��CS0����Flash��д */

/*
 * CS Ƭѡ���ƼĴ���
 */
#define SPI_CS_MASK             0xF0            /* Ƭѡ */
#define SPI_CS_SHIFT            4
#define SPI_CS_FLASH            0x10            /* Ƭѡ Flash */
#define SPI_CS_1                0x20
#define SPI_CS_2                0x40
#define SPI_CS_3                0x80
#define SPI_CS_EN_MASK          0x0F            /* Ƭѡʹ��, ����Ч */
#define SPI_CS_EN_FLASH         0x01            /* ʹ��Ƭѡ Flash */
#define SPI_CS_EN_1             0x02
#define SPI_CS_EN_2             0x04
#define SPI_CS_EN_3             0x08

/*
 * TIMING ʱ����ƼĴ���
 */
#define SPI_TIMING_FAST         bit(2)          /* SPI flash ������ģʽ. 0=���ز���,������SPI����; 1=���ز���,���1��SPI����*/
#define SPI_TIMING_CSH_MASK     0x07            /* SPI flash Ƭѡ�ź������Чʱ��, �Է�Ƶ���ʱ������T���� */
#define SPI_TIMING_CSH_1T       0
#define SPI_TIMING_CSH_2T       1
#define SPI_TIMING_CSH_4T       2
#define SPI_TIMING_CSH_8T       3

/**********************************************************************************************
 * UART ������
 **********************************************************************************************/
/*
 * XXX UART0/1 ʹ��8Mʱ��, UART2 ʹ�� 32K ʱ��
 */

#define NS16550_FIFO_SIZE       16              /* XXX 16 bytes? */

typedef struct ls1c101_NS16550
{
    union
	{
    	volatile unsigned char dat;             // 0x00 ���ݼĴ���
    	volatile unsigned char dll;             // 0x00 ��Ƶֵ���ֽڼĴ���
	} R0;
    union
	{
    	volatile unsigned char ier;             // 0x01 �ж�ʹ�ܼĴ���
    	volatile unsigned char dlh;             // 0x01 ��Ƶֵ���ֽڼĴ���
	} R1;
    union
	{
		volatile unsigned char isr;             // 0x02 �ж�״̬�Ĵ���
		volatile unsigned char fcr;             // 0x02 FIFO���ƼĴ���
		volatile unsigned char dld;             // 0x02 ��ƵֵС���Ĵ���
	} R2;
    volatile unsigned char lcr;                 // 0x03 ��·���ƼĴ���
    volatile unsigned char samp;                // 0x04 bit ���ڻ��ֺͲ������ƼĴ���
    volatile unsigned char lsr;                 // 0x05 ��·״̬�Ĵ���
    volatile unsigned char tfcnt;               // 0x06 ���Ͷ������ݴ���
    volatile unsigned char sr;                  // 0x07 ״̬�Ĵ���
} HW_NS16550_t;

/*
 * IER �ж�ʹ�ܼĴ���
 */
#define NS16550_IER_MEN         bit(3)          /* Modem ״̬�ж�ʹ�� */
#define NS16550_IER_LEN         bit(2)          /* ��·״̬�ж�ʹ�� */
#define NS16550_IER_TEN         bit(1)          /* ����״̬�ж�ʹ�� */
#define NS16550_IER_REN         bit(0)          /* ����״̬�ж�ʹ�� */

/*
 * ISR �ж�״̬�Ĵ���
 */
#define NS16550_ISR_SRC_MASK    0x0E            /* RO �ж�Դ */
#define NS16550_ISR_SRC_SHIFT   1
#define NS16550_ISR_LSR         0x06            /* 3��b011 ��·״̬�ж�, ���ȼ�1, ��ż/���/֡����/���ʱ�ж�, ��LSR��� */
#define NS16550_ISR_RX          0x04            /* 3��b010 ����״̬�ж�, ���ȼ�2, RX�����ﵽtrigger��ֵ, ��data��� */
#define NS16550_ISR_RXTMO       0x0C            /* 3��b110 ����״̬�ж�, ���ȼ�2, RX��ʱ, ��data��� */
#define NS16550_ISR_TX          0x02            /* 3��b001 ����״̬�ж�, ���ȼ�3, TX FIFOΪ��, дdata���isr��� */
#define NS16550_ISR_MODEM       0x00            /* 3��b000 Modem״̬�ж�, ���ȼ�4, reserved, �� Modem״̬�Ĵ������ */
#define NS16550_ISR_PENDING     bit(0)          /* �ж�δ��״̬ */

/*
 * FCR FIFO ���ƼĴ���
 */
#define NS16550_FCR_TRIG_MASK   0xF8            /* �����ж�״̬����trigger. 0/1=1�ֽ�, ���16�ֽ� */
#define NS16550_FCR_TRIG_SHIFT  3
#define NS16550_FCR_TRIGGER(n)  (n<<3)
#define NS16550_FCR_TXFIFO_RST  bit(2)          /* ��λ����FIFO */
#define NS16550_FCR_RXFIFO_RST  bit(1)          /* ��λ����FIFO */
#define NS16550_FCR_FIFO_EN     bit(0)          /* ʹ��FIFO? */

/*
 * LCR ��·���ƼĴ���
 */
#define NS16550_LCR_DLAB        bit(7)          /* ��Ƶ��ģʽ. 0=���������Ĵ���, 1=���ʷ�Ƶ�Ĵ��� */
#define NS16550_LCR_BCB         bit(6)          /* ��Ͽ���λ. 0=��������, 1=���������0(���״̬) */
#define NS16550_LCR_SPD         bit(5)          /* ָ����żУ��λ. 0:��ָ����żУ��λ, 1: eps=1��У��λΪ0, eps=0��У��λΪ1 */
#define NS16550_LCR_EPS         bit(4)          /* ��żУ��λѡ��. 0=��У��, 1=żУ�� */
#define NS16550_LCR_PE          bit(3)          /* 1=��żУ��λʹ�� */
#define NS16550_LCR_SB          bit(2)          /* ����ֹͣλλ��. 0:1��ֹͣλ, 1:bec=5ʱ1.5��ֹͣλ, ����2��ֹͣλ */
#define NS16550_LCR_BITS_MASK   0x03            /* �ַ�λ�� */
#define NS16550_LCR_BITS_5      0
#define NS16550_LCR_BITS_6      1
#define NS16550_LCR_BITS_7      2
#define NS16550_LCR_BITS_8      3

/*
 * LSR ��·״̬�Ĵ���
 */
#define NS16550_LSR_ERR         bit(7)          /* 1=�д���, У��/֡��������ж� */
#define NS16550_LSR_TE          bit(6)          /* 0=������, 1=TX FIFO�ʹ�����λ�Ĵ���Ϊ��. дTXFIFOʱ��� */
#define NS16550_LSR_TFE         bit(5)          /* 1=����FIFO Ϊ�� */
#define NS16550_LSR_BI          bit(4)          /* ����ж�. 0=û���ж� */
#define NS16550_LSR_FE          bit(3)          /* ֡���� */
#define NS16550_LSR_PE          bit(2)          /* ��żУ��λ���� */
#define NS16550_LSR_OE          bit(1)          /* ������� */
#define NS16550_LSR_DR          bit(0)          /* ����������Ч. 0=RXFIFO������, 1=RXFIFO������ */

/*
 * TF_CNT ���Ͷ����д����͵�������
 */
#define NS16550_TFCNT_LOOPBACK  bit(7)          /* �Իػ�ģʽ����λ */
#define NS16550_TFCNT_MASK      0x1F            /* ���Ͷ����д����͵������� */

/*
 * SR ״̬�Ĵ����Ĵ���
 */
#define NS16550_SR_RX_RST       bit(7)          /* ��������ͨ·��32K ʱ����ĸ�λ״̬. 1=���ڸ�λ */
#define NS16550_SR_CLK32K_RST   bit(6)          /* �����߼�32K ʱ����ĸ�λ״̬. 1=���ڸ�λ */
#define NS16550_SR_FLUSH_WAIT   bit(5)          /* ��������ͨ·�����ݶ����ȴ���ʶ. 1=���ڶ��� */
#define NS16550_SR_RFCNT_MASK   0x1F            /* ���ն����е������� */

/**********************************************************************************************
 * ʵʱʱ��
 **********************************************************************************************/

typedef struct ls1c101_RTC
{
	volatile unsigned int freq;                 // 0x00 ��Ƶֵ�Ĵ���
	volatile unsigned int cfg;                  // 0x04 ���üĴ���
	volatile unsigned int rtc0;                 // 0x08  ʱ��ֵ�Ĵ���0
	volatile unsigned int rtc1;                 // 0x0C ʱ��ֵ�Ĵ���1
} HW_RTC_t;

/*
 * FREQ ��Ƶֵ�Ĵ���, freqscale = freq_in/16
 */
#define RTC_FREQ_I_MASK         0x0FFF0000      /* bit[27:16], ��Ƶϵ���������� */
#define RTC_FREQ_I_SHIFT        16
#define RTC_FREQ_F_MASK         0x0000FFC0      /* bit[15:6], ��Ƶϵ��С������ */
#define RTC_FREQ_F_SHIFT        6

/*
 * CFG ���üĴ���
 */
#define RTC_CFG_STATE           bit(31)         /* ��������״̬. 1=��д����ִ����, д1����, ����Ӳ������ */
#define RTC_CFG_TIMER_EN        bit(30)         /* ��ʱ��ʹ��. 1=ʹ��, ʱ�䵽���Զ����� */
#define RTC_CFG_MONTH_MASK      0x3C000000      /* bit[29:26] �� */
#define RTC_CFG_MONTH_SHIFT     26
#define RTC_CFG_DAY_MASK        0x03E00000      /* bit[25:21] �� */
#define RTC_CFG_DAY_SHIFT       21
#define RTC_CFG_HOUR_MASK       0x001F0000      /* bit[20:16] ʱ */
#define RTC_CFG_HOUR_SHIFT      16
#define RTC_CFG_MINUTE_MASK     0x0000FC00      /* bit[15:10] �� */
#define RTC_CFG_MINUTE_SHIFT    10
#define RTC_CFG_SECOND_MASK     0x000003F0      /* bit[9:4] �� */
#define RTC_CFG_SECOND_SHIFT    4
#define RTC_CFG_SIXTEENTH_MASK  0x0000000F      /* bit[3:0] ʮ����֮һ�� */
#define RTC_CFG_SIXTEENTH_SHIFT 0

/*
 * RTC0 ʱ��ֵ�Ĵ���0
 */
#define RTC_0_BAD_TIME          bit(31)         /* ��Ч��ֵ */
#define RTC_0_HOUR_MASK         0x001F0000      /* bit[20:16] ʱ */
#define RTC_0_HOUR_SHIFT        16
#define RTC_0_MINUTE_MASK       0x0000FC00      /* bit[15:10] �� */
#define RTC_0_MINUTE_SHIFT      10
#define RTC_0_SECOND_MASK       0x000003F0      /* bit[9:4] �� */
#define RTC_0_SECOND_SHIFT      4
#define RTC_0_SIXTEENTH_MASK    0x0000000F      /* bit[3:0] ʮ����֮һ�� */
#define RTC_0_SIXTEENTH_SHIFT   0

/*
 * RTC1 ʱ��ֵ�Ĵ���1
 */
#define RTC_1_BAD_TIME         bit(31)          /* ��Ч��ֵ */
#define RTC_1_YEAR_MASK        0x0000FE00       /* bit[15:9] ��, ��2000���� */
#define RTC_1_YEAR_SHIFT       9
#define RTC_1_MONTH_MASK       0x000001E0       /* bit[8:5] �� */
#define RTC_1_MONTH_SHIFT      5
#define RTC_1_DAY_MASK         0x0000001F       /* bit[4:0] �� */
#define RTC_1_DAY_SHIFT        0

/**********************************************************************************************
 * DMA ������
 **********************************************************************************************/

typedef struct ls1c101_DMA
{
	volatile unsigned int ordsrc;               // 0x00 DMA ����Դ��ַ��д�˿�. ��̬�仯
	volatile unsigned int ordlen;               // 0x04 DMA �������ݳ��ȶ�д�˿�, ���˵�����, ��̬�仯
	volatile unsigned int cmdsr;                // 0x08 �����״̬�Ĵ���
	volatile unsigned int intsr;                // 0x0c �жϺ�״̬�Ĵ���
	volatile unsigned int src0;                 // 0x10 ��������� 0 ��Դ��ַ����
	volatile unsigned int src1;                 // 0x14 ���������1��Դ��ַ����
	volatile unsigned int cnt0;                 // 0x18 ��������� 0 ��DMA���Ȳ���
	volatile unsigned int cnt1;                 // 0x1c ��������� 1 ��DMA���Ȳ���
} HW_DMA_t;

/*
 * SMD & STATUS �����״̬�Ĵ���
 */
#define DMA_CMDSR_SOFT_RST      bit(31)         /* DMA ��������λ. д1��λ, ����Զ����� */
#define DMA_CMDSR_IND_1ST       bit(1)          /* ��ʶDMA �ĵ�һ������ */
#define DMA_CMDSR_EN            bit(0)          /* DMA ������Ч */

/*
 * INT & STATUS �жϺ�״̬�Ĵ���
 */
#define DMA_INTSR_BUF_RPTR      bit(19)         /* DMA ���ݻ���Ķ�ָ��ֵ */
#define DMA_INTSR_BUF_WPTR      bit(18)         /* DMA ���ݻ����дָ��ֵ */
#define DMA_INTSR_BUFCNT_MASK   0x00030000      /* DMA ���ݻ���洢����Ч�������� */
#define DMA_INTSR_BUFCNT_SHIFT  16
#define DMA_INTSR_CMD_RPTR      bit(13)         /* DMA ������еĶ�ָ��ֵ */
#define DMA_INTSR_CMD_WPTR      bit(12)         /* DMA ������е�дָ��ֵ */
#define DMA_INTSR_CMD1_MASK     0x00000C00      /* bit[11:10] DMA �������1 ������ֵ */
#define DMA_INTSR_CMD1_SHIFT    10
#define DMA_INTSR_CMD0_MASK     0x00000C00      /* bit[9:8] DMA �������0 ������ֵ */
#define DMA_INTSR_CMD0_SHIFT    10
#define DMA_INTSR_CMD_INVALID   0               /* ������Ч */
#define DMA_INTSR_CMD_NO_1ST    1               /* ������Ч, ִ��ʱ����Ҫ��ʾ��һ������ */
#define DMA_INTSR_CMD_IND_1ST   3               /* ������Ч, ִ��ʱ��Ҫ��ʾ��һ������ */
#define DMA_INTSR_INT_CNT_MASK  0x03            /* bit[1:0] �жϼ����� */
#define DMA_INTSR_INT_CLR       bit(0)          /* ÿд��1,int_cnt-=1, ��=0ʱ, ����ж� */

/**********************************************************************************************
 * VPWM ģ��
 **********************************************************************************************/

typedef struct ls1c101_VPWM
{
	volatile unsigned int cfg;                  // 0x00 �㷨����
	volatile unsigned int rsv;                  // 0x04
	volatile unsigned int sr;                   // 0x08 ����д�˿�״̬
	volatile unsigned int port;                 // 0x0C ����д�˿�
} HW_VPWM_t;

/*
 * VPWMCFG �㷨����
 */
#define VPWM_CFG_ALG            bit(30)         /* �㷨ѡ�� */
#define VPWM_CFG_NEG            bit(29)         /* �����ת */
#define VPWM_CFG_FREQ_SEL       bit(27)         /* ʱ��ѡ��. 0=32M, 1=8M */
#define VPWM_CFG_FREQ_RST       bit(26)         /* ʱ�Ӹ�λ. */
#define VPWM_CFG_IFACTOR_MASK   0x03000000      /* bit[25:24] ��ֵϵ�� */
#define VPWM_CFG_IFACTOR_SHIFT  24
#define VPWM_CFG_AVAILBIT_MASK  0x00F00000      /* bit[23:20] ��Чλ�� */
#define VPWM_CFG_AVAILBIT_SHIFT 20
#define VPWM_CFG_DMA_EN         bit(19)         /* DMA ʹ�� */
#define VPWM_CFG_INTERPOL_EN    bit(18)         /* ���ݲ�ֵʹ�� */
#define VPWM_CFG_ITERATE_EN     bit(17)         /* �����ظ�ʹ�� */
#define VPWM_CFG_ADPCM_EN       bit(16)         /* ѹ��ʹ�� */
#define VPWM_CFG_SUMWIDTH_MASK  0x0000FFF0      /* ÿ�����������źſ�� */
#define VPWM_CFG_SUMWIDTH_SHIFT 4

/*
 * PORT STATUS ����д�˿�״̬
 */
#define VPWM_SR_FIRST_DATA      bit(1)          /* ��һ������ */
#define VPWM_SR_READY           bit(0)          /* ������. 1=VPWM���������Ͷ����� */

/*
 * PORT ����д�˿�: ������Ϊͨ���Ĵ����ӿڻ�ȡ����ʱ, �������Ƶ����д��üĴ���
 */

/**********************************************************************************************
 * TSENSOR ��������������
 **********************************************************************************************/

typedef struct ls1c101_TSENSOR
{
	volatile unsigned int ctrl;                 // 0x00 ���ƼĴ���
	volatile unsigned int sr;                   // 0x04 ״̬�Ĵ���
	volatile unsigned int cfg;                  // 0x08 ���üĴ���
	volatile unsigned int pollTime;             // 0x0c ɨ��ʱ��Ĵ���
	volatile unsigned int diffThres;            // 0x10 ���췧ֵ�Ĵ���
	volatile unsigned int cntMax;               // 0x14 ������ֵ
	volatile unsigned int cntMin;               // 0x18 ��С����ֵ
	volatile unsigned int cntLow;               // 0x1c �ڶ�С����ֵ
	volatile unsigned int rsv[8];               // 0x20~0x3C
	volatile unsigned int cntAdj[16];           // 0x40~0x7c ��������ֵ0~15
	volatile unsigned int cntRes[16];           // 0x80~0xbc �������0~15
} HW_TSENSOR_t;

/*
 * TSCTRL ���ƼĴ���
 */
#define TS_CTRL_SCAN_MASK       0xFFFF0000      /* bit[31:16] ɨ���ӦλΪ1��ͨ��; ȫ0���������, ���浽cntRes */
#define TS_CTRL_SCAN_SHIFT      16
#define TS_CTRL_DBC_EN          bit(15)         /* ȥ��ʹ�� */
#define TS_CTRL_DBC_NUM_MASK    0x00007000      /* bit[14:12] ȥ������, ������⵽ 0~7 �ΰ����ŷ��ж� */
#define TS_CTRL_DBC_NUM_SHIFT   12
#define TS_CTRL_EOS_OV          bit(11)         /* ɨ�����ǿ����� */
#define TS_CTRL_WARMUP          0x00000700      /* bit[10:8] ��������� 0~7 �� */
#define TS_CTRL_IEN_MASM        0x000000F0      /* bit[7:4] �ж�ʹ�� */
#define TS_CTRL_IEN_SHIFT       4
#define TS_CTRL_IEN_OFLOW       bit(7)          /* ����ж�ʹ�� */
#define TS_CTRL_IEN_TRIG        bit(6)          /* �����ж�ʹ�� */
#define TS_CTRL_IEN_UP          bit(5)          /* ̧���ж�ʹ�� */
#define TS_CTRL_IEN_DOWN        bit(4)          /* �����ж�ʹ�� */
#define TS_CTRL_TEST_EN         bit(3)          /* ����ģʽ */
#define TS_CTRL_ADJ_EN          bit(2)          /* ��������ʹ�� */
#define TS_CTRL_POLL_EN         bit(1)          /* ѭ��ɨ��ʹ�� */
#define TS_CTRL_SCAN_EN         bit(0)          /* ����ɨ��ʹ�� */

/*
 * TSSTATE ״̬�Ĵ���
 */
#define TS_SR_SCAN_MASK         0x0F000000      /* bit[27:24] ɨ��״̬ */
#define TS_SR_SCAN_SHIFT        24
#define TS_SR_SCAN_IDLE         (0<<24)
#define TS_SR_SCAN_SEL          (1<<24)
#define TS_SR_SCAN_CNT          (2<<24)
#define TS_SR_SCAN_REC          (3<<24)
#define TS_SR_POLL_MAKS         0x00F00000      /* bit[19:16] ѭ��״̬ */
#define TS_SR_POLL_IDLE         (0<<16)
#define TS_SR_POLL_ONCE         (1<<16)
#define TS_SR_POLL_STBW         (2<<16)
#define TS_SR_POLL_STBR         (3<<16)
#define TS_SR_POLL_ACTW         (4<<16)
#define TS_SR_POLL_ACTR         (5<<16)
#define TS_SR_POLL_DBCW         (6<<16)
#define TS_SR_POLL_DBCR         (7<<16)
#define TS_SR_CODE_MASK         0x000000F0      /* bit[7:4] ��������0~15 */
#define TS_SR_CODE_SHIFT        4
#define TS_SR_OVERFLOW          bit(3)          /* ��� */
#define TS_SR_TRIG              bit(2)          /* ���� */
#define TS_SR_UP                bit(1)          /* ̧�� */
#define TS_SR_DOWN              bit(0)          /* ���� */

/*
 * OSC CFG �������üĴ���
 */
#define TS_CFG_CNT_NEG          bit(16)         /* ʹ��˫�ؼ��� */
#define TS_CFG_CNT_PRD_MASK     0x000001F0      /* bit[12:8] ��������, ��32Kʱ������Ϊ��λ? */
#define TS_CFG_CNT_PRD_SHIFT    8
#define TS_CFG_RSEL_MASK        0x0000000F      /* bit[3:0] ����ѡ��, 1~14=1K~14K */

/*
 * PollTim ɨ��ʱ��Ĵ���
 */
#define TS_POLL_DBC_DLY_MASK    0xFF000000      /* bit[31:24] ȥ���������, ��32Kʱ������Ϊ��λ, 0=256 */
#define TS_POLL_DBC_DLY_SHIFT   24
#define TS_POLL_STB_PRD_MASK    0x00FF0000      /* bit[23:16] ����ģʽ����, �Լ���ģʽɨ������Ϊ��λ, 0=256 */
#define TS_POLL_STB_PRD_SHIFT   16
#define TS_POLL_ACT_NUM_MASK    0x00003000      /* bit[13:12] ����ģʽɨ��ʱ��, �Դ���ģʽ����Ϊ��λ, 0=4 */
#define TS_POLL_ACT_NUM_SHIFT   12
#define TS_POLL_ACT_PRD_MASK    0x00000F00      /* bit[11:8] ����ģʽ����, ��256��32Kʱ��Ϊ��λ, 0=2^12 */
#define TS_POLL_ACT_PRD_SHIFT   8

/*
 * DiffThres ������ֵ�Ĵ���
 */
#define TS_DIFF_PRESS_H_MASK    0xFF000000      /* bit[31:24] ������ֵ */
#define TS_DIFF_PRESS_H_SHIFT   24
#define TS_DIFF_PRESS_L_MASK    0x00FF0000      /* bit[23:16] ������ֵ */
#define TS_DIFF_PRESS_L_SHIFT   16
#define TS_DIFF_PRESS_D_MASK    0x0000FF00      /* bit[15:8] ������ֵ */
#define TS_DIFF_PRESS_D_SHIFT   16
#define TS_DIFF_TOUCH_EN        bit(7)          /* �������ʹ�� */
#define TS_DIFF_TOUCH_MASK      0x0000007F      /* ������ֵ */

/*
 * CntMax ������
 * CntMin ��С����
 * CntLow �ڶ�С����
 */
#define TS_CNT_POS_MASK         0x000F0000      /* bit[19:16] λ�� */
#define TS_CNT_POS_SHIFT        16
#define TS_CNT_VAL_MASK         0x00000FFF      /* bit[11:0] ֵ */
#define TS_CNT_VAL_SHIFT        0

/*
 * CntAdj �����Ĵ���
 */
#define TS_ADJ_CTUNE_MASK       0x00FF0000      /* bit[23:16] ����΢����, 1��Ϊ5PF */
#define TS_ADJ_MASK             0x000000FF      /* bit[7:0] �������, ��ȥ��ֵ */

/*
 * cntRes �������0~15
 */
#define TS_RES_OV               bit(31)         /* ������� */
#define TS_RES_VAL_MASK         0x00000FFF      /* bit[11:0] ����ֵ, ��������ԭʼֵ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LS1C101_H_ */
