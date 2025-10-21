// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../algorithms/check_breckets.h"

TEST(TestCheckBreckets, test_check_breckets_classic) {
    bool res = check_breckets("()()()");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_nested) {
    bool res = check_breckets("{[()]}");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_complex_mix) {
    bool res = check_breckets("({[]})[]{}");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_with_other_chars) {
    bool res = check_breckets("a(b[c]d)e{f}g");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_empty) {
    bool res = check_breckets("");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_only_square) {
    bool res = check_breckets("[[][]]");
    ASSERT_TRUE(res);
}

TEST(TestCheckBreckets, test_check_breckets_no_close_at_end) {
    bool res = check_breckets("{[(");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_mismatched_overlap) {
    bool res = check_breckets("{[(])}");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_close_without_open) {
    bool res = check_breckets("()]}");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_wrong_type) {
    bool res = check_breckets("{[)]}");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_extra_close_in_middle) {
    bool res = check_breckets("(()))(");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_extra_open) {
    bool res = check_breckets("((()))(");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_single_open) {
    bool res = check_breckets("(");
    ASSERT_FALSE(res);
}

TEST(TestCheckBreckets, test_check_breckets_single_close) {
    bool res = check_breckets("}");
    ASSERT_FALSE(res);
}