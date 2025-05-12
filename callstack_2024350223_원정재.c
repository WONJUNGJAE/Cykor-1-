#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define STACK_SIZE 50

int call_stack[STACK_SIZE];
char stack_info[STACK_SIZE][20];
int SP = -1;
int FP = -1;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);


void push(int num, char* info) {
    call_stack[++SP] = num;
    strcpy(stack_info[SP], info);
}


void pop(int num) {
    SP -= num;
    if (SP < -1) SP = -1;
}


void prologue(char* function) {

    push(-1, "Return Address");


    char SFP[20];
    sprintf(SFP, "%s SFP", function);
    push(FP, SFP);


    FP = SP;
}


void epilogue() {

    SP = FP;


    FP = call_stack[SP];


    pop(2);
}

void print_stack() {
    if (SP == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");

    for (int i = SP; i >= 0; i--) {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}

void func1(int arg1, int arg2, int arg3) {
    int var_1 = 100;


    prologue("func1");


    push(var_1, "var_1");

    print_stack();


    push(13, "arg2");
    push(11, "arg1");

    func2(11, 13);


    pop(2);

    print_stack();


    epilogue();
}

void func2(int arg1, int arg2) {
    int var_2 = 200;


    prologue("func2");


    push(var_2, "var_2");

    print_stack();


    push(77, "arg1");

    func3(77);


    pop(1);

    print_stack();


    epilogue();
}

void func3(int arg1) {
    int var_3 = 300;
    int var_4 = 400;


    prologue("func3");


    push(var_3, "var_3");
    push(var_4, "var_4");

    print_stack();


    epilogue();
}

int main() {

    push(3, "arg3");
    push(2, "arg2");
    push(1, "arg1");

    func1(1, 2, 3);


    pop(3);

    print_stack();
    return 0;
}