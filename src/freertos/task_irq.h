#ifndef TASK_IRQ_H
#define TASK_IRQ_H 

void irq_task(uint gpio, uint32_t events);

void isr_test_task(void);

void launch_isr_test_task(void);

#define RF_DIO1 15

#endif // TASK_IRQ_H