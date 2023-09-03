#ifndef __MENU_H__
#define __MENU_H__

#include "typedefs.h"
#include "errors.h"

#include <functional>
template<typename T>
using func = std::function<T>;
using callback_t = func<err_t()>;

#include <vector>
template<typename T>
using vec = std::vector<T>;

class Action {
public:
    Action(const char *information, callback_t callback)
        : info(information), cb(callback)
    {
    }

    const char *text() const { return info; }
    err_t exec() const { return cb(); }

private:
    const char *info;
    callback_t cb;
};

class Menu {
public:
    Menu();

    err_t run();

private:
    void add_action(Action &action);

    void print() const;

    err_t validate_choice() const;

    vec<Action> m_actions;
    u32 m_choice = 0;
    err_t m_error_code = OK;
};

#endif // __MENU_H__
