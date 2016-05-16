#include <stdio.h>
#include <unistd.h>

#include "ptaxi.h"

#define MALLOC_TAGBIT 4

typedef struct malloc_ll {
  size_t size;
  struct malloc_ll *back;
  struct malloc_ll *next;
} malloc_ll;

malloc_ll *malloc_root;

void __attribute__ ((constructor)) ptaxi_app_policy() {
  ptaxi_policy_privilege_protect_data(MALLOC_TAGBIT);
  ptaxi_policy_privilege_init(MALLOC_TAGBIT);
  ptaxi_enforce_policy();
}

void *pmalloc_internal(size_t size) {
  malloc_ll *node = sbrk(sizeof(malloc_ll) + size);
  node->size = size;
  node->back = NULL;
  node->next = malloc_root;
  if (malloc_root != NULL) {
    malloc_root->back = node;
  }
  ptaxi_base_policy_settag_multi(MALLOC_TAGBIT, node, sizeof(malloc_ll), 1);
  malloc_root = node;
  void *res = ((void *) node) + sizeof(malloc_ll);
  return res;
}

void *pmalloc(size_t size) {
  ptaxi_policy_privilege_enter(MALLOC_TAGBIT);
  void *res = pmalloc_internal(size);
  ptaxi_policy_privilege_leave(MALLOC_TAGBIT);
  return res;
}

void read_size(char *a) {
  malloc_ll *m = (malloc_ll *) (a - sizeof(malloc_ll));
  size_t size = m->size;    // Should trap here!
  printf("Malloc Size = %d \n", size);
}

int main(int argc, char** argv) {

  char *a = (char *) pmalloc(48);
  a[0] = 'H';
  a[1] = 'E';
  a[2] = 'L';
  a[3] = 'L';
  a[4] = 'O';
  a[5] = '\0';

  printf("String = %s\n", a);
  if (argc > 1) {
     // Should pass instead of fail.
  } else {
    read_size(a);
  }
  return 0;
}
