#ifndef _DRIVER_FLASH
#define _DRIVER_FLASH
  #include "..\DataStruct.h"
#endif

//sst26
#define RSTEN		       	   (0x66)
#define RST			   (0x99)
#define ULBPR			   (0x98)
#define STATUS_REGISTER            (0x05)
#define SECTOR_ERASE		   (0x20)
#define BLOCK_ERASE                (0xD8)
#define CHIP_ERASE		   (0xc7)
#define SST_READ		   (0x03)
#define SST_WRITE		   (0x02)
#define WREN		  	   (0x06)
#define WRDI			   (0x04)
#define RSID			   (0x88)
#define RDID			   (0x90)
#define JEDEC			   (0x9F)

//sst25�õ���ָ��
#define EWSR			   (0x50)
#define WRSR			   (0x01)

#define UNSELECT_CHIP    P8OUT |= BIT1
#define SELECT_CHIP      P8OUT &= ~BIT1


void EraseFlash(INT32U addr)                  //���FLASH��(512BYTE)
{   
    volatile INT16U * ptr;                    //addrΪ�öε��׵�ַ

    INT16U j;
    
    _DINT();  
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    for(j = 0; j < 1000; j++)
    {
      if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
      break;
    }    
     
    ptr = (INT16U *)addr;
	WatchDog();
    FCTL1          = 0xA502;                  //ERASE =1
    FCTL3          = 0xA500;                  //LOCK=0
    *ptr           = 0;
    FCTL1          = FWKEY;                   // Clear WRT bit
    FCTL3          = FWKEY + LOCK;            // Set LOCK bit    
    _EINT();
}
void WriteFlashNByte(INT32U dst, INT16U src, INT8U len)            //��ָ����ַд��len���ȵ�����,Դ��ַ��ʼ��len������д��Ŀ�ĵ�ַȥ
{
    INT16U i,j;
    INT8U *ptr,*ptr1;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT8U *)dst;
    ptr1 = (INT8U *)src;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(ptr1 + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashBuffLongWord(INT32U dst, INT32S *data, INT8U len)
{
    INT16U i,j;
    INT32S *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT32S *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashBuffWord(INT32U dst, INT16S *data, INT8U len)
{
    INT16U i,j;
    INT16S *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT16S *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashWord(INT32U dst, INT16U data)
{
    INT16U i;
    INT16U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT16U *)dst;
    for(i = 0; i < 1000; i++)
    {
      if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
      break;
    }
    FCTL3 = FWKEY;                            //  LOCK=0
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    *ptr = data;
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}
void WriteFlashByte(INT32U dst, INT8U data)
{
    INT16U i;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT8U *)dst;
    for(i = 0; i < 1000; i++)
    {
      if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
      break;
    }
    FCTL3 = FWKEY;                            //  LOCK=0
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    *ptr = data;
	WatchDog();
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}

//**************************************
//  date : 2012-07-17
//  Mender: KYO
//  Modify: FCTL1 = FWKEY + ERASE;   *ptr = 0;
//  fault : write flash oncetime
//  whence: The Flash is not Erase
void WriteFlashBuff(INT32U dst, INT8U *data, INT8U len)
{
    INT16U i;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT8U *)dst;
    FCTL1 = FWKEY + ERASE; 
    FCTL3 = FWKEY;                            //  LOCK=0
    *ptr = 0;
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    for(i = 0; i < len; i++)
    {
        *ptr++ = *(data + i);
		WatchDog();
    }
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}




void WriteFlashBuff1(INT32U dst, INT8U *data, INT8U len)
{
    INT16U i,j;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
    WatchDog();                             ////���ⲿ���Ź�
    ptr  = (INT8U *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //��æ������,��ɲ���
          break;
        }
        WatchDog();
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}





//***************************************************************
//    data     : 2012
//    mender   :  KYO
//    Function :  Read Flash Date


