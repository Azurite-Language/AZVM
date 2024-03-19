#ifndef STREAM_READER_H_INCLUDED
#define STREAM_READER_H_INCLUDED
#include <stdint.h>

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>

#include "constant.h"
#include "undef.h"
#define GOTO_c 2
#define EXIT_c 1

#define READER_SIZE 200

static FILE *reader_ = NULL;
#define OPEN(url) (reader_ = fopen(url, "rb"))
#define GOTO_(line) (fseek(reader_, line * 4 * sizeof(paramType), SEEK_SET))
#define GOTO_REL(line) (fseek(reader_, line * 4 * sizeof(paramType), SEEK_CUR))
#define EXECUTE_READER_(datas) \
    fread(datas, sizeof(paramType), 4, reader_) // fseek(reader_,4* sizeof(paramType), SEEK_CUR)

#define PUSH_PARAMETERS(datas, e1, e2)            \
    if (datas[3] & 0x2)                           \
        e1 = TOP_RELATIVE(datas[1]).internal.INT; \
    else                                          \
    {                                             \
        e1 = TOP().internal.INT;                  \
        POP();                                    \
    }                                             \
    if (datas[3] & 0x1)                           \
        e2 = TOP_RELATIVE(datas[2]).internal.INT; \
    else                                          \
    {                                             \
        e2 = TOP().internal.INT;                  \
        POP();                                    \
    }

#define EXECUTE_ORDER(datas)                                      \
    uint32_t e1;                                                  \
    uint32_t e2;                                                  \
    switch (datas[0])                                             \
    {                                                             \
    case OP_GOTO:                                                 \
        GOTO_(datas[1]);                                          \
        printf("go to %d", datas[1]);                             \
        break;                                                    \
    case OP_PUSH:                                                 \
        PUSH(INT, datas[1]);                                      \
        printf("push value: %d", datas[1]);                       \
        break;                                                    \
    case OP_IF:                                                   \
        if (!(TOP().internal.INT))                                \
            GOTO_REL(1);                                          \
        POP();                                                    \
                                                                  \
        break;                                                    \
    case OP_IFn:                                                  \
        if (TOP().internal.INT)                                   \
            GOTO_REL(1);                                          \
        POP();                                                    \
        break;                                                    \
    case OP_EQUAL:                                                \
        PUSH_PARAMETERS(datas, e1, e2);                           \
        PUSH(INT, (e1 = e2));                                     \
        break;                                                    \
    case OP_NEQUAL:                                               \
        PUSH_PARAMETERS(datas, e1, e2);                           \
        PUSH(INT, (e1 != e2));                                    \
        break;                                                    \
    case OP_EXIT:                                                 \
        printf("the program returned: %d", TOP().internal.INT);   \
        break;                                                    \
    case OP_PLUS:                                                 \
        PUSH_PARAMETERS(datas, e1, e2)                            \
        PUSH(INT, (e1 + e2));                                     \
        break;                                                    \
    case OP_MINUS:                                                \
        break;                                                    \
        PUSH_PARAMETERS(datas, e1, e2)                            \
        PUSH(INT, (e1 - e2));                                     \
    case OP_MULT:                                                 \
        PUSH_PARAMETERS(datas, e1, e2)                            \
        PUSH(INT, (e1 + e2));                                     \
        break;                                                    \
    case OP_PUSH_CALLSTACK:                                       \
        PUSH_CALLSTACK(ftell(reader_) / (4 * sizeof(paramType))); \
        break;                                                    \
    case OP_POP_CALLSTACK:                                        \
        POP_CALLSTACK;                                            \
        break;                                                    \
    default:                                                      \
        printf("%d not implemented (yet)", datas[0]);             \
        exit(1);                                                  \
        break;                                                    \
    }

#endif