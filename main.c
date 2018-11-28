#include <ch.h>
#include <hal.h>

#include <chprintf.h>

#include <usbcfg.h>

static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

I2CDriver               *imu_bus    = &I2CD1;
i2c_module_t            *imu_mod    = NULL;
BaseSequentialStream    *debug_str  = (BaseSequentialStream *)&SDU1;

static THD_WORKING_AREA(waReceiverIMU, 128);
static THD_FUNCTION(ReceiverIMU, arg) 
{
    arg = arg;

    /* Init I2C */
    i2cStart(imu_bus, &i2cfg1);

    imu_mod = i2c_init( imu_bus );

    while (true)
    {
        chThdSleepSeconds(1);
    }
}

int main(void)
{
    /* RT Core initialization */
    chSysInit();
    /* HAL (Hardware Abstraction Layer) initialization */
    halInit();

//    chThdCreateStatic(waReceiverIMU, sizeof(waReceiverIMU), NORMALPRIO, ReceiverIMU, NULL /* arg is NULL */);

    sduObjectInit( &SDU1 );
    sduStart( &SDU1, &serusbcfg );

    usbDisconnectBus( serusbcfg.usbp );
    chThdSleepMilliseconds( 1500 );
    usbStart( serusbcfg.usbp, &usbcfg );
    usbConnectBus( serusbcfg.usbp );

    palSetPadMode( GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL );

    while (true)
    {
        chprintf( debug_str, "Hello\n" );

        palTogglePad( GPIOC, 13 );

        chThdSleepSeconds(1);
    }
}
