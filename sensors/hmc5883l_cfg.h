#ifndef HMC5883L_CFG_H_
#define HMC5883L_CFG_H_

#define HMC5883_ADDRESS                            0x1E

/* Data types */

typedef union
{
    struct
    {
        uint8_t x_mag_h,
                x_mag_l,
                z_mag_h,
                z_mag_l,
                y_mag_h,
                y_mag_l;

    } reg;
    struct
    {
        int16_t x_magnet,
                z_magnet,
                y_magnet;
    } value;
} mag_raw_data_t;

/*  EEPROM registers */

#define HMC5883_REGISTER_MAG_CRA_REG_M             0x00
#define HMC5883_REGISTER_MAG_CRB_REG_M             0x01
#define HMC5883_REGISTER_MAG_MR_REG_M              0x02
#define HMC5883_REGISTER_MAG_OUT_X_H_M             0x03
#define HMC5883_REGISTER_MAG_OUT_X_L_M             0x04
#define HMC5883_REGISTER_MAG_OUT_Z_H_M             0x05
#define HMC5883_REGISTER_MAG_OUT_Z_L_M             0x06
#define HMC5883_REGISTER_MAG_OUT_Y_H_M             0x07
#define HMC5883_REGISTER_MAG_OUT_Y_L_M             0x08
#define HMC5883_REGISTER_MAG_SR_REG_Mg             0x09
#define HMC5883_REGISTER_MAG_IRA_REG_M             0x0A
#define HMC5883_REGISTER_MAG_IRB_REG_M             0x0B
#define HMC5883_REGISTER_MAG_IRC_REG_M             0x0C
#define HMC5883_REGISTER_MAG_TEMP_OUT_H_M          0x31
#define HMC5883_REGISTER_MAG_TEMP_OUT_L_M          0x32


#define GAIN_MULTIPLYER             100L
#define INIT_CALIBRATION_SAMPLES    100

#define MATH_MULTIPLYER             1000L

/* Configuration register A */

#define HMC5883_AVERAGED_SAMPLES_BIT            6
#define HMC5883_AVERAGED_SAMPLES_LENGTH         2
    
#define HMC5883_OUTPUT_RATE_BIT                 4
#define HMC5883_OUTPUT_RATE_LENGTH              3

#define HMC5883_MEASUREMENT_MODE_BIT            1
#define HMC5883_MEASUREMENT_MODE_LENGTH         2

#define HMC5883_MEASUREMENT_MODE_NORMAL         0b00

#define HMC5883_OPERATING_MODE_CONTINIOUS       0b00 ///fix this

/* Configuration register B */

#define HMC5883_GAIN_CONFIGURATION_LSb          5

#endif /* HMC5883L_CFG_H_ */
