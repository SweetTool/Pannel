#include "file_utils.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "common.h"

bool file_utils::isExists(const char *path) {
    struct stat sb;
    return 0 == stat(path, &sb);
}