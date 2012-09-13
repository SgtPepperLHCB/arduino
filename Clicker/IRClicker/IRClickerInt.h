#ifndef __IRCLICKERINT_H__
#define __IRCLICKERINT_H__

#ifdef F_CPU
#define SYSCLOCK F_CPU     // main Arduino clock
#else

enum {
  SYSCLOCK = 16000000
} ; // main Arduino clock
#endif

enum {
  TIMER_PWM_PIN = 3
} ;

enum {
  TOPBIT = 0x80000000
} ;

// Timer 2 defines
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR2A |= _BV(COM2B1))
#define TIMER_DISABLE_PWM    (TCCR2A &= ~(_BV(COM2B1)))
#define TIMER_ENABLE_INTR    (TIMSK2 = _BV(OCIE2A))
#define TIMER_DISABLE_INTR   (TIMSK2 = 0)
#define TIMER_INTR_NAME      TIMER2_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint8_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR2A = _BV(WGM20); \
  TCCR2B = _BV(WGM22) | _BV(CS20); \
  OCR2A = pwmval; \
  OCR2B = pwmval / 3; \
})

#endif
