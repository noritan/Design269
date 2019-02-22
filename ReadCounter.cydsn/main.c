/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define     N_DIFF      (32)

uint16 diffs[N_DIFF];

void func_measure(uint32 index) {
        uint32 s;
        uint32 e;
        
        s = Timer_COUNTER_REG;
        asm (
            "b .measure_1\n"
            " .align 3\n"
            ".measure_1:"
            " b .measure_2\n"
            " .align 3\n"
            ".measure_2:\n"
        );
        e = Timer_COUNTER_REG;
        
        diffs[index] = (e - s) & Timer_16BIT_MASK;
}

int main(void) {
    uint32 i;
    
    // CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Timer_Start();
    
    for (i = 0; i < N_DIFF; i++) {
        func_measure(i);
    }

    UART_PutCRLF();
    UART_PutString("Start:");
    UART_PutCRLF();
    for (i = 0; i < N_DIFF; i++) {
        UART_PutHexInt(diffs[i]);        
        if ((i & 7) < 7) {
            UART_PutChar(' ');
        } else {
            UART_PutCRLF();
        }
    }
    
    CySysClkWriteImoFreq(12000000u);

    for(;;) {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
