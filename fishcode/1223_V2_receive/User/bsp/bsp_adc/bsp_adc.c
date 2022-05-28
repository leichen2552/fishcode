#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUM] = {0};

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
	// ���� IO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //������������


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
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE + 0x4c;// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;// ���ݴ��䷽��Ϊ���赽�洢��	
	
	DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_NUM;// ��������СΪ��ָһ�δ����������
	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// �洢����ַ����
	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ѭ������ģʽ
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;// ��ֹDMA FIFO	��ʹ��ֱ��ģʽ	  	
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;// FIFO ��С��FIFOģʽ��ֹʱ�������������
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
		  
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
	
	// ����ADCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	
	// -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
	// ����ADCģʽ
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	// ʱ��Ϊfpclk x��Ƶ	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	// ��ֹDMAֱ�ӷ���ģʽ	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//����ڶ���ADCģʽ�²���
	// ����ʱ����	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  //��������ˣ��������ֵ�������
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	// -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
	ADC_StructInit(&ADC_InitStructure);
	// ADC �ֱ���
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	// ɨ��ģʽ����ͨ���ɼ�����Ҫ	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
	// ����ת��	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
	//��ֹ�ⲿ���ش���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//�ⲿ����ͨ����������ʹ�������������ֵ��㸳ֵ����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	//�����Ҷ���	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//ת��ͨ�� 1��
	ADC_InitStructure.ADC_NbrOfConversion = ADC_CHANNEL_NUM;                                    
	ADC_Init(ADC1, &ADC_InitStructure);
	//---------------------------------------------------------------------------
	
	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ3��ʱ������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, CONVERT_RANK_1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, CONVERT_RANK_2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, CONVERT_RANK_3, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, CONVERT_RANK_4, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, CONVERT_RANK_5, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, CONVERT_RANK_6, ADC_SampleTime_3Cycles);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, CONVERT_RANK_7, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, CONVERT_RANK_8, ADC_SampleTime_3Cycles);

	// ʹ��DMA���� after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	// ʹ��ADC
	ADC_Cmd(ADC1, ENABLE);  
	
	ADC_SoftwareStartConv(ADC1);
}

void BspInitADC(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
}

