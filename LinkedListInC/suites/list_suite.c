#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct linked_list *l;

// static struct linked_list *_create_list_size_1(void) {
//     struct linked_list *longerList = _create_list();
//     _push_front(longerList, _malloc_string("Charmander"));
//     return longerList;
// }

// static struct linked_list *_create_list_size_2(void) {
//     struct linked_list *longerList = _create_list();
//     _push_front(longerList, _malloc_string("Charmander"));
//     _push_front(longerList, _malloc_string("Pikachu"));
//     return longerList;
// }

// static struct linked_list *_create_longer_list2(void) {
//     struct linked_list *longerList = _create_list();
//     _push_front(longerList, _malloc_string("Charmander"));
//     _push_front(longerList, _malloc_string("Sqirtle"));
//     _push_front(longerList, _malloc_string("Pikachu"));
//     return longerList;
// }

static struct linked_list *_create_length_1_list(void) {
    struct linked_list *shortList = _create_list();
    _push_front(shortList, _malloc_string("Squirtle"));
    return shortList;
}

static struct linked_list *_create_longer_list(void) {
    struct linked_list *longerList = _create_list();
    _push_front(longerList, _malloc_string("Dratini"));
    _push_front(longerList, _malloc_string("Squirtle"));
    _push_front(longerList, _malloc_string("Eevee"));
    return longerList;
}

void teardown_bar_list(void) {
    if (l != NULL) {
        _free_list_nodes_and_data(l);
        l = NULL;
    }
}


START_TEST(test_list_create_list_basic) {
    struct linked_list *l1 = create_list();
    ck_assert_msg(l1, "create_list should not return null");
    ck_assert_msg(!l1->size, "create_list should return a list of size 0");
    ck_assert_msg(!l1->head, "create_list should return a list with no head");
    free(l1);
}
END_TEST


START_TEST(test_list_create_malloc_failure) {
    mallocs_until_fail = 0;
    struct linked_list *l1 = create_list();
    ck_assert_msg(!l1, "create_list improperly handles malloc failure");
}
END_TEST


/******************************************************************************/
/************************** push_front() tests ********************************/
/******************************************************************************/

void setup_list_push_front(void) {
    reset_mallocs_until_fail();
    l = _create_list();
    ck_assert(l);
}

void teardown_list_push_front(void) {
    if (l) {
        free(l);
        l = NULL;
    }
}

START_TEST(test_list_push_front_NULL_list) {
    char *b = _malloc_string("Squirtle");
    ck_assert_msg(push_front(NULL, b) != 0, "should not be able to push to a NULL list");
    free(b);
}
END_TEST

START_TEST(test_list_push_front_NULL_data) {
    ck_assert_msg(push_front(l, NULL) == 0, "successful push_front should return 0");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should add a node");
    ck_assert_msg(!l->head->next, "you may be adding extra nodes somehow");
    ck_assert_msg(!l->head->data, "adding NULL data shoud persist as NULL");
    free(l->head);
}
END_TEST

START_TEST(test_list_push_front_empty) {
    char *b = _malloc_string("Gibran");
    ck_assert_msg(push_front(l, b) == 0, "push_front should succeed on an empty list");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should should add a node to list");
    ck_assert_msg(!l->head->next, "push_front should only add one node");
    ck_assert_msg(l->head->data == b, "push_front adds wrond data");

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head);
    free(b);
}
END_TEST

START_TEST(test_list_push_front_nonempty) {
    // Put some stuff in the struct linked_list
    char *b0 = _malloc_string("Pikachu");
    char *b1 = _malloc_string("Squirtle");
    char *b2 = _malloc_string("Charmander");
    l->head = _create_node(b0);
    l->head->next = _create_node(b1);
    l->size = 3;

    char *b3 = _malloc_string("Bulbasaur");
    ck_assert_msg(push_front(l, b3) == 0, "push_front should return 0 on success");
    ck_assert_msg(l->size == 4, "push_front should increment size");
    ck_assert(l->head);
    ck_assert_msg(l->head->data == b3, "push_front should push correct data");

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head->next->next->next);
    free(l->head->next->next);
    free(l->head->next);
    free(l->head);
    free(b0);
    free(b1);
    free(b2);
    free(b3);
}
END_TEST

