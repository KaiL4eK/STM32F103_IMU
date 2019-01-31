#ifndef AHRS_HARDWARE_H_
#define AHRS_HARDWARE_H_

/*** common libc headers ***/
#include <errno.h>
#include <stdint.h>

#define SWAP( x, y ) { uint8_t tmp = x; x = y; y = tmp; }

/*** Error codes that are not included in errno.h ***/

#ifndef EOK
  #define EOK       100
#endif

#ifndef ETIMEOUT
  #define ETIMEOUT  101
#endif

/* Debug printf */
void dbgprintf( const char* format, ... );

/*** The interface is used by I2C communication modules ***/

#define I2C_TIMEOUT_MS  10

typedef void *  i2c_module_t;

int         i2c_get_errno   ( i2c_module_t p_module );

uint8_t     i2c_read_byte   ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr );
int         i2c_read_bytes  ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t size, uint8_t *data);
int         i2c_write_bytes ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t size, uint8_t *data );
int         i2c_write_byte  ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t data );
int         i2c_write_word  ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint16_t data );

uint8_t     i2c_read_bit    ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start );
uint8_t     i2c_read_bits   ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t length );
int         i2c_write_bit   ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t data );
int         i2c_write_bits  ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t length, uint8_t data );


void 		delay_ms( uint32_t msec );

#endif /* AHRS_HARDWARE_H_ */
