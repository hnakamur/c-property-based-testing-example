#include <greatest.h>
#include <theft.h>
#include <stdint.h>
#include <stdio.h>
#include "round.h"

static inline uint64_t
straightforward_round_up(uint64_t d, uint64_t a) {
    return (d % a == 0 ? d / a : d / a + 1) * a;
}

static enum theft_trial_res
prop_round_up_should_equal_straightforward_impl(struct theft *t, void *arg1,
                                                void *arg2) {
    uint64_t d = *(uint64_t *)arg1;
    uint64_t a = *(uint64_t *)arg2;
    if (a == 0 || d > UINT64_MAX / a) return THEFT_TRIAL_SKIP;
    uint64_t actual = round_up(d, a);
    uint64_t expected = straightforward_round_up(d, a);
    return actual == expected ? THEFT_TRIAL_PASS : THEFT_TRIAL_FAIL;
}

TEST test_round_up_should_equal_straightforward_impl(void) {
    theft_seed seed = theft_seed_of_time();

    struct theft_type_info random_uint64_info;
    theft_copy_builtin_type_info(THEFT_BUILTIN_uint64_t, &random_uint64_info);

    struct theft_run_config config = {
        .name = __func__,
        .prop2 = prop_round_up_should_equal_straightforward_impl,
        .type_info = {
            &random_uint64_info,
            &random_uint64_info,
        },
        .seed = seed,
    };
    enum theft_run_res res = theft_run(&config);
    if (res == THEFT_RUN_SKIP) SKIP();
    ASSERT_EQ(THEFT_RUN_PASS, res);
    PASS();
}

SUITE(the_suite) {
    RUN_TEST(test_round_up_should_equal_straightforward_impl);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(the_suite);
    GREATEST_MAIN_END();
}