/******************************************************************************/
/************************** push_back() tests *********************************/
/******************************************************************************/
START_TEST(test_list_push_back_empty) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Eevee");
    ck_assert_msg(push_back(l1, b0) == 0, "push_back should succeed on an empty list");
    ck_assert_msg(l1->head->data == b0, "push_back should add a node with correct data");
    ck_assert_msg(l1->size == 1, "push_back should increment size");
    free(l1->head);
    free(l1);
    free(b0);

}
END_TEST
START_TEST(test_list_push_back_non_empty) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Bulbasaur");
    char *b1 = _malloc_string("Squirtle");

    _push_front(l1, b0);

    ck_assert_msg(push_back(l1, b1) == 0, "push_back should retunr 0 on success");
    ck_assert_msg(b0 == l1->head->data, "push_back should not change front of list");
    ck_assert_msg(l1->size == 2, "push_back should increment size");

    free(l1->head->next);
    free(l1->head);
    free(b0);
    free(b1);
    free(l1);
}
END_TEST
START_TEST(test_list_push_back_null) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Pichu");
    ck_assert_msg(push_back(NULL, b0) != 0, "push_back shouldn't return 0 with null list");
    ck_assert_msg(push_back(l1, NULL) == 0, "push_back should return 0 with null data and non-null list");
    ck_assert_msg(l1->size == 1, "push_back should increase size");
    ck_assert_msg(!l1->head->data, "adding null data should add null data");

    free(b0);
    free(l1->head);
    free(l1);
}
END_TEST

/******************************************************************************/
/**************************** remove_at_index() tests *************************/
/******************************************************************************/
START_TEST(test_list_remove_at_index_NULL_list) {
    char *dataOut = (char *) 0xDEADBEEFU;
    ck_assert(remove_at_index(NULL, &dataOut, 0) != 0);
}
END_TEST

START_TEST(test_list_remove_at_index_NULL_dataOut) {
    l = _create_length_1_list();
    ck_assert(remove_at_index(l, NULL, 0) != 0);
}
END_TEST

START_TEST(test_list_remove_at_index_out_of_bounds) {
    l = _create_length_1_list();
    ck_assert(remove_at_index(l, NULL, -1) != 0);
}
END_TEST

START_TEST(test_list_remove_at_index_front) {
    l = _create_longer_list();
    char *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert(dataOut);
    int nameCheck = !strcmp(dataOut, "Eevee");
    free(dataOut);
    ck_assert(result == 0);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(!strcmp(l->head->data, "Squirtle"));
    ck_assert(!strcmp(l->head->next->data, "Dratini"));
}
END_TEST

START_TEST(test_list_remove_at_index_middle) {
    l = _create_longer_list();
    char *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 1);
    ck_assert(dataOut);
    int nameCheck = !strcmp(dataOut, "Squirtle");
    free(dataOut);
    ck_assert(result == 0);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(!strcmp(l->head->data, "Eevee"));
    ck_assert(!strcmp(l->head->next->data, "Dratini"));
    ck_assert(!l->head->next->next);
}
END_TEST

START_TEST(test_list_remove_at_index_back) {
    l = _create_longer_list();
    char *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 2);
    ck_assert(dataOut);
    int nameCheck = !strcmp(dataOut, "Dratini");
    free(dataOut);
    ck_assert(result == 0);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(!strcmp(l->head->data, "Eevee"));
    ck_assert(!strcmp(l->head->next->data, "Squirtle"));
    ck_assert(!l->head->next->next);
}
END_TEST

START_TEST(test_list_remove_at_index_length_1) {
    l = _create_length_1_list();
    char *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert(dataOut);
    int nameCheck = !strcmp(dataOut, "Squirtle");
    free(dataOut);
    ck_assert(result == 0);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);
}
END_TEST

/******************************************************************************/
/************************** add_at_index() tests ***************************************/
/******************************************************************************/
START_TEST(test_list_add_at_index_out_of_bounds) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Squirtle");

    ck_assert(add_at_index(l1, b0, -1) != 0);

    _push_front(l1, b0);

    ck_assert(add_at_index(l1, b0, 2) != 0);

    free(l1->head);
    free(l1);
    free(b0);

}
END_TEST

START_TEST(test_list_add_at_index_empty_list) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Mawile");
    char *b1 = _malloc_string("Charmander");

    ck_assert(add_at_index(l1, b0, 0) == 0);
    ck_assert_int_eq(l1->size, 1);
    ck_assert_ptr_eq(l1->head->data, b0);

    ck_assert(add_at_index(l1, b1, 2) != 0);

    ck_assert(add_at_index(l1, b1, 1) == 0);

    ck_assert_int_eq(l1->size, 2);

    _free_list_nodes_and_data(l1);


}
END_TEST

START_TEST(test_list_add_at_index_non_empty_list) {

    struct linked_list *l1 = _create_longer_list();
    char *b0 = _malloc_string("Pikachu");
    ck_assert(add_at_index(l1, b0, 1) == 0);
    ck_assert_ptr_eq(l1->head->next->data, b0);
    ck_assert_int_eq(l1->size, 4);

    _free_list_nodes_and_data(l1);

}
END_TEST

