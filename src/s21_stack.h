#ifndef SRC_S21_STACK_H
#define SRC_S21_SATCK_H
#include <stdio.h>

typedef struct stack_type {
  double v;
  struct stack_type *next;
} stack_t1;

void Push(double v, stack_t1 **stack);
double Pop(stack_t1 **stack);
double Peek(stack_t1 **stack);
void RemoveStack(stack_t1 *list);
int IsEmpty(stack_t1 **stack);

#endif  // SRC_S21_STACK_H