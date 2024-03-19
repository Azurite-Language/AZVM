#ifndef CONSTANTS_H
#define CONSTANTS_H

#define STACK_SIZE 200




#define DEBUG

#ifdef DEBUG
#define log(x, ...) printf(x, __VA_ARGS__)
#else
#define log(x, ...)
#endif

#endif