START_TEST(test_list_add_at_index_null) {
    struct linked_list *l1 = _create_list();
    char *b0 = _malloc_string("Pikachu");

    ck_assert(add_at_index(NULL, NULL, 0) != 0);

    ck_assert(add_at_index(NULL, b0, 0) != 0);

    ck_assert(add_at_index(l1, NULL, 0) == 0);
    ck_assert_int_eq(l1->size, 1);
    ck_assert(!l1->head->data);

    free(l1->head);
    free(l1);
    free(b0);
}
END_TEST

/******************************************************************************/
/*************************** pop_front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_front_NULL_list) {
    char *dataOut = (char *) 0xDEADBEEFU;
    ck_assert(pop_front(NULL, &dataOut) != 0);
}
END_TEST

START_TEST(test_list_pop_front_NULL_dataOut) {
    l = _create_list();
    ck_assert(pop_front(l, NULL) != 0);
}
END_TEST

START_TEST(test_list_pop_front_empty) {
    l = _create_list();
    char *dataOut = (char *) 0xDEADBEEFU;
    ck_assert(pop_front(l, &dataOut) != 0);
}
END_TEST

START_TEST(test_list_pop_front_nonempty) {
    l = _create_length_1_list();
    char *Squirtle = NULL;
    int result = pop_front(l, &Squirtle);
    ck_assert(Squirtle);
    int nameCheck = !strcmp(Squirtle, "Squirtle");
    free(Squirtle);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_front_longer_list) {
    l = _create_longer_list();
    char *data = NULL;
    int result = pop_front(l, &data);
    ck_assert(data);
    int nameCheck = !strcmp(data, "Eevee");
    free(data);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(nameCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 2);
    ck_assert(!strcmp(l->head->data, "Squirtle"));
    ck_assert(!strcmp(l->head->next->data, "Dratini"));
    ck_assert(!l->head->next->next);

    result = pop_front(l, &data);
    nameCheck = !strcmp(data, "Squirtle");
    free(data);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(nameCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 1);
    ck_assert(!strcmp(l->head->data, "Dratini"));
    ck_assert(!l->head->next);
}
END_TEST

/******************************************************************************/
/**************************** pop_back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_back_NULL_list) {
    char *dataOut = (char *)0xDEADBEEFU;
    ck_assert(pop_back(NULL, &dataOut) != 0);
}
END_TEST

START_TEST(test_list_pop_back_NULL_dataOut) {
    l = _create_list();
    ck_assert(pop_back(l, NULL) != 0);
}
END_TEST

START_TEST(test_list_pop_back_empty) {
    l = _create_list();
    char *dataOut = (char *)0xDEADBEEFU;
    ck_assert(pop_back(l, &dataOut) != 0);
}
END_TEST

START_TEST(test_list_pop_back_nonempty) {
    l = _create_length_1_list();
    char *Squirtle = NULL;
    int result = pop_back(l, (char **) &Squirtle);
    ck_assert(Squirtle);

    int nameCheck = !strcmp(Squirtle, "Squirtle");
    free(Squirtle);
    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(nameCheck, "returned value with the wrong name");
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_back_longer_list) {
    l = _create_longer_list();
    char *data = NULL;
    int result = pop_back(l, (char **) &data);
    ck_assert(data);
    int name_check = !strcmp(data, "Dratini");
    free(data);
    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(name_check, "returned value with the wrong name");
    ck_assert_int_eq(l->size, 2);
    ck_assert(!strcmp(l->head->data, "Eevee"));
    ck_assert(!strcmp(l->head->next->data, "Squirtle"));
    ck_assert(!l->head->next->next);

    result = pop_back(l, (char **) &data);
    name_check = !strcmp(data, "Squirtle");
    free(data);
    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(name_check, "returned value with the wrong name");
    ck_assert_int_eq(l->size, 1);
    ck_assert(!strcmp(l->head->data, "Eevee"));
    ck_assert(!l->head->next);
}
END_TEST

/******************************************************************************/
/******************************* get() tests **********************************/
/******************************************************************************/
void checkLongerListUnchanged(void) {
    ck_assert(!strcmp(l->head->data, "Eevee"));
    ck_assert(!strcmp(l->head->next->data, "Squirtle"));
    ck_assert(!strcmp(l->head->next->next->data, "Dratini"));
    ck_assert(!l->head->next->next->next);
}

START_TEST(test_list_get_NULL_list) {
    char *b = (char *)0xDEADBEEFU;
    ck_assert(get(NULL, 0, &b) != 0);
}
END_TEST

