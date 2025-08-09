/*
 * sys_config_exc.c
 *
 *  Created on: Aug 9, 2025
 *      Author: shreyaa_vinod
 */


#include<stdint.h>
#include<stdio.h>

int main(){

	//1. enable sys exception - UBM

	uint32_t * SHCRS = (uint32_t *)0xE000ED24U;
	//a. enable Usage fault
	*SHCRS |= (0x1<<18);
	//b. enable bus fault
	*SHCRS |= (0x1<<17);
	//c. enable memmanage fault
	*SHCRS |= (0x1<<16);

	// 2. implement the fault handlers

	//implementing an invalid opcode storing it in SRAM region and assigning that to a function pointer:
	uint32_t *SRAM_addr = (uint32_t *) 0x20000010U;
	//opcode
	*SRAM_addr = 0xFFFFFFFF;
	void (* func)(void);
	func= (void*) 0x20000010U;
	func();

	//3. forced faults

}
void HardFault_Handler(void)
{
	printf("Exception:HardFault.\r\n");
	while(1);
}
void MemManage_Handler(void)
{
	printf("Exception:MemManageFault.\r\n");
	while(1);

}

void BusFault_Handler(void)
{
	printf("Exception:BusFault.\r\n");
	while(1);

}
void UsageFault_Handler(void)
{
	uint32_t * UFSR= (uint32_t *)0xE000ED2AU;
	uint32_t UFSR_val= (*UFSR & (0xFFFF));
	printf("Fault cause: %ld\r\n",UFSR_val);
	printf("Exception:UsageFault.\r\n");
	while(1);

}
