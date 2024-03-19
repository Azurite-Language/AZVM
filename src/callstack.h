#ifndef CALLSTACK_H_INCLUDED
#define CALLSTACK_H_INCLUDED
#include <stdint.h>
#include "stream_reader.h"
#include "builtin.h"


static size_t callstack[200] = {0};
static uint32_t callstack_ptr = 0;

// represent ce position of the stack ptr.
#define CALL_STACK_PTR_POS (callstack[callstack_ptr-1] & 0xFFFF)
#define CALL_STACK_PTR_LINE (callstack[callstack_ptr-1] >> 16)


#define PUSH_CALLSTACK(offset) callstack[callstack_ptr] = (stack_ptr - offset);
#define PUSH_CALLSTACK_ADDR(line) callstack[callstack_ptr] |= (line << 16)
/*
* Top value stay at the top because it’s the value returned by the call.
* Restore the stack pointer to it’s previous value.
* Jump to the next instruction.
*/
#define POP_CALLSTACK(offset) stack[CALL_STACK_PTR_POS] = TOP(); stack_ptr = (CALL_STACK_PTR_POS+1); GOTO_(CALL_STACK_PTR_LINE+1); callstack_ptr--


#endif