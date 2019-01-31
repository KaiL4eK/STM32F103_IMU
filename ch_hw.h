#ifndef CH_HW_H_
#define CH_HW_H_

#include <ch.h>
#include <hal.h>
#include <ahrs_hardware.h>

i2c_module_t    i2c_init( I2CDriver *dr );
void            i2c_free( i2c_module_t p_module );

void 			debug_stream_init( void );

#endif /* CH_HW_H_ */
