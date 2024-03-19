#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "builtin.h"
#include <string.h>

#define ADDv APPLY2({stack[stack_ptr-1].chunk += GET_COUNT(stack[stack_ptr].chunk)<<16; strcat(x, y);}, {*x += *y;}, {*x += *y;}, {*x += *y;}, {printf("%lx\t%lx", (uint64_t)x, (uint64_t)y); puts("\n"); } ,{return 1;})
#define MULv APPLY2({return 2;}, {*x *= *y;}, {*x *= *y;}, {*x *= *y;}, {printf("%lx\t%lx", (uint64_t)x, (uint64_t)y); puts("\n"); } ,{return 2;})
#define SUBv APPLY2({return 2;}, {*x *= *y;}, {*x *= *y;}, {*x *= *y;}, {printf("%lx\t%lx", (uint64_t)x, (uint64_t)y); puts("\n"); } ,{return 2;})
#define DIVv APPLY2({return 2;}, {*x /= *y;}, {*x /= *y;}, {*x /= *y;}, {printf("%lx\t%lx", (uint64_t)x, (uint64_t)y); puts("\n"); } ,{return 2;})
#define LENv {if( GET_ISLIST(stack[stack_ptr].chunk)){ stack[stack_ptr].internal.INT = GET_SIZE(stack[stack_ptr].chunk); stack[stack_ptr].chunk = WRITE_CHUNK(INT, 0, 0); } else{stack[stack_ptr].internal.INT = GET_SIZE(stack[stack_ptr].chunk) ; stack[stack_ptr].chunk = WRITE_CHUNK(INT, 0, 0); }}

#endif