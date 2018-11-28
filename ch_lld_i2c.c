#include <i2c_interface.h>

#include <string.h>
#include <hal.h>

/*** System dependent module ***/

extern BaseSequentialStream    *debug_str;

#define delay_ms(x) (chThdSleepMilliseconds((x)))

int i2c_get_errno( i2c_module_t p_module )
{
    int32_t err = 0;

    if ( (err = i2cGetErrors( p_module )) != I2C_NO_ERROR )
    {
        return EFAULT;
    }

    return EOK;
}

i2c_module_t i2c_init( I2CDriver *dr )
{
    return dr;
}

void i2c_free( void )
{

}

int i2c_write_bytes( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t size, uint8_t *data )
{
    if ( size == 0 )
        return EOK;

    static uint8_t  tx_buffer[32];

    if ( size > sizeof( tx_buffer ) - 1 )
        return EINVAL;

    /* Set eeprom address and data to write */
    tx_buffer[0] = reg_addr;
    memcpy( &tx_buffer[1], data, size );

    i2cAcquireBus( p_module );
    msg_t msg = i2cMasterTransmitTimeout( p_module, i2c_address, tx_buffer, size + 1, NULL, 0, MS2ST(I2C_TIMEOUT_MS) );
    i2cReleaseBus( p_module );

    if ( msg != MSG_OK )
        return EFAULT;

    return EOK;
}

int i2c_read_bytes( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t size, uint8_t *data )
{
    if ( size == 0 )
        return EOK;

    i2cAcquireBus( p_module );
    msg_t msg = i2cMasterTransmitTimeout( p_module, i2c_address, &reg_addr, 1, data, size, MS2ST(I2C_TIMEOUT_MS) );
    i2cReleaseBus( p_module );
    chprintf( debug_str, "Err %x\n", msg );
    if ( msg != MSG_OK )
        return EFAULT;

    return EOK;
}

int i2c_write_byte( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t data )
{
    return i2c_write_bytes( p_module, i2c_address, reg_addr, 1, &data );
}

int i2c_write_word  ( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint16_t data )
{
    uint8_t arr[]   = { data >> 8   & 0xFF,
                        data        & 0xFF };

    return i2c_write_bytes( p_module, i2c_address, reg_addr, 2, arr );
}

uint8_t i2c_read_byte( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr )
{
    uint8_t data;
    if ( i2c_read_bytes( p_module, i2c_address, reg_addr, 1, &data ) != EOK )
    {
        return 0;
    }

    return data;
}

int i2c_write_bits( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t length, uint8_t data )
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t data_reg    = i2c_read_byte( p_module, i2c_address, reg_addr ),
            data_write  = data;

    if ( i2c_get_errno( p_module ) != EOK )
        return EFAULT;

    uint8_t mask = ((1 << length) - 1) << (bit_start - length + 1);
    data_write <<= (bit_start - length + 1); // shift data into correct position
    data_write &= mask; // zero all non-important bits in data
    data_reg &= ~(mask); // zero all important bits in existing byte
    data_reg |= data_write; // combine data with existing byte

    if ( i2c_write_byte( p_module, i2c_address, reg_addr, data_reg ) != EOK )
        return EFAULT;

    return EOK;
}

int i2c_write_bit( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t data )
{
    return i2c_write_bits( p_module, i2c_address, reg_addr, bit_start, 1, data );
}

uint8_t i2c_read_bits( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start, uint8_t length )
{
    if ( !length )
        return EOK;

    uint8_t mask = (1 << length) - 1;
    uint8_t result = (i2c_read_byte( p_module, i2c_address, reg_addr ) >> (bit_start - length + 1)) & mask;

    if ( i2c_get_errno( p_module ) != EOK )
        return 0;

    return result;
}

uint8_t i2c_read_bit( i2c_module_t p_module, uint8_t i2c_address, uint8_t reg_addr, uint8_t bit_start )
{
    uint8_t result = (i2c_read_byte( p_module, i2c_address, reg_addr ) >> bit_start) & 0x1;

    if ( i2c_get_errno( p_module ) != EOK )
        return 0;

    return result;
}
