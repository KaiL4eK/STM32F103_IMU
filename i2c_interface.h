#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include <errno.h>
#include <stdint.h>

/*** The interface is used by I2C communication modules ***/

#define I2C_TIMEOUT_MS  10

typedef void *  i2c_module_t;

#ifndef EOK
  #define EOK       100
#endif

#ifndef ETIMEOUT
  #define ETIMEOUT  101
#endif

i2c_module_t    i2c_init ( I2CDriver *dr );
void            i2c_free ( void );

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


#endif // I2C_INTERFACE_H_