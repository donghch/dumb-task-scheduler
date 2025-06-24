#include "unity.h"
#include "types/task-queue.h"
#include "task.h"

#include <stdio.h>

task_t test_list[10];
task_queue_t test_queue;

void setUp(){
    task_queue_init(&test_queue, 10, test_list);
}

void tearDown(){

}

// tests
void test_peek_empty_head() {
    task_t *task = task_queue_head(&test_queue);
    TEST_ASSERT_NULL(task);
}

void test_add_to_full() {
    task_t task;
    for (int i = 0; i < 10; i++) {
        task.priority = i;
        TEST_ASSERT(task_queue_push(&test_queue, &task) == 0);
    }

    TEST_ASSERT(task_queue_push(&test_queue, &task) == -1);
}

void test_check_pop_order() {
    task_t *task;
    for (int i = 0; i < 10; i++) {
        task = task_queue_head(&test_queue);
        printf("Task at head: %p\n", task);
        TEST_ASSERT_NOT_NULL(task);
        TEST_ASSERT_EQUAL_UINT8(i, task->priority);
        task_queue_pop(&test_queue);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_peek_empty_head);
    RUN_TEST(test_add_to_full);
    RUN_TEST(test_check_pop_order);

    return UNITY_END();
}