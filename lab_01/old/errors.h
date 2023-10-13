#ifndef __ERRORS_H__
#define __ERRORS_H__

#include "colors.h"

#define ERR(x) TCR x RC
#define MSG_INVALID_INPUT "Неверный ввод."

enum err_t {
    OK,

    ERR_MONKEY,
    ERR_EOF,
    ERR_INDEX,
};

err_t handle_error(const err_t &error_code);

#endif // __ERRORS_H__
