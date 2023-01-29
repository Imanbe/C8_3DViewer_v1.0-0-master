#include "s21_stack.h"
#include <stdlib.h>

void Push(double v, stack_t1 **stack) {
  stack_t1 *tmp = (stack_t1 *)malloc(sizeof(stack_t1));
  if (tmp != NULL) {
    tmp->next = *stack;
    tmp->v = v;
    *stack = tmp;
  }
}

double Pop(stack_t1 **stack) {
  double v;
  stack_t1 *p = *stack;
  v = p->v;
  *stack = p->next;
  free(p);
  return v;
}

double Peek(stack_t1 **stack) {
  double v = 0;
  if (!IsEmpty(stack)) {
    stack_t1 *p = *stack;
    v = p->v;
  }
  return v;
}

void RemoveStack(stack_t1 *list) {
  int k = 0;
  while (!IsEmpty(&list)) {
    stack_t1 *tmp = list;
    ++k;
    list = list->next;
    free(tmp);
  }
  printf("%d\n", k);
}

int IsEmpty(stack_t1 **stack) { return *stack == NULL; }

