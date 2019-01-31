#include <ch_hw.h>
#include <ADXL345.h>
#include <HMC5883L.h>

i2c_module_t            imu_mod     = NULL;

int main(void)
{
    /* RT Core initialization */
    chSysInit();
    /* HAL (Hardware Abstraction Layer) initialization */
    halInit();

    debug_stream_init();

    /* For LED control */
    palSetPadMode( GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL );

    /* Setup I2CD1 pins */
    palSetPadMode( GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
    palSetPadMode( GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

    imu_mod = i2c_init( &I2CD1 );

    adxl345_init( imu_mod );
    hmc5883l_init( imu_mod, 0, 0 );

    while (true)
    {
        uint8_t id = adxl345_get_self_id();

        dbgprintf( "ID: %x\n", id );

        palTogglePad( GPIOC, 13 );
        chThdSleepMilliseconds( 500 );
    }
}
