#include <stdio.h>

int main() {
    printf("Running integration tests...\n");

    test_stack_push_pop();
    test_stack_empty();

    test_queue_fifo();

    test_round_robin_behavior();

    test_fifo_scheduler();

    test_first_fit();

    //test_bruteforce();
    //test_greedy();
    //test_dp();

    printf("All tests passed!\n");

    return 0;
}
