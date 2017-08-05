#ifndef ANDROID_SYSTEM_UTILS_H
#define ANDROID_SYSTEM_UTILS_H

#include <cstddef>

class android_system_utils {
public:
    /**
     * get android system boot time(unit second).
     * time since 1970-01-01 00:00:00 +0000 (UTC).
     */
    static long getBootTime();

private:
    static long parseBootTime(const char* text, size_t size);
};


#endif
