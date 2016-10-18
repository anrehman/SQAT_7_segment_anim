/*
 * switchmatrix.c
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#include "chip.h"
#include "swm.h"

int SWM_init(LPC_SYSCTL_T* pLPC_SYSCON,
		LPC_SWM_T* pLPC_SWM)
{
	if ( !pLPC_SYSCON || !pLPC_SWM ){
		return SWM_RC_PARAM_ERROR;
	}
	// Enable SWM clock
	pLPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

	// SDA in PI0_10
	pLPC_SWM->PINASSIGN[7] = 0x0BFFFFFF;	// (p. 130)

	// SCL in PI0_11
	pLPC_SWM->PINASSIGN[8] = 0xFFFFFF0A;	// (p. 131)

	// Configure fixed-pin functions
	// These are default values -- could be changed
	pLPC_SWM->PINENABLE0 = 0xffffffb3UL;		// (p. 132)

	// Disable SWM clock - power saving
	pLPC_SYSCON->SYSAHBCLKCTRL &= (~(1<<7));
	return SWM_RC_OK;
}
