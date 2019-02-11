#include <ch_hw.h>
#include <ADXL345.h>
#include <HMC5883L.h>
#include <math.h>
#include <stdio.h>

i2c_module_t            imu_mod     = NULL;

int main(void)
{
    /* RT Core initialization */
    chSysInit();
    /* HAL (Hardware Abstraction Layer) initialization */
    halInit();
    float angle = 0;
    float angle1 = 0;
    debug_stream_init();
    int x_in;
    int y_in;
    int16_t x_value;
    int16_t y_value;
    int16_t z_value;


    float x_bias =25.666091;
    float y_bias =45.694381;
    float z_bias =19.796037;

    //float x_scale = 1.1158392;
    //float y_scale = 0.8961;





    /* For LED control */
    palSetPadMode( GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL );

    /* Setup I2CD1 pins */
    palSetPadMode( GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
    palSetPadMode( GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

    imu_mod = i2c_init( &I2CD1 );

//    adxl345_init( imu_mod );
    hmc5883l_init( imu_mod, 0, 0 );

    hmc5883l_data_t *hmc_5883 = hmc5883l_get_data_ptr();

    x_value = hmc_5883->x_magnet;
    y_value = hmc_5883->y_magnet;
    z_value = hmc_5883->z_magnet;

//    uint8_t Reg_A_conf = hmc5883_get_reg( 0x00 );
//    uint8_t Reg_B_conf = hmc5883_get_reg( 0x01 );
//    uint8_t Reg_mode = hmc5883_get_reg( 0x02 );


    while (true)
    {



        hmc5883l_update_data();
//        uint8_t id = adxl345_get_self_id();
//        uint8_t Reg_A = hmc5883_get_reg( 0x0A );
//        uint8_t Reg_B = hmc5883_get_reg( 0x0B );
//        uint8_t Reg_C = hmc5883_get_reg( 0x0C );
//
        uint8_t Reg_A_conf = hmc5883_get_reg( 0x00 );
        uint8_t Reg_B_conf = hmc5883_get_reg( 0x01 );
        uint8_t Reg_mode = hmc5883_get_reg( 0x02 );

//        uint8_t Reg_data_test1 = hmc5883_get_reg( 0x06 );
//        uint8_t Reg_data_test2 = hmc5883_get_reg( 0x03 );

//        if(x_value == hmc_5883->x_magnet ||y_value == hmc_5883->y_magnet ||z_value == hmc_5883->z_magnet)
//        {
//          palTogglePad( GPIOC, 13 );
//        }

        chThdSleepMilliseconds( 500 );
        x_value = hmc_5883->x_magnet;
        y_value = hmc_5883->y_magnet;
        z_value = hmc_5883->z_magnet;

        float x=x_value - x_bias;
        float y=y_value - y_bias;

        //x = x * x_scale;
        //y = y * y_scale;


        angle = atan2((double)y,(double)x);
        angle = angle * 180/3.14159265;
        angle = angle +180;



//        dbgprintf( "ID_adxl345: %x\n", id );
//        dbgprintf( "Reg_A_hmc5883: %x\n", Reg_A );
//        dbgprintf( "Reg_B_hmc5883: %x\n", Reg_B );
//        dbgprintf( "Reg_C_hmc5883: %x\n", Reg_C );

        dbgprintf( "x_value_hmc5883: %d\n", x_value );
        dbgprintf( "y_value_hmc5883: %d\n", y_value );
        dbgprintf( "z_value_hmc5883: %d\n", z_value );

        dbgprintf( "Reg_A_conf_hmc5883: %x\n", Reg_A_conf );
        dbgprintf( "Reg_B_conf_hmc5883: %x\n", Reg_B_conf );
        dbgprintf( "Reg_mode_hmc5883: %x\n", Reg_mode );



        dbgprintf( "angle1_hmc5883: %d\n", (int)angle );
        //dbgprintf( "angle_hmc5883: %d\n", y );
//
//        dbgprintf( "Reg_data_test1: %x\n", Reg_data_test1 );
//        dbgprintf( "Reg_data_test2: %x\n", Reg_data_test2 );


    }
}
