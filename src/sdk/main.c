#include "xparameters.h"
#include <stdio.h>

#include "xscutimer.h"  // if PS Timer is used
#include "xaxidma.h"	// if AXI_DMA is used
#include "xaxicdma.h"	// if AXI_DMA is used

#include "xscugic.h" 	// if PS GIC is used
#include "xil_exception.h"	// if interrupt is used
#include "xil_cache.h"
#include "xil_printf.h"
#include "xil_types.h" 

#include "xsdps.h"
#include "dma_intr.h"
#include "sys_intr.h"
//#include "uart.h"   不使用uart
#include "sd_card.h"


//把DDR分成四个部分
#define DDR_MEMORY  0x01000000
#define LENGTH 51200      //每个DDR的容量大小
#define CDMA_BARAM_MEMORY 0xC0000000

//自定义寄存器的地址
u8 *AxiLite_reg = (u8 *)XPAR_AXI_LITE_CMD_0_S00_AXI_BASEADDR;

//定时器的地址
#define TIMER_DEVICE_ID	XPAR_SCUTIMER_DEVICE_ID
#define TIMER_LOAD_VALUE 0xFFFFFFFF
#define INTC_DEVICE_INT_ID XPAR_SCUGIC_SINGLE_DEVICE_ID


//PS GIC
XScuGic Gic;

//由于我这个工程没有在硬件处勾选uart，因此无法使用这个外设
// UART related definitions
//int Status_Uart;
//XUartPs Uart_PS;

// AXI_DMA related definitions
int Status_AxiDma1;
XAxiDma AxiDma1;
int Status_AxiDma2;
XAxiDma AxiDma2;
int Status_AxiDma3;
XAxiDma AxiDma3;
int Status_AxiDma4;
XAxiDma AxiDma4;

//CDMA related definition
int Status_Cdma;
XAxiCdma Cdma;



//SD_Card definitions
static FATFS SD_Dev; // File System instance
char *SD_Path =  "0:/"; //  string pointer to the logical drive number
static char FileName[32] = "TEST.BIN"; // name of the log

// PS Timer related definitions
int Status_Timer;
XScuTimer Timer;
volatile u32 CntValue1;
XScuTimer_Config *ConfigPtr;
XScuTimer *TimerInstancePtr = &Timer;


u8 *source = (u8 *)DDR_MEMORY;


