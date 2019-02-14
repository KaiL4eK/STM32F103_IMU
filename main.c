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
    float x_value;
    float y_value;
    float z_value;


    float x_bias =13.583052;
    float y_bias =-6.090640;
    float z_bias =-56.473310;

    double bias[3] =
    {
     13.583052,
     -6.090640,
     -56.473310
    };

    double calibration_matrix[3][3]=
    {
     {1.009434, 0.000136, -0.076213},
     {0.000136, 1.014606, -0.069870},
     {-0.076213, -0.069870, 0.963730}
    };

    float uncalibrated_values[3] = {0,0,0};
//
//
    float calibrated_values[3] = {0,0,0};
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
    int value = 0;

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
        x_value = (float)hmc_5883->x_magnet;
        y_value = (float)hmc_5883->y_magnet;
        z_value = (float)hmc_5883->z_magnet;

//        float calib_x = x_value - x_bias;
//        float calib_y = y_value - y_bias;

        uncalibrated_values[0] =x_value;
        uncalibrated_values[1] =y_value;
        uncalibrated_values[2] =z_value;


        for (int i=0; i<3; ++i) uncalibrated_values[i] = uncalibrated_values[i] - bias[i];
        float result[3] = {0, 0, 0};

        for (int i=0; i<3; ++i)
          {
            for (int j=0; j<3; ++j)
            {
              result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
            }
          }

        for (int i=0; i<3; ++i) calibrated_values[i] = result[i];

        angle = atan2((double)calibrated_values[1],(double)calibrated_values[0]);

        if(x_value<0)
        {
          value = 180-angle*180/3,14159265;
        }

        else if(x_value>0)
        {
          if(y_value<0)
          {
            value = angle*180/3,14159265;
          }
          else
          {
            value = 360-angle*180/3,14159265;
          }
        }
        else
        {
          if(y_value<0) value = 90;
          else value = 270;
        }

        dbgprintf( "value %d\n",(int)value );
        msg = sdReadTimeout( comm_dr, rcv_buffer, rcv_bytes, MS2ST( 10 ) );

//        dbgprintf( "%d\t",(int)y_value );
//        dbgprintf( "%d\n",(int)z_value );

//        dbgprintf( "111x_value %d\n",(int)calib_x );
//        dbgprintf( "111y_value %d\n",(int)calib_y );
//
////
//        dbgprintf( "angle1_hmc5883: %d\n",(int)angle );



    }
}
