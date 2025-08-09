
#include<stdio.h>
#include<stdint.h>

int main(){
	//1. use svc instruction with argument

	__asm("SVC #0X01");
	while(1);

}
__attribute((naked))void SVC_Handler(void)
{
	__asm("MRS R0,MSP");
	__asm("B SVC_Handler_c ");
}
void SVC_Handler_c(uint32_t *msp_top) {


    uint32_t PC_val = msp_top[6];                    // Saved PC value
    uint16_t *SVC_ins_addr = (uint16_t *)(PC_val - 2); // Address of SVC instruction
    uint16_t svc_instr = *SVC_ins_addr;              // Read 16-bit Thumb instruction (0xDFxx)
    uint8_t svc_num = (uint8_t)(svc_instr & 0xFF);   // Extract imm8 (SVC number)

    printf("Inside SVC handler\r\n");
    printf("SVC NUMBER IS : %d\r\n", svc_num);
}

