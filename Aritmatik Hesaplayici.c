
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

  #define SIZE 100
int variables[256]; // Değişken isimlerini tek karakter olarak düşündüm

typedef struct Stack {
  int top;
  int st[SIZE];
}
Stack;

void initialize(Stack * stack);

int isEmpty(Stack * stack);

int isFull(Stack * stack);

void push(int value, Stack * stack);

int pop(Stack * stack);

char top(Stack * stack);

int precedence(char a, char b);

int IsOperator(char C);

void printStack(Stack S);

void printStackint(Stack S);

void PostFix(Stack * stack, char * Equation, char * PostFix);

int digit(int a);

int getnbr(char * str, int i);

void Solve(char * postfixExpression, char * Equation, Stack * stack);

void sifirla(Stack * stack);

int main() {
  Stack * stack = (Stack * ) malloc(sizeof(Stack));
  initialize(stack);
  char Equation[256] = "";
  char postfixExpression[256];
  FILE * Dosya = fopen("input.txt", "r");
  int i = 0;
  int j = 0;
  char * a;
  for (i = 0; i < 256; i++)
    variables[i] = -9999;
  do {
    fgets(Equation, 100, Dosya);
    printf("Readed Phrase : %s\n", Equation);
    sifirla(stack);
    PostFix(stack, Equation, postfixExpression);
    sifirla(stack);
    Solve(postfixExpression, Equation, stack);
  } while (!feof(Dosya));

  for (i = 0; i < 256; i++) {
    if (variables[i] != -9999)
      printf("\n%c = %d ", i, variables[i]);
  }
  fclose(Dosya);
  return 0;
}

void initialize(Stack * stack) {
  stack -> top = 0;
}

int isEmpty(Stack * stack) {
  if (stack -> top == 0)
    return 1;
  else
    return 0;
}

int isFull(Stack * stack) {
  if (stack -> top == SIZE)
    return 1;
  else
    return 0;

}

void push(int value, Stack * stack) {
  if (isFull(stack)) {
    printf("Stack is Full");
  } else {
    stack -> st[stack -> top] = value;
    stack -> top++;
  }

}

int pop(Stack * stack) {
  if (isEmpty(stack)) {
    printf("Stack is Empty");
    exit(1);
  } else {
    stack -> top--;
    return stack -> st[stack -> top];
  }
}

char top(Stack * stack) {
  return stack -> st[stack -> top - 1];
}

int precedence(char a, char b) {

  int aa, bb;
  if (a == '+' || a == '-' || a == 'û')
    aa = 0;
  else {
    aa = 1;
  }
  if (b == '+' || b == '-' || b == 'û')
    bb = 0;
  else {
    bb = 1;
  }
  if (aa >= bb) {
    return 1;
  }
  return 0;

}

int IsOperator(char C) {
  if (C == '+' || C == '-' || C == '*' || C == '/')
    return 1;

  return 0;
}

void printStack(Stack S) {
  int i;
  if (isEmpty( & S)) {
    printf("Stack : Empty\n");
    return;
  }
  printf("Stack :");
  for (i = 0; i < S.top; i++) {
    printf("%c ", S.st[i]);
  }
  printf("\n");
}

void printStackint(Stack S) {
  int i;
  if (isEmpty( & S)) {
    printf("Stack : Empty\n");
    return;
  }
  printf("Stack :");
  for (i = 0; i < S.top; i++) {
    printf("%d ", S.st[i]);
  }
  printf("\n");
}

void PostFix(Stack * stack, char * Equation, char * PostFix) {

  printf("infix - Postfix \n");
  memset(PostFix, 0, sizeof(PostFix));
  memset(stack -> st, 0, sizeof(stack -> st));
  int len = strlen(Equation);
  int j = 0;
  int i = 0;
  while (Equation[i] != '=') {
    i++;
  }
  int k;
  len = strlen(Equation);
  for (k = 0; k < len - 2; k++) {
    if (Equation[i] == '(') {
      push(Equation[i], stack);
      printf("PostFix : %s ", PostFix);
      printStack( * stack);
    } else if (Equation[i] == ')') {
      while (top(stack) != '(') {
        PostFix[j++] = pop(stack);
        PostFix[j++] = ' ';
        PostFix[j + 1] = '\0';
      }
      pop(stack);
      printf("PostFix : %s ", PostFix);
      printStack( * stack);
    } else if (isalnum(Equation[i])) {
      if (isdigit(Equation[i])) {
        while (isdigit(Equation[i])) {
          PostFix[j++] = Equation[i];
          i++;
        }
        i--;
        PostFix[j++] = ' ';
        PostFix[j + 1] = '\0';
      } else {

        PostFix[j++] = Equation[i];
        PostFix[j++] = ' ';
        PostFix[j + 1] = '\0';
      }
      printf("PostFix : %s ", PostFix);
      printStack( * stack);
    } else if (IsOperator(Equation[i])) {

      if (top(stack) == '(' || !(precedence(top(stack), Equation[i]))) {
        push(Equation[i], stack);
      } else if ((precedence(top(stack), Equation[i]))) {
        while (!isEmpty(stack) && precedence(top(stack), Equation[i]) && top(stack) != '(') {
          PostFix[j++] = pop(stack);
          PostFix[j++] = ' ';
        }
        push(Equation[i], stack);
      }
      printf("PostFix : %s ", PostFix);
      printStack( * stack);
    }
    i++;
  }

  while (!isEmpty(stack)) {
    PostFix[j++] = pop(stack);
    PostFix[j++] = ' ';
  }
  PostFix[j + 1] = '\0';

  printf("\n");

  printf("PostFix : %s \n", PostFix);
  sifirla(stack);
}

int digit(int a) {
  int digit = 0;
  while (a > 0) {
    digit++;
    a /= 10;
  }
  return digit;
}

int getnbr(char * str, int i) {
  int result;
  int puiss;

  result = 0;
  puiss = 1;

  while ((str[i] >= '0') && (str[i] <= '9')) {
    result = (result * 10) + ((str[i]) - '0');
    i++;
  }
  return (result * puiss);
}

void Solve(char * postfixExpression, char * Equation, Stack * stack) {

  printf("Solving Postfix \n");
  printf("\nPostFix = %s\n", postfixExpression);
  int len = strlen(postfixExpression);
  int i = 0;
  int k = 0;
  int tmp, tmp2;
  for (k = 0; k < len; k += 2) {
    if (isdigit(postfixExpression[i])) {

      tmp = getnbr(postfixExpression, i);
      k += digit(tmp) - 1;
      push(tmp, stack);
      i += digit(tmp) + 1;
    } else if (isalnum(postfixExpression[i])) {
      push(variables[postfixExpression[i]], stack);
      i++;
      i++;
    } else if (IsOperator(postfixExpression[i])) {
      tmp = pop(stack);
      tmp2 = pop(stack);
      if (postfixExpression[i] == '*') {
        push(tmp * tmp2, stack);
      } else if (postfixExpression[i] == '/') {
        push(tmp2 / tmp, stack);
      } else if (postfixExpression[i] == '+') {
        push(tmp + tmp2, stack);
      } else if (postfixExpression[i] == '-') {
        push(tmp2 - tmp, stack);
      }

      i++;
      i++;
    }

    printStackint( * stack);
  }
  variables[Equation[0]] = pop(stack);
  printf("\n%c = %d", Equation[0], variables[Equation[0]]);
  printf("\n\n");
}

void sifirla(Stack * stack) {
  int i;
  int k = stack -> top;
  for (i = 0; i < k; i++) {
    pop(stack);
  }
}
