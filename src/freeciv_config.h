/* gen_headers/freeciv_config.h.  Generated from freeciv_config.h.in by configure.  */
/**********************************************************************
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

/* This header is generated from gen_headers/freeciv_config.h.in.
 * It contains values to specific freeciv build, but only such
 * values that should not conflict with configuration headers from
 * other autotools projects. This is meant to be usable for external
 * projects building against some freeciv components. */

#ifndef FC__FREECIV_CONFIG_H
#define FC__FREECIV_CONFIG_H

/* Is this freeciv-web instead of regular build */
/* #undef FREECIV_WEB */

/* Testmatic integration enabled */
/* #undef FREECIV_TESTMATIC */

/* Metaserver URL */
#define FREECIV_META_URL "http://meta.freeciv.org/metaserver.php"

/* Month next version will be released */
#define FREECIV_RELEASE_MONTH 0

/* Use pthreads as thread implementation */
#define FREECIV_HAVE_PTHREAD 1

/* Use Windows threads as thread implementation */
/* #undef FREECIV_HAVE_WINTHREADS */

/* Has thread condition variable implementation */
#define FREECIV_HAVE_THREAD_COND 1

/* Build xml-backend for registry */
/* #undef FREECIV_HAVE_XML_REGISTRY */

/* Native language support enabled */
/* #undef FREECIV_ENABLE_NLS */

/* locale.h available */
#define FREECIV_HAVE_LOCALE_H 1

/* libintl.h available */
#define FREECIV_HAVE_LIBINTL_H 1

/* inttypes.h available */
#define FREECIV_HAVE_INTTYPES_H 1

/* stdint.h available */
#define FREECIV_HAVE_STDINT_H 1

/* ws2tcpip.h available */
/* #undef FREECIV_HAVE_WS2TCPIP_H */

/* sys/types.h available */
#define FREECIV_HAVE_SYS_TYPES_H 1

/* unistd.h available */
#define FREECIV_HAVE_UNISTD_H 1

/* sys/time.h available */
#define FREECIV_HAVE_SYS_TIME_H 1

/* sys/socket.h available */
#define FREECIV_HAVE_SYS_SOCKET_H 1

/* sys/select.h available */
#define FREECIV_HAVE_SYS_SELECT_H 1

/* netinet/in.h available */
#define FREECIV_HAVE_NETINET_IN_H 1

/* Have standard compliant stdbool.h */
#define FREECIV_HAVE_STDBOOL_H 1

/* Readline support */
/* #undef FREECIV_HAVE_LIBREADLINE */

/* Have socklen_t type defined */
#define FREECIV_HAVE_SOCKLEN_T 1

/* jansson network protocol in use */
/* #undef FREECIV_JSON_CONNECTION */

/* Windows build */
/* #undef FREECIV_MSWINDOWS */

/* uses some winsock version */
/* #undef FREECIV_HAVE_WINSOCK */

/* uses winsock2 */
/* #undef FREECIV_HAVE_WINSOCK2 */

/* socket zero isn't same stdin */
/* #undef FREECIV_SOCKET_ZERO_NOT_STDIN */

/* Extra debugging support */
/* #undef FREECIV_DEBUG */

/* No freeciv specific debugging support at all */
/* #undef FREECIV_NDEBUG */

/* zlib is available */
#define FREECIV_HAVE_LIBZ 1

/* libbzip2 is available */
/* #undef FREECIV_HAVE_LIBBZ2 */

/* liblzma is available */
/* #undef FREECIV_HAVE_LIBLZMA */

/* IPv6 Support built in */
#define FREECIV_IPV6_SUPPORT 1

/* Max number of AI modules */
#define FREECIV_AI_MOD_LAST (0+1)

/* C11 static assert supported */
#define FREECIV_C11_STATIC_ASSERT 1

/* C++11 static assert supported */
#define FREECIV_CXX11_STATIC_ASSERT 1

#endif /* FC__FREECIV_CONFIG_H */
