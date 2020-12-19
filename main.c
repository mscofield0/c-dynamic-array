#include <stdio.h>
#include <stdlib.h>

#define DARR_TYPEDEF_NAME($Ty) darr_ ## $Ty

#define DARR_DEFAULT_CAPACITY 32

#define DARR_ROUND_TO_POWER_OF_TWO($Val) $Val--; \
	$Val |= $Val >> (size_t) 1;                           \
	$Val |= $Val >> (size_t) 2;                           \
	$Val |= $Val >> (size_t) 4;                           \
	$Val |= $Val >> (size_t) 8;                           \
	$Val |= $Val >> (size_t) 16;                          \
	$Val++

#define DARR_CREATE_WITH_CAPACITY($Ty) DARR_TYPEDEF_NAME($Ty) darr_ ## $Ty ## _create_from_capacity (size_t capacity) { \
    DARR_ROUND_TO_POWER_OF_TWO(capacity);                     \
    DARR_TYPEDEF_NAME($Ty) arr = {                                       \
        .data = malloc(capacity * sizeof($Ty)),                           \
        .capacity = capacity,                                            \
        .size = 0                                                        \
    };                                                                   \
    return arr;                                                          \
}

#define DARR_CREATE($Ty) DARR_TYPEDEF_NAME($Ty) darr_ ## $Ty ## _create () { \
	return darr_ ## $Ty ## _create_from_capacity(DARR_DEFAULT_CAPACITY);              \
}

#define DARR_FREE($Ty) void darr_ ## $Ty ## _free (DARR_TYPEDEF_NAME($Ty)* darr) { \
    free(darr->data);                                                          \
    darr->capacity = 0;                                                        \
    darr->size = 0;                                                            \
}

#define DARR_CLAMP($Val, $Min, $Max) (($Val) < ($Min)) \
	? (($Val) = ($Min))                                       \
		: (($Val) > ($Max))                                    \
		? (($Val) = ($Max))                                    \
			: ($Val)

#define DARR_REALLOC($Ty) void darr_ ## $Ty ## _realloc (DARR_TYPEDEF_NAME($Ty)* darr, size_t new_capacity) { \
    darr->data = realloc(darr->data, new_capacity);                            \
    darr->capacity = new_capacity;                                             \
    darr->size = DARR_CLAMP(darr->size, 0, new_capacity);                      \
}

#define DARR_PUSH($Ty) void darr_ ## $Ty ## _push (DARR_TYPEDEF_NAME($Ty)* darr, const $Ty val) { \
    if (darr->size >= darr->capacity) {                                          \
        darr_ ## $Ty ## _realloc(darr, darr->capacity * 2);                      \
    }                                                                            \
    darr->data[darr->size++] = val;                                              \
}

#define DARR_POP($Ty) $Ty darr_ ## $Ty ## _pop (DARR_TYPEDEF_NAME($Ty)* darr) { \
    return darr->data[darr->size--];                                            \
}

#define DARR_FIRST($Ty) $Ty* darr_ ## $Ty ## _first (DARR_TYPEDEF_NAME($Ty)* darr) { \
    return darr->data;                                            \
}

#define DARR_LAST($Ty) $Ty* darr_ ## $Ty ## _last (DARR_TYPEDEF_NAME($Ty)* darr) { \
    return darr->data + darr->size - 1;                                            \
}

#define DARR_DEFINE($Ty) \
	typedef struct DynamicArray_ ## $Ty { \
        $Ty* data;                    \
        size_t capacity;            \
        size_t size;                \
    } DARR_TYPEDEF_NAME($Ty);           \
	DARR_CREATE_WITH_CAPACITY($Ty) \
	DARR_CREATE($Ty) \
	DARR_FREE($Ty) \
	DARR_REALLOC($Ty)       \
	DARR_PUSH($Ty)          \
	DARR_POP($Ty)           \
	DARR_FIRST($Ty)         \
	DARR_LAST($Ty)

int main() {

    return 0;
}
