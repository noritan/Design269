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
#include <stdio.h>

// Constant declaration
#define     N_DIFF      (32)    // Number of cycle difference storage
#define     BAUDRATE    (9600)  // Baudrate used for UART

// Set the CPU clock frequency
void setFreq(uint32 freq) {
    // Select a longest wait cycle
    CySysFlashSetWaitCycles(48);
    
    // Change the IMO and related parameters
    CySysClkWriteImoFreq(freq);
    CySysFlashSetWaitCycles(freq);
    CyDelayFreq(freq * 1000000u);

    // Reconfigure the UART clock frequency
    Clock_UART_SetDivider(cydelayFreqHz/BAUDRATE/UART_UART_OVS_FACTOR-1);
}

// Clock cycle difference storage
uint16  diffs[N_DIFF];

// Measure the execution cycle time
uint32 measure(reg32 *reg) __attribute__((aligned(256)));
uint32 measure(reg32 *reg) {
    uint32  s;
    uint32  e;
    
    asm(
//        "nop\n"   // 9
//        "nop\n"   // 8
//        "nop\n"   // 7
//        "nop\n"   // 6
//        "nop\n"   // 5
//        "nop\n"   // 4
//        "nop\n"   // 3
//        "nop\n"   // 2
//        "nop\n"   // 1
        "label_1:\n"
    );
    s = *reg;
    asm(
//        "nop\n"
//        "mov r3,#170\n"
        "mul r3,r0\n"
    );
    e = *reg;
    
    return e - s;
}

// Measure the cycle time repeatedly
// The CPU frequency is set as specified in argument
void loop(uint32 freq) {
    uint32  i;
    char    sbuf[32];
    
    // Set CPU frequency
    setFreq(freq);
    
    // Measure the cycle time
    for (i = 0; i < N_DIFF; i++) {
        diffs[i] = measure(Timer_COUNTER_PTR) & Timer_16BIT_MASK;
    }

    // Show the measurement results
    sprintf(sbuf, "\r\nFreq:%ld\r\n", freq);
    UART_UartPutString(sbuf);
    for (i = 0; i < N_DIFF; i++) {
        sprintf(sbuf, "%04X", diffs[i]);
        UART_UartPutString(sbuf);
        if ((i & 7) < 7) {
            UART_UartPutChar(' ');
        } else {
            UART_UartPutCRLF(' ');
        }
    }

    // Wait for UART communication completed
    while (!(UART_GetTxInterruptSource() & UART_INTR_TX_UART_DONE));
}

static char message[]="Happy April Fool!!";

void showMessage(uint32 freq) {
    uint32 i, j;
    char    sbuf[32];
    
    // Show the message
    sprintf(sbuf, "\r\nFreq:%ld\r\n", freq);
    UART_UartPutString(sbuf);
    for (i = 0; i < strlen(message); i++) {
        for (j = 0; j < 8; j++) {
            sprintf(sbuf, "%04X", (message[i] & (1u<<j))?(0x0005):(0x0004));
            UART_UartPutString(sbuf);
            UART_UartPutChar(' ');
        }
        UART_UartPutCRLF(' ');
    }    
}

int main(void) {
    // CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Timer_Start();
    UART_Start();
        
    showMessage(48);

    loop(48);
    loop(24);
    loop(12);
    
    for(;;) {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
