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
#include <stdlib.h>

div_t x;

div_t func0(void) {
    x = div(10000, 10);
    return x;
}

void func1(void) __attribute__((aligned(32)));
void func1(void) {
    __ASM(
        "func1_0: nop\n"        // 8
        "func1_1: nop\n"        // 7
        "func1_2: nop\n"        // 6
        "func1_3: nop\n"        // 5
        "func1_4: nop\n"        // 4
        "func1_5: nop\n"        // 3
        "func1_6: nop\n"        // 2
        "func1_7: nop\n"        // 1
        "func1_8:\n"            // 0
    );
}

void func1_0(void);
void func1_1(void);
void func1_2(void);
void func1_3(void);
void func1_4(void);
void func1_5(void);
void func1_6(void);
void func1_7(void);
void func1_8(void);

void func9(reg8 *reg, uint8 val) __attribute__((aligned(32)));
void func9(reg8 *reg, uint8 val) {
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
        func1_0();
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
