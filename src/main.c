#include <stdio.h>
#include <string.h>
#include <assert.h>

#if 0
#include "stream_reader.h"
#include "callstack.h"
#include "constant.h"
#include "undef.h"

#define SET_ENUM(truc)

int main()
{

    paramType datas[4];
    //char datas[100];

#include "constant.h"
    OPEN("./output.byte");
    while (1)
    {

        EXECUTE_READER_(datas);
        printf("current truc: %d", datas[0]);
        EXECUTE_ORDER(datas);
    }
#include "undef.h"
}
#endif

#if 0
#include "operations.h"
int main(){
    for(long long i = 0; i < 1000000; i++){
        for(int y = 0; y < 100; y++)
            PUSH(STR, "Bonjour messieurs fideles. ");
        for(int y = 0; y < 99; y++)
            ADDv
        //printf("%d\n", stack_ptr);
        //assert(stack_ptr == 0);
        stack_ptr = 0;
    }
    stack_ptr++;
    DEBUG_STACK();
}
#endif

#if 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    for(long long i = 0; i < 1000000; i++){
        char* i = calloc(8192, sizeof(char));
        char* to_cat = calloc(8192, (sizeof(char)));
        for(int y = 0; y < 99; y++){
            strcat(to_cat, "Bonjour messieurs fideles. ");
        }
        strcat(i, to_cat);
        free(i);
        free(to_cat);
    }

}

#endif

#if 1
#define STREAM_READER_H_INCLUDED
#include "callstack.h"
#include "constant.h"
#define READER_SIZE 200

static FILE *reader_ = NULL;
#define OPEN(url) (reader_ = fopen(url, "rb"))
#define GOTO_(line) (fseek(reader_, (line) * 4 * sizeof(paramType), SEEK_SET))
#define GOTO_REL(line) (fseek(reader_, (line) * 4 * sizeof(paramType), SEEK_CUR))
#define EXECUTE_READER_(datas) \
    fread(datas, sizeof(paramType), 4, reader_)

#define modifiers(data) (-(1 - (2 * (data & 0x4))))
#define PUSH_PARAMETERS(datas, e1, e2) \
    if ((datas[3] >> 2) & 0b01)        \
    {                                  \
        e2 = TOP_RELATIVE(datas[2]);   \
    }                                  \
    else if ((datas[3] >> 2) & 0b10)   \
    {                                  \
        e2 = stack[datas[2]];          \
    }                                  \
    else                               \
    {                                  \
        e2 = TOP();                    \
        POP();                         \
    }                                  \
    if (datas[3] & 0b01)               \
    {                                  \
        e1 = TOP_RELATIVE(datas[1]);   \
    }                                  \
    else if (datas[3] & 0b10)          \
    {                                  \
        e1 = stack[datas[1]];          \
    }                                  \
    else                               \
    {                                  \
        e1 = TOP();                    \
        POP();                         \
    }                                  \
    printf("e1: %d e2: %d\n", e1.internal.INT, e2.internal.INT);

void print_debug(paramType *datas)
{
    printf("%s %d %d %d\n", OPCODE_NAMES[datas[0]], datas[1], datas[2], datas[3]);
    printf("stack: \n");
    for (size_t i = 0; i < stack_ptr; i++)
    {
        printf("%d", stack[i].internal.INT);
        if (callstack_ptr != 0 && CALL_STACK_PTR_POS == i)
            printf(" <- callstack");
        printf("\n");
    }
}

