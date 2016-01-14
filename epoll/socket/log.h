#include <stdio.h>
#define LogError(...) do {\
	fprintf(stderr, __VA_ARGS__);\
}while(0)
#define LogDebug(...) do {\
	fprintf(stderr, __VA_ARGS__);\
}while(0)
#define LogTrace(...) do {\
	fprintf(stderr, __VA_ARGS__);\
}while(0)
#define LogInfo(...) do {\
	fprintf(stderr, __VA_ARGS__);\
}while(0)
