/*
 * File:
 * Author(s):
 *   Vasileios Trigonakis
 */

#include "intset.h"
#include "utils.h"

__thread ssmem_allocator_t* alloc;

node_t*
new_node(skey_t key, sval_t val, node_t* next, int initializing)
{
  volatile node_t* node;
#if GC == 1
  if (unlikely(initializing))		/* for initialization AND the coupling algorithm */
    {
      node = (volatile node_t*) ssalloc(sizeof(node_t));
    }
  else
    {
      node = (volatile node_t*) ssmem_alloc(alloc, sizeof(node_t));
    }
#else
  node = (volatile node_t*) ssalloc(sizeof(node_t));
#endif
  
  if (node == NULL) 
    {
      perror("malloc @ new_node");
      exit(1);
    }

  node->key = key;
  node->val = val;
  node->next = next;

#if defined(__tile__)
  /* on tilera you may have store reordering causing the pointer to a new node
     to become visible, before the contents of the node are visible */
  MEM_BARRIER;
#endif	/* __tile__ */

  return (node_t*) node;
}

intset_t *set_new()
{
  intset_t *set;
  node_t *min, *max;

  if ((set = (intset_t *)ssalloc_aligned(CACHE_LINE_SIZE, sizeof(intset_t))) == NULL) 
    {
      perror("malloc");
      exit(1);
    }

  max = new_node(KEY_MAX, 0, NULL, 1);
  /* ssalloc_align_alloc(0); */
  min = new_node(KEY_MIN, 0, max, 1);
  set->head = min;

  MEM_BARRIER;
  return set;
}

void
node_delete(node_t *node) 
{
#if GC == 1
  ssmem_free(alloc, (void*) node);
#else
  /* ssfree(node); */
#endif
}

void set_delete_l(intset_t *set)
{
  node_t *node, *next;

  node = set->head;
  while (node != NULL) 
    {
      next = node->next;
      ssfree((void*) node);		/* TODO : fix with ssmem */
      node = next;
    }
  ssfree(set);
}

int set_size(intset_t* set)
{
  int size = 0;
  node_t *node;

  /* We have at least 2 elements */
  node = set->head->next;
  while (node->next != NULL) 
    {
      size++;
      node = node->next;
    }

  return size;
}



	
