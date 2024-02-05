#include <cctype>
#include <iostream>
#include <vector>
#include <mutex>
#include <cstring>
/* #include <memory> */

#include "utils.h"

#define BUFFER_SIZE 255

/* Вариант: Составление файла-словаря с количеством употреблений каждой N-граммы
 * букв из одного слова (N задаётся как входной парметр и фиксируется -- 3, 4, 5
 * -- в рамках одной серии экспериментов) в тексте на русском языке. */

/* Размер файла для замеров времени кратен 100 килобайт. */

// @ TODO: 
// [x] 1) Считать файл с диска
// [ ] 2) Привести его к виду массив слов
// [ ] 2.1) Соединить по \n
// [ ] 2.2) Всё с маленькой буквы
// [ ] 2.3) Убрать знаки препинания
// [ ] 2.4) Убрать небуквенные символы
// [ ] 2.5) Убрать двойные пробелы
// [ ] 3) Прочитать слово (по файловому указателю)
// [ ] 3.1) Если слово есть в словаре (сделать кастомную структуру данных для словаря, поддерживающую HAS), увеличить счетчик этого слова
// {
//     "file.txt": {
//         "word1": {
//             "ngrams": {
//                 "wor": 1,
//                 "ord": 1,
//                 "rd1": 1
//             },
//             "count": 2
//         }
//     }
// }

template<int N>
struct Ngram {
    Ngram(wchar_t w[N + 1]) {
        memcpy(ngram, w, N * sizeof(wchar_t));
        ngram[N] = L'\0';
        count = 1;
    }

    Ngram(const Ngram &ngr) {
        memcpy(ngram, ngr.ngram, N * sizeof(wchar_t));
        ngram[N] = L'\0';
        count = ngr.count;
    }

    wchar_t ngram[N + 1];
    int count;
};

template<int N, int BUFSIZE>
struct Word {
    Word(wchar_t w[BUFSIZE]) {
        memcpy(word, w, BUFSIZE * sizeof(wchar_t));
        word[BUFSIZE - 1] = L'\0';
        count = 1;
    }

    Word(const Word &w) {
        memcpy(word, w.word, BUFSIZE * sizeof(wchar_t));
        word[BUFSIZE - 1] = L'\0';
        count = w.count;
    }

    wchar_t word[BUFSIZE];
    std::vector<Ngram<N>> ngrams;
    int count;
};

template<int N, int BUFSIZE>
void word_print(Word<N, BUFSIZE> &word) {
    wprintf(L"%ls (%d)\n", word.word, word.count);
    if (word.ngrams.size() == 0) {
        wprintf(L"\tNo ngrams yet.\n");
    } else {
        int i = 1;
        for (Ngram<N> &ngr : word.ngrams) {
            wprintf(L"\t%d. %ls (%d)\n", i, ngr.ngram, ngr.count);
            ++i;
        }
    }
}

template<int N, int BUFSIZE>
void word_generate_ngrams(Word<N, BUFSIZE> &word) {
    bool flag = false;
    int begin = 0;
    int end = N - 1;

    while (word.word[end] != L'\0') {
        Ngram<N> ngram(word.word + begin); 

        for (Ngram<N> &ngr : word.ngrams) {
            if (wcscmp(ngram.ngram, ngr.ngram) == 0) {
                flag = true;
                ++ngr.count;
                break;
            }
        }

        if (!flag) {
            word.ngrams.push_back(ngram);
        }

        ++begin;
        ++end;
        flag = false;
    }
}

template<int N, int BUFSIZE = BUFFER_SIZE>
class AtomicDict {
    using word_t = Word<N, BUFSIZE>;
    using ngram_t = wchar_t[N + 1];
public:
    AtomicDict(const char *filename) : m_filename(filename) { m_words.reserve(255); } // @ HACK FIXME

