/*****************************************************************************
* | File        : log.h
* | Author      : Luke Mulder
* | Function    : Debug utilities for logging system events
* | Info        :
*   Provides a flexible logging mechanism to assist in debugging applications.
*   Supports multiple logging levels (ERROR, WARNING, INFO, and NONE) and is
*   capable of logging messages from various modules of the application. The
*   logging function uses printf-style input for ease of use and flexibility.
*   Designed to facilitate easy integration and minimal dependencies.
*   
*   Use cases include:
*     - Tracking and reporting runtime errors
*     - Monitoring application flow and behavior
*     - Diagnostic outputs for development and testing phases
*
*   Ensure to configure the logger according to the target environment and
*   application requirements. This module is adaptable for both development
*   and production builds, with adjustable log levels and output formats.
*----------------
* | This version:   V1.0
* | Date        :   2023-05-24
* | Info        :   Basic version
*   - Initial release includes basic logging functions.
*   - Supports variable argument lists similar to printf for formatted output.
*   - Configurable modules and logging levels.
*   - Basic thread safety and performance considerations addressed.
*   
*   Future enhancements:
*   - Enhanced thread safety features.
*   - Support for logging to external files or systems.
*   - Extended configuration options for runtime adjustments.
*
******************************************************************************/
#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define LOGGING_ENABLED 1

typedef enum {
  ERROR = 0,
  WARNING,
  INFO,
  NONE,
  MAX_LOG_LEVEL
} LogLevel_e;

typedef enum {
  HAL_LCD = 0,
  HAL_SPI,
  HAL_PWM,
  HAL_GPIO,
  DRV_LCD,
  DRV_GUI,
  MAIN,
  MAX_LOG_MODULE
} LogModule_e;

typedef struct {
  LogLevel_e level;
  LogModule_e module;
  char module_name[10];
} LogConfig_t;

const static LogConfig_t logTable[MAX_LOG_MODULE] = {
    {ERROR, HAL_LCD, "HAL_LCD"},
    {WARNING, HAL_SPI, "HAL_SPI"},
    {INFO, HAL_PWM, "HAL_PWM"},
    {NONE, HAL_GPIO, "HAL_GPIO"},
    {ERROR, DRV_LCD, "DRV_LCD"},
    {INFO, DRV_GUI, "DRV_GUI"},
    {INFO, MAIN, "MAIN"}
};

// Static assert to ensure the logTable size matches the number of LogModule_e entries (minus 1 for MAX_LOG_MODULE)
_Static_assert((sizeof(logTable) / sizeof(logTable[0])) == (MAX_LOG_MODULE), "Number of logTable entries does not match number of LogModule_e entries");

void logging(const char *file, int line, const char *func, LogModule_e module, const char *log_str, ...) {
    va_list args;
    va_start(args, log_str);

    printf("[%s] %s:%d %s() - ", logTable[module].module_name, file, line, func);
    vprintf(log_str, args);
    va_end(args);
    printf("\n");
}

#ifdef LOGGING_ENABLED
  #define LOG(module, log_str, ...) logging(__FILE__, __LINE__, __func__, module, log_str, ##__VA_ARGS__)
#else // LOGGING_ENABLED
  #define LOG(module, log_str, ...)
#endif // LOGGING_ENABLED

#endif // _LOGGING_H_