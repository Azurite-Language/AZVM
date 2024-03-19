
// #define OP_EXIT 0
// #define OP_PUSH 1
// #define OP_POP 2
// #define OP_DEFUN 3
// #define OP_SET 4
// #define OP_GOTO 5
// #define OP_RELATIVE 6
// #define OP_RTS 7
// #define OP_JSR 8
// #define OP_IF 9
// #define OP_IFn 10
// #define OP_ENDIF 11
// #define OP_ELSE 12
// #define OP_THEN 13
// #define OP_EQUAL 14
// #define OP_NEQUAL 15
// #define OP_PLUS 16
// #define OP_MINUS 17
// #define OP_DIV 18
// #define OP_MULT 19
// #define OP_INF 20
// #define OP_PUSH_CALLSTACK 21
// #define OP_POP_CALLSTACK 22
// #define OP_INPUT 23
// #define OP_LAST 24
// #define OP_INVALID 25

enum OPCODE
{
	OP_EXIT = 0,
	OP_PUSH,
	OP_POP,
	OP_DEFUN,
	OP_SET,
	OP_GOTO,
	OP_GOTO_RELATIVE,
	OP_RELATIVE,
	OP_RTS,
	OP_JSR,
	OP_IF,
	OP_IFn,
	OP_ENDIF,
	OP_ELSE,
	OP_THEN,
	OP_EQUAL,
	OP_NEQUAL,
	OP_PLUS,
	OP_MINUS,
	OP_DIV,
	OP_MULT,
	OP_INF,
	OP_PUSH_CALLSTACK,
	OP_POP_CALLSTACK,
	OP_INPUT,
	OP_PUSH_S,
	OP_POP_S,
	OP_ALLOCATE,
	OP_DC,
	OP_PUSHA,
	OP_GET,
	OP_LAST,
	OP_INVALID
};

#ifndef AZVM_CONSTANT_INCLUDED
#define AZVM_CONSTANT_INCLUDED
enum Operator
{
	OPERATOR_EQUAL = 0,
	OPERATOR_PLUS,
	OPERATOR_MINUS,
	OPERATOR_DIV,
	OPERATOR_MULT,
	OPERATOR_INF,
	OPERATOR_LT,
	OPERATOR_LAST,
	OPERATOR_INVALID
};

char *OPCODE_NAMES[] = {
	[OP_EXIT] = "OP_EXIT",
	[OP_PUSH] = "OP_PUSH",
	[OP_POP] = "OP_POP",
	[OP_DEFUN] = "OP_DEFUN",
	[OP_SET] = "OP_SET",
	[OP_GOTO] = "OP_GOTO",
	[OP_GOTO_RELATIVE] = "OP_GOTO_RELATIVE",
	[OP_RELATIVE] = "OP_RELATIVE",
	[OP_RTS] = "OP_RTS",
	[OP_JSR] = "OP_JSR",
	[OP_IF] = "OP_IF",
	[OP_IFn] = "OP_IFn",
	[OP_ENDIF] = "OP_ENDIF",
	[OP_ELSE] = "OP_ELSE",
	[OP_THEN] = "OP_THEN",
	[OP_EQUAL] = "OP_EQUAL",
	[OP_NEQUAL] = "OP_NEQUAL",
	[OP_PLUS] = "OP_PLUS",
	[OP_MINUS] = "OP_MINUS",
	[OP_DIV] = "OP_DIV",
	[OP_MULT] = "OP_MULT",
	[OP_INF] = "OP_INF",
	[OP_PUSH_CALLSTACK] = "OP_PUSH_CALLSTACK",
	[OP_POP_CALLSTACK] = "OP_POP_CALLSTACK",
	[OP_INPUT] = "OP_INPUT",
	[OP_PUSH_S] = "OP_PUSH_S",
	[OP_POP_S] = "OP_POP_S",
	[OP_ALLOCATE] = "OP_ALLOCATE",
	[OP_DC] = "OP_DC",
	[OP_PUSHA] = "OP_PUSHA",
	[OP_GET] = "OP_GET",
	[OP_LAST] = "OP_LAST",
	[OP_INVALID] = "OP_INVALID"
};
#endif