#ifndef __STC_INTERRUPT_H__
#define __STC_INTERRUPT_H__

#define IRQ_enable	1
#define IRQ_disable	0

void set_vector_handler(VECTORn_t VECTORn , void pfunc_handler(void));
void Whether_IRQ(VECTORn_t VECTORn , bit able);

#endif //STC_interrupt