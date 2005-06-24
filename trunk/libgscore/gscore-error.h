#ifndef _LIBGSCORE_GSCORE_ERROR_H
#define _LIBGSCORE_GSCORE_ERROR_H

#ifdef __cplusplus
  extern "C" {
#endif

typedef enum {
        GSCORE_ERROR_UNKNOWN = 0,
        GSCORE_ERROR_MEMORY = 1
} gscore_error_t;

gscore_error_t GSCORE_ERROR;

#ifdef __cplusplus
  }
#endif


#endif
