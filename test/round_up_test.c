#include <greatest.h>
#include "round.h"

TEST test_round_up(void) {
    ASSERT_EQ(0, round_up(0, 20));
    ASSERT_EQ(20, round_up(1, 20));
    ASSERT_EQ(20, round_up(20, 20));
    ASSERT_EQ(40, round_up(21, 20));
    PASS();
}

SUITE(the_suite) {
    RUN_TEST(test_round_up);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(the_suite);
    GREATEST_MAIN_END();
}
