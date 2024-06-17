/*****************************************************************************
* | File        : logging.h
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
* | Date        :   2024-05-24
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
  NONE = 0,
  ERROR,
  WARNING,
  INFO,
  MAX_LOG_LEVEL
} LogLevel_e;

// Define string representations for log levels
#define NONE_STR    "NONE"
#define ERROR_STR   "ERROR"
#define WARNING_STR "WARNING"
#define INFO_STR    "INFO"

// LOG LEVELS
// Place these levels in your c file to specify the log level you wish to set
// (From least to most verbose)
// #define LOG_LEVEL_NONE
// #define LOG_LEVEL_ERROR
// #define LOG_LEVEL_WARNING
// #define LOG_LEVEL_INFO

#define LOG_LEVEL_SETTING_NONE    0
#define LOG_LEVEL_SETTING_ERROR   1
#define LOG_LEVEL_SETTING_WARNING 2
#define LOG_LEVEL_SETTING_INFO    3

#ifdef LOG_LEVEL_NONE
  #define LOG_LEVEL LOG_LEVEL_SETTING_NONE
#endif
#ifdef LOG_LEVEL_ERROR
  #define LOG_LEVEL LOG_LEVEL_SETTING_ERROR
#endif
#ifdef LOG_LEVEL_WARNING
  #define LOG_LEVEL LOG_LEVEL_SETTING_WARNING
#endif
#ifdef LOG_LEVEL_INFO
  #define LOG_LEVEL LOG_LEVEL_SETTING_INFO
#endif

void logging(const char *file, int line, const char *func, LogLevel_e level, const char *log_str, ...);

#ifdef LOGGING_ENABLED
  #if LOG_LEVEL >= LOG_LEVEL_SETTING_ERROR
    #define LOG_ERROR(log_str, ...) logging(__FILE__, __LINE__, __func__, ERROR, log_str, ##__VA_ARGS__)
  #else
    #define LOG_ERROR(log_str, ...)
  #endif

  #if LOG_LEVEL >= LOG_LEVEL_SETTING_WARNING
    #define LOG_WARNING(log_str, ...) logging(__FILE__, __LINE__, __func__, WARNING, log_str, ##__VA_ARGS__)
  #else
    #define LOG_WARNING(log_str, ...)
  #endif

  #if LOG_LEVEL >= LOG_LEVEL_SETTING_INFO
    #define LOG_INFO(log_str, ...) logging(__FILE__, __LINE__, __func__, INFO, log_str, ##__VA_ARGS__)
  #else
    #define LOG_INFO(log_str, ...)
  #endif
#else // LOGGING_ENABLED
  #define LOG_ERROR(log_str, ...)
  #define LOG_WARNING(log_str, ...)
  #define LOG_INFO(log_str, ...)
#endif // LOGGING_ENABLED

#endif // _LOGGING_H_