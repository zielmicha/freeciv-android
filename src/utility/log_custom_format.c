/********************************************************************** 
 Freeciv-Android
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif /* HAVE_CONFIG_H */

#include <time.h>
#include <string.h>
#include <errno.h>

/* utility */
#include "log.h"
#include "shared.h"

#ifdef CUSTOM_LOG_FORMAT_ACTIVE

static log_pre_callback_fn wrapped_log_function = NULL;

static void custom_log(enum log_level level, bool print_from_where,
                          const char *where, const char *msg);
#endif /* CUSTOM_LOG_FORMAT_ACTIVE */

void custom_log_init(void)
{
#ifdef CUSTOM_LOG_FORMAT_ACTIVE
  wrapped_log_function = log_set_pre_callback(custom_log);
#endif
}

#ifdef CUSTOM_LOG_FORMAT_ACTIVE

static void fc_vsnprintf_va_arg(char *string, size_t n, char *format, ...) {
  va_list ap;
  va_start(ap, format);
  fc_vsnprintf(string, n, format, ap);
  va_end(ap);
}

static void custom_log(enum log_level level, bool print_from_where,
                          const char *where, const char *msg) {
  char custom_log_str[256];
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  struct tm *tm_info = localtime(&spec.tv_sec);
  if (tm_info) {
    strftime(custom_log_str, sizeof(custom_log_str), "%b %d %H:%M:%S.", tm_info);
    fc_vsnprintf_va_arg(&custom_log_str[strlen(custom_log_str)], sizeof(custom_log_str) - strlen(custom_log_str), "%03ld ", spec.tv_nsec / 1000000);
  } else {
    fc_vsnprintf_va_arg(custom_log_str, sizeof(custom_log_str), "%s", strerror(errno));
  }
  wrapped_log_function(level, print_from_where, custom_log_str, msg);
}

#endif /* CUSTOM_LOG_FORMAT_ACTIVE */