START_TEST(test_list_get_NULL_dataOut) {
    l = _create_longer_list();
    ck_assert(get(l, 0, NULL) != 0);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_negative_index) {
    l = _create_longer_list();
    char *b = (char *) 0xDEADBEEFU;
    ck_assert(get(l, -1, &b) != 0);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_front) {
    l = _create_longer_list();
    char *b = (char *) 0xDEADBEEFU;
    ck_assert(get(l, 0, &b) == 0);
    ck_assert(!strcmp(b, "Eevee"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_middle) {
    l = _create_longer_list();
    char *b = (char *) 0xDEADBEEFU;
    ck_assert(get(l, 1, &b) == 0);
    ck_assert(!strcmp(b, "Squirtle"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_back) {
    l = _create_longer_list();
    char *b = (char *)0xDEADBEEFU;
    ck_assert(get(l, 2, &b) == 0);
    ck_assert(!strcmp(b, "Dratini"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_out_of_bounds_index) {
    l = _create_longer_list();
    char *b = (char *) 0xDEADBEEFU;
    ck_assert(get(l, 3, &b) != 0);
    checkLongerListUnchanged();
}
END_TEST

/******************************************************************************/
/**************************** contains() tests ********************************/
/******************************************************************************/

START_TEST(test_list_contains_NULL_list) {
    char *henry = _malloc_string("Gibran");
    char *dataOut = (char *) 0xDEADBEEFU;
    int result = contains(NULL, (char *) henry, &dataOut);
    free(henry);
    ck_assert(!result);
}
END_TEST

START_TEST(test_list_contains_NULL_dataOut) {
    char *henry = _malloc_string("Gibran");
    l = _create_longer_list();
    int result = contains(l, (char *) henry, NULL);
    free(henry);
    ck_assert(!result);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_empty) {
    l = _create_list();
    char *henry = _malloc_string("Gibran");
    char *dataOut = (char *) 0xDEADBEEFU;
    int result = contains(l, (char *) henry, &dataOut);
    free(henry);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_contains_not_contained) {
    l = _create_longer_list();
    char *henry = _malloc_string("Marlet");
    char *dataOut = (char *)0xDEADBEEFU;
    int result = contains(l, (char *) henry, &dataOut);
    free(henry);
    ck_assert(!result);
    ck_assert(!dataOut);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_is_contained) {
    l = _create_longer_list();
    char *Squirtle = _malloc_string("Squirtle");
    char *dataOut = (char *)0xDEADBEEFU;
    int result = contains(l, (char *) Squirtle, &dataOut);
    free(Squirtle);
    ck_assert(result);
    ck_assert(dataOut != Squirtle);
    ck_assert(!strcmp(dataOut, "Squirtle"));
    checkLongerListUnchanged();
}
END_TEST

/******************************************************************************/
/**************************** merge_nodes() tests *****************************/
/******************************************************************************/

START_TEST(test_list_merge_nodes_NULL_list) {
    ck_assert(merge_nodes(NULL, 0) != 0);
}
END_TEST

START_TEST(test_list_merge_nodes_negative_index) {
    l = _create_longer_list();
    ck_assert(merge_nodes(l, -1) != 0);
}
END_TEST

START_TEST(test_list_merge_nodes_out_of_bounds_index) {
    l = _create_longer_list();
    ck_assert(merge_nodes(l, 2) != 0);
}
END_TEST

START_TEST(test_list_merge_nodes) {
    l = _create_longer_list();
    ck_assert_msg(merge_nodes(l, 1) == 0, "merge_nodes should return 0 on success");
    ck_assert_msg(l->size == 2, "merge_nodes should decrease size");
    ck_assert(!strcmp(l->head->next->data, "SquirtleDratini"));
    teardown_bar_list();
    l = _create_longer_list();
    ck_assert_msg(merge_nodes(l, 0) == 0, "merge_nodes should return 0 on success");
    ck_assert_msg(l->size == 2, "merge_nodes should decrease size");
    ck_assert(!strcmp(l->head->data, "EeveeSquirtle"));
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/
START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    empty_list(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    l = _create_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    l = _create_length_1_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    l = _create_longer_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST


Suite *list_suite(void) {
    Suite *s = suite_create("struct linked_list");
    
    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_malloc_failure);

    // push_front() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_data);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_nonempty);


    // push_back() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_non_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_null);

    // remove_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_length_1);

    // pop_front() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_longer_list);

    // pop_back() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_longer_list);

    // add_at_index() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_out_of_bounds);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_non_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_null);

    // get() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_out_of_bounds_index);

    // contains() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_not_contained);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_is_contained);

    // merge_nodes() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_merge_nodes_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_merge_nodes_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_merge_nodes_out_of_bounds_index);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_merge_nodes);


    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_longer_list);
    return s;
}