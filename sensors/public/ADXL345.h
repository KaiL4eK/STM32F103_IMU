#ifndef ADXL345_H_
#define ADXL345_H_

#include <ahrs_hardware.h>

int 	adxl345_init( i2c_module_t p_i2c );
uint8_t adxl345_get_self_id( void );

#endif /* ADXL345_H_ */
