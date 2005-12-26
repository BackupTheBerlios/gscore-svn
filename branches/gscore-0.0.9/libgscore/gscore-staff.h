#ifndef _LIBGSCORE_GSCORE_STAFF_H
#define _LIBGSCORE_GSCORE_STAFF_H

#include "gscore-error.h"

#ifdef __cplusplus
  extern "C" {
#endif

GSCORE_ERROR gscore_staff_new(Staff_t **staff);
GSCORE_ERROR gscore_staff_set_time_signature(Staff_t *staff, guint8 time_signature[2]);
GSCORE_ERROR gscore_staff_prepend(Score_t *score, Staff_t *staff);
GSCORE_ERROR gscore_staff_append(Score_t *score, Staff_t *staff);

#ifdef __cplusplus
  }
#endif


#endif
