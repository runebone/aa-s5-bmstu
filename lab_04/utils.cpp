#include "utils.h"

bool is_space(wchar_t wch) {
    return wch == L' '
        || wch == L'\f'
        || wch == L'\n'
        || wch == L'\r'
        || wch == L'\t'
        || wch == L'\v';
}