void Read_para(long *src, char *des,int count)
{             
  int i;
  
   _DINT();
  WDTCTL = WDTPW + WDTHOLD;          // ֹͣ���Ź�
  WatchDog();                             ////���ⲿ���Ź�
  //FCTL2 = FWKEY + FSSEL0 + FN0;      // ����FLASHʱ����������ʱ��
  

  FCTL1 = FWKEY + ERASE;             // ʹ�ܲ�������
  FCTL3 = FWKEY;                     // FLASH����
  FCTL1 = FWKEY + WRT;               // ����д����
  for (i=0; i<count; i++)
  {
    *des++ = *src++;            // ѭ��д
  }
    
  FCTL1 = FWKEY;                  
  FCTL3 = FWKEY + LOCK;              //д���ˣ�����
  
   _EINT();	

}

//**************************************
//  date : 2012-07-17
//  Mender: KYO
//  Function: write Flash 
//void write_para(INT8U *src, INT8U count)
//{
//  INT8U *Flash_ptr; 
//             
//  char i;
//  
//   _DINT();
//  WDTCTL = WDTPW + WDTHOLD;               ////��ֹ�ڲ����Ź�
//  WatchDog();                             ////���ⲿ���Ź�
//  
//  Flash_ptr = (INT8U *) 0x10600;       // ��ʼ��ָ��
//  FCTL1 = FWKEY + ERASE;             // ʹ�ܲ�������
//  FCTL3 = FWKEY;                     // FLASH����
//  *Flash_ptr = 0;                    // ��д����������
//  FCTL1 = FWKEY + WRT;               // ����д����
//  for (i=0; i<count; i++)
//  {
//    *Flash_ptr++ = *src++;            // ѭ��д
//  }
//    
//  
//  FCTL1 = FWKEY;                  
//  FCTL3 = FWKEY + LOCK;              //д���ˣ�����
//    
//   _EINT();	
//}





//==============================================================================
//  ��������   : SPIWriteBuf
//  ��������   : SPI����һ�ֽ�����
//  �������   : ucData: ��д������
//  �������   ��<��>
//  ����ֵ     : UCB0TXBUF�Ĵ�������
//  ����˵��   : 
//  ����       ��
//==============================================================================
unsigned char SPIWriteBuf(unsigned char ucData)
{
    unsigned char i;
    UCB2TXBUF = ucData;
    for( i = 0; i < 255; i++ )
    {
    if((UCB2STAT&UCBUSY)==0)
    {    
        break;
    }
    }

    return UCB2TXBUF;
}

//==============================================================================
//  ��������   : InitSPI
//  ��������   : SPI����һ�ֽ�����
//  �������   : <��>
//  �������   ��<��>
//  ����ֵ     : UCB0RXBUF�Ĵ�������
//  ����˵��   : 
//  ����       ��
//==============================================================================
unsigned char SPIReadBuf(void)
{
    unsigned char i;
    SPIWriteBuf(0);
    for( i = 0; i < 250; i++ )
    {
    if((UCB2STAT&UCBUSY)==0)
    {    
        break;
    }
    }
    return UCB2RXBUF;
}

