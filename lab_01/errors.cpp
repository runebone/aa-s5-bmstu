#include "errors.h"

#include <stdio.h>

err_t handle_error(const err_t &error_code) {
    switch (error_code) {
        case OK:
            break;
        case ERR_MONKEY:
            printf("%s\n", ERR(MSG_INVALID_INPUT));
            break;
        case ERR_EOF:
            return ERR_EOF;
        case ERR_INDEX:
            printf("%s\n", ERR(MSG_INVALID_INPUT));
            break;
    }

    return OK;
}
