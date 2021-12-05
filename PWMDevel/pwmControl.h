#include <io.h>
#include "generalFunctions.h"

void pwm_init_timer0_A();
void pwm_init_timer2_B();
void runMotor(long percentMaxPower, const char* motorID, const char* direction);