//==============================================================================
//  ��������   : Sst_Reset
//  ��������   : ��λоƬ
//  �������   : <��>
//  �������   ��<��>
//  ����ֵ     : <��>
//  ����˵��   : 
//  ����       ��
//==============================================================================
 void Sst_Reset(void)
{
    SELECT_CHIP;
    SPIWriteBuf(RSTEN);
    UNSELECT_CHIP;
    SELECT_CHIP;
    SPIWriteBuf(RST);
    UNSELECT_CHIP;
}
 //==============================================================================
 //  ��������   : Sst_Unlock
 //  ��������   : ����оƬ
 //  �������   : <��>
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
void Sst_Unlock(void)
{
	unsigned char temp[3];
	Sst_ReadJEDECID(temp,3);
	if(temp[2]==0x4B)
		{//SST25VF064C
     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(ULBPR);
     UNSELECT_CHIP;
	 SELECT_CHIP;         //sst25�ϵ���Ҫ�ֶ�����鱣��״̬
     SPIWriteBuf(EWSR);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(WRSR);
     SPIWriteBuf(0x00);  //����鱣��
     UNSELECT_CHIP;
		}
	else if(temp[2]==0x43)
		{//SST26VF064B
     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(ULBPR);
     UNSELECT_CHIP;	
     SELECT_CHIP;
     SPIWriteBuf(WRSR);
     SPIWriteBuf(0x00); 	 
     SPIWriteBuf(0x0a);  //����鱣��
     UNSELECT_CHIP;	 
		}
}
//==============================================================================
//  ��������   : SpiWaitBusy
//  ��������   : ͨ����״̬�Ĵ������æ״̬
//  �������   : <��>
//  �������   ��<��>
//  ����ֵ     : <��>
//  ����˵��   :
//  ����       ��
//==============================================================================
 void SpiWaitBusy(void)
{
    unsigned char temp = 0;
    unsigned int a = 0;
	
	SELECT_CHIP;
        SPIWriteBuf(STATUS_REGISTER);
        //SPIWriteBuf(0x35);

	for(a=0;a<2000;a++)
	{
		temp = SPIReadBuf();
		//k=temp;
		temp&=0x01;//temp&=0x81;
		if(temp==0)
		{
		    break;
		}
	}
	UNSELECT_CHIP;
}
 //==============================================================================
 //  ��������   : Sst_ReadID
 //  ��������   : ��ȡID
 //  �������   : <��>
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
void Sst_ReadID(unsigned char *PcData,unsigned int Size)
{
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(RDID);
 	SPIWriteBuf((unsigned char)(0));
	SPIWriteBuf((unsigned char)(0));
	SPIWriteBuf((unsigned char)(0));
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
}

 void Sst_ReadJEDECID(unsigned char *PcData,unsigned int Size)
{
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(JEDEC);
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
}
 //==============================================================================
 //  ��������   :Sector_Erase
 //  ��������   : ����� (4k Bytes)
 //  �������   : ���ַ����12λ��Ч
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Sector_Erase(long unBlock)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(SECTOR_ERASE);
     SPIWriteBuf((unsigned char)(unBlock >> 16));
     SPIWriteBuf((unsigned char)(unBlock >> 8));
     SPIWriteBuf((unsigned char)unBlock);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
     delayms(50);
 }

