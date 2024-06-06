# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(traffic-light-lcd-dma)

# Ensure that the paths to the components include their respective directories
set(EXTRA_COMPONENT_DIRS "hal_lcd" "hal_pwm" "hal_spi" "lib" "gui")