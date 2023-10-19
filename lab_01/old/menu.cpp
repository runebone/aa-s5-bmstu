#include "menu.h"

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <limits>

#include "colors.h"
#include "errors.h"

#include "algorithm.h"

#define CURDIR "/home/human/University/aa/lab_01"

using std::string;
/* using std::cin; */
/* using std::cout; */
using std::istream;

// Menu functions
namespace mf {
    err_t input_two_lines(istream &in, string &str1, string &str2) {
        in >> str1 >> str2;

        return OK;
    }

    err_t benchmark() {
        return OK;
    }
}

Menu::Menu() {
    Action input_two_lines("Ввести два слова", [](){
            string str1, str2;

            /* printf("Введите два слова через пробел: " TCB); */
            /* err_t error_code = mf::input_two_lines(cin, str1, str2); */
            /* printf(RC); */

            std::ifstream fs;
            fs.open(CURDIR "/tests/01.txt");
            err_t error_code = mf::input_two_lines(fs, str1, str2);
            fs.close();

            if (error_code == OK) {
                u32 result = lev_iterative(str1.c_str(), str1.length(), str2.c_str(), str2.length());
                printf("Levenshtein iterative: %d\n", result);

                result = damlev_iterative_with_matrix(str1.c_str(), str1.length(), str2.c_str(), str2.length());
                printf("Damerau-Levenshtein with matrix: %d\n", result);
            }

            return error_code;
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
