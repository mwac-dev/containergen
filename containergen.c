#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINE_LENGTH 256
#define MAX_TYPE_LENGTH 64

static void emit_hash_function(FILE* out) {
    fprintf(out,
            "// Source : https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function \n"
            "// FNV-1a is a Simple non-cryptographic hash function\n"
            "// However I am planning on researching other hashing functions for best performance "
            "based on the length\n"
            "static inline uint64_t mwac_hash_bytes(const void* data, size_t len) {\n"
            "    const uint8_t* bytes = (const uint8_t*)data;\n"
            "    uint64_t hash = 14695981039346656037ULL; // FNV offset basis\n"
            "    for (size_t i = 0; i < len; i++) {\n"
            "        hash ^= bytes[i];\n"
            "        hash *= 1099511628211ULL; // FNV prime\n"
            "    }\n"
            "    return hash;\n"
            "}\n\n");

    fprintf(out,
            "static inline uint64_t mwac_hash_string(const char* str) {\n"
            "    uint64_t hash = 14695981039346656037ULL;\n"
            "    while (*str) {\n"
            "        hash ^= (uint8_t)*str++;\n"
            "        hash *= 1099511628211ULL;\n"
            "    }\n"
            "    return hash;\n"
            "}\n\n");

    fprintf(out, "#define mwac_hash(key) mwac_hash_bytes(&(key), sizeof(key))\n\n");
}

static void emit_header_prefix(FILE* out) {
    fprintf(out,
            "// mwac_containers.h - Auto-generated type-safe containers\n"
            "// Do not edit manually - regenerate with codegen\n"
            "#ifndef MWAC_CONTAINERS_H\n"
            "#define MWAC_CONTAINERS_H\n"
            "\n"
            "#include <assert.h>\n"
            "#include <stddef.h>\n"
            "#include <stdint.h>\n"
            "#include <stdbool.h>\n"
            "#include <string.h>\n"
            "#include \"allocator.h\"\n"
            "\n");

    emit_hash_function(out);

    fprintf(out,
            "enum {\n"
            "    MWAC_ENTRY_EMPTY     = 0,\n"
            "    MWAC_ENTRY_OCCUPIED  = 1,\n"
            "    MWAC_ENTRY_TOMBSTONE = 2\n"
            "};\n\n");
}

static void emit_header_suffix(FILE* out) {
    fprintf(out,
            "\n"
            "#endif // MWAC_CONTAINERS_H\n");
}

// Triming leading and trailing whitespace
static char* trim(char* str) {
    while (isspace((unsigned char)*str))
        str++;
    if (*str == '\0')
        return str;

    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';

    return str;
}

