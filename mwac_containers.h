// mwac_containers.h - Auto-generated type-safe containers
// Do not edit manually - regenerate with codegen
#ifndef MWAC_CONTAINERS_H
#define MWAC_CONTAINERS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Source : https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function 
// FNV-1a is a Simple non-cryptographic hash function
// However I am planning on researching other hashing functions for best performance based on the length
static inline uint64_t mwac_hash_bytes(const void* data, size_t len) {
    const uint8_t* bytes = (const uint8_t*)data;
    uint64_t hash = 14695981039346656037ULL; // FNV offset basis
    for (size_t i = 0; i < len; i++) {
        hash ^= bytes[i];
        hash *= 1099511628211ULL; // FNV prime
    }
    return hash;
}

static inline uint64_t mwac_hash_string(const char* str) {
    uint64_t hash = 14695981039346656037ULL;
    while (*str) {
        hash ^= (uint8_t)*str++;
        hash *= 1099511628211ULL;
    }
    return hash;
}

#define mwac_hash(key) mwac_hash_bytes(&(key), sizeof(key))

enum {
    MWAC_ENTRY_EMPTY     = 0,
    MWAC_ENTRY_OCCUPIED  = 1,
    MWAC_ENTRY_TOMBSTONE = 2
};

// =============== C - Vectors ===============

typedef struct {
    int*    data;
    size_t length;
    size_t capacity;
} cvec_int;

