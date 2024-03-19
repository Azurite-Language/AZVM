#ifndef POOL_H
#define POOL_H

#define POOL_SIZE 200
#define ALLOCATE_POOL static char pool[POOL_SIZE][8192] = {""};

typedef struct
{
    uint32_t size;
    uint32_t index;
} POOL_ENTRY;


#define POOL(x) pool[x]
ALLOCATE_POOL
// static uint32_t pool_indexer[200];
// static size_t pool_ptr = 0;
// #define POOL_ALLOCATE(size, code) pool_indexer[pool_ptr++] = {(size), (code)};

#endif