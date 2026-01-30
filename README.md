# containergen

A code generator for type-safe C containers. Reads simple `.gen` files and outputs a single header with vectors, hashmaps, and hashsets for the specified types.

## Building

```
cc -o containergen containergen.c
```

## Usage

Place your `.gen` files in the same directory as the executable and run:

```
./containergen
```

This reads `vector.gen`, `hashmap.gen`, and `hashset.gen` (all optional) and outputs `mwac_containers.h`.

## Included Files

The repository includes default `.gen` files with common type configurations and an example `mwac_containers.h` generated from them. You can use these directly or modify them for your needs.

## .gen File Format

**vector.gen** - one type per line:
```
int
float
void*
Enemy*
```

**hashmap.gen** - key and value types separated by space:
```
int int
uint64_t void*
char* int
```

**hashset.gen** - one type per line:
```
uint32_t
char*
```

You can comment lines out by starting them with `#`.

Pointer types are supported. Putting `Enemy*` in vector.gen outputs `cvec_Enemy_ptr` in the generated code.

String keys (`char*`) are handled specially - they compare by content using `strcmp`, not by pointer value.

## Generated API

### Vector

```c
cvec_int v;
cvec_int_init(&v, NULL); // NULL = heap allocator - Note that you'll still need a default allocator implementation

cvec_int_push(&v, 42);
cvec_int_push(&v, 17);

int x = cvec_int_pop(&v);       // returns 17
int y = cvec_int_peek(&v);      // returns 42, doesn't remove
int* p = cvec_int_get(&v, 0);   // pointer to element at index
cvec_int_set(&v, 0, 99);        // set element at index

size_t len = cvec_int_len(&v);
cvec_int_reserve(&v, 100);      // pre-allocate capacity
cvec_int_clear(&v);             // reset length to 0, keeps memory
cvec_int_free(&v);              // release memory
```

### Hashmap

```c
cmap_char_ptr_int m;
cmap_char_ptr_int_init(&m, NULL);

cmap_char_ptr_int_put(&m, "alice", 100);
cmap_char_ptr_int_put(&m, "bob", 200);

int* val = cmap_char_ptr_int_get(&m, "alice");  // returns pointer to value, or NULL
if (val) {
    printf("%d\n", *val);  // 100
}

bool exists = cmap_char_ptr_int_has(&m, "bob");     // true
bool removed = cmap_char_ptr_int_del(&m, "bob");    // true

size_t count = cmap_char_ptr_int_count(&m);
cmap_char_ptr_int_clear(&m);    // remove all entries, keeps memory
cmap_char_ptr_int_free(&m);     // release memory
```

### Hashset

```c
cset_uint32_t s;
cset_uint32_t_init(&s, NULL);

bool added = cset_uint32_t_add(&s, 42);     // true (new element)
bool again = cset_uint32_t_add(&s, 42);     // false (already exists)

bool exists = cset_uint32_t_has(&s, 42);    // true
bool removed = cset_uint32_t_remove(&s, 42); // true

size_t count = cset_uint32_t_count(&s);
cset_uint32_t_clear(&s);
cset_uint32_t_free(&s);
```

## Custom Types

For custom structs, ensure they are defined/included before including the generated header. Example:

```c
typedef struct {
    int id;
    float x, y;
} Enemy;
#include "mwac_containers.h"

cvec_Enemy v;
cvec_Enemy_init(&v);
```

or cleaner if your type is in a header:

```c
#include "enemy.h"
#include "mwac_containers.h"

```


## Implementation Details

- Vectors use geometric growth (2x) with initial capacity of 8
- Hashmaps use open addressing with linear probing
- Load factor threshold of 0.7 triggers growth
- Tombstone deletion to maintain probe chains
- FNV-1a hash function
- All functions are static inline for performance
- Bounds checking via assert() on vector access (get, set, pop, peek). Compile with -DNDEBUG to disable in release builds.

## Limitations

- No thread safety
- Type names must be under 64 characters (unless you modify generator code for increased limits)

## Notes

### Allocators

Containers will take in an allocator of a certain signature (NULL for a heap allocator that uses malloc/free)
For a ready-to-use allocator, see [mwacstl](https://github.com/mwac-dev/mwacstl)
This provides a `mwac_allocator` for both an arena allocator and a default heap allocator

### Using with Arena Allocator
```c
#include "allocator.h"  // from mwacstl
#include "mwac_containers.h"

unsigned char buffer[4096];
mwac_arena arena;
mwac_arena_init(&arena, buffer, sizeof(buffer));
mwac_allocator alloc = mwac_arena_allocator(&arena);

cvec_int v;
cvec_int_init(&v, &alloc);
cvec_int_push(&v, 42);

// No free needed - reset arena to reclaim all memory
mwac_arena_reset(&arena);
```

### Key Comparison

Hashmap/hashset keys are compared with `memcmp` (or `strcmp` for `char*`). 
Ensure your keys are integers, pointers, strings, not complex structs.

## License

MIT
