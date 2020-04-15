#include "../list.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define tcase_hack(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}

extern void *_malloc_string(char* str);
extern Node *_create_node(char *data);
extern struct linked_list *_create_list(void);
extern struct hash_table *_create_hash_table(void);
extern int _push_front(struct linked_list *listToPrependTo, char *data);
extern void _empty_list(struct linked_list *listToEmpty);
extern void _free_list_nodes_and_data(struct linked_list *listToEmpty);
extern void _free_list_nodes(struct linked_list *listToEmpty);
extern void _free_node(Node* node);
