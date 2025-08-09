#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t data;


    __asm volatile ("SVC #0x01");

    __asm volatile ("MOV %0, R0" : "=r"(data));

    printf("The returned value is: %d\r\n", data);

    while (1);
}


__attribute__((naked)) void SVC_Handler(void)
{
    __asm volatile (
        "MRS R0, MSP       \n"
        "B   SVC_Handler_c \n"
    );
}


void SVC_Handler_c(uint32_t *msp_top)
{

    uint32_t PC_val = msp_top[6];
    uint16_t *SVC_ins_addr = (uint16_t *)(PC_val - 2); // address of SVC instruction
    uint8_t svc_num = (uint8_t)(*SVC_ins_addr & 0xFF); // extract imm8

    printf("Inside SVC handler\r\n");
    printf("SVC NUMBER IS : %d\r\n", svc_num);

    svc_num+=4;
    // Set return value in stacked R0 so main() can read it
    msp_top[0] =svc_num ;  // when handler returns, R0 = 0x1234ABCD
}
