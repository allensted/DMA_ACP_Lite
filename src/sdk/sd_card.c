#include "sd_card.h"




int SD_init(FATFS *SD_Dev,char *SD_Path)
{
	FRESULT result;
	//-----------------------mount dev-----------------------------------------------
	result = f_mount(SD_Dev,SD_Path, 0);
	if (result != 0) {
//		xil_printf("SD card ERROR\r\n");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}


int SD_read(char *FileName,u8 *DestinationAddress,u32 ByteLength)
{
	FIL file;
	FRESULT result;
	UINT BytesRd;

	result = f_open(&file,FileName,FA_READ);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_lseek(&file, 0);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_read(&file, (void*)DestinationAddress,ByteLength,&BytesRd);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_close(&file);
	if(result)
	{
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}


int SD_write(char *FileName,u8 *SourceAddress,u32 ByteLength)
{
	FIL file;
	FRESULT result;
	UINT BytesWr;

	result = f_open(&file,FileName,FA_CREATE_ALWAYS | FA_WRITE);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_lseek(&file, 0);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_write(&file,(void*) SourceAddress,ByteLength,&BytesWr);
	if(result)
	{
		return XST_FAILURE;
	}

	result = f_close(&file);
	if(result){
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
