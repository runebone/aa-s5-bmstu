#include "menu.h"

#include <stdio.h>
#include <iostream>
#include <limits>

#include "colors.h"
#include "errors.h"

#include "algorithm.h"

Menu::Menu() {
    Action input_two_lines("Ввести две строки", [](){
            printf("res %d\n", lev_iterative("skat", 4, "kot", 3));
            return OK;
            });
    Action benchmark("Запустить тесты и построить графики", [](){
            return OK;
            });
    Action quit("Выйти", [](){
            return ERR_EOF;
            });

    add_action(input_two_lines);
    add_action(benchmark);
    add_action(quit);
}

void Menu::add_action(Action &action) {
    m_actions.push_back(action);
}

void Menu::print() const {
    u32 i = 1;

    printf(TCY "Выберите действие:\n" RC);
    for (auto a: m_actions) {
        printf(TCB "%d" RC " - %s\n", i++, a.text());
    }
    printf("> ");
}

static err_t handle_input(u32 &action_number) {
    err_t error_code = OK;
    u32 tmp_action_number = 0;

    if (!(std::cin >> tmp_action_number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (std::cin.eof()) {
            error_code = ERR_EOF;
        } else {
            error_code = ERR_MONKEY;
        }
    } else {
        action_number = tmp_action_number;
    }

    return error_code;
}

err_t Menu::validate_choice() const {
    err_t error_code = OK;

    if (m_choice < 1 || m_choice > m_actions.size()) {
        error_code = ERR_INDEX;
    }

    return error_code;
}

err_t Menu::run() {
    while (m_error_code == OK) {
        print();

        m_error_code = handle_input(m_choice);

        if (m_error_code == OK) {
            m_error_code = validate_choice();
        }

        if (m_error_code == OK) {
            m_error_code = m_actions[m_choice - 1].exec();
        }

        if (m_error_code != OK) {
            m_error_code = handle_error(m_error_code);
        }

        if (m_error_code == OK) {
            printf("\n");
        }
    }

    return m_error_code;
}