int main()
{
    size_t jecpa;
    // char datas[100];
    char buffer[200];
    OPEN("./output.byte");
    value e1;
    value e2;
    size_t iterator;
    uint32_t entry;
    size_t offset = 0;
    while (1)
    {
        fgetc(stdin);
        paramType datas[4] = {0};
        EXECUTE_READER_(datas);
        switch (datas[0])
        {
        case OP_GOTO:
            GOTO_(datas[1] - 1 + offset);
            // printf("go to %d\n", datas[1]);
            break;
        case OP_PUSH:
            PUSH(INT, datas[1]);
            // printf("push value: %d\n", datas[1]);
            break;
        case OP_IF:
            if (!(TOP().internal.INT))
                GOTO_REL(1);
            POP();
            break;
        case OP_IFn:
            if (!TOP().internal.INT)
                GOTO_REL(1);
            POP();
            break;
        case OP_EQUAL:
            PUSH_PARAMETERS(datas, e1, e2)
            VISIT2(
                e1, e2, { PUSH(INT, strcmp(x, y) == 0); };, { PUSH(INT, *x == *y); }, { PUSH(INT, *x == *y); }, { PUSH(INT, *x == *y); }, { return 2; }, { return 2; })
            // PUSH(INT, (e1 == e2));
            break;
        case OP_NEQUAL:
            PUSH_PARAMETERS(datas, e1, e2);
            VISIT2(
                e1, e2, { PUSH(INT, strcmp(x, y) != 0); }, { PUSH(INT, *x != *y); }, { PUSH(INT, *x != *y); }, { PUSH(INT, *x != *y); }, { return 2; }, { return 2; });
            // PUSH(INT, (e1 != e2));
            break;
        case OP_EXIT:
            printf("the program returned: %d\n", TOP().internal.INT);
            exit(datas[1]);
            break;
        case OP_PLUS:
            PUSH_PARAMETERS(datas, e1, e2)
            VISIT2(
                e1, e2, { return 2; }, { PUSH(INT, *x + *y); }, { PUSH(INT, *x + *y); }, { PUSH(INT, *x + *y); }, { return 2; }, { return 2; });
            // PUSH(INT, (e1 + e2));
            break;
        case OP_MINUS:
            PUSH_PARAMETERS(datas, e1, e2);
            // PUSH(INT, (e1 - e2));
            VISIT2(
                e1, e2, { return 2; }, { return 2; }, { PUSH(INT, *x - *y); }, { PUSH(INT, *x - *y); }, { return 2; }, { return 2; });

            break;
        case OP_MULT:
            PUSH_PARAMETERS(datas, e1, e2);
            VISIT2(
                e1, e2, { return 2; }, { return 2; }, { PUSH(INT, *x * *y); }, { PUSH(INT, *x * *y); }, { return 2; }, { return 2; });
            break;
        case OP_INF:
            PUSH_PARAMETERS(datas, e1, e2);
            VISIT2(
                e1, e2, { return 2; }, { return 2; }, { PUSH(INT, *x < *y); }, { PUSH(INT, *x < *y); }, { return 2; }, { return 2; });
            // PUSH(INT, (e1 * e2));
            break;
        case OP_DIV:
            PUSH_PARAMETERS(datas, e1, e2);
            VISIT2(
                e1, e2, { return 2; }, { return 2; }, { PUSH(INT, *x + *y); }, { PUSH(INT, *x + *y); }, { return 2; }, { return 2; });
            // PUSH(INT, (e1 / e2));
            break;
        case OP_PUSH_CALLSTACK:
            PUSH_CALLSTACK(datas[1]);
            break;
        case OP_JSR:
            PUSH_CALLSTACK_ADDR((ftell(reader_) / (4 * sizeof(paramType))) - 1);
            callstack_ptr++;
            GOTO_(datas[1] - 1 + offset);
            printf("return addr is: %d\n", CALL_STACK_PTR_LINE + 1);
            break;
        case OP_POP_CALLSTACK:
            printf("Returning to: %d\n", CALL_STACK_PTR_LINE + 1);
            POP_CALLSTACK(datas[1]);
            break;
        case OP_INPUT:
            printf("%s", TOP().internal.STR);
            POP();
            scanf("%s", buffer);
            // strcpy(pool[datas[2]], buffer);
            PUSH(STR, buffer);
            break;
        case OP_ALLOCATE:
            offset++;
            PUSH(STR, "\0");
            break;
        case OP_DC:
            jecpa = ftell(reader_);
            fseek(reader_, -2 * sizeof(paramType), SEEK_CUR);
            fread(&(buffer[0]), sizeof(char), 1, reader_);
            for (iterator = 1; buffer[iterator - 1] != '\0'; iterator++)
            {
                fread(&(buffer[iterator]), sizeof(char), 1, reader_);
            }
            PUSH(STR, buffer);
            // strcpy(pool[datas[1]],buffer);
            entry = ftell(reader_) + (16 - (ftell(reader_) % 16));
            offset += (entry - jecpa) / (4 * sizeof(paramType)) + 1;
            fseek(reader_, entry, SEEK_SET);
            break;
        case OP_PUSHA:
            PUSH_ADDRESS(datas[1]);
            break;
        case OP_GET:
            // empty

            break;
        default:
            printf("%d not implemented (yet)", datas[0]);
            exit(1);
            break;
        }
        print_debug(datas);
    }
}

#endif