//==============================================================================
 //  ��������   :Block_Erase
 //  ��������   : ����� (���ݴ洢������block���ֽ���8k��32k��64k����)
 //  �������   : ���ַ����12λ��Ч15-13λ���ݿ��С�ı�
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Block_Erase(long unBlock)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(BLOCK_ERASE);
     SPIWriteBuf((unsigned char)(unBlock >> 16));
     SPIWriteBuf((unsigned char)(unBlock >> 8));
     SPIWriteBuf((unsigned char)unBlock);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
     
     delay(30000);//����֮����ʱһ��ʱ��ERASE_DELAY
     
 }
 //==============================================================================
 //  ��������   :Chip_Erase
 //  ��������   : оƬƬ����
 //  �������   : <��>
 //  �������   ��<��>
 //  ����ֵ     : 	<��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Chip_Erase(void)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(CHIP_ERASE);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
 }
 //==============================================================================
 //  ��������   : Sst26vf064b_Read
 //  ��������   : ������
 //  �������   : unAddr�����������Ե�ַ �� PcData��Ŀ�����ݴ洢ָ�� ��Size����ȡ���ݸ����
 //  �������   ��<��>
 //  ����ֵ     : 	<��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Sst26vf064b_Read(long unAddr,unsigned char *PcData,unsigned int Size)
 {
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(SST_READ);
 	SPIWriteBuf((unsigned char)(unAddr >> 16));
 	SPIWriteBuf((unsigned char)(unAddr >> 8));
    SPIWriteBuf((unsigned char) unAddr);
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
 }
 //==============================================================================
 //  ��������   : Sst26vf064b_Page_Write
 //  ��������   : д����
 //  �������   : unAddr�����������Ե�ַ��  PcData��Ŀ�����ݴ洢ָ�룻 Size��д�����ݸ���(<=256��ע���ҳ)
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Sst26vf064b_Page_WriteBytes(long unAddr,unsigned char *PcData,unsigned int Size)
 {
     unsigned int i;
     SpiWaitBusy();

     //Flash_cs=0;
     SELECT_CHIP;
    // delay(1);
     SPIWriteBuf(WREN);							//����д
    // Flash_cs=1;
    // delay(1);
     UNSELECT_CHIP;

    // Flash_cs=0;
     SELECT_CHIP;
     SPIWriteBuf(SST_WRITE);						//дָ��
     SPIWriteBuf((unsigned char)(unAddr >> 16));	//��ַ
     SPIWriteBuf((unsigned char)(unAddr >> 8));
     SPIWriteBuf((unsigned char) unAddr);
     for(i = 0;i < Size;i++)					//����
     {
    	SPIWriteBuf(*PcData);
    	PcData++;
     }
     delay(20);
     UNSELECT_CHIP;

     SELECT_CHIP;
  //   delay(1);
     SPIWriteBuf(WRDI);							//��ֹд
     //Flash_cs=1;
  //   delay(1);
     UNSELECT_CHIP;
 }

 //==============================================================================
 //  ��������   : Sst26vf064b_Page_Write
 //  ��������   : д����
 //  �������   : unAddr�����������Ե�ַ��  PcData��Ŀ�����ݴ洢ָ�룻 Size��д�����ݸ���(<=256��ע���ҳ)
 //  �������   ��<��>
 //  ����ֵ     : <��>
 //  ����˵��   :
 //  ����       ��
 //==============================================================================
 void Sst26vf064b_Page_WriteWords(long unAddr,unsigned int *PcData,unsigned int Size)
 {
     unsigned int i;
     unsigned char *PcBufTemp;

     Size *= 2;
     PcBufTemp = (unsigned char*)PcData;
     SpiWaitBusy();

     //Flash_cs=0;
     SELECT_CHIP;
    // delay(1);
     SPIWriteBuf(WREN);							//����д
    // Flash_cs=1;
    // delay(1);
     UNSELECT_CHIP;

    // Flash_cs=0;
     SELECT_CHIP;
   //  delay(1);
     SPIWriteBuf(SST_WRITE);						//дָ��
     SPIWriteBuf((unsigned char)(unAddr >> 16));	//��ַ
     SPIWriteBuf((unsigned char)(unAddr >> 8));
     SPIWriteBuf((unsigned char) unAddr);
     for(i = 0;i < Size;i++)					//����
     {
    	SPIWriteBuf(*PcBufTemp);
    	PcBufTemp++;
     }
     
     UNSELECT_CHIP;
     delayms(2);
   /*  
     SELECT_CHIP;
  //   delay(1);
     SPIWriteBuf(WRDI);							//��ֹд
     //Flash_cs=1;
  //   delay(1);
     UNSELECT_CHIP;
     */
 }


//==============================================================================
//  ��������   : CopySoeEepToFlash
//  ��������   : EEPROM�е�SOE���ݵ���FLASH
//  �������   : <��>
//  �������   ��<��>
//  ����ֵ     : <��>
//  ����˵��   : 
//  ����       ��
//==============================================================================
//void CopySoeEepToFlash(void)
//{
//    unsigned int j;
//    unsigned int tSoeBuff[SOE_DATA_LEN * 10];
//    for(j = 0; j < 4; j++)   //ÿ�����д��256�ֽڣ����Է�4��д��
//    {
//       // for(i = 0; i < 10; i++)    //�����ڴ��е�SOE���ݿ�����ʱ���£���˲�ֱ�Ӳ����ڴ�����ݣ�����EEPROM��һ��һ��ȡ��
//        {
//            //CAT_SpiReadWords(EEPADD_SOE_DATA + j * 240 , SOE_DATA_LEN * 10, tSoeBuff);   //���δ�EEPROM��ȡ��SOE���ݣ��ŵ�tSoeBuff��
//        }  
//           // Sst26vf064b_Page_WriteWords((FADDR_SOE_START) * 256, tSoeBuff,SOE_DATA_LEN * 10);      //�����ݱ������FLASH��
//        
//          //  Sst26vf064b_Read((FADDR_SOE_START + g_sSoeData.m_unSoeFlashPos + j) * 256, stSoeBuff,240);
//    }
//   // WritePageFromBuffer(g_sSoeData.m_unSoeFlashPos,DB_2_BUFFER);
//}
//