    bool add(wchar_t word[BUFSIZE]) {
        bool flag_has_word = true;

        if (!has(word)) {
            flag_has_word = false;
            word_t w{word};
            m_mutex.lock();
            m_words.push_back(w); // @ NOTE uses Word(const Word &w)
            m_mutex.unlock();
        }

        if (flag_has_word) {
            m_mutex.lock();
            word_t &w = m_words.back();
            ++w.count;
            m_mutex.unlock();
        }

        return !flag_has_word;
    }

    void update(wchar_t word[BUFSIZE], std::vector<ngram_t> ngrams) {
        int i = get_index(word);

        m_mutex.lock();
        word_t &w = m_words.at(i);
        w.ngrams = ngrams;
        m_mutex.unlock();
    }

    bool has(wchar_t word[BUFSIZE]) {
        bool found = false;

        m_mutex.lock();
        for (unsigned long i = 0; i < m_words.size(); ++i) {
            word_t &w = m_words.at(i);
            if (wcscmp(w.word, word) == 0) {
                found = true;
                break;
            }
        }
        m_mutex.unlock();

        return found;
    }

    unsigned long get_index(wchar_t word[BUFSIZE]) {
        unsigned long i = 0;

        m_mutex.lock();
        for (; i < m_words.size(); ++i) {
            word_t &w = m_words.at(i);
            if (wcscmp(w.word, word) == 0) {
                break;
            }
        }
        m_mutex.unlock();

        return i;
    }

    Word<N, BUFSIZE> &get_word(int index) {
        m_mutex.lock();
        Word<N, BUFSIZE> &w = m_words.at(index);
        m_mutex.unlock();

        return w;
    }

    void print() {
        for (word_t &w : m_words) {
            word_print(w);
        }
    }

private:
    const char *m_filename;
    std::mutex m_mutex;
    std::vector<word_t> m_words;
};

int atomic_read(FILE *opened_file, wchar_t word[BUFFER_SIZE], std::mutex &fpmutex) {
    // @ TODO meh, error handling
    int rc = 0;

    fpmutex.lock();
    wchar_t wch = (wchar_t)fgetwc(opened_file);
    while (is_space(wch)) {
        wch = (wchar_t)fgetwc(opened_file);
    }
    int i = 0;
    for (; !is_space(wch) && i < BUFFER_SIZE - 1; ++i) {
        /* if (wch == WEOF) { */
            /* rc = 1; */
        /* } else { */
        {
            word[i] = wch;
            wch = (wchar_t)fgetwc(opened_file);
        }
    }
    word[i] = L'\0';
    fpmutex.unlock();

    return rc;
}

/* void worker(FILE *file, std::mutex &fpmutex, std::shared_ptr<AtomicDict<3>> pdict) { */
template<int N, int BUFSIZE = BUFFER_SIZE>
void worker(FILE *file, std::mutex &fpmutex, AtomicDict<N, BUFSIZE> *pdict) {
    // @ TODO main thread owns an array of words of bufsize size and shares each array
    // element with corresponding worker thread, to not alloc word buf on stack
    wchar_t word[BUFSIZE];

    /* while (atomic_read(file, word, fpmutex) == 0) { */
    for (int i = 0; atomic_read(file, word, fpmutex) == 0 && i < 20; ++i) { // FIXME works strangely when i < k, k > 1
        if (pdict->add(word)) {
            unsigned long index = pdict->get_index(word);
            Word<N, BUFSIZE> &w = pdict->get_word(index);
            word_generate_ngrams(w);
        }
    }
}

// Thread func:
// if (add(word)) { search for ngrams; update }
// go to the next word

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    const char *filename = "../lab_04/words.txt";

    FILE *file = fopen(filename, "r");
    /* wchar_t word[BUFFER_SIZE]; */
    std::mutex fpmutex;

    AtomicDict<4> dict{filename};

    /* worker(file, fpmutex, std::make_shared<AtomicDict<3>>(dict)); */
    worker(file, fpmutex, &dict);

    dict.print();

    /* for (int i = 0; i < 10; ++i) { */
    /*     atomic_read(file, word, fpmutex); */
    /*     wprintf(L"%ls\n", word); */
    /* } */

    fclose(file);
}
