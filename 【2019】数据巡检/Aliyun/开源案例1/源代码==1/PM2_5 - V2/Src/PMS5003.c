#include "PMS5003.h"
#include "usart.h"



PMS5003_t PMS5003_Data;

void PMS_RevData()
{
//	uint16_t tempcnt = 0;//接收数据的个数
//	uint16_t sum=0;
//	uint16_t i;
//	while(Uart2.receive_flag)//串口2接收标志 可能接收到多帧数据
//	{  
//		Uart2.receive_flag--;//
//		
//		i=Uart2.rx_head + tempcnt;//帧头索引
//		if(Uart2.usartDMA_rxBuf[i%RECEIVELEN] == 0x42 && Uart2.usartDMA_rxBuf[(i+1)%RECEIVELEN] == 0x4D)//判断帧头
//		{
//			tempcnt = Uart2.usartDMA_rxBuf[(i+3)%RECEIVELEN] + 4;//帧长度
//			for(uint16_t k=i;k<(i+tempcnt-2);k++)
//			{
//				sum+=Uart2.usartDMA_rxBuf[k%RECEIVELEN];//求校验和
//			}
//			if((Uart2.usartDMA_rxBuf[(i+tempcnt-1)%RECEIVELEN] == (sum&0xFF)) && (Uart2.usartDMA_rxBuf[(i+tempcnt-2)%RECEIVELEN] == (sum>>8)))//判断校验和
//			{
//				PMS5003_Data.PM1_0 = ((uint16_t)(Uart2.usartDMA_rxBuf[(10+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(11+i)%RECEIVELEN];
//				PMS5003_Data.PM2_5 = ((uint16_t)(Uart2.usartDMA_rxBuf[(12+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(13+i)%RECEIVELEN];
//				PMS5003_Data.PM10 = ((uint16_t)(Uart2.usartDMA_rxBuf[(14+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(15+i)%RECEIVELEN];
//				#ifdef PMS5003_ST	
//					PMS5003_Data.HCHO = ((uint16_t)(Uart2.usartDMA_rxBuf[(28+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(29+i)%RECEIVELEN];
//					PMS5003_Data.Temperature = ((uint16_t)(Uart2.usartDMA_rxBuf[(30+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(31+i)%RECEIVELEN];
//					PMS5003_Data.Humidity = ((uint16_t)(Uart2.usartDMA_rxBuf[(32+i)%RECEIVELEN])<<8) | Uart2.usartDMA_rxBuf[(33+i)%RECEIVELEN];
//				#endif
//			}
//		}
//	
//	} 

		uint16_t sum=0;
		if(Uart2.rx_flag==1)
		{
			for(uint8_t i=0;i<(Uart2.rx_len+2);i++)
			{
				sum+=Uart2.usart_rxBuf[i];
			}
			if((Uart2.usart_rxBuf[Uart2.rx_len+3] == (sum&0xFF)) && (Uart2.usart_rxBuf[Uart2.rx_len+2] == (sum>>8)))//判断校验和
			{
				PMS5003_Data.PM1_0 = ((uint16_t)(Uart2.usart_rxBuf[10])<<8) | Uart2.usart_rxBuf[11];
				PMS5003_Data.PM2_5 = ((uint16_t)(Uart2.usart_rxBuf[12])<<8) | Uart2.usart_rxBuf[13];
				PMS5003_Data.PM10 = ((uint16_t)(Uart2.usart_rxBuf[14])<<8) | Uart2.usart_rxBuf[15];
				#ifdef PMS5003_ST	
					PMS5003_Data.HCHO = ((uint16_t)(Uart2.usart_rxBuf[28])<<8) | Uart2.usart_rxBuf[29];
					PMS5003_Data.Temperature = ((uint16_t)(Uart2.usart_rxBuf[30])<<8) | Uart2.usart_rxBuf[31];
					PMS5003_Data.Humidity = ((uint16_t)(Uart2.usart_rxBuf[32])<<8) | Uart2.usart_rxBuf[33];
				#endif
			}
			Uart2.rx_len=0;
			Uart2.rx_flag=0;
		}
}

