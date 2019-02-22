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

void func9(reg8 *reg, uint8 val) __attribute__((aligned(32)));
void func9(reg8 *reg, uint8 val) {
    __ASM(
        "nop\n"         // 10
        "nop\n"         // 9
        "nop\n"         // 8
        "nop\n"         // 7
        "nop\n"         // 6
        "nop\n"         // 5
        "nop\n"         // 4
        "nop\n"         // 3
        "nop\n"         // 2
        "nop\n"         // 1
        ".label_1:\n"
    );
    for (;;) {
        __ASM(
            "nop\n"         // 10
            "nop\n"         // 9
            "nop\n"         // 8
            "nop\n"         // 7
            "nop\n"         // 6
            "nop\n"         // 5
            "nop\n"         // 4
            "nop\n"         // 3
            "nop\n"         // 2
            "nop\n"         // 1
            ".label_2:"
        );
        *reg = val;
    }
}

int main(void) __attribute__((aligned(32)));
int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_1_Start();
    PWM_2_Start();

    for (;;) {
        /* Place your application code here. */
        func9(CR1_Control_PTR, 1u);
    }
}

/* [] END OF FILE */
