#ifndef HMC5883L_H_
#define	HMC5883L_H_

#include <ahrs_hardware.h>

typedef struct 
{
    int16_t x_magnet,
            y_magnet,
            z_magnet;

} hmc5883l_data_t;

hmc5883l_data_t *hmc5883l_get_data_ptr ( void );

int     hmc5883l_init ( i2c_module_t p_i2c, int16_t offset_x, int16_t offset_y );
int     hmc5883l_update_data ( void );

int16_t hmc5883l_get_yaw_angle ( void );
void    hmc5883l_set_continious_operating_mode ( void );
void    hmc5883l_make_calibration ( uint32_t calibration_times );

typedef enum
{
    HMC5883_AVERAGED_SAMPLES_1      = 0b00, // Default
    HMC5883_AVERAGED_SAMPLES_2      = 0b01,
    HMC5883_AVERAGED_SAMPLES_4      = 0b10,
    HMC5883_AVERAGED_SAMPLES_8      = 0b11
} Hmc5883l_avrg_samples_t;

void hmc5883l_set_averaged_samples ( Hmc5883l_avrg_samples_t avrgd_smpls );

typedef enum
{
    HMC5883_OUTPUT_RATE_0_75        = 0b000,  // 0.75 Hz
    HMC5883_OUTPUT_RATE_1_5         = 0b001,  // 1.5 Hz
    HMC5883_OUTPUT_RATE_3           = 0b010,  // 3 Hz
    HMC5883_OUTPUT_RATE_7_5         = 0b011,  // 7.5 Hz - Default
    HMC5883_OUTPUT_RATE_15          = 0b100,  // 15 Hz
    HMC5883_OUTPUT_RATE_30          = 0b101,  // 30 Hz
    HMC5883_OUTPUT_RATE_75          = 0b110   // 75 Hz
} Hmc5883l_output_rate_t;

void hmc5883l_set_output_rate ( Hmc5883l_output_rate_t rate );

typedef enum
{
    HMC5883l_MAGGAIN_0_88           = 0b000,  // +/- 0.88
    HMC5883l_MAGGAIN_1_3            = 0b001,  // +/- 1.3 - Default
    HMC5883l_MAGGAIN_1_9            = 0b010,  // +/- 1.9
    HMC5883l_MAGGAIN_2_5            = 0b011,  // +/- 2.5
    HMC5883l_MAGGAIN_4_0            = 0b100,  // +/- 4.0
    HMC5883l_MAGGAIN_4_7            = 0b101,  // +/- 4.7
    HMC5883l_MAGGAIN_5_6            = 0b110,  // +/- 5.6
    HMC5883l_MAGGAIN_8_1            = 0b111   // +/- 8.1
} Hmc5883l_mag_gain_t;

void hmc5883l_set_magnetic_gain ( Hmc5883l_mag_gain_t gain );

#endif	/* HMC5883L_H_ */

