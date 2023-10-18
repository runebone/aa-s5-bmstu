#include <gtest/gtest.h>
#include "func.h"

#define BUFSIZE 100'000

class MainTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    void Run(wchar_t *str1, wchar_t *str2, bool run_dlr = true) {
        wcscpy(s1, str1);
        wcscpy(s2, str2);

        size_t len1 = wcsnlen(s1, BUFSIZE);
        size_t len2 = wcsnlen(s2, BUFSIZE);

        LI = levenshtein_iterative_full_matrix(s1, len1, s2, len2);
        DLI = damerau_levenshtein_iterative_full_matrix(s1, len1, s2, len2);
        if (run_dlr) DLR = damerau_levenshtein_recursive_no_cache(s1, len1, s2, len2);
        DLRC = damerau_levenshtein_recursive_with_cache(s1, len1, s2, len2);
    }

    wchar_t s1[BUFSIZE] = { 0 };
    wchar_t s2[BUFSIZE] = { 0 };

    size_t len1;
    size_t len2;

    size_t LI, DLI, DLR, DLRC;
};

TEST_F(MainTest, SeminarExample) {
    wchar_t str1[BUFSIZE] = L"скат";
    wchar_t str2[BUFSIZE] = L"кот";
    Run(str1, str2);
	ASSERT_EQ(LI,   2U);
	ASSERT_EQ(DLI,  2U);
	ASSERT_EQ(DLR,  2U);
	ASSERT_EQ(DLRC, 2U);
}

TEST_F(MainTest, SameWordsSoNoChanges) {
    wchar_t str1[BUFSIZE] = L"обеъьяа";
    wchar_t str2[BUFSIZE] = L"обеъьяа";
    Run(str1, str2);
	ASSERT_EQ(LI,   0U);
	ASSERT_EQ(DLI,  0U);
	ASSERT_EQ(DLR,  0U);
	ASSERT_EQ(DLRC, 0U);
}

TEST_F(MainTest, TestedManuallyInNotebook1) {
    wchar_t str1[BUFSIZE] = L"howiwantadrink";
    wchar_t str2[BUFSIZE] = L"alcoholicofcourse";
    Run(str1, str2, false);
	ASSERT_EQ(LI,   14U);
	ASSERT_EQ(DLI,  14U);
	ASSERT_EQ(DLRC, 14U);
}

TEST_F(MainTest, TestedManuallyInNotebook2) {
    wchar_t str1[BUFSIZE] = L"python";
    wchar_t str2[BUFSIZE] = L"ptyhon";
    Run(str1, str2);
	ASSERT_EQ(LI,   2U);
	ASSERT_EQ(DLI,  1U);
	ASSERT_EQ(DLR,  1U);
	ASSERT_EQ(DLRC, 1U);
}

TEST_F(MainTest, TestedManuallyInNotebook3) {
    wchar_t str1[BUFSIZE] = L"sobr";
    wchar_t str2[BUFSIZE] = L"osrb";
    Run(str1, str2);
	ASSERT_EQ(LI,   3U);
	ASSERT_EQ(DLI,  2U);
	ASSERT_EQ(DLR,  2U);
	ASSERT_EQ(DLRC, 2U);
}

TEST_F(MainTest, UnicodeEmojis) {
    wchar_t str1[BUFSIZE] = L"😎😂";
    wchar_t str2[BUFSIZE] = L"😂😎";
    Run(str1, str2);
	ASSERT_EQ(LI,   2U);
	ASSERT_EQ(DLI,  1U);
	ASSERT_EQ(DLR,  1U);
	ASSERT_EQ(DLRC, 1U);
}

TEST_F(MainTest, SingleLetters) {
    wchar_t str1[BUFSIZE] = L"ζ";
    wchar_t str2[BUFSIZE] = L"η";
    Run(str1, str2);
	ASSERT_EQ(LI,   1U);
	ASSERT_EQ(DLI,  1U);
	ASSERT_EQ(DLR,  1U);
	ASSERT_EQ(DLRC, 1U);
}

TEST_F(MainTest, FirstStringEmpty) {
    wchar_t str1[BUFSIZE] = L"";
    wchar_t str2[BUFSIZE] = L"asdfasdfasdfas";
    Run(str1, str2);
	ASSERT_EQ(LI,   14U);
	ASSERT_EQ(DLI,  14U);
	ASSERT_EQ(DLR,  14U);
	ASSERT_EQ(DLRC, 14U);
}

TEST_F(MainTest, SecondStringEmpty) {
    wchar_t str1[BUFSIZE] = L"ABCD";
    wchar_t str2[BUFSIZE] = L"";
    Run(str1, str2);
	ASSERT_EQ(LI,   4U);
	ASSERT_EQ(DLI,  4U);
	ASSERT_EQ(DLR,  4U);
	ASSERT_EQ(DLRC, 4U);
}

TEST_F(MainTest, BothStringsEmpty) {
    wchar_t str1[BUFSIZE] = L"";
    wchar_t str2[BUFSIZE] = L"";
    Run(str1, str2);
	ASSERT_EQ(LI,   0U);
	ASSERT_EQ(DLI,  0U);
	ASSERT_EQ(DLR,  0U);
	ASSERT_EQ(DLRC, 0U);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