// Parsing a line into tokens
// Returns the number of tokens found
//
// **Modifies the input line by inserting null terminators**
static int parse_line(char* line, char** tokens, int max_tokens) {
    int count = 0;
    char* p = line;

    while (*p && count < max_tokens) {
        while (*p && isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;

        tokens[count++] = p;

        while (*p && !isspace((unsigned char)*p))
            p++;
        if (*p) {
            *p = '\0';
            p++;
        }
    }

    return count;
}

// Sanitize type name for use in identifiers
// e.g., "Enemy*" -> "Enemy_ptr", "void*" -> "void_ptr"
static char* sanitize_type_name(const char* type) {
    static char buffer[MAX_TYPE_LENGTH * 2];
    char* dst = buffer;

    for (const char* src = type; *src; src++) {
        if (*src == '*') {
            *dst++ = '_';
            *dst++ = 'p';
            *dst++ = 't';
            *dst++ = 'r';
        } else if (*src == ' ') {
            // skip
        } else {
            *dst++ = *src;
        }
    }
    *dst = '\0';

    return buffer;
}

static void emit_vector_type(FILE* out, const char* T) {
    char* sanitized_T = sanitize_type_name(T);

    // Struct definition
    fprintf(out,
            "typedef struct {\n"
            "    %s*             data;\n"
            "    size_t          length;\n"
            "    size_t          capacity;\n"
            "    mwac_allocator* allocator;\n"
            "} cvec_%s;\n\n",
            T,
            sanitized_T);

    // cvec_T_init
    fprintf(out,
            "static inline void cvec_%s_init(cvec_%s* v, mwac_allocator* alloc) {\n"
            "    v->data = NULL;\n"
            "    v->length = 0;\n"
            "    v->capacity = 0;\n"
            "    v->allocator = alloc ? alloc : mwac_heap_allocator_default();\n"
            "}\n\n",
            sanitized_T,
            sanitized_T);

    // cvec_T_free
    fprintf(out,
            "static inline void cvec_%s_free(cvec_%s* v) {\n"
            "    mwac_free(v->allocator, v->data);\n"
            "    v->data = NULL;\n"
            "    v->length = 0;\n"
            "    v->capacity = 0;\n"
            "}\n\n",
            sanitized_T,
            sanitized_T);

    // cvec_T_push
    fprintf(out,
            "static inline void cvec_%s_push(cvec_%s* v, %s item) {\n"
            "    if (v->length >= v->capacity) {\n"
            "        size_t old_cap = v->capacity;\n"
            "        size_t new_cap = old_cap == 0 ? 8 : old_cap * 2;\n"
            "        v->data = (%s*)mwac_realloc(v->allocator, v->data,\n"
            "                                     old_cap * sizeof(%s),\n"
            "                                     new_cap * sizeof(%s));\n"
            "        v->capacity = new_cap;\n"
            "    }\n"
            "    v->data[v->length++] = item;\n"
            "}\n\n",
            sanitized_T,
            sanitized_T,
            T,
            T,
            T,
            T);

    // cvec_T_pop
    fprintf(out,
            "static inline %s cvec_%s_pop(cvec_%s* v) {\n"
            "    assert(v->length > 0 && \"pop from empty vector\");\n"
            "    return v->data[--v->length];\n"
            "}\n\n",
            T,
            sanitized_T,
            sanitized_T);

    // cvec_T_peek
    fprintf(out,
            "static inline %s cvec_%s_peek(cvec_%s* v) {\n"
            "    assert(v->length > 0 && \"peek on empty vector\");\n"
            "    return v->data[v->length - 1];\n"
            "}\n\n",
            T,
            sanitized_T,
            sanitized_T);

    // cvec_T_get
    fprintf(out,
            "static inline %s* cvec_%s_get(cvec_%s* v, size_t index) {\n"
            "    assert(index < v->length && \"index out of bounds\");\n"
            "    return &v->data[index];\n"
            "}\n\n",
            T,
            sanitized_T,
            sanitized_T);

    // cvec_T_set
    fprintf(out,
            "static inline void cvec_%s_set(cvec_%s* v, size_t index, %s item) {\n"
            "    assert(index < v->length && \"index out of bounds\");\n"
            "    v->data[index] = item;\n"
            "}\n\n",
            sanitized_T,
            sanitized_T,
            T);

    // cvec_T_len
    fprintf(out,
            "static inline size_t cvec_%s_len(cvec_%s* v) {\n"
            "    return v->length;\n"
            "}\n\n",
            sanitized_T,
            sanitized_T);

    // cvec_T_clear
    fprintf(out,
            "static inline void cvec_%s_clear(cvec_%s* v) {\n"
            "    v->length = 0;\n"
            "}\n\n",
            sanitized_T,
            sanitized_T);

    // cvec_T_reserve
    fprintf(out,
            "static inline void cvec_%s_reserve(cvec_%s* v, size_t n) {\n"
            "    if (n > v->capacity) {\n"
            "        v->data = (%s*)mwac_realloc(v->allocator, v->data,\n"
            "                                     v->capacity * sizeof(%s),\n"
            "                                     n * sizeof(%s));\n"
            "        v->capacity = n;\n"
            "    }\n"
            "}\n\n",
            sanitized_T,
            sanitized_T,
            T,
            T,
            T);
}

static void process_vector_file(FILE* out, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Note: %s not found, skipping vector generation.\n", filename);
        return;
    }

    fprintf(out, "// =============== C - Vectors ===============\n\n");

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), f)) {
        char* trimmed = trim(line);

        if (trimmed[0] == '\0' || trimmed[0] == '#')
            continue;

        char* tokens[1];
        int count = parse_line(trimmed, tokens, 1);

        if (count == 1) {

            if (strlen(tokens[0]) > MAX_TYPE_LENGTH) {
                fprintf(
                    stderr,
                    "Warning: type name too long in vector: %s\n"
                    "either increase MAX_TYPE_LENGTH or recheck the type passed into vector.gen",
                    tokens[0]);
            }
            emit_vector_type(out, tokens[0]);
        }
    }
    fclose(f);
}

