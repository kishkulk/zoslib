///////////////////////////////////////////////////////////////////////////////
// Licensed Materials - Property of IBM
// ZOSLIB
// (C) Copyright IBM Corp. 2020. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication
// or disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
///////////////////////////////////////////////////////////////////////////////

// APIs that implement various I/O operations.

#ifndef ZOS_IO_H_
#define ZOS_IO_H_

#include "zos-macros.h"

#include <stdarg.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TRACE_ON
/**
 * Prints information about a file descriptor.
 * \param [in] fd file descriptor.
 */
__Z_EXPORT void __fdinfo(int fd);

__Z_EXPORT void __perror(const char *str);
__Z_EXPORT int __dpoll(void *array, unsigned int count, int timeout);
__Z_EXPORT ssize_t __write(int fd, const void *buffer, size_t sz);
__Z_EXPORT ssize_t __read(int fd, void *buffer, size_t sz);
__Z_EXPORT int __close(int fd);
__Z_EXPORT int __open(const char *file, int oflag, int mode);
#endif // ifdef TRACE_ON

/**
 * Debug Printf.
 * \return returns total number of bytes written to file descriptor
 */
__Z_EXPORT int dprintf(int fd, const char *, ...);

/**
 * Variadic Debug Printf.
 * \return returns total number of bytes written to file descriptor
 */
__Z_EXPORT int vdprintf(int fd, const char *, va_list ap);

/**
 * Dump to console.
 */
__Z_EXPORT void __dump(int fd, const void *addr, size_t len, size_t bw);

/**
 * Dump title to console.
 */
__Z_EXPORT void __dump_title(int fd, const void *addr, size_t len, size_t bw,
                             const char *, ...);

/**
 * Print given buffer to MVS Console.
 */
__Z_EXPORT void __console(const void *p_in, int len_i);

/**
 * Print formatted data to MVS Console.
 */
__Z_EXPORT int __console_printf(const char *fmt, ...);

/**
 * Finds file in a given path
 * \param [out] out Found path string
 * \param [in] size Max size of path string
 * \param [in] envar Environment variable to search
 * \param [in] file file to search
 * \return returns non-zero if successful, 0 if not found.
 */
__Z_EXPORT int __find_file_in_path(char *out, int size, const char *envvar,
                                   const char *file);

/**
 * Apply or remove an advisory lock on an open file
 * \param [in] fd file descriptor of the open file
 * \param [in] operation is one of LOCK_SH, LOCK_EX or LOCK_UN
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __flock(int fd, int operation);

/**
 * Change file descriptor to CCSID.
 * \param [in] fd file descriptor.
 * \param [in] ccsid CCSID.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __chgfdccsid(int fd, unsigned short ccsid);

/**
 * Change file descriptor to CCSID from a codeset
 * \param [in] fd file descriptor.
 * \param [in] codeset code set
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __chgfdcodeset(int fd, char* codeset);

/**
 * Change file descriptor to text (819 or controlled via envar)
 * \param [in] fd file descriptor.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __setfdtext(int fd);

/**
 * Change file descriptor to binary
 * \param [in] fd file descriptor.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __setfdbinary(int fd);

/**
 * Disable auto-conversion on file descriptors
 * \param [in] fd file descriptor.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __disableautocvt(int fd);

/**
 * Copy ccsid from source fd to destination fd
 * \param [in] sourcefd file descriptor.
 * \param [in] destfd file descriptor.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __copyfdccsid(int sourcefd, int destfd);

/**
 * Get file descriptor CCSID.
 * \param [in] fd file descriptor.
 * \return returns file descriptors ccsid.
 */
__Z_EXPORT int __getfdccsid(int fd);

/**
 * Set file descriptor to the provided CCSID.
 * \param [in] fd file descriptor.
 * \param [in] t_ccsid CCSID.
 * \return returns 0 if successful, or -1 on failure.
 */
__Z_EXPORT int __setfdccsid(int fd, int t_ccsid);

/**
 * Returns true if logging of memory [de]allocation is specified.
 */
__Z_EXPORT bool __doLogMemoryUsage();

/**
 * Returns the file name, including "stdout" or "stderr", used to log memory
 * [de]allocation to.
 */
__Z_EXPORT char *__getMemoryUsageLogFile();

/**
 * Returns true if all messages from memory [de]allocation are being
 * displayed.
 */
__Z_EXPORT bool __doLogMemoryAll();

/**
 * Returns true if only warnings from memory [de]allocation are being
 * displayed. Errors are always included if memory logging in on.
 */
__Z_EXPORT bool __doLogMemoryWarning();

/**
 * Returns true if memory allocation should be displayed when curvar increases
 * by the value set in environment variable __MEMORY_USAGE_LOG_INC since the last
 * currently allocated size was displayed.
 */
__Z_EXPORT bool __doLogMemoryInc(size_t curval, size_t *plastval);

/**
 * Returns the fileno to which memory diagnostics is written (use for
 * instance in a `__display_backtrace(__getLogMemoryFileNo());` call).
 */
__Z_EXPORT int __getLogMemoryFileNo();

/**
 * Logs memory [de]allocation to the file name specified in the environment
 * variable zoslib_config_t.MEMORY_USAGE_LOG_FILE_ENVAR.
 * \param [in] same as C's printf() parameters
 */
__Z_EXPORT void __memprintf(const char *format, ...);

/**
 * Logs memory [de]allocation to the file name specified in the environment
 * variable zoslib_config_t.MEMORY_USAGE_LOG_FILE_ENVAR, but without the
 * process-id or thread-id prefix as __memprintf does.
 * \param [in] same as C's printf() parameters
 */
__Z_EXPORT void __memprintfx(const char *format, ...);

/**
 * Returns the file name component of a given path.
 * Similar to basename(path), but doesn't modify path, and if path ends with /,
 * which is unexpected for a filename path, then it returns a pointer to that /.
 * \param [in] path of a file.
 * \return the file name component of a given path.
 */
__Z_EXPORT const char *__file_basename(const char *path);

#ifdef __cplusplus
}
#endif
#endif // ZOS_IO_H_