static inline void cvec_int_init(cvec_int* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int_free(cvec_int* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int_push(cvec_int* v, int item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (int*)realloc(v->data, new_cap * sizeof(int));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline int cvec_int_pop(cvec_int* v) {
    return v->data[--v->length];
}

static inline int cvec_int_peek(cvec_int* v) {
    return v->data[v->length - 1];
}

static inline int* cvec_int_get(cvec_int* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_int_set(cvec_int* v, size_t index, int item) {
    v->data[index] = item;
}

static inline size_t cvec_int_len(cvec_int* v) {
    return v->length;
}

static inline void cvec_int_clear(cvec_int* v) {
    v->length = 0;
}

static inline void cvec_int_reserve(cvec_int* v, size_t n) {
    if (n > v->capacity) {
        v->data = (int*)realloc(v->data, n * sizeof(int));
        v->capacity = n;
    }
}

typedef struct {
    float*    data;
    size_t length;
    size_t capacity;
} cvec_float;

static inline void cvec_float_init(cvec_float* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_float_free(cvec_float* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_float_push(cvec_float* v, float item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (float*)realloc(v->data, new_cap * sizeof(float));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline float cvec_float_pop(cvec_float* v) {
    return v->data[--v->length];
}

static inline float cvec_float_peek(cvec_float* v) {
    return v->data[v->length - 1];
}

static inline float* cvec_float_get(cvec_float* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_float_set(cvec_float* v, size_t index, float item) {
    v->data[index] = item;
}

static inline size_t cvec_float_len(cvec_float* v) {
    return v->length;
}

static inline void cvec_float_clear(cvec_float* v) {
    v->length = 0;
}

static inline void cvec_float_reserve(cvec_float* v, size_t n) {
    if (n > v->capacity) {
        v->data = (float*)realloc(v->data, n * sizeof(float));
        v->capacity = n;
    }
}

typedef struct {
    double*    data;
    size_t length;
    size_t capacity;
} cvec_double;

static inline void cvec_double_init(cvec_double* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_double_free(cvec_double* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_double_push(cvec_double* v, double item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (double*)realloc(v->data, new_cap * sizeof(double));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline double cvec_double_pop(cvec_double* v) {
    return v->data[--v->length];
}

static inline double cvec_double_peek(cvec_double* v) {
    return v->data[v->length - 1];
}

static inline double* cvec_double_get(cvec_double* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_double_set(cvec_double* v, size_t index, double item) {
    v->data[index] = item;
}

static inline size_t cvec_double_len(cvec_double* v) {
    return v->length;
}

static inline void cvec_double_clear(cvec_double* v) {
    v->length = 0;
}

static inline void cvec_double_reserve(cvec_double* v, size_t n) {
    if (n > v->capacity) {
        v->data = (double*)realloc(v->data, n * sizeof(double));
        v->capacity = n;
    }
}

typedef struct {
    char*    data;
    size_t length;
    size_t capacity;
} cvec_char;

static inline void cvec_char_init(cvec_char* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_char_free(cvec_char* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_char_push(cvec_char* v, char item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (char*)realloc(v->data, new_cap * sizeof(char));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline char cvec_char_pop(cvec_char* v) {
    return v->data[--v->length];
}

static inline char cvec_char_peek(cvec_char* v) {
    return v->data[v->length - 1];
}

static inline char* cvec_char_get(cvec_char* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_char_set(cvec_char* v, size_t index, char item) {
    v->data[index] = item;
}

static inline size_t cvec_char_len(cvec_char* v) {
    return v->length;
}

static inline void cvec_char_clear(cvec_char* v) {
    v->length = 0;
}

static inline void cvec_char_reserve(cvec_char* v, size_t n) {
    if (n > v->capacity) {
        v->data = (char*)realloc(v->data, n * sizeof(char));
        v->capacity = n;
    }
}

typedef struct {
    int8_t*    data;
    size_t length;
    size_t capacity;
} cvec_int8_t;

static inline void cvec_int8_t_init(cvec_int8_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int8_t_free(cvec_int8_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int8_t_push(cvec_int8_t* v, int8_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (int8_t*)realloc(v->data, new_cap * sizeof(int8_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline int8_t cvec_int8_t_pop(cvec_int8_t* v) {
    return v->data[--v->length];
}

static inline int8_t cvec_int8_t_peek(cvec_int8_t* v) {
    return v->data[v->length - 1];
}

static inline int8_t* cvec_int8_t_get(cvec_int8_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_int8_t_set(cvec_int8_t* v, size_t index, int8_t item) {
    v->data[index] = item;
}

static inline size_t cvec_int8_t_len(cvec_int8_t* v) {
    return v->length;
}

static inline void cvec_int8_t_clear(cvec_int8_t* v) {
    v->length = 0;
}

static inline void cvec_int8_t_reserve(cvec_int8_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (int8_t*)realloc(v->data, n * sizeof(int8_t));
        v->capacity = n;
    }
}

typedef struct {
    int16_t*    data;
    size_t length;
    size_t capacity;
} cvec_int16_t;

static inline void cvec_int16_t_init(cvec_int16_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int16_t_free(cvec_int16_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int16_t_push(cvec_int16_t* v, int16_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (int16_t*)realloc(v->data, new_cap * sizeof(int16_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline int16_t cvec_int16_t_pop(cvec_int16_t* v) {
    return v->data[--v->length];
}

static inline int16_t cvec_int16_t_peek(cvec_int16_t* v) {
    return v->data[v->length - 1];
}

static inline int16_t* cvec_int16_t_get(cvec_int16_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_int16_t_set(cvec_int16_t* v, size_t index, int16_t item) {
    v->data[index] = item;
}

static inline size_t cvec_int16_t_len(cvec_int16_t* v) {
    return v->length;
}

static inline void cvec_int16_t_clear(cvec_int16_t* v) {
    v->length = 0;
}

static inline void cvec_int16_t_reserve(cvec_int16_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (int16_t*)realloc(v->data, n * sizeof(int16_t));
        v->capacity = n;
    }
}

typedef struct {
    int32_t*    data;
    size_t length;
    size_t capacity;
} cvec_int32_t;

static inline void cvec_int32_t_init(cvec_int32_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int32_t_free(cvec_int32_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int32_t_push(cvec_int32_t* v, int32_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (int32_t*)realloc(v->data, new_cap * sizeof(int32_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline int32_t cvec_int32_t_pop(cvec_int32_t* v) {
    return v->data[--v->length];
}

static inline int32_t cvec_int32_t_peek(cvec_int32_t* v) {
    return v->data[v->length - 1];
}

static inline int32_t* cvec_int32_t_get(cvec_int32_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_int32_t_set(cvec_int32_t* v, size_t index, int32_t item) {
    v->data[index] = item;
}

static inline size_t cvec_int32_t_len(cvec_int32_t* v) {
    return v->length;
}

static inline void cvec_int32_t_clear(cvec_int32_t* v) {
    v->length = 0;
}

static inline void cvec_int32_t_reserve(cvec_int32_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (int32_t*)realloc(v->data, n * sizeof(int32_t));
        v->capacity = n;
    }
}

typedef struct {
    int64_t*    data;
    size_t length;
    size_t capacity;
} cvec_int64_t;

static inline void cvec_int64_t_init(cvec_int64_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int64_t_free(cvec_int64_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_int64_t_push(cvec_int64_t* v, int64_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (int64_t*)realloc(v->data, new_cap * sizeof(int64_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline int64_t cvec_int64_t_pop(cvec_int64_t* v) {
    return v->data[--v->length];
}

static inline int64_t cvec_int64_t_peek(cvec_int64_t* v) {
    return v->data[v->length - 1];
}

static inline int64_t* cvec_int64_t_get(cvec_int64_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_int64_t_set(cvec_int64_t* v, size_t index, int64_t item) {
    v->data[index] = item;
}

static inline size_t cvec_int64_t_len(cvec_int64_t* v) {
    return v->length;
}

static inline void cvec_int64_t_clear(cvec_int64_t* v) {
    v->length = 0;
}

static inline void cvec_int64_t_reserve(cvec_int64_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (int64_t*)realloc(v->data, n * sizeof(int64_t));
        v->capacity = n;
    }
}

typedef struct {
    uint8_t*    data;
    size_t length;
    size_t capacity;
} cvec_uint8_t;

static inline void cvec_uint8_t_init(cvec_uint8_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint8_t_free(cvec_uint8_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint8_t_push(cvec_uint8_t* v, uint8_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (uint8_t*)realloc(v->data, new_cap * sizeof(uint8_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline uint8_t cvec_uint8_t_pop(cvec_uint8_t* v) {
    return v->data[--v->length];
}

static inline uint8_t cvec_uint8_t_peek(cvec_uint8_t* v) {
    return v->data[v->length - 1];
}

static inline uint8_t* cvec_uint8_t_get(cvec_uint8_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_uint8_t_set(cvec_uint8_t* v, size_t index, uint8_t item) {
    v->data[index] = item;
}

static inline size_t cvec_uint8_t_len(cvec_uint8_t* v) {
    return v->length;
}

static inline void cvec_uint8_t_clear(cvec_uint8_t* v) {
    v->length = 0;
}

static inline void cvec_uint8_t_reserve(cvec_uint8_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (uint8_t*)realloc(v->data, n * sizeof(uint8_t));
        v->capacity = n;
    }
}

typedef struct {
    uint16_t*    data;
    size_t length;
    size_t capacity;
} cvec_uint16_t;

static inline void cvec_uint16_t_init(cvec_uint16_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint16_t_free(cvec_uint16_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint16_t_push(cvec_uint16_t* v, uint16_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (uint16_t*)realloc(v->data, new_cap * sizeof(uint16_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline uint16_t cvec_uint16_t_pop(cvec_uint16_t* v) {
    return v->data[--v->length];
}

static inline uint16_t cvec_uint16_t_peek(cvec_uint16_t* v) {
    return v->data[v->length - 1];
}

static inline uint16_t* cvec_uint16_t_get(cvec_uint16_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_uint16_t_set(cvec_uint16_t* v, size_t index, uint16_t item) {
    v->data[index] = item;
}

static inline size_t cvec_uint16_t_len(cvec_uint16_t* v) {
    return v->length;
}

static inline void cvec_uint16_t_clear(cvec_uint16_t* v) {
    v->length = 0;
}

static inline void cvec_uint16_t_reserve(cvec_uint16_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (uint16_t*)realloc(v->data, n * sizeof(uint16_t));
        v->capacity = n;
    }
}

typedef struct {
    uint32_t*    data;
    size_t length;
    size_t capacity;
} cvec_uint32_t;

static inline void cvec_uint32_t_init(cvec_uint32_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint32_t_free(cvec_uint32_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint32_t_push(cvec_uint32_t* v, uint32_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (uint32_t*)realloc(v->data, new_cap * sizeof(uint32_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline uint32_t cvec_uint32_t_pop(cvec_uint32_t* v) {
    return v->data[--v->length];
}

static inline uint32_t cvec_uint32_t_peek(cvec_uint32_t* v) {
    return v->data[v->length - 1];
}

static inline uint32_t* cvec_uint32_t_get(cvec_uint32_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_uint32_t_set(cvec_uint32_t* v, size_t index, uint32_t item) {
    v->data[index] = item;
}

static inline size_t cvec_uint32_t_len(cvec_uint32_t* v) {
    return v->length;
}

static inline void cvec_uint32_t_clear(cvec_uint32_t* v) {
    v->length = 0;
}

static inline void cvec_uint32_t_reserve(cvec_uint32_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (uint32_t*)realloc(v->data, n * sizeof(uint32_t));
        v->capacity = n;
    }
}

typedef struct {
    uint64_t*    data;
    size_t length;
    size_t capacity;
} cvec_uint64_t;

static inline void cvec_uint64_t_init(cvec_uint64_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint64_t_free(cvec_uint64_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_uint64_t_push(cvec_uint64_t* v, uint64_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (uint64_t*)realloc(v->data, new_cap * sizeof(uint64_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline uint64_t cvec_uint64_t_pop(cvec_uint64_t* v) {
    return v->data[--v->length];
}

static inline uint64_t cvec_uint64_t_peek(cvec_uint64_t* v) {
    return v->data[v->length - 1];
}

static inline uint64_t* cvec_uint64_t_get(cvec_uint64_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_uint64_t_set(cvec_uint64_t* v, size_t index, uint64_t item) {
    v->data[index] = item;
}

static inline size_t cvec_uint64_t_len(cvec_uint64_t* v) {
    return v->length;
}

static inline void cvec_uint64_t_clear(cvec_uint64_t* v) {
    v->length = 0;
}

static inline void cvec_uint64_t_reserve(cvec_uint64_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (uint64_t*)realloc(v->data, n * sizeof(uint64_t));
        v->capacity = n;
    }
}

typedef struct {
    size_t*    data;
    size_t length;
    size_t capacity;
} cvec_size_t;

static inline void cvec_size_t_init(cvec_size_t* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_size_t_free(cvec_size_t* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_size_t_push(cvec_size_t* v, size_t item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (size_t*)realloc(v->data, new_cap * sizeof(size_t));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline size_t cvec_size_t_pop(cvec_size_t* v) {
    return v->data[--v->length];
}

static inline size_t cvec_size_t_peek(cvec_size_t* v) {
    return v->data[v->length - 1];
}

static inline size_t* cvec_size_t_get(cvec_size_t* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_size_t_set(cvec_size_t* v, size_t index, size_t item) {
    v->data[index] = item;
}

static inline size_t cvec_size_t_len(cvec_size_t* v) {
    return v->length;
}

static inline void cvec_size_t_clear(cvec_size_t* v) {
    v->length = 0;
}

static inline void cvec_size_t_reserve(cvec_size_t* v, size_t n) {
    if (n > v->capacity) {
        v->data = (size_t*)realloc(v->data, n * sizeof(size_t));
        v->capacity = n;
    }
}

typedef struct {
    void**    data;
    size_t length;
    size_t capacity;
} cvec_void_ptr;

static inline void cvec_void_ptr_init(cvec_void_ptr* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_void_ptr_free(cvec_void_ptr* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_void_ptr_push(cvec_void_ptr* v, void* item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (void**)realloc(v->data, new_cap * sizeof(void*));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline void* cvec_void_ptr_pop(cvec_void_ptr* v) {
    return v->data[--v->length];
}

static inline void* cvec_void_ptr_peek(cvec_void_ptr* v) {
    return v->data[v->length - 1];
}

static inline void** cvec_void_ptr_get(cvec_void_ptr* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_void_ptr_set(cvec_void_ptr* v, size_t index, void* item) {
    v->data[index] = item;
}

static inline size_t cvec_void_ptr_len(cvec_void_ptr* v) {
    return v->length;
}

static inline void cvec_void_ptr_clear(cvec_void_ptr* v) {
    v->length = 0;
}

static inline void cvec_void_ptr_reserve(cvec_void_ptr* v, size_t n) {
    if (n > v->capacity) {
        v->data = (void**)realloc(v->data, n * sizeof(void*));
        v->capacity = n;
    }
}

typedef struct {
    char**    data;
    size_t length;
    size_t capacity;
} cvec_char_ptr;

static inline void cvec_char_ptr_init(cvec_char_ptr* v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_char_ptr_free(cvec_char_ptr* v) {
    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}

static inline void cvec_char_ptr_push(cvec_char_ptr* v, char* item) {
    if (v->length >= v->capacity) {
        size_t new_cap = v->capacity == 0 ? 8 : v->capacity * 2;
        v->data = (char**)realloc(v->data, new_cap * sizeof(char*));
        v->capacity = new_cap;
    }
    v->data[v->length++] = item;
}

static inline char* cvec_char_ptr_pop(cvec_char_ptr* v) {
    return v->data[--v->length];
}

static inline char* cvec_char_ptr_peek(cvec_char_ptr* v) {
    return v->data[v->length - 1];
}

static inline char** cvec_char_ptr_get(cvec_char_ptr* v, size_t index) {
    return &v->data[index];
}

static inline void cvec_char_ptr_set(cvec_char_ptr* v, size_t index, char* item) {
    v->data[index] = item;
}

static inline size_t cvec_char_ptr_len(cvec_char_ptr* v) {
    return v->length;
}

static inline void cvec_char_ptr_clear(cvec_char_ptr* v) {
    v->length = 0;
}

static inline void cvec_char_ptr_reserve(cvec_char_ptr* v, size_t n) {
    if (n > v->capacity) {
        v->data = (char**)realloc(v->data, n * sizeof(char*));
        v->capacity = n;
    }
}

// ============ C - Hashmaps ============

typedef struct {
    int      key;
    int      value;
    uint8_t state;
} cmap_int_int_entry;

typedef struct {
    cmap_int_int_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_int_int;

static inline void cmap_int_int_init(cmap_int_int* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_int_int_free(cmap_int_int* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_int_int_grow(cmap_int_int* m);

static inline void cmap_int_int_put(cmap_int_int* m, int key, int value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_int_int_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_int_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline int* cmap_int_int_get(cmap_int_int* m, int key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_int_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_int_int_has(cmap_int_int* m, int key) {
    return cmap_int_int_get(m, key) != NULL;
}

static inline bool cmap_int_int_del(cmap_int_int* m, int key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_int_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_int_int_count(cmap_int_int* m) {
    return m->count;
}

static inline void cmap_int_int_clear(cmap_int_int* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_int_int_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_int_int_grow(cmap_int_int* m) {
    size_t old_cap = m->capacity;
    cmap_int_int_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_int_int_entry*)calloc(m->capacity, sizeof(cmap_int_int_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_int_int_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint32_t      key;
    uint32_t      value;
    uint8_t state;
} cmap_uint32_t_uint32_t_entry;

typedef struct {
    cmap_uint32_t_uint32_t_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_uint32_t_uint32_t;

static inline void cmap_uint32_t_uint32_t_init(cmap_uint32_t_uint32_t* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_uint32_t_uint32_t_free(cmap_uint32_t_uint32_t* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint32_t_uint32_t_grow(cmap_uint32_t_uint32_t* m);

static inline void cmap_uint32_t_uint32_t_put(cmap_uint32_t_uint32_t* m, uint32_t key, uint32_t value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_uint32_t_uint32_t_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_uint32_t_uint32_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline uint32_t* cmap_uint32_t_uint32_t_get(cmap_uint32_t_uint32_t* m, uint32_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint32_t_uint32_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_uint32_t_uint32_t_has(cmap_uint32_t_uint32_t* m, uint32_t key) {
    return cmap_uint32_t_uint32_t_get(m, key) != NULL;
}

static inline bool cmap_uint32_t_uint32_t_del(cmap_uint32_t_uint32_t* m, uint32_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint32_t_uint32_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_uint32_t_uint32_t_count(cmap_uint32_t_uint32_t* m) {
    return m->count;
}

static inline void cmap_uint32_t_uint32_t_clear(cmap_uint32_t_uint32_t* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_uint32_t_uint32_t_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint32_t_uint32_t_grow(cmap_uint32_t_uint32_t* m) {
    size_t old_cap = m->capacity;
    cmap_uint32_t_uint32_t_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_uint32_t_uint32_t_entry*)calloc(m->capacity, sizeof(cmap_uint32_t_uint32_t_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_uint32_t_uint32_t_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint64_t      key;
    uint64_t      value;
    uint8_t state;
} cmap_uint64_t_uint64_t_entry;

typedef struct {
    cmap_uint64_t_uint64_t_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_uint64_t_uint64_t;

static inline void cmap_uint64_t_uint64_t_init(cmap_uint64_t_uint64_t* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_uint64_t_uint64_t_free(cmap_uint64_t_uint64_t* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint64_t_uint64_t_grow(cmap_uint64_t_uint64_t* m);

static inline void cmap_uint64_t_uint64_t_put(cmap_uint64_t_uint64_t* m, uint64_t key, uint64_t value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_uint64_t_uint64_t_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_uint64_t_uint64_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline uint64_t* cmap_uint64_t_uint64_t_get(cmap_uint64_t_uint64_t* m, uint64_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint64_t_uint64_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_uint64_t_uint64_t_has(cmap_uint64_t_uint64_t* m, uint64_t key) {
    return cmap_uint64_t_uint64_t_get(m, key) != NULL;
}

static inline bool cmap_uint64_t_uint64_t_del(cmap_uint64_t_uint64_t* m, uint64_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint64_t_uint64_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_uint64_t_uint64_t_count(cmap_uint64_t_uint64_t* m) {
    return m->count;
}

static inline void cmap_uint64_t_uint64_t_clear(cmap_uint64_t_uint64_t* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_uint64_t_uint64_t_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint64_t_uint64_t_grow(cmap_uint64_t_uint64_t* m) {
    size_t old_cap = m->capacity;
    cmap_uint64_t_uint64_t_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_uint64_t_uint64_t_entry*)calloc(m->capacity, sizeof(cmap_uint64_t_uint64_t_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_uint64_t_uint64_t_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    size_t      key;
    size_t      value;
    uint8_t state;
} cmap_size_t_size_t_entry;

typedef struct {
    cmap_size_t_size_t_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_size_t_size_t;

static inline void cmap_size_t_size_t_init(cmap_size_t_size_t* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_size_t_size_t_free(cmap_size_t_size_t* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_size_t_size_t_grow(cmap_size_t_size_t* m);

static inline void cmap_size_t_size_t_put(cmap_size_t_size_t* m, size_t key, size_t value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_size_t_size_t_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_size_t_size_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t* cmap_size_t_size_t_get(cmap_size_t_size_t* m, size_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_size_t_size_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_size_t_size_t_has(cmap_size_t_size_t* m, size_t key) {
    return cmap_size_t_size_t_get(m, key) != NULL;
}

static inline bool cmap_size_t_size_t_del(cmap_size_t_size_t* m, size_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_size_t_size_t_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_size_t_size_t_count(cmap_size_t_size_t* m) {
    return m->count;
}

static inline void cmap_size_t_size_t_clear(cmap_size_t_size_t* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_size_t_size_t_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_size_t_size_t_grow(cmap_size_t_size_t* m) {
    size_t old_cap = m->capacity;
    cmap_size_t_size_t_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_size_t_size_t_entry*)calloc(m->capacity, sizeof(cmap_size_t_size_t_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_size_t_size_t_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint32_t      key;
    void*      value;
    uint8_t state;
} cmap_uint32_t_void_ptr_entry;

typedef struct {
    cmap_uint32_t_void_ptr_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_uint32_t_void_ptr;

static inline void cmap_uint32_t_void_ptr_init(cmap_uint32_t_void_ptr* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_uint32_t_void_ptr_free(cmap_uint32_t_void_ptr* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint32_t_void_ptr_grow(cmap_uint32_t_void_ptr* m);

static inline void cmap_uint32_t_void_ptr_put(cmap_uint32_t_void_ptr* m, uint32_t key, void* value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_uint32_t_void_ptr_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_uint32_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline void** cmap_uint32_t_void_ptr_get(cmap_uint32_t_void_ptr* m, uint32_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint32_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_uint32_t_void_ptr_has(cmap_uint32_t_void_ptr* m, uint32_t key) {
    return cmap_uint32_t_void_ptr_get(m, key) != NULL;
}

static inline bool cmap_uint32_t_void_ptr_del(cmap_uint32_t_void_ptr* m, uint32_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint32_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_uint32_t_void_ptr_count(cmap_uint32_t_void_ptr* m) {
    return m->count;
}

static inline void cmap_uint32_t_void_ptr_clear(cmap_uint32_t_void_ptr* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_uint32_t_void_ptr_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint32_t_void_ptr_grow(cmap_uint32_t_void_ptr* m) {
    size_t old_cap = m->capacity;
    cmap_uint32_t_void_ptr_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_uint32_t_void_ptr_entry*)calloc(m->capacity, sizeof(cmap_uint32_t_void_ptr_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_uint32_t_void_ptr_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint64_t      key;
    void*      value;
    uint8_t state;
} cmap_uint64_t_void_ptr_entry;

typedef struct {
    cmap_uint64_t_void_ptr_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_uint64_t_void_ptr;

static inline void cmap_uint64_t_void_ptr_init(cmap_uint64_t_void_ptr* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_uint64_t_void_ptr_free(cmap_uint64_t_void_ptr* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint64_t_void_ptr_grow(cmap_uint64_t_void_ptr* m);

static inline void cmap_uint64_t_void_ptr_put(cmap_uint64_t_void_ptr* m, uint64_t key, void* value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_uint64_t_void_ptr_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_uint64_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline void** cmap_uint64_t_void_ptr_get(cmap_uint64_t_void_ptr* m, uint64_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint64_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_uint64_t_void_ptr_has(cmap_uint64_t_void_ptr* m, uint64_t key) {
    return cmap_uint64_t_void_ptr_get(m, key) != NULL;
}

static inline bool cmap_uint64_t_void_ptr_del(cmap_uint64_t_void_ptr* m, uint64_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_uint64_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_uint64_t_void_ptr_count(cmap_uint64_t_void_ptr* m) {
    return m->count;
}

static inline void cmap_uint64_t_void_ptr_clear(cmap_uint64_t_void_ptr* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_uint64_t_void_ptr_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_uint64_t_void_ptr_grow(cmap_uint64_t_void_ptr* m) {
    size_t old_cap = m->capacity;
    cmap_uint64_t_void_ptr_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_uint64_t_void_ptr_entry*)calloc(m->capacity, sizeof(cmap_uint64_t_void_ptr_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_uint64_t_void_ptr_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    size_t      key;
    void*      value;
    uint8_t state;
} cmap_size_t_void_ptr_entry;

typedef struct {
    cmap_size_t_void_ptr_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_size_t_void_ptr;

static inline void cmap_size_t_void_ptr_init(cmap_size_t_void_ptr* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_size_t_void_ptr_free(cmap_size_t_void_ptr* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_size_t_void_ptr_grow(cmap_size_t_void_ptr* m);

static inline void cmap_size_t_void_ptr_put(cmap_size_t_void_ptr* m, size_t key, void* value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_size_t_void_ptr_grow(m);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_size_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline void** cmap_size_t_void_ptr_get(cmap_size_t_void_ptr* m, size_t key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_size_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_size_t_void_ptr_has(cmap_size_t_void_ptr* m, size_t key) {
    return cmap_size_t_void_ptr_get(m, key) != NULL;
}

static inline bool cmap_size_t_void_ptr_del(cmap_size_t_void_ptr* m, size_t key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_size_t_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_size_t_void_ptr_count(cmap_size_t_void_ptr* m) {
    return m->count;
}

static inline void cmap_size_t_void_ptr_clear(cmap_size_t_void_ptr* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_size_t_void_ptr_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_size_t_void_ptr_grow(cmap_size_t_void_ptr* m) {
    size_t old_cap = m->capacity;
    cmap_size_t_void_ptr_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_size_t_void_ptr_entry*)calloc(m->capacity, sizeof(cmap_size_t_void_ptr_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_size_t_void_ptr_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    char*      key;
    int      value;
    uint8_t state;
} cmap_char_ptr_int_entry;

typedef struct {
    cmap_char_ptr_int_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_char_ptr_int;

static inline void cmap_char_ptr_int_init(cmap_char_ptr_int* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_char_ptr_int_free(cmap_char_ptr_int* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_char_ptr_int_grow(cmap_char_ptr_int* m);

static inline void cmap_char_ptr_int_put(cmap_char_ptr_int* m, char* key, int value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_char_ptr_int_grow(m);
    }
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_char_ptr_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (strcmp(e->key, key) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline int* cmap_char_ptr_int_get(cmap_char_ptr_int* m, char* key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_char_ptr_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_char_ptr_int_has(cmap_char_ptr_int* m, char* key) {
    return cmap_char_ptr_int_get(m, key) != NULL;
}

static inline bool cmap_char_ptr_int_del(cmap_char_ptr_int* m, char* key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_char_ptr_int_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_char_ptr_int_count(cmap_char_ptr_int* m) {
    return m->count;
}

static inline void cmap_char_ptr_int_clear(cmap_char_ptr_int* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_char_ptr_int_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_char_ptr_int_grow(cmap_char_ptr_int* m) {
    size_t old_cap = m->capacity;
    cmap_char_ptr_int_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_char_ptr_int_entry*)calloc(m->capacity, sizeof(cmap_char_ptr_int_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_char_ptr_int_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

typedef struct {
    char*      key;
    void*      value;
    uint8_t state;
} cmap_char_ptr_void_ptr_entry;

typedef struct {
    cmap_char_ptr_void_ptr_entry* entries;
    size_t           capacity;
    size_t           count;
    size_t           tombstones;
} cmap_char_ptr_void_ptr;

static inline void cmap_char_ptr_void_ptr_init(cmap_char_ptr_void_ptr* m) {
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static inline void cmap_char_ptr_void_ptr_free(cmap_char_ptr_void_ptr* m) {
    free(m->entries);
    m->entries = NULL;
    m->capacity = 0;
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_char_ptr_void_ptr_grow(cmap_char_ptr_void_ptr* m);

static inline void cmap_char_ptr_void_ptr_put(cmap_char_ptr_void_ptr* m, char* key, void* value) {
    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {
        cmap_char_ptr_void_ptr_grow(m);
    }
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cmap_char_ptr_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &m->entries[first_tombstone];
                m->tombstones--;
            }
            e->key = key;
            e->value = value;
            e->state = MWAC_ENTRY_OCCUPIED;
            m->count++;
            return;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (strcmp(e->key, key) == 0) {
            e->value = value;
            return;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline void** cmap_char_ptr_void_ptr_get(cmap_char_ptr_void_ptr* m, char* key) {
    if (m->capacity == 0) return NULL;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_char_ptr_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return NULL;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            return &e->value;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline bool cmap_char_ptr_void_ptr_has(cmap_char_ptr_void_ptr* m, char* key) {
    return cmap_char_ptr_void_ptr_get(m, key) != NULL;
}

static inline bool cmap_char_ptr_void_ptr_del(cmap_char_ptr_void_ptr* m, char* key) {
    if (m->capacity == 0) return false;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (m->capacity - 1);
    
    for (;;) {
        cmap_char_ptr_void_ptr_entry* e = &m->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            m->count--;
            m->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (m->capacity - 1);
    }
}

static inline size_t cmap_char_ptr_void_ptr_count(cmap_char_ptr_void_ptr* m) {
    return m->count;
}

static inline void cmap_char_ptr_void_ptr_clear(cmap_char_ptr_void_ptr* m) {
    if (m->entries) {
        memset(m->entries, 0, m->capacity * sizeof(cmap_char_ptr_void_ptr_entry));
    }
    m->count = 0;
    m->tombstones = 0;
}

static void cmap_char_ptr_void_ptr_grow(cmap_char_ptr_void_ptr* m) {
    size_t old_cap = m->capacity;
    cmap_char_ptr_void_ptr_entry* old_entries = m->entries;
    
    // New capacity: double, or start at 16
    m->capacity = old_cap == 0 ? 16 : old_cap * 2;
    m->entries = (cmap_char_ptr_void_ptr_entry*)calloc(m->capacity, sizeof(cmap_char_ptr_void_ptr_entry));
    m->count = 0;
    m->tombstones = 0;
    
    // Reinsert old entries
    // Need to do this since the positions depends on capacity (mod the hash by capacity)
    // may revisit for a different approach but this works
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cmap_char_ptr_void_ptr_put(m, old_entries[i].key, old_entries[i].value);
        }
    }
    
    free(old_entries);
}

// ============ C - Hashsets ============

typedef struct {
    int      key;
    uint8_t state;
} cset_int_entry;

typedef struct {
    cset_int_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_int;

static inline void cset_int_init(cset_int* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_int_free(cset_int* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_int_grow(cset_int* s);

static inline bool cset_int_add(cset_int* s, int key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_int_grow(s);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_int_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_int_has(cset_int* s, int key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_int_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_int_remove(cset_int* s, int key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_int_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_int_count(cset_int* s) {
    return s->count;
}

static inline void cset_int_clear(cset_int* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_int_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_int_grow(cset_int* s) {
    size_t old_cap = s->capacity;
    cset_int_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_int_entry*)calloc(s->capacity, sizeof(cset_int_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_int_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint32_t      key;
    uint8_t state;
} cset_uint32_t_entry;

typedef struct {
    cset_uint32_t_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_uint32_t;

static inline void cset_uint32_t_init(cset_uint32_t* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_uint32_t_free(cset_uint32_t* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_uint32_t_grow(cset_uint32_t* s);

static inline bool cset_uint32_t_add(cset_uint32_t* s, uint32_t key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_uint32_t_grow(s);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_uint32_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_uint32_t_has(cset_uint32_t* s, uint32_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_uint32_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_uint32_t_remove(cset_uint32_t* s, uint32_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_uint32_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_uint32_t_count(cset_uint32_t* s) {
    return s->count;
}

static inline void cset_uint32_t_clear(cset_uint32_t* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_uint32_t_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_uint32_t_grow(cset_uint32_t* s) {
    size_t old_cap = s->capacity;
    cset_uint32_t_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_uint32_t_entry*)calloc(s->capacity, sizeof(cset_uint32_t_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_uint32_t_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}

typedef struct {
    uint64_t      key;
    uint8_t state;
} cset_uint64_t_entry;

typedef struct {
    cset_uint64_t_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_uint64_t;

static inline void cset_uint64_t_init(cset_uint64_t* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_uint64_t_free(cset_uint64_t* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_uint64_t_grow(cset_uint64_t* s);

static inline bool cset_uint64_t_add(cset_uint64_t* s, uint64_t key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_uint64_t_grow(s);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_uint64_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_uint64_t_has(cset_uint64_t* s, uint64_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_uint64_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_uint64_t_remove(cset_uint64_t* s, uint64_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_uint64_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_uint64_t_count(cset_uint64_t* s) {
    return s->count;
}

static inline void cset_uint64_t_clear(cset_uint64_t* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_uint64_t_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_uint64_t_grow(cset_uint64_t* s) {
    size_t old_cap = s->capacity;
    cset_uint64_t_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_uint64_t_entry*)calloc(s->capacity, sizeof(cset_uint64_t_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_uint64_t_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}

typedef struct {
    size_t      key;
    uint8_t state;
} cset_size_t_entry;

typedef struct {
    cset_size_t_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_size_t;

static inline void cset_size_t_init(cset_size_t* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_size_t_free(cset_size_t* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_size_t_grow(cset_size_t* s);

static inline bool cset_size_t_add(cset_size_t* s, size_t key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_size_t_grow(s);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_size_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_size_t_has(cset_size_t* s, size_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_size_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_size_t_remove(cset_size_t* s, size_t key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_size_t_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_size_t_count(cset_size_t* s) {
    return s->count;
}

static inline void cset_size_t_clear(cset_size_t* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_size_t_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_size_t_grow(cset_size_t* s) {
    size_t old_cap = s->capacity;
    cset_size_t_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_size_t_entry*)calloc(s->capacity, sizeof(cset_size_t_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_size_t_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}

typedef struct {
    void*      key;
    uint8_t state;
} cset_void_ptr_entry;

typedef struct {
    cset_void_ptr_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_void_ptr;

static inline void cset_void_ptr_init(cset_void_ptr* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_void_ptr_free(cset_void_ptr* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_void_ptr_grow(cset_void_ptr* s);

static inline bool cset_void_ptr_add(cset_void_ptr* s, void* key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_void_ptr_grow(s);
    }
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_void_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_void_ptr_has(cset_void_ptr* s, void* key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_void_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_void_ptr_remove(cset_void_ptr* s, void* key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_void_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && memcmp(&e->key, &key, sizeof(e->key)) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_void_ptr_count(cset_void_ptr* s) {
    return s->count;
}

static inline void cset_void_ptr_clear(cset_void_ptr* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_void_ptr_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_void_ptr_grow(cset_void_ptr* s) {
    size_t old_cap = s->capacity;
    cset_void_ptr_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_void_ptr_entry*)calloc(s->capacity, sizeof(cset_void_ptr_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_void_ptr_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}

typedef struct {
    char*      key;
    uint8_t state;
} cset_char_ptr_entry;

typedef struct {
    cset_char_ptr_entry* entries;
    size_t        capacity;
    size_t        count;
    size_t        tombstones;
} cset_char_ptr;

static inline void cset_char_ptr_init(cset_char_ptr* s) {
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static inline void cset_char_ptr_free(cset_char_ptr* s) {
    free(s->entries);
    s->entries = NULL;
    s->capacity = 0;
    s->count = 0;
    s->tombstones = 0;
}

static void cset_char_ptr_grow(cset_char_ptr* s);

static inline bool cset_char_ptr_add(cset_char_ptr* s, char* key) {
    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {
        cset_char_ptr_grow(s);
    }
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (s->capacity - 1);
    size_t first_tombstone = SIZE_MAX;
    
    for (;;) {
        cset_char_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            if (first_tombstone != SIZE_MAX) {
                e = &s->entries[first_tombstone];
                s->tombstones--;
            }
            e->key = key;
            e->state = MWAC_ENTRY_OCCUPIED;
            s->count++;
            return true;
        }
        
        if (e->state == MWAC_ENTRY_TOMBSTONE) {
            if (first_tombstone == SIZE_MAX) first_tombstone = idx;
        } else if (strcmp(e->key, key) == 0) {
            return false;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_char_ptr_has(cset_char_ptr* s, char* key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_char_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline bool cset_char_ptr_remove(cset_char_ptr* s, char* key) {
    if (s->capacity == 0) return false;
    
    uint64_t hash = mwac_hash_string(key);
    size_t idx = hash & (s->capacity - 1);
    
    for (;;) {
        cset_char_ptr_entry* e = &s->entries[idx];
        
        if (e->state == MWAC_ENTRY_EMPTY) {
            return false;
        }
        
        if (e->state == MWAC_ENTRY_OCCUPIED && strcmp(e->key, key) == 0) {
            e->state = MWAC_ENTRY_TOMBSTONE;
            s->count--;
            s->tombstones++;
            return true;
        }
        
        idx = (idx + 1) & (s->capacity - 1);
    }
}

static inline size_t cset_char_ptr_count(cset_char_ptr* s) {
    return s->count;
}

static inline void cset_char_ptr_clear(cset_char_ptr* s) {
    if (s->entries) {
        memset(s->entries, 0, s->capacity * sizeof(cset_char_ptr_entry));
    }
    s->count = 0;
    s->tombstones = 0;
}

static void cset_char_ptr_grow(cset_char_ptr* s) {
    size_t old_cap = s->capacity;
    cset_char_ptr_entry* old_entries = s->entries;
    
    s->capacity = old_cap == 0 ? 16 : old_cap * 2;
    s->entries = (cset_char_ptr_entry*)calloc(s->capacity, sizeof(cset_char_ptr_entry));
    s->count = 0;
    s->tombstones = 0;
    
    for (size_t i = 0; i < old_cap; i++) {
        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {
            cset_char_ptr_add(s, old_entries[i].key);
        }
    }
    
    free(old_entries);
}


#endif // MWAC_CONTAINERS_H
