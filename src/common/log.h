#ifndef NW_CORE_LOGGER_H
#define NW_CORE_LOGGER_H

#include "type.h"

/**
 *
 *an enum defining the various log levels 
 */
enum nw_log_level{
  NW_LOG_LEVEL_DEBUG = 0, NW_LOG_LEVEL_INFO, NW_LOG_LEVEL_WARNING, NW_LOG_LEVEL_ERROR
};

/**
 *starts the logging subsystem
 *should be called before any call to the other logging functions
 *@param path the path to the log file or NULL for logging in stdout
 *@param min_level any log message with a level less than the minimum will be ignored
 *@param format_buffer_size the size of the format buffer, zero for default
 */
nw_status nw_start_log(const char *path, enum nw_log_level min_level, size_t format_buffer_size);

/**
 *prints a formatted log message
 *@param level the level of this log message
 *@param format the format string
 *@param ... the formatted parameters
 */
void nw_log(enum nw_log_level level, const char *format, ...);

/**
 *prints a formatted log message with log level debug
 *@param format the format string
 *@param ... the formatted parameters
 */
void nw_debug(const char *format, ...);

/**
 *prints a formatted log message with log level info
 *@param format the format string
 *@param ... the formatted parameters
 */
void nw_info(const char *format, ...);

/**
 *prints a formatted log message with log level warning
 *@param format the format string
 *@param ... the formatted parameters
 */
void nw_warning(const char *format, ...);

/**
 *prints a formatted log message with log level error
 *@param format the format string
 *@param ... the formatted parameters
 */
void nw_error(const char *format, ...);


/**
 *stops the logger subsystem
 *should be called after the last log message was printed
 */
void nw_stop_log();

#endif
