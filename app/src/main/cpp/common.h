#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <cstdio>

#ifdef ANDROID
#include <android/log.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ANDROID
#define ldebug(tag, format, ...) __android_log_print(ANDROID_LOG_DEBUG, \
    tag, format, ##__VA_ARGS__ )
#define lwarning(tag, format, ...) __android_log_print(ANDROID_LOG_WARN, \
    tag, format, ##__VA_ARGS__ )
#define lerror(tag, format, ...) __android_log_print(ANDROID_LOG_ERROR, \
    tag, format, ##__VA_ARGS__ )
#else
#define ldebug(tag, format, ...) fprintf(stdout, \
    "%s  " format, tag, ##__VA_ARGS__ )
#define lwarning(tag, format, ...) fprintf(stdout, \
    "%s  " format, tag, ##__VA_ARGS__ )
#define lerror(tag, format, ...) fprintf(stderr, \
    "%s  "format, tag, ##__VA_ARGS__ )
#endif

/**
 * in case read interruption
 */
inline ssize_t safe_read(int fd, char *buf, size_t size) {
    ssize_t ret = -1;
    while (-1 == (ret = read(fd, buf, size)) && EINTR == errno) {
        // continue;
    }
    return ret;
}

#ifdef __cplusplus
}
#endif
#endif