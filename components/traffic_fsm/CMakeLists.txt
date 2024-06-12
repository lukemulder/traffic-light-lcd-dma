idf_component_register(SRCS "traffic_fsm.c"
                    INCLUDE_DIRS "include"
                    REQUIRES gui hal_lcd hal_button esp_timer logging)