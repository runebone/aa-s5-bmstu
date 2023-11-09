#include "sort_radix.h"

#include <memory.h>
#include <cstdio>

typedef unsigned char byte;

size_t get_msbit_idx(byte x)
{
    size_t msbit_idx = 7;

    // Находим наибольший бит, отличающийся от нуля в байте x.

    while ((x & (1 << msbit_idx)) == 0)
        msbit_idx--;

    return msbit_idx;
}

size_t find_msbit(void *base, size_t nmemb, size_t size)
{
    byte byte_ptr = size - 1;
    byte sum = 0;

    // Для каждого элемента base, проходимся по нему побайтово, от старшего
    // байта к младшему. Делаем побитовое ИЛИ соответствующих байтов всех
    // элементов. Если итоговое побитовое ИЛИ не равно нулю, значит наибольший
    // значащий бит находится в текущем байте. Поиск можно завершать.

    while (sum == 0 && byte_ptr >= 0) {
        for (size_t i = 0; i < nmemb; i++) {
            byte *elem = (byte*)base + size * i;
            elem += byte_ptr;

            sum |= *elem;
        }

        if (sum == 0)
            byte_ptr--;
    }

    // Если побитовые ИЛИ для каждого байта всех элементов равны нулю, значит
    // двоичные представления всех элементов равны нулю.

    if (byte_ptr < 0)
        return -1; // All elements = 0

    size_t msbit_idx = 8 * byte_ptr + get_msbit_idx(sum);

    return msbit_idx;
}

void radix_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    // Сортируем данные произвольного типа побитово, не поразрядно. В связи с
    // этим, при сортировке по возрастанию знаковых целых чисел, отрицательные
    // числа будут находиться в конце.

    size_t msbit_idx = find_msbit(base, nmemb, size);
    size_t byte_ptr = 0;

    void *zero_elems[nmemb];
    void *one_elems[nmemb];

    size_t zero_ptr = 0;
    size_t zero_cnt = 0;
    size_t one_ptr = 0;
    size_t one_cnt = 0;
    size_t ptr = 0;

    // Сортировка происходит засчёт прохождения по всем элементам base побитово,
    // от младшего бита - к старшему. На каждой итерации элементы base
    // распределяются между двумя массивами: zero_elems и one_elems. В
    // zero_elems помещаются элементы base, у которых текущий бит равен нулю.

    // Сравнения элементов base функцией cmp в сортировке нигде не происходит,
    // но, тем не менее, её нужно учитывать.

    // Идея:
    // Считать, что, если cmp(bin max, bin min) = 1 (сигнал того, что элементы
    // надо поменять местами), то порядок сортировки - по возрастанию, иначе -
    // по убыванию.
    byte a[size], b[size];
    memset(a, 255, size);
    memset(b, 0, size);
    int order_asc = cmp(a, b);

    // zero_elems и one_elems - массивы указателей на элементы base, иначе бы
    // пришлось выделять дополнительной памяти в два раза больше, чем размер
    // исходного массива base, что очень затратно.

    // В связи с этим, возникает другая проблема - после заполнения zero_elems
    // и one_elems, нужно по указателям, хранимым в этих массивах, изменить
    // исходный массив base. Но если мы начнём изменять массив base, поочерёдно
    // вставляя в него элементы из него же самого по указателям из массивов,
    // произойдёт потеря информации.

    // Решение:
    // Хранить копию base, заполнять её в соответствии с zero_elems, one_elems
    // элементами из исходного массива, после чего перезаписывать исходный
    // массив его изменённой копией.
    byte base_copy[nmemb * size];
    memcpy(base_copy, base, nmemb * size);

    // Маска - указатель на текущий бит.
    byte mask = 1;

    for (size_t curbit = 0; curbit <= msbit_idx; curbit++, mask <<= 1) {
        zero_ptr = 0;
        zero_cnt = 0;
        one_ptr = 0;
        one_cnt = 0;
        ptr = 0;

        // Если перешли на следующий байт, корректируем битовый и байтовый
        // указатели.
        if (curbit && (curbit % 8) == 0) {
            mask = 1;
            byte_ptr++;
        }

        for (size_t i = 0; i < nmemb; i++) {
            byte *elem = (byte*)base + size * i;
            elem += byte_ptr;

            // HACK Когда order_asc = 1, условие эквивалентно (*elem & mask) >
            // 0, но когда order_asc = 0 мы начинаем класть элементы с нулевыми
            // текущими битами в массив one_elems (изначально предназначавшийся
            // для хранения элементов с единичными текущими битами). Это
            // сделано для того, чтобы учесть порядок, избежав дублирования кода
            // в дальнейшем.
            bool cond = ((*elem & mask) > 0) ^ !order_asc;
            if (cond) {
                one_elems[one_ptr] = elem;
                one_ptr++;
            } else {
                zero_elems[zero_ptr] = elem;
                zero_ptr++;
            }
        }

        // Заполняем base_copy в соответствии с zero_elems и one_elems.
        // NOTE При order_asc = 0 (сортировке по убыванию), в zero_elems
        // хранятся элементы с единичными текущими битами.
        for (; zero_ptr; zero_ptr--) {
            void *dst = (byte*)base_copy + size * ptr;
            void *src = (byte*)zero_elems[zero_cnt] - byte_ptr;
            memcpy(dst, src, size);
            zero_cnt++;
            ptr++;
        }
        for (; one_ptr; one_ptr--) {
            void *dst = (byte*)base_copy + size * ptr;
            void *src = (byte*)one_elems[one_cnt] - byte_ptr;
            memcpy(dst, src, size);
            one_cnt++;
            ptr++;
        }

        // Перезаписываем base.
        memcpy(base, base_copy, nmemb * size);
    }

    printf("%lu\n", msbit_idx);
}

