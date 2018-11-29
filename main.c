#include <ch.h>
#include <hal.h>

#include <chprintf.h>

#include <usbcfg.h>

#include <i2c_interface.h>

i2c_module_t    i2c_init ( I2CDriver *dr );
void            i2c_free ( void );

static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

I2CDriver               *imu_bus    = &I2CD1;
i2c_module_t            imu_mod     = NULL;
BaseSequentialStream    *debug_str  = (BaseSequentialStream *)&SDU1;

int adxl345_init( i2c_module_t p_i2c );
uint8_t adxl345_get_self_id( void );

static THD_WORKING_AREA(waReceiverIMU, 128);
static THD_FUNCTION(ReceiverIMU, arg) 
{
    arg = arg;

    while (true)
    {
        chThdSleepMilliseconds(100);
    }
}

int main(void)
{
    /* RT Core initialization */
    chSysInit();
    /* HAL (Hardware Abstraction Layer) initialization */
    halInit();

    sduObjectInit( &SDU1 );
    sduStart( &SDU1, &serusbcfg );

    usbDisconnectBus( serusbcfg.usbp );
    chThdSleepMilliseconds( 1500 );
    usbStart( serusbcfg.usbp, &usbcfg );
    usbConnectBus( serusbcfg.usbp );

    palSetPadMode( GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL );

    /* Init I2C */
    i2cStart( imu_bus, &i2cfg1 );

    palSetPadMode( GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
    palSetPadMode( GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

    imu_mod = i2c_init( imu_bus );

    adxl345_init( imu_mod );

    while (true)
    {
        palTogglePad( GPIOC, 13 );
        uint8_t id = adxl345_get_self_id();

        chprintf( debug_str, "ID: %x\n", id );

        chThdSleepMilliseconds( 500 );
    }
}
