/*
 * sd_card.h
 *
 *  Created on: 2021Äê1ÔÂ16ÈÕ
 *      Author: allen
 */

#ifndef SRC_SD_CARD_H_
#define SRC_SD_CARD_H_

#include "xparameters.h"
#include <stdio.h>
#include "xil_printf.h"
#include "xil_types.h"
#include "ff.h"
#include "xstatus.h"





int SD_init(FATFS *SD_Dev,char *SD_Path);
int SD_read(char *FileName,u8 *DestinationAddress,u32 ByteLength);
int SD_write(char *FileName,u8 *SourceAddress,u32 ByteLength);







#endif /* SRC_SD_CARD_H_ */
