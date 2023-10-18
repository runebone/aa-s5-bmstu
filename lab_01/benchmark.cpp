#include "benchmark.h"

#include <time.h>
#include <iostream>
#include <functional>
#include <random>
#include <limits.h>
/* #include <unistd.h> */
#include <fstream>
#include <vector>
#include "func.h"

typedef std::function<void()> func_t;

#define BUFSIZE 100'000
#define U_INF -1U // Unsigned infinity

struct BenchmarkData
{
    size_t string_length = 0;
    long t_lim_ns   = -1;
    long t_lifm_ns  = -1;
    long t_dlifm_ns = -1;
    long t_dlr_ns   = -1;
    long t_dlrc_ns  = -1;

    BenchmarkData(size_t slen, long lim, long lifm, long dlifm, long dlr, long dlrc)
        : string_length(slen), t_lim_ns(lim), t_lifm_ns(lifm),
          t_dlifm_ns(dlifm), t_dlr_ns(dlr), t_dlrc_ns(dlrc) {}

    // XXX
    std::vector<std::string> get_data()
    {
        std::vector<std::string> vec;

        vec.push_back(std::to_string(string_length));
        vec.push_back(std::to_string(t_lim_ns));
        vec.push_back(std::to_string(t_lifm_ns));
        vec.push_back(std::to_string(t_dlifm_ns));
        vec.push_back(std::to_string(t_dlr_ns));
        vec.push_back(std::to_string(t_dlrc_ns));

        return vec;
    }
};

void log(std::vector<BenchmarkData> &bdv, const char *filename = "/home/human/University/aa/lab_01/benchmark/data.csv")
{
    std::ofstream output(filename);

    if (!output.is_open())
    {
        std::cerr << "Error: Failed to open the file for writing." << std::endl;
        return;
    }

    output << "length,tlim,tlifm,tdlifm,tdlr,tdlrc\n"; // XXX

    for (auto &bd : bdv)
    {
        auto data = bd.get_data();

        for (size_t i = 0; i < data.size(); i++)
        {
            output << data[i];
            if (i < data.size() - 1) output << ",";
        }
        output << "\n";
    }

    output.close();
}

long int get_cpu_time_ns()
{
	struct timespec t;

	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t))
	/* if (clock_gettime(CLOCK_MONOTONIC, &t)) */
    {
		std::cerr << "Невозможно получить время.\n";
		return -1;
	}

	return t.tv_sec * 1'000'000'000LL + t.tv_nsec;
}

long int timeit(func_t func)
{
    long int start = get_cpu_time_ns();
    /* wprintf(L"Start: %ld\n", start); */
    func();
    long int end = get_cpu_time_ns();
    /* wprintf(L"End: %ld\n", end); */
    /* wprintf(L"End - Start: %ld\n", end - start); */

    return end - start;
}

std::wstring generate_random_string(size_t length)
{
    std::wstring charset = L"0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
        "αβγδεζηθλ"
        "!@#$%^&*()_+-=[]{}\\|;:'\"<>,./? 😂";

    std::wstring random_string;
    random_string.resize(length);

	srand(time(NULL));

	std::random_device dev;
	std::mt19937 random_number_generator(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, charset.size() - 1);

    for (size_t i = 0; i < length; i++)
    {
		random_string[i] = charset[distribution(random_number_generator)];
    }

    return random_string;
}

void clean(size_t **matrix, size_t n_rows, size_t n_columns, bool for_rwc = false)
{
    if (!for_rwc)
    {
        for (size_t i = 1; i < n_rows; i++)
        {
            for (size_t j = 1; j < n_columns; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    else
    {
        for (size_t i = 0; i < n_rows; i++)
        {
            for (size_t j = 0; j < n_columns; j++)
            {
                matrix[i][j] = U_INF;
            }
        }
    }
}

BenchmarkData benchmark_run_one(const wchar_t str1[BUFSIZE], const wchar_t str2[BUFSIZE])
{
    size_t len1 = wcsnlen(str1, BUFSIZE);
    size_t len2 = wcsnlen(str2, BUFSIZE);

    bool run_dlr = len1 < 13 && len2 < 13;

    // Shifting strings right (~ inserting λ at pos. 0)
    const wchar_t *s1 = str1 - 1;
    const wchar_t *s2 = str2 - 1;
    size_t l1 = len1 + 1;
    size_t l2 = len2 + 1;

    size_t **matrix = create_matrix(l1, l2);
    size_t **matrix_2xN = create_matrix(2, l2);
    size_t *first_row = matrix_2xN[0];
    size_t **matrix_rwc = create_matrix(len1, len2);

    for (size_t i = 0; i < len1; i++)
    {
        for (size_t j = 0; j < len2; j++)
        {
            matrix_rwc[i][j] = U_INF;
        }
    }

    func_t lim = [=](){ lev_im_helper(matrix_2xN, s1, l1, s2, l2); /* sleep(2); */ };
    func_t lifm = [=](){ lev_ifm_helper(matrix, s1, l1, s2, l2); };
    func_t dlifm = [=](){ damlev_ifm_helper(matrix, s1, l1, s2, l2); };
    func_t dlr = [=](){ damerau_levenshtein_recursive_no_cache(str1, len1, str2, len2); };
    func_t dlrc = [=](){ damlev_rwc_helper(matrix_rwc, str1, len1, str2, len2); };

    wprintf(L"Benchmarking...\n");

    long tlim = timeit(lim);
    /* clean(matrix_2xN, 2, l2); */
    long tlifm = timeit(lifm);
    clean(matrix, l1, l2);
    long tdlifm = timeit(dlifm);
    /* clean(matrix, l1, l2); */
    long tdlr = run_dlr ? timeit(dlr) : -1;
    long tdlrc = timeit(dlrc);
    /* clean(matrix_rwc, len1, len2, true); */

    wprintf(L"%-41ls: %ld, %ld\n", L"String lengths", len1, len2);
    wprintf(L"%-41ls: %ld\n", L"Levenshtein Iterative (memory-optimized)", tlim);
    wprintf(L"%-41ls: %ld\n", L"Levenshtein Iterative", tlifm);
    wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Iterative", tdlifm);
    if (run_dlr) wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Recursive No Cache", tdlr);
    wprintf(L"%-41ls: %ld\n\n", L"Damerau-Levenshtein Recursive With Cache", tdlrc);

    free_matrix(matrix_rwc, matrix_rwc[0]);
    free_matrix(matrix_2xN, first_row);
    free_matrix(matrix, matrix[0]);

    BenchmarkData bd(len1, tlim, tlifm, tdlifm, tdlr, tdlrc);

    return bd;
}

BenchmarkData benchmark_run_one(std::wstring str1, std::wstring str2)
{
    return benchmark_run_one(str1.c_str(), str2.c_str());
}

void benchmark(size_t start, size_t stop, size_t step, size_t count)
{
    auto grs = [](size_t length){ return generate_random_string(length); };

    std::vector<BenchmarkData> bdv;

    for (size_t len = start; len < stop; len += step)
    {
        for (size_t i = 0; i < count; i++)
        {
            bdv.push_back(benchmark_run_one(grs(len), grs(len)));
        }
    }

    log(bdv);
}

void benchmark()
{
    auto grs = [](size_t length){ return generate_random_string(length); };

    std::vector<BenchmarkData> bdv;

    for (size_t len : { 10, 50, 100, 500, 1000 })
    {
        for (size_t i = 0; i < 10; i++)
        {
            bdv.push_back(benchmark_run_one(grs(len), grs(len)));
        }
    }

    log(bdv);
}
