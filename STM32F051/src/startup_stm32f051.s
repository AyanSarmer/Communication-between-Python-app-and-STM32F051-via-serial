  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

.equ  BootRAM, 0xF108F85F
  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/*Check if boot space corresponds to test memory*/
 
    LDR R0,=0x00000004
    LDR R1, [R0]
    LSRS R1, R1, #24
    LDR R2,=0x1F
    CMP R1, R2
    BNE ApplicationStart

 /*SYSCFG clock enable*/

    LDR R0,=0x40021018
    LDR R1,=0x00000001
    STR R1, [R0]

/*Set CFGR1 register with flash memory remap at address 0*/
    LDR R0,=0x40010000
    LDR R1,=0x00000000
    STR R1, [R0]

ApplicationStart:
/* Copy the data segment initializers from flash to SRAM */
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs r3, #0
  str  r3, [r2]
  adds r2, r2, #4


LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call the clock system intitialization function.*/
    bl  SystemInit
    
/* Call the application's entry point.*/
  bl main
  
LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word _estack
  .word Reset_Handler

  .word NMI_Handler
  .word HardFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word 0
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler


  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word RTC_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_1_IRQHandler
  .word EXTI2_3_IRQHandler
  .word EXTI4_15_IRQHandler
  .word TS_IRQHandler
  .word DMA1_Channel1_IRQHandler
  .word DMA1_Channel2_3_IRQHandler
  .word DMA1_Channel4_5_IRQHandler
  .word ADC1_COMP_IRQHandler 
  .word TIM1_BRK_UP_TRG_COM_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM6_DAC_IRQHandler
  .word 0  
  .word TIM14_IRQHandler
  .word TIM15_IRQHandler
  .word TIM16_IRQHandler
  .word TIM17_IRQHandler
  .word I2C1_IRQHandler
  .word I2C2_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word 0
  .word CEC_IRQHandler
  .word 0
  .word BootRAM          

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Default_Handler

  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler
  
  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler
  
  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler
  
  .weak RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler
  
  .weak EXTI0_1_IRQHandler
  .thumb_set EXTI0_1_IRQHandler,Default_Handler
  
  .weak EXTI2_3_IRQHandler
  .thumb_set EXTI2_3_IRQHandler,Default_Handler
  
  .weak EXTI4_15_IRQHandler
  .thumb_set EXTI4_15_IRQHandler,Default_Handler
  
  .weak TS_IRQHandler
  .thumb_set TS_IRQHandler,Default_Handler
  
  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler
  
  .weak DMA1_Channel2_3_IRQHandler
  .thumb_set DMA1_Channel2_3_IRQHandler,Default_Handler
  
  .weak DMA1_Channel4_5_IRQHandler
  .thumb_set DMA1_Channel4_5_IRQHandler,Default_Handler
  
  .weak ADC1_COMP_IRQHandler
  .thumb_set ADC1_COMP_IRQHandler,Default_Handler
   
  .weak TIM1_BRK_UP_TRG_COM_IRQHandler
  .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler
  
  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Default_Handler
  
  .weak TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Default_Handler
  
  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Default_Handler
  
  .weak TIM6_DAC_IRQHandler
  .thumb_set TIM6_DAC_IRQHandler,Default_Handler
  
  .weak TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,Default_Handler
  
  .weak TIM15_IRQHandler
  .thumb_set TIM15_IRQHandler,Default_Handler
  
  .weak TIM16_IRQHandler
  .thumb_set TIM16_IRQHandler,Default_Handler
  
  .weak TIM17_IRQHandler
  .thumb_set TIM17_IRQHandler,Default_Handler
  
  .weak I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Default_Handler
  
  .weak I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,Default_Handler
  
  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler
  
  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler
  
  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler
  
  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler
  
  .weak CEC_IRQHandler
  .thumb_set CEC_IRQHandler,Default_Handler