int init_intr_sys(void)
{
	//4个DMA + 1个CDMA
	//XAxiDma_Reset(&AxiDma1);

	if(XAxiDma_ResetIsDone(&AxiDma1) == 1)
	{
		DMA_Intr_Init(&AxiDma1,XPAR_AXI_DMA_0_DEVICE_ID);//initial interrupt system
		DMA_Intr_Init(&AxiDma2,XPAR_AXI_DMA_1_DEVICE_ID);//initial interrupt system
		DMA_Intr_Init(&AxiDma3,XPAR_AXI_DMA_2_DEVICE_ID);//initial interrupt system
		DMA_Intr_Init(&AxiDma4,XPAR_AXI_DMA_3_DEVICE_ID);//initial interrupt system

		Status_Cdma=CDMA_Intr_Init(&Cdma,XPAR_AXI_CDMA_0_DEVICE_ID);
	}




	//中断控制器初始化
	Init_Intr_System(&Gic); // initial DMA interrupt system
	Setup_Intr_Exception(&Gic);
//	Status_Uart = Init_Uart(&Uart_PS);


	//4个DMA + 1个CDMA (注意下面这几个中断初始化函数的中断通道都有问题，因为都使用了同一个通道，本工程不使用中断)
	DMA_Setup_Intr_System(&Gic,&AxiDma1,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system
	DMA_Setup_Intr_System(&Gic,&AxiDma2,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system
	DMA_Setup_Intr_System(&Gic,&AxiDma3,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system
	DMA_Setup_Intr_System(&Gic,&AxiDma4,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system

	Status_Cdma=CDMA_Setup_Intr_System(&Gic,&Cdma,TX_INTR_ID,RX_INTR_ID);//setup dma interrpt system


	//4个DMA + 1个CDMA
	DMA_Intr_Enable(&Gic,&AxiDma1);
	DMA_Intr_Enable(&Gic,&AxiDma2);
	DMA_Intr_Enable(&Gic,&AxiDma3);
	DMA_Intr_Enable(&Gic,&AxiDma4);


	//下面这个函数实际上是在关闭中断
	Status_Cdma=CDMA_Intr_Enable(&Gic,&Cdma);

	//Enable SD Card
	SD_init(&SD_Dev,SD_Path);


	//定时器初始化
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);

	Status_Timer = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr,
				 ConfigPtr->BaseAddr);
	if (Status_Timer != XST_SUCCESS) {
		return XST_FAILURE;
	}

	//下面这两个我注释了，实在不知道有什么用？
	//Enable the IRQ exception.
	//Xil_ExceptionEnable();

	// Disable DCache
	//Xil_DCacheDisable();

	return 0;
}

//测试4个DMA同时搬运的速度（这个测试代码用的是sd_Card里的text.bin写入ddr中的数据，下面两个都是直接搬运变量中的数据）
int axi_dma_test()
{
	// Flush the SrcBuffer before the DMA transfer, in case the Data Cache is enabled

	Xil_DCacheFlushRange(DDR_MEMORY, 4*LENGTH);

	// Start the Scu Private Timer device.
	XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);
	XScuTimer_Start(TimerInstancePtr);
	XScuTimer_RestartTimer(TimerInstancePtr);


	// DMA in polling mode 4个DMA
	Status_AxiDma1 = XAxiDma_SimpleTransfer(&AxiDma1,(UINTPTR)DDR_MEMORY,
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma2 = XAxiDma_SimpleTransfer(&AxiDma2,(UINTPTR)(DDR_MEMORY+LENGTH),
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma3 = XAxiDma_SimpleTransfer(&AxiDma3,(UINTPTR)(DDR_MEMORY+2*LENGTH),
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma4 = XAxiDma_SimpleTransfer(&AxiDma4,(UINTPTR)(DDR_MEMORY+3*LENGTH),
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	//Status_Cdma = XAxiCdma_SimpleTransfer(&Cdma, (UINTPTR)DDR_MEMORY+4*LENGTH, (UINTPTR) CDMA_BARAM_MEMORY, 20, NULL, (void *) &Cdma);



	if ((Status_AxiDma1 != XST_SUCCESS)|| (Status_AxiDma2 != XST_SUCCESS)||(Status_AxiDma3 != XST_SUCCESS)||(Status_AxiDma4 != XST_SUCCESS))
	{
//		print("fuck, there are errors!!!\r\n");
		return 1;
	}

	Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma2 = XAxiDma_Busy(&AxiDma2,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma3 = XAxiDma_Busy(&AxiDma3,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma4 = XAxiDma_Busy(&AxiDma4,XAXIDMA_DMA_TO_DEVICE);

	//Status_Cdma = XAxiCdma_IsBusy(&Cdma);

	while (Status_AxiDma1 || Status_AxiDma2 || Status_AxiDma3 || Status_AxiDma4)
	{
		Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma2 = XAxiDma_Busy(&AxiDma2,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma3 = XAxiDma_Busy(&AxiDma3,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma4 = XAxiDma_Busy(&AxiDma4,XAXIDMA_DMA_TO_DEVICE);

		//Status_Cdma = XAxiCdma_IsBusy(&Cdma);

	}
	CntValue1 = TIMER_LOAD_VALUE - XScuTimer_GetCounterValue(TimerInstancePtr);

	if(Status_AxiDma1 || Status_AxiDma2 || Status_AxiDma3 || Status_AxiDma4)
		return 1;
	else
		return 0;

}


//测试DMA1的速度
u8 data[LENGTH]={0};
int i=0;
int test_sd_dma()
{



	for(i=0;i<LENGTH;i++)
		data[i]=12;
	Xil_DCacheFlushRange(DDR_MEMORY, LENGTH);


	// Start the Scu Private Timer device.
	XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);
	XScuTimer_Start(TimerInstancePtr);
	XScuTimer_RestartTimer(TimerInstancePtr);

	// DMA in polling mode 4个DMA
	Status_AxiDma1 = XAxiDma_SimpleTransfer(&AxiDma1,(UINTPTR)data,
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
	while(Status_AxiDma1 == 1)
	{
		Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
	}
	CntValue1 = TIMER_LOAD_VALUE - XScuTimer_GetCounterValue(TimerInstancePtr);

	if(Status_AxiDma1 == 0)
		return 0;
	else
		return 1;


}

//测试四个通道的速度
int test_dma0_2()
{

	for(i=0;i<LENGTH;i++)
			data[i]=12;
	Xil_DCacheFlushRange(DDR_MEMORY, 4*LENGTH);


	// Start the Scu Private Timer device.
	XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);
	XScuTimer_Start(TimerInstancePtr);
	XScuTimer_RestartTimer(TimerInstancePtr);

	// DMA in polling mode 4个DMA
	Status_AxiDma1 = XAxiDma_SimpleTransfer(&AxiDma1,(UINTPTR)data,
						LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma2 = XAxiDma_SimpleTransfer(&AxiDma2,(UINTPTR)data,
							LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma3 = XAxiDma_SimpleTransfer(&AxiDma3,(UINTPTR)data,
							LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma4 = XAxiDma_SimpleTransfer(&AxiDma4,(UINTPTR)data,
							LENGTH, XAXIDMA_DMA_TO_DEVICE);




	Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma2 = XAxiDma_Busy(&AxiDma2,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma3 = XAxiDma_Busy(&AxiDma3,XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma4 = XAxiDma_Busy(&AxiDma4,XAXIDMA_DMA_TO_DEVICE);
	while( Status_AxiDma1 || Status_AxiDma2|| Status_AxiDma3 || Status_AxiDma4)
	{
		Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma2 = XAxiDma_Busy(&AxiDma2,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma3 = XAxiDma_Busy(&AxiDma3,XAXIDMA_DMA_TO_DEVICE);
		Status_AxiDma4 = XAxiDma_Busy(&AxiDma4,XAXIDMA_DMA_TO_DEVICE);
	}
	CntValue1 = TIMER_LOAD_VALUE - XScuTimer_GetCounterValue(TimerInstancePtr);

	if(Status_AxiDma1 == 0)
		return 0;
	else
		return 1;


}


//测试0通道同时读写
int dma0_read_write()
{

	Xil_DCacheFlushRange(DDR_MEMORY, 4*LENGTH);
	// Start the Scu Private Timer device.
	XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);
	XScuTimer_Start(TimerInstancePtr);
	XScuTimer_RestartTimer(TimerInstancePtr);

//	Status_AxiDma1 = XAxiDma_SimpleTransfer(&AxiDma1,(UINTPTR)DDR_MEMORY,
//							LENGTH, XAXIDMA_DMA_TO_DEVICE);
	Status_AxiDma1 = XAxiDma_SimpleTransfer(&AxiDma1,(UINTPTR)DDR_MEMORY,
								LENGTH, XAXIDMA_DEVICE_TO_DMA);

	Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);

	while( Status_AxiDma1 )
		{
			Status_AxiDma1 = XAxiDma_Busy(&AxiDma1,XAXIDMA_DMA_TO_DEVICE);
		}

	CntValue1 = TIMER_LOAD_VALUE - XScuTimer_GetCounterValue(TimerInstancePtr);




	if(Status_AxiDma1 == 0)
		return 0;
	else
		return 1;

}

int main (void) {

	init_intr_sys();

	//下面的代码要实现SD卡读取数据到DDR里面
	/*DDR数据需要划分为好几个部分， 每个部分搬到不同的BRAM里面*/

	//写入bin文件  执行这一步是因为我现在还没有bin文件
//	print("begin to transfer\r\n");
//	for(i=0;i<LENGTH;i++)
//			data[i]=12;
//	SD_write(FileName,(u8 *)(data),LENGTH);


    //读取至DDR中
	SD_read(FileName,(u8 *)(DDR_MEMORY),LENGTH);
	SD_read(FileName,(u8 *)(DDR_MEMORY+LENGTH),LENGTH);
	SD_read(FileName,(u8 *)(DDR_MEMORY+2*LENGTH),LENGTH);
	SD_read(FileName,(u8 *)(DDR_MEMORY+3*LENGTH),LENGTH);
//	SD_read(FileName,(u8 *)(DDR_MEMORY+4*LENGTH),LENGTH);


    while(1)
    {
		if( *AxiLite_reg == 1)
		{
			//Xil_ICacheDisable();
			dma0_read_write();
			//test_sd_dma();
			//dma0_read_write();
			*AxiLite_reg = 4;

			//测试ACP口的数据上行
//			Status_Cdma = XAxiCdma_SimpleTransfer(&Cdma, (UINTPTR) CDMA_BARAM_MEMORY,(UINTPTR)DDR_MEMORY+4*LENGTH, 20, NULL, (void *) &Cdma);
//			while(XAxiCdma_IsBusy(&Cdma))
//				;
//			*AxiLite_reg = 5;
		}

    }

    return 0;
}

