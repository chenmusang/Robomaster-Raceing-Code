#include "USART.h"

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    USART1_QuickInit
  * @brief   USART1���ٳ�ʼ��
  * @param   USART_BaudRate: ������
  * @author  ���� 
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void USART1_QuickInit(uint32_t USART_BaudRate)
{
    /*ʹ�ܽṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ʹ�� GPIO ʱ�� */
    /*USART1_TX -> PB6*/
    /*USART1_RX -> PB7*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

    /* ʹ�� USART1 ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* GPIO��ʼ�� */
    /* �Ƿ����ø������
    	GPIO_OType��
     1��GPIO_OType_PP �����ø������
     2��GPIO_OType_OD	���ø������
    */

    /* �Ƿ�������
    	GPIO_PuPd
    1��GPIO_PuPd_NOPULL
    2��GPIO_PuPd_UP
    3��GPIO_PuPd_DOWN
    */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /* ����Tx����  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* ����Rx���� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*ӳ��ӿڸ���*/
    /* ���� PXx �� USARTx_Tx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

    /*  ���� PXx �� USARTx_Rx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    /* ���ô�USART ģʽ */
    /* ���������ã�USART_BAUDRATE */
    USART_InitStructure.USART_BaudRate = USART_BaudRate;

    /* ���ݳ���(����λ+У��λ)��8 */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    /* ֹͣλ��1��ֹͣλ */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;

    /* У��λѡ�񣺲�ʹ��У�� */
    USART_InitStructure.USART_Parity = USART_Parity_No;

    /* Ӳ�������ƣ���ʹ��Ӳ���� */
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    /* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* ���USART��ʼ������ */
    USART_Init(USART1, &USART_InitStructure);

    /* �����ж����ȼ����� */
    NVIC_Config(USART1_IRQn, 0, 2);

    /* ʹ�ܴ��ڽ����ж� */
    //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* ʹ�ܴ��ڿ����ж� */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    /* ʹ�ܴ��� */
    USART_Cmd(USART1, ENABLE);
}




/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    USART1_RXDMA_Config
  * @brief   USART1 RXDMAͨ����ʼ��
  * @param   USART1_DMABuff_addr: �ڴ��ַ 
**			 	 	 buffsize: �����С 
  * @author  ���� 
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*����DMA2ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* ��λ��ʼ��DMA������ */
    /* USART1_RX_DMA_STREAM = DMA2_Stream2 */
    /*����USART1��DMAͨ����Ӧ����DMA2��ͨ��4��������2���������ͨ����DMA����ͨ�����*/
    DMA_DeInit(DMA2_Stream2);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE)
    {
        /*���û�и�λ��ɻ����޵Ŀ���while����*/
    }

    /*usart1 rx��Ӧdma2��ͨ��4��������2*/
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;

    /*����DMAԴ���������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);//(uint32_t)(&USART1->DR)	//����1���ݼĴ�����ַ

    /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    /*USART1_DMABuff_addr ->����*/
    /*���������Լ��趨*/
    DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;

    /*���򣺴����赽�ڴ�*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
    /*buffsize ->����*/
    DMA_InitStructure.DMA_BufferSize = buffsize;

    /*�����ַ����*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /*�������ݵ�λ*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /*DMAģʽ������ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

    /*���ȼ�����*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*����FIFO*/
    /*�����������ʲô��˼��*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    /*�洢��ͻ������ 16 ������*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;

    /*����ͻ������ 1 ������*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /*����DMA2��������*/
    DMA_Init(DMA2_Stream2, &DMA_InitStructure);

    /*ʹ��DMA*/
    DMA_Cmd(DMA2_Stream2, ENABLE);

    /* �ȴ�DMA��������Ч*/
    while(DMA_GetCmdStatus(DMA2_Stream2) != ENABLE)
    {

    }

    /*ʹ��DMA��������*/
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);

}














static USART_TypeDef* Using_USART = USART2;

/**
  * @brief  USARTʹ��printf��scanf�˿�����
  * @param  USARTx 	USART����
  * @retval None
  */
void USART_setPort(USART_TypeDef* USARTx) 
{
    Using_USART = USARTx;
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ����� */
    USART_SendData(Using_USART, (uint8_t) ch);

    /* �ȴ�������� */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);

    return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
    /* �ȴ������������� */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(Using_USART);
}