static void emit_hashmap_type(FILE* out, const char* K, const char* V) {
    char sanitized_K[MAX_TYPE_LENGTH * 2];
    char sanitized_V[MAX_TYPE_LENGTH * 2];
    snprintf(sanitized_K, sizeof(sanitized_K), "%s", sanitize_type_name(K));
    snprintf(sanitized_V, sizeof(sanitized_V), "%s", sanitize_type_name(V));

    bool string_key = (strcmp(K, "char*") == 0);

    // Entry struct
    fprintf(out,
            "typedef struct {\n"
            "    %s      key;\n"
            "    %s      value;\n"
            "    uint8_t state;\n"
            "} cmap_%s_%s_entry;\n\n",
            K, V, sanitized_K, sanitized_V);

    // CMap struct
    fprintf(out,
            "typedef struct {\n"
            "    cmap_%s_%s_entry* entries;\n"
            "    size_t            capacity;\n"
            "    size_t            count;\n"
            "    size_t            tombstones;\n"
            "    mwac_allocator*   allocator;\n"
            "} cmap_%s_%s;\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V);

    // Init
    fprintf(out,
            "static inline void cmap_%s_%s_init(cmap_%s_%s* m, mwac_allocator* alloc) {\n"
            "    m->entries = NULL;\n"
            "    m->capacity = 0;\n"
            "    m->count = 0;\n"
            "    m->tombstones = 0;\n"
            "    m->allocator = alloc ? alloc : mwac_heap_allocator_default();\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V);

    // Free
    fprintf(out,
            "static inline void cmap_%s_%s_free(cmap_%s_%s* m) {\n"
            "    mwac_free(m->allocator, m->entries);\n"
            "    m->entries = NULL;\n"
            "    m->capacity = 0;\n"
            "    m->count = 0;\n"
            "    m->tombstones = 0;\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V);

    // Forward declare grow
    fprintf(out,
            "static void cmap_%s_%s_grow(cmap_%s_%s* m);\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V);

    // Put
    fprintf(out,
            "static inline void cmap_%s_%s_put(cmap_%s_%s* m, %s key, %s value) {\n"
            "    if (m->capacity == 0 || (m->count + m->tombstones + 1) * 10 > m->capacity * 7) {\n"
            "        cmap_%s_%s_grow(m);\n"
            "    }\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (m->capacity - 1);\n"
            "    size_t first_tombstone = SIZE_MAX;\n"
            "    \n"
            "    for (;;) {\n"
            "        cmap_%s_%s_entry* e = &m->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            if (first_tombstone != SIZE_MAX) {\n"
            "                e = &m->entries[first_tombstone];\n"
            "                m->tombstones--;\n"
            "            }\n"
            "            e->key = key;\n"
            "            e->value = value;\n"
            "            e->state = MWAC_ENTRY_OCCUPIED;\n"
            "            m->count++;\n"
            "            return;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_TOMBSTONE) {\n"
            "            if (first_tombstone == SIZE_MAX) first_tombstone = idx;\n"
            "        } else if (%s) {\n"
            "            e->value = value;\n"
            "            return;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (m->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V, K, V,
            sanitized_K, sanitized_V,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K, sanitized_V,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Get
    fprintf(out,
            "static inline %s* cmap_%s_%s_get(cmap_%s_%s* m, %s key) {\n"
            "    if (m->capacity == 0) return NULL;\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (m->capacity - 1);\n"
            "    \n"
            "    for (;;) {\n"
            "        cmap_%s_%s_entry* e = &m->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            return NULL;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_OCCUPIED && %s) {\n"
            "            return &e->value;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (m->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            V, sanitized_K, sanitized_V, sanitized_K, sanitized_V, K,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K, sanitized_V,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Has
    fprintf(out,
            "static inline bool cmap_%s_%s_has(cmap_%s_%s* m, %s key) {\n"
            "    return cmap_%s_%s_get(m, key) != NULL;\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V, K,
            sanitized_K, sanitized_V);

    // Del
    fprintf(out,
            "static inline bool cmap_%s_%s_del(cmap_%s_%s* m, %s key) {\n"
            "    if (m->capacity == 0) return false;\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (m->capacity - 1);\n"
            "    \n"
            "    for (;;) {\n"
            "        cmap_%s_%s_entry* e = &m->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            return false;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_OCCUPIED && %s) {\n"
            "            e->state = MWAC_ENTRY_TOMBSTONE;\n"
            "            m->count--;\n"
            "            m->tombstones++;\n"
            "            return true;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (m->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V, K,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K, sanitized_V,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Count
    fprintf(out,
            "static inline size_t cmap_%s_%s_count(cmap_%s_%s* m) {\n"
            "    return m->count;\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V);

    // Clear
    fprintf(out,
            "static inline void cmap_%s_%s_clear(cmap_%s_%s* m) {\n"
            "    if (m->entries) {\n"
            "        memset(m->entries, 0, m->capacity * sizeof(cmap_%s_%s_entry));\n"
            "    }\n"
            "    m->count = 0;\n"
            "    m->tombstones = 0;\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V,
            sanitized_K, sanitized_V);

    // Grow
    fprintf(out,
            "static void cmap_%s_%s_grow(cmap_%s_%s* m) {\n"
            "    size_t old_cap = m->capacity;\n"
            "    cmap_%s_%s_entry* old_entries = m->entries;\n"
            "    \n"
            "    m->capacity = old_cap == 0 ? 16 : old_cap * 2;\n"
            "    m->entries = (cmap_%s_%s_entry*)mwac_calloc(m->allocator,\n"
            "                                                m->capacity,\n"
            "                                                sizeof(cmap_%s_%s_entry));\n"
            "    m->count = 0;\n"
            "    m->tombstones = 0;\n"
            "    \n"
            "    for (size_t i = 0; i < old_cap; i++) {\n"
            "        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {\n"
            "            cmap_%s_%s_put(m, old_entries[i].key, old_entries[i].value);\n"
            "        }\n"
            "    }\n"
            "    \n"
            "    mwac_free(m->allocator, old_entries);\n"
            "}\n\n",
            sanitized_K, sanitized_V, sanitized_K, sanitized_V,
            sanitized_K, sanitized_V,
            sanitized_K, sanitized_V, sanitized_K, sanitized_V,
            sanitized_K, sanitized_V);
}

static void process_hashmap_file(FILE* out, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Note: %s not found, skipping hashmaps\n", filename);
        return;
    }

    fprintf(out, "// ============ C - Hashmaps ============\n\n");

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), f)) {
        char* trimmed = trim(line);

        if (trimmed[0] == '\0' || trimmed[0] == '#')
            continue;

        char* tokens[2];
        int count = parse_line(trimmed, tokens, 2);

        if (count == 2) {

            if (strlen(tokens[0]) > MAX_TYPE_LENGTH) {
                fprintf(
                    stderr,
                    "Warning: type name too long in hashmap: %s\n"
                    "either increase MAX_TYPE_LENGTH or recheck the type passed into hashmap.gen",
                    tokens[0]);
            }

            if (strlen(tokens[1]) > MAX_TYPE_LENGTH) {
                fprintf(
                    stderr,
                    "Warning: type name too long in hashmap: %s\n"
                    "either increase MAX_TYPE_LENGTH or recheck the type passed into hashmap.gen",
                    tokens[1]);
            }
            emit_hashmap_type(out, tokens[0], tokens[1]);
        } else {
            fprintf(stderr, "Warning: invalid hashmap line: %s\n", line);
        }
    }

    fclose(f);
}

static void emit_hashset_type(FILE* out, const char* K) {
    char* sanitized_K = sanitize_type_name(K);

    bool string_key = (strcmp(K, "char*") == 0);

    // Entry struct
    fprintf(out,
            "typedef struct {\n"
            "    %s      key;\n"
            "    uint8_t state;\n"
            "} cset_%s_entry;\n\n",
            K, sanitized_K);

    // CSet struct
    fprintf(out,
            "typedef struct {\n"
            "    cset_%s_entry*  entries;\n"
            "    size_t          capacity;\n"
            "    size_t          count;\n"
            "    size_t          tombstones;\n"
            "    mwac_allocator* allocator;\n"
            "} cset_%s;\n\n",
            sanitized_K, sanitized_K);

    // Init
    fprintf(out,
            "static inline void cset_%s_init(cset_%s* s, mwac_allocator* alloc) {\n"
            "    s->entries = NULL;\n"
            "    s->capacity = 0;\n"
            "    s->count = 0;\n"
            "    s->tombstones = 0;\n"
            "    s->allocator = alloc ? alloc : mwac_heap_allocator_default();\n"
            "}\n\n",
            sanitized_K, sanitized_K);

    // Free
    fprintf(out,
            "static inline void cset_%s_free(cset_%s* s) {\n"
            "    mwac_free(s->allocator, s->entries);\n"
            "    s->entries = NULL;\n"
            "    s->capacity = 0;\n"
            "    s->count = 0;\n"
            "    s->tombstones = 0;\n"
            "}\n\n",
            sanitized_K, sanitized_K);

    // Forward declare grow
    fprintf(out,
            "static void cset_%s_grow(cset_%s* s);\n\n",
            sanitized_K, sanitized_K);

    // Add
    fprintf(out,
            "static inline bool cset_%s_add(cset_%s* s, %s key) {\n"
            "    if (s->capacity == 0 || (s->count + s->tombstones + 1) * 10 > s->capacity * 7) {\n"
            "        cset_%s_grow(s);\n"
            "    }\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (s->capacity - 1);\n"
            "    size_t first_tombstone = SIZE_MAX;\n"
            "    \n"
            "    for (;;) {\n"
            "        cset_%s_entry* e = &s->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            if (first_tombstone != SIZE_MAX) {\n"
            "                e = &s->entries[first_tombstone];\n"
            "                s->tombstones--;\n"
            "            }\n"
            "            e->key = key;\n"
            "            e->state = MWAC_ENTRY_OCCUPIED;\n"
            "            s->count++;\n"
            "            return true;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_TOMBSTONE) {\n"
            "            if (first_tombstone == SIZE_MAX) first_tombstone = idx;\n"
            "        } else if (%s) {\n"
            "            return false;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (s->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            sanitized_K, sanitized_K, K,
            sanitized_K,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Has
    fprintf(out,
            "static inline bool cset_%s_has(cset_%s* s, %s key) {\n"
            "    if (s->capacity == 0) return false;\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (s->capacity - 1);\n"
            "    \n"
            "    for (;;) {\n"
            "        cset_%s_entry* e = &s->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            return false;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_OCCUPIED && %s) {\n"
            "            return true;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (s->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            sanitized_K, sanitized_K, K,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Remove
    fprintf(out,
            "static inline bool cset_%s_remove(cset_%s* s, %s key) {\n"
            "    if (s->capacity == 0) return false;\n"
            "    \n"
            "    uint64_t hash = %s;\n"
            "    size_t idx = hash & (s->capacity - 1);\n"
            "    \n"
            "    for (;;) {\n"
            "        cset_%s_entry* e = &s->entries[idx];\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_EMPTY) {\n"
            "            return false;\n"
            "        }\n"
            "        \n"
            "        if (e->state == MWAC_ENTRY_OCCUPIED && %s) {\n"
            "            e->state = MWAC_ENTRY_TOMBSTONE;\n"
            "            s->count--;\n"
            "            s->tombstones++;\n"
            "            return true;\n"
            "        }\n"
            "        \n"
            "        idx = (idx + 1) & (s->capacity - 1);\n"
            "    }\n"
            "}\n\n",
            sanitized_K, sanitized_K, K,
            string_key ? "mwac_hash_string(key)" : "mwac_hash(key)",
            sanitized_K,
            string_key ? "strcmp(e->key, key) == 0" : "memcmp(&e->key, &key, sizeof(e->key)) == 0");

    // Count
    fprintf(out,
            "static inline size_t cset_%s_count(cset_%s* s) {\n"
            "    return s->count;\n"
            "}\n\n",
            sanitized_K, sanitized_K);

    // Clear
    fprintf(out,
            "static inline void cset_%s_clear(cset_%s* s) {\n"
            "    if (s->entries) {\n"
            "        memset(s->entries, 0, s->capacity * sizeof(cset_%s_entry));\n"
            "    }\n"
            "    s->count = 0;\n"
            "    s->tombstones = 0;\n"
            "}\n\n",
            sanitized_K, sanitized_K, sanitized_K);

    // Grow
    fprintf(out,
            "static void cset_%s_grow(cset_%s* s) {\n"
            "    size_t old_cap = s->capacity;\n"
            "    cset_%s_entry* old_entries = s->entries;\n"
            "    \n"
            "    s->capacity = old_cap == 0 ? 16 : old_cap * 2;\n"
            "    s->entries = (cset_%s_entry*)mwac_calloc(s->allocator,\n"
            "                                             s->capacity,\n"
            "                                             sizeof(cset_%s_entry));\n"
            "    s->count = 0;\n"
            "    s->tombstones = 0;\n"
            "    \n"
            "    for (size_t i = 0; i < old_cap; i++) {\n"
            "        if (old_entries[i].state == MWAC_ENTRY_OCCUPIED) {\n"
            "            cset_%s_add(s, old_entries[i].key);\n"
            "        }\n"
            "    }\n"
            "    \n"
            "    mwac_free(s->allocator, old_entries);\n"
            "}\n\n",
            sanitized_K, sanitized_K,
            sanitized_K,
            sanitized_K, sanitized_K,
            sanitized_K);
}

static void process_hashset_file(FILE* out, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Note: %s not found, skipping hashsets\n", filename);
        return;
    }

    fprintf(out, "// ============ C - Hashsets ============\n\n");

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), f)) {
        char* trimmed = trim(line);

        if (trimmed[0] == '\0' || trimmed[0] == '#')
            continue;

        char* tokens[1];
        int count = parse_line(trimmed, tokens, 1);

        if (count == 1) {
            if (strlen(tokens[0]) > MAX_TYPE_LENGTH) {
                fprintf(
                    stderr,
                    "Warning: type name too long in hashset: %s\n"
                    "either increase MAX_TYPE_LENGTH or recheck the type passed into hashset.gen",
                    tokens[0]);
            }
            emit_hashset_type(out, tokens[0]);
        }
    }

    fclose(f);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    FILE* out = fopen("mwac_containers.h", "w");
    if (!out) {
        fprintf(stderr, "Error: could not open output file\n");
        return 1;
    }

    emit_header_prefix(out);

    process_vector_file(out, "vector.gen");
    process_hashmap_file(out, "hashmap.gen");
    process_hashset_file(out, "hashset.gen");

    emit_header_suffix(out);

    fclose(out);
    printf("Generated mwac_containers.h successfully.\n");

    return 0;
}
