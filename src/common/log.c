#include "config.h"
#include "log.h"
#include "thread.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LOG_BUFFER_SIZE 1024

#define LOG_MESSAGE_PREFIX_LENGTH 8

static char log_prefix[4][LOG_MESSAGE_PREFIX_LENGTH+1] = {
  "debug:  ",
  "info:   ",
  "warning:",
  "error:  "
}; 

static FILE *log_file = NULL;

static enum nw_log_level min_log_level;

static char *log_buffer;

static size_t log_buffer_size;

#ifdef NW_HAVE_THREAD

static nw_mutex log_mutex;

#endif

nw_status nw_start_log(const char *path, enum nw_log_level min_level, size_t format_buffer_size){
  
  if(format_buffer_size <= LOG_MESSAGE_PREFIX_LENGTH){
    log_buffer_size = DEFAULT_LOG_BUFFER_SIZE;
  }else{
    log_buffer_size = format_buffer_size;
  }
  log_buffer = malloc(log_buffer_size);
  if(log_buffer == NULL){
    return NW_ALLOC_ERROR;
  }
  
  if(path == NULL){
    log_file = stdout;
  }else{
    FILE *file = fopen(path, "a");
    if(file == NULL){
      free(log_buffer);
      return NW_IO_ERROR;
    }
    log_file = file;
  }

#ifdef NW_HAVE_THREAD

  nw_status status = nw_mutex_create(&log_mutex);
  if(status){
    free(log_buffer);
    if(log_file != stdout){
      fclose(log_file);
    }
    return status;
  }
  
#endif

  min_log_level = min_level;
  return NW_OK;
}

static void do_log(enum nw_log_level level, const char *format, va_list args){
  assert(format != NULL);
  assert(log_file != NULL);
  size_t format_length = strlen(format);
  size_t new_format_length = format_length + LOG_MESSAGE_PREFIX_LENGTH;
  
  if(new_format_length >= log_buffer_size){
    char *tmp_buffer = malloc(new_format_length+1);
    if(tmp_buffer){
      memcpy(tmp_buffer, log_prefix[level], LOG_MESSAGE_PREFIX_LENGTH);
      memcpy(tmp_buffer, format, format_length + 1);

#ifdef NW_HAVE_THREAD

      nw_status status = nw_mutex_lock(&log_mutex);
      if(status){
	free(tmp_buffer);
      }
      
#endif

      vprintf(tmp_buffer, args);
      free(tmp_buffer);
      
#ifdef NW_HAVE_THREAD

      nw_mutex_unlock(&log_mutex);

#endif
      
    }
  }else{

#ifdef NW_HAVE_THREAD

    nw_status status = nw_mutex_lock(&log_mutex);
    if(status == NW_OK){

#endif

      memcpy(log_buffer, log_prefix[level], LOG_MESSAGE_PREFIX_LENGTH);
      memcpy(log_buffer+LOG_MESSAGE_PREFIX_LENGTH, format, format_length + 1);
      vprintf(log_buffer, args);

#ifdef NW_HAVE_THREAD
    
      nw_mutex_unlock(&log_mutex);

    }
    
#endif

  }
}

void nw_log(enum nw_log_level level, const char *format, ...){
  if(min_log_level <= level){
    va_list args;
    va_start(args, format);
    do_log(level, format, args);
    va_end(args);
  }
}


void nw_debug(const char *format, ...){
  if(min_log_level == NW_LOG_LEVEL_DEBUG){
    va_list args;
    va_start(args, format);
    do_log(NW_LOG_LEVEL_DEBUG, format, args);
    va_end(args);
  }
}

void nw_info(const char *format, ...){
  if(min_log_level == NW_LOG_LEVEL_INFO){
    va_list args;
    va_start(args, format);
    do_log(NW_LOG_LEVEL_INFO, format, args);
    va_end(args);
  }
}

void nw_warning(const char *format, ...){
  if(min_log_level == NW_LOG_LEVEL_WARNING){
    va_list args;
    va_start(args, format);
    do_log(NW_LOG_LEVEL_WARNING, format, args);
    va_end(args);
  }
}

void nw_error(const char *format, ...){
  if(min_log_level == NW_LOG_LEVEL_ERROR){
    va_list args;
    va_start(args, format);
    do_log(NW_LOG_LEVEL_ERROR, format, args);
    va_end(args);
  }
}

void nw_stop_log(){
  if(log_file == stdout){
    fflush(log_file);
  }else{
    fclose(log_file);
  }
  log_file = NULL;
}
