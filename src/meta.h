#ifndef META_H
#define META_H

#define lambda(x_) ({ x_ _;})
#define let(n, lambdaa) __typeof__(lambdaa) n = lambdaa

#define SET3(x, y, z, w) __typeof__(x) ___val0; __typeof__(y) ___val1; __typeof__(z) ___val2; __typeof__(w) ___val3;
#define SET2(x, y, z) __typeof__(x) ___val0; __typeof__(y) ___val1; __typeof__(z) ___val2;
#define SET1(x, y) __typeof__(x) ___val0; __typeof__(y) ___val1;
#define SET0(x) __typeof__(x) ___val0;
#define SET_(x, y, z, w, M, ...) M
#define SET(...) SET_(__VA_ARGS__,SET3,SET2,SET1,SET0)(__VA_ARGS__)
#define TUPLEA3(x, y, z, w) x = tupleret.___val0; y = tupleret.___val1; z = tupleret.___val2; w = tupleret.___val3;
#define TUPLEA2(x, y, z) x = tupleret.___val0; y = tupleret.___val1; z = tupleret.___val2;
#define TUPLEA1(x, y) x = tupleret.___val0; y = tupleret.___val1;
#define TUPLEA0(x) x = tupleret.___val0;
#define TUPLEA_(x, y, z, w, M, ...) M
#define TUPLEA(...) SET_(__VA_ARGS__,TUPLEA3,TUPLEA2,TUPLEA1,TUPLEA0)(__VA_ARGS__)
#define TUPLERET1(...) {typedef struct tupleret_s{SET(__VA_ARGS__)} tupleret_t; tupleret_t* tupleret = malloc(sizeof(tupleret_t)); *tupleret = (tupleret_t){__VA_ARGS__};return tupleret;}
#define TUPLERET0(x) return(x)
#define TUPLERET_(x, y, z, w, M, ...) M
typedef void* tuple;
#define tuple(...) tuple
#define tie(...) for(int tuplei = 0; !tuplei;) for(tuple iter; tuplei < 2; tuplei++) if(tuplei) { typedef struct tupleret_s{SET(__VA_ARGS__)} tupleret_t; tupleret_t tupleret = *(tupleret_t*)iter; TUPLEA(__VA_ARGS__); free(iter);} else iter
#define return(...) TUPLERET_(__VA_ARGS__, TUPLERET1, TUPLERET1, TUPLERET1, TUPLERET0)(__VA_ARGS__)

#define yieldpush() static int state=0; switch(state) { case 0:
#define yield(x) { state=__LINE__; return x; case __LINE__:; }
#define yieldpop() }

#endif