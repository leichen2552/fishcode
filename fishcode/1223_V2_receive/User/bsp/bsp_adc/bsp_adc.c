#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUM] = {0};

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能 GPIO 时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
	// 配置 IO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //不上拉不下拉


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
								  GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE + 0x4c;// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;// 存储器地址，实际上就是一个内部SRAM的变量
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;// 数据传输方向为外设到存储器	
	
	DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_NUM;// 缓冲区大小为，指一次传输的数据量
	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// 存储器地址递增
	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// 外设数据大小为半字，即两个字节 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //	存储器数据大小也为半字，跟外设数据大小相同
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 循环传输模式
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;// 禁止DMA FIFO	，使用直连模式	  	
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;// FIFO 大小，FIFO模式禁止时，这个不用配置
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
		  
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);//初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
	
	// 开启ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	
	// -------------------ADC Common 结构体 参数 初始化------------------------
	// 独立ADC模式
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	// 时钟为fpclk x分频	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	// 禁止DMA直接访问模式	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//这个在多重ADC模式下才用
	// 采样时间间隔	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  //上面禁用了，下面这个值可以随便
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	// -------------------ADC Init 结构体 参数 初始化--------------------------
	ADC_StructInit(&ADC_InitStructure);
	// ADC 分辨率
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	// 扫描模式，多通道采集才需要	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
	// 连续转换	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
	//禁止外部边沿触发
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//外部触发通道，本例子使用软件触发，此值随便赋值即可
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	//数据右对齐	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//转换通道 1个
	ADC_InitStructure.ADC_NbrOfConversion = ADC_CHANNEL_NUM;                                    
	ADC_Init(ADC1, &ADC_InitStructure);
	//---------------------------------------------------------------------------
	
	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为3个时钟周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, CONVERT_RANK_1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, CONVERT_RANK_2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, CONVERT_RANK_3, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, CONVERT_RANK_4, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, CONVERT_RANK_5, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, CONVERT_RANK_6, ADC_SampleTime_3Cycles);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, CONVERT_RANK_7, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, CONVERT_RANK_8, ADC_SampleTime_3Cycles);

	// 使能DMA请求 after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	// 使能ADC
	ADC_Cmd(ADC1, ENABLE);  
	
	ADC_SoftwareStartConv(ADC1);
}

void BspInitADC(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
}

