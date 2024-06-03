idf_component_register(SRCS "hal_lcd.c"
                    INCLUDE_DIRS "include"
                    REQUIRES hal_spi hal_pwm logging)
