// Timed Lab 4 Tests, Spring 2020

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"
static struct list *l;

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

static void reset_mallocs_until_fail(void) { mallocs_until_fail = -1; }

static struct list *_create_list_empty(void) {
  struct list *emptyList = _create_list();
  return emptyList;
}

static struct list *_create_length_1_list(void) {
  struct list *shortList = _create_list();
  _push_front(shortList, 5, "pichu");
  return shortList;
}

static struct list *_create_longer_list(void) {
  struct list *longerList = _create_list();
  _push_front(longerList, 5, "pichu");
  _push_front(longerList, 7, "pikachu");
  _push_front(longerList, 9, "raichu");
  return longerList;
}

void teardown_bar_list(void) {
  if (l != NULL) {
    _free_list_nodes_and_data(l);
    l = NULL;
  }
}

/******************************************************************************/
/*************************** deep_copy() tests ***************************/
/******************************************************************************/
START_TEST(test_list_deep_copy_basic_easy) {
  struct list *l1 = _create_length_1_list();
  struct list *l2 = deep_copy(l1);

  ck_assert(l2);

  struct node *current_l1 = l1->head;
  struct node *current_l2 = l2->head;

  // checks to make sure l2 isn't null
  ck_assert(current_l2);

  // checks to ensure it is the correct data and the correct id
  ck_assert_str_eq(current_l1->data, current_l2->data);
  ck_assert_int_eq(current_l1->id, current_l2->id);

  _free_list_nodes_and_data(l1);
  _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_deep_copy_basic_hard) {
  struct list *l1 = _create_length_1_list();
  struct list *l2 = deep_copy(l1);

  ck_assert(l2);

  struct node *current_l1 = l1->head;
  struct node *current_l2 = l2->head;

  // checks to make sure l2 isn't null
  ck_assert(current_l2);

  // checks to ensure it is the correct data and the correct id
  ck_assert_str_eq(current_l1->data, current_l2->data);
  ck_assert_int_eq(current_l1->id, current_l2->id);

  // checks to ensure that they did deep copy - double check this though
  ck_assert_ptr_ne(current_l1, current_l2);
  ck_assert_ptr_ne(current_l1->data, current_l2->data);

  _free_list_nodes_and_data(l1);
  _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_deep_copy_long_easy) {
  struct list *l1 = _create_longer_list();

  struct list *l2 = deep_copy(l1);

  ck_assert(l2);

  struct node *current_l1 = l1->head;
  struct node *current_l2 = l2->head;

  ck_assert(current_l2);

  while (current_l1) {
    ck_assert_str_eq(current_l1->data, current_l2->data);
    ck_assert_int_eq(current_l1->id, current_l2->id);
    current_l1 = current_l1->next;
    current_l2 = current_l2->next;
  }

  _free_list_nodes_and_data(l1);
  _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_deep_copy_long_hard) {
  struct list *l1 = _create_longer_list();

  struct list *l2 = deep_copy(l1);

  ck_assert(l2);

  struct node *current_l1 = l1->head;
  struct node *current_l2 = l2->head;

  ck_assert(current_l2);

  while (current_l1) {
    ck_assert_str_eq(current_l1->data, current_l2->data);
    ck_assert_int_eq(current_l1->id, current_l2->id);
    ck_assert_ptr_ne(current_l1, current_l2);
    ck_assert_ptr_ne(current_l1->data, current_l2->data);
    current_l1 = current_l1->next;
    current_l2 = current_l2->next;
  }

  _free_list_nodes_and_data(l1);
  _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_deep_copy_malloc_failure) {
  struct list *l1 = _create_longer_list();

  mallocs_until_fail = 1;
  struct list *l2 = deep_copy(l1);

  ck_assert(!l2);

  _free_list_nodes_and_data(l1);
}
END_TEST

START_TEST(test_list_deep_copy_malloc_failure_hard) {
  struct list *l1 = _create_longer_list();

  mallocs_until_fail = 2;
  struct list *l2 = deep_copy(l1);

  ck_assert(!l2);

  _free_list_nodes_and_data(l1);
}
END_TEST

START_TEST(test_list_deep_copy_empty_list) {
  struct list *l1 = _create_list_empty();
  struct list *l2 = deep_copy(l1);

  ck_assert(l2);
  ck_assert(!l2->head);
  free(l1);
  free(l2);
}
END_TEST

START_TEST(test_list_deep_copy_null_list) {
  struct list *l1 = deep_copy(NULL);
  ck_assert(!l1);
}
END_TEST

/******************************************************************************/
/************************ destroy() tests *****************************/
/******************************************************************************/
START_TEST(test_list_destroy_NULL_list) {
  // Success if there is no error
  destroy(NULL);
}
END_TEST

START_TEST(test_list_destroy_empty) {
  struct list *l = _create_list();
  destroy(l);
}
END_TEST

START_TEST(test_list_destroy_length_1) {
  struct list *l = _create_length_1_list();
  destroy(l);
}
END_TEST

START_TEST(test_list_destroy_longer_list) {
  struct list *l = _create_longer_list();
  destroy(l);
}
END_TEST

Suite *list_suite(void) {
  Suite *s = suite_create("struct list");

  // deep_copy() tests
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_basic_easy);
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_basic_hard);
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_long_easy);
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_long_hard);
  tcase_hack(s, reset_mallocs_until_fail, NULL,
             test_list_deep_copy_malloc_failure);
  tcase_hack(s, reset_mallocs_until_fail, NULL,
             test_list_deep_copy_malloc_failure_hard);
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_null_list);
  tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_deep_copy_empty_list);

  // destroy() tests
  tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list,
             test_list_destroy_NULL_list);
  tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list,
             test_list_destroy_empty);
  tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list,
             test_list_destroy_length_1);
  tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list,
             test_list_destroy_longer_list);

  return s;
}