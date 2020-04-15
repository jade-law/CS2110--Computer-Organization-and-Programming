#include "../tl4.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define tcase_hack(suite, setup_fixture, teardown_fixture, func)    \
  {                                                                 \
    TCase *tc = tcase_create(STRINGIFY(func));                      \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func);                                       \
    suite_add_tcase(s, tc);                                         \
  }

extern struct list *_create_list(void);
extern int _push_front(struct list *listToAddTo, int level, char *type);
extern void _empty_list(struct list *listToEmpty);
extern void _free_list_nodes_and_data(struct list *listToEmpty);
