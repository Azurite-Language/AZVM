#ifndef BUILTIN_H_VM
#define BUILTIN_H_VM

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "meta.h"
#include "pool.h"
#include "callstack.h"

typedef enum
{
    STR,
    CHAR,
    INT,
    FLOAT,
    OTHER
} vmtype;

typedef uint32_t paramType;

typedef struct
{
    /*vmtype type;
    bool is_list;
    size_t count;*/
    uint32_t chunk;
    union
    {
        char CHAR;
        int64_t INT;
        double FLOAT;
        int64_t *INT_LIST;
        double *FLOAT_LIST;
        char *CHAR_LIST;
        char *STR;
        void *OTHER;
    } internal;
} value;

#define WRITE_CHUNK(type, is_list, count) (((((uint32_t)count << 8) | (unsigned char)is_list) << 8) | (unsigned char)type)
#define GET_COUNT(x) (x >> 16)
#define GET_ISLIST(x) ((x >> 8) & 1)
#define GET_TYPE(x) (x & 0xF)

#define GETDEFAULTINTV ((int64_t)0)
#define GETDEFAULTCHARV ((char)0)
#define GETDEFAULTFLOATV ((float)0.0f)
#define GETDEFAULTSTRV (pool[stack_ptr])

#define INITINT(x) x
#define INITFLOAT INITINT
#define INITCHAR INITINT
#define INITOTHER INITINT
#define INITSTR(x) (strcpy(POOL(stack_ptr - 1), x), POOL(stack_ptr - 1))

#define GETDEFAULTV(type) GETDEFAULT##type##V

#if 0
#define GETDEFAULT(typea) ((value){.type = typea, .is_list = false, .count = 0, .internal = {.typea = GETDEFAULTV(typea)}})
#define INITV(typea, v) ((value){.type = typea, .is_list = false, .count = 0, .internal = {.typea = INIT##typea(v)}})
#endif

#define GETDEFAULT(typea) ((value){.chunk = WRITE_CHUNK(typea, 0, 0), .internal = {.typea = GETDEFAULTV(typea)}})
#define INITV(typea, v) ((value){.chunk = WRITE_CHUNK(typea, 0, 0), .internal = {.typea = INIT##typea(v)}})

static value stack[200] = {GETDEFAULT(INT)};
static uint32_t stack_ptr = 0;

#define PUSHDEFAULT(typea) stack[stack_ptr++] = GETDEFAULT(typea)
#define PUSH(typea, v) stack[stack_ptr++] = INITV(typea, v)
#define PUSH_ADDRESS(adress) stack[stack_ptr++] = stack[adress];


#define POP()                                                                                  \
    {                                                                                          \
        if (GET_ISLIST(stack[--stack_ptr].chunk) || GET_TYPE(stack[stack_ptr].chunk) == OTHER) \
            free(stack[stack_ptr].internal.OTHER);                                             \
    }
#define TOP() stack[stack_ptr - 1]
#define UNFOLD(_BODY)       \
    while (stack_ptr-- > 0) \
    {                       \
        _BODY;              \
    }                       \
    stack_ptr = 0;
#define DEBUG_STACK() UNFOLD({ printf("%d:\t", stack_ptr); logvm(TOP()); puts("\n"); })
#define TOP_RELATIVE(off) stack[CALL_STACK_PTR_POS + off]
#define VISIT(xb, _STR, _CHAR, _INT, _FLOAT, _OTHER) \
    {                                                \
        {                                            \
            switch (GET_TYPE(xb.chunk))              \
            {                                        \
            case STR:                                \
            {                                        \
                char *x = xb.internal.STR;           \
                _STR                                 \
            }                                        \
            break;                                   \
            case CHAR:                               \
            {                                        \
                let(x, &xb.internal.CHAR);           \
                _CHAR                                \
            }                                        \
            break;                                   \
            case INT:                                \
            {                                        \
                let(x, &xb.internal.INT);            \
                _INT                                 \
            }                                        \
            break;                                   \
            case FLOAT:                              \
            {                                        \
                let(x, &xb.internal.FLOAT);          \
                _FLOAT                               \
            }                                        \
            break;                                   \
            case OTHER:                              \
            {                                        \
                void *x = xb.internal.OTHER;         \
                _OTHER                               \
            }                                        \
            break;                                   \
            default:                                 \
                break;                               \
            }                                        \
        }                                            \
    }

#define VISIT2(xb, yb, _STR, _CHAR, _INT, _FLOAT, _OTHER, _DIFF)             \
    {                                                                        \
        if (GET_TYPE(xb.chunk) == STR && GET_TYPE(yb.chunk) == STR)          \
        {                                                                    \
            char *x = xb.internal.STR;                                       \
            char *y = yb.internal.STR;                                       \
            _STR                                                             \
        }                                                                    \
        else if (GET_TYPE(xb.chunk) == CHAR && GET_TYPE(yb.chunk) == CHAR)   \
        {                                                                    \
            char *x = &xb.internal.CHAR;                                     \
            char *y = &yb.internal.CHAR;                                     \
            _CHAR                                                            \
        }                                                                    \
        else if (GET_TYPE(xb.chunk) == INT && GET_TYPE(yb.chunk) == INT)     \
        {                                                                    \
            int64_t *x = &xb.internal.INT;                                   \
            int64_t *y = &yb.internal.INT;                                   \
            _INT                                                             \
        }                                                                    \
        else if (GET_TYPE(xb.chunk) == FLOAT && GET_TYPE(yb.chunk) == FLOAT) \
        {                                                                    \
            double *x = &xb.internal.FLOAT;                                  \
            double *y = &yb.internal.FLOAT;                                  \
            _FLOAT                                                           \
        }                                                                    \
        else if (GET_TYPE(xb.chunk) == OTHER && GET_TYPE(yb.chunk) == OTHER) \
        {                                                                    \
            void *x = &xb.internal.OTHER;                                    \
            void *y = &yb.internal.OTHER;                                    \
            _OTHER                                                           \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            _DIFF                                                            \
        }                                                                    \
    }

#define VISITTOP(_STR, _CHAR, _INT, _FLOAT, _OTHER) VISIT(stack[stack_ptr], _STR, _CHAR, _INT, _FLOAT, _OTHER)
#define VISIT2TOP(_STR, _CHAR, _INT, _FLOAT, _OTHER, _DIFF) VISIT2(stack[stack_ptr - 2], stack[stack_ptr - 1], _STR, _CHAR, _INT, _FLOAT, _OTHER, _DIFF)

#define APPLY(_STR, _CHAR, _INT, _FLOAT, _OTHER)     \
    {                                                \
        VISITTOP(_STR, _CHAR, _INT, _FLOAT, _OTHER); \
    }
#define APPLY2(_STR, _CHAR, _INT, _FLOAT, _OTHER, _DIFF)     \
    {                                                        \
        VISIT2TOP(_STR, _CHAR, _INT, _FLOAT, _OTHER, _DIFF); \
        stack_ptr--;                                         \
    }

#define logvm(xb) VISIT(xb, printf("%s", x);, printf("%c", *x);, printf("%ld", *x);, printf("%f", *x);, printf("unknown at %lx", (uint64_t)x);)

#endif