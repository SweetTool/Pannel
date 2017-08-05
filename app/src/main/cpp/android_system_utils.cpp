#include "android_system_utils.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cctype>

#include "common.h"
#include "file_utils.h"

static char TAG[] = "android_system_utils";

long android_system_utils::getBootTime() {
    const char filepath[] = "/proc/stat";

    if (!file_utils::isExists(filepath)) {
        return -1;
    }

    int fd = open(filepath, O_RDONLY);
    if (-1 == (fd)) {
        lerror(TAG, "getBootTime. open: %s file failed. errno: %d, error: %s", errno, strerror(errno));
        return -1;
    }
    errno = 0;
    char storebuf[128] = {0}; // 128bit is enough as we only concern about btime text.
    char buf[2] = {0};
    ssize_t len = 0;
    long ret = -1;
    do {
        memset(buf, 0, sizeof(buf));
        if ((len = safe_read(fd, buf, 1)) > 0) { // only read on character.
            if ('\n' == buf[0]) { // match a new line.
                if (-1 != (ret = parseBootTime(storebuf, strlen(storebuf)))) {
                    break;
                }
                memset(storebuf, 0, sizeof(storebuf));
            } else if (strlen(storebuf) < sizeof(storebuf) - 1) { // fill a line data.
                strcat(storebuf, buf);
            }
        }
    } while (len > 0);
    if (-1 == len) {
        lerror(TAG, "getBootTime. read error. errno: %d, error: %s", errno, strerror(errno));
    }

    close(fd);

    return ret;
};

long android_system_utils::parseBootTime(const char *text, size_t size) {
    const char btime[] = "btime";
    const char *find = strstr(text, btime);
    if (NULL == find) {
        return -1;
    }

    char c[2] = {0};
    char buf[64] = {0};
    for (size_t i = 0; i < size; i++) {
        c[0] = *(text + i);
        if (isdigit(c[0])) { // fill buf with digital.
            strcat(buf, c);
        }
    }
    if (0 == strlen(buf)) {
        return -1;
    }

    return atol(buf);
}