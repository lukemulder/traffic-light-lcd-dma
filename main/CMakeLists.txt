idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES hal_button traffic_fsm hal_lcd hal_spi hal_pwm lib log driver gui)