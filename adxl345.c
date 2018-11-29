#include <i2c_interface.h>

i2c_module_t m_i2c = NULL;

#define ADXL345_ADDR    0x53

int adxl345_init( i2c_module_t p_i2c )
{
    m_i2c = p_i2c;

    return EOK;
}

uint8_t adxl345_get_self_id( void )
{
    if ( !m_i2c )
        return 0;

    uint8_t data[2];

    i2c_read_bytes( m_i2c, ADXL345_ADDR, 0x00, 2, data );

    if ( i2c_get_errno( m_i2c ) != EOK )
    {
        return 0;
    }

    return data[0];
}
