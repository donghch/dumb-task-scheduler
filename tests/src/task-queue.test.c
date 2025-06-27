#include "unity.h"
#include "types/task-queue.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

task_t test_list[10];
task_queue_t test_queue;

void setUp(){
    task_queue_init(&test_queue, 10, test_list);
}

void tearDown(){
    memset(&test_queue, 0, sizeof(test_queue));
    memset(test_list, 0, sizeof(test_list));
}

/* Core Functionality Tests */

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
    task_t task_in;

    // first fill the queue
    for (int i = 0; i < 10; i++) {
        task_in.priority = i;
        task_queue_push(&test_queue, &task_in);
    }

    // now check the order of popping
    for (int i = 0; i < 10; i++) {
        task = task_queue_head(&test_queue);
        TEST_ASSERT_NOT_NULL(task);
        TEST_ASSERT_EQUAL_UINT8(i, task->priority);
        task_queue_pop(&test_queue);
    }
}

void test_tail_wrap_around() {
    task_t task_in;
    task_t *task;

    // fill 10 tasks
    for (int i = 0; i < 10; i++) {
        task_in.priority = i;
        task_queue_push(&test_queue, &task_in);
    }

    // pop 5 tasks
    for (int i = 0; i < 5; i++) {
        task_queue_pop(&test_queue);
    }

    // add 5 more tasks
    for (int i = 10; i < 15; i++) {
        task_in.priority = i;
        TEST_ASSERT(task_queue_push(&test_queue, &task_in) == 0);
    }
}

/* Edge Case Tests */

void test_init_with_null() {
    task_queue_t *null_queue = NULL;
    task_t *null_tasks = NULL;

    // Attempt to initialize with null queue and tasks
    TEST_ASSERT_EQUAL_INT(-1, task_queue_init(null_queue, 10, null_tasks));
    
    // Attempt to initialize with null queue
    task_t tasks[10];
    TEST_ASSERT_EQUAL_INT(-1, task_queue_init(null_queue, 10, tasks));
    
    // Attempt to initialize with null tasks
    task_queue_t queue;
    TEST_ASSERT_EQUAL_INT(-1, task_queue_init(&queue, 10, null_tasks));

    // Attempt to initialize with zero capacity
    TEST_ASSERT_EQUAL_INT(-1, task_queue_init(&queue, 0, tasks));
}

void test_push_with_null() {
    task_queue_t *null_queue = NULL;
    task_t *null_task = NULL;

    // Attempt to push a null task into a null queue
    TEST_ASSERT_EQUAL_INT(-1, task_queue_push(null_queue, null_task));

    // Attempt to push a null task into an initialized queue
    task_queue_init(&test_queue, 10, test_list);
    TEST_ASSERT_EQUAL_INT(-1, task_queue_push(&test_queue, null_task));

    // Attempt to push a valid task into a null queue
    task_t valid_task;
    TEST_ASSERT_EQUAL_INT(-1, task_queue_push(null_queue, &valid_task));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_peek_empty_head);
    RUN_TEST(test_add_to_full);
    RUN_TEST(test_check_pop_order);
    RUN_TEST(test_tail_wrap_around);

    return UNITY_END();
}