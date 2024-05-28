idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES hal_lcd hal_spi hal_pwm drv lib log driver)