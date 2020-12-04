#include "bm_search_nocase.h"
#include "su_bm.h"
#include <malloc.h>

const char* bm_search(const char* str, size_t str_len, const char* needle, size_t needle_len) {
    bm_fwd_table_t *tab = bm_memmem_study(needle, needle_len);
    const char *res = bm_memmem(str, str_len, needle, needle_len, tab);
    free(tab);
    return res;
}

const char* bm_isearch(const char* str, size_t str_len, const char* needle, size_t needle_len) {
    bm_fwd_table_t *tab = bm_memcasemem_study(needle, needle_len);
    const char *res = bm_memcasemem(str, str_len, needle, needle_len, tab);
    free(tab);
    return res;
}

const wchar_t* bm_search16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len) {
    bm_fwd_table_t *tab = bm_memmem_study((const char *)needle, needle_len * sizeof(wchar_t));
    const char *res = bm_memmem((const char *)str, str_len * sizeof(wchar_t), (const char *)needle, needle_len * sizeof(wchar_t), tab);
    free(tab);
    return (const wchar_t*)res;
}

const wchar_t* bm_isearch16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len) {
    bm_fwd_table_t *tab = bm_memcasemem_study((const char *)needle, needle_len * sizeof(wchar_t));
    const char *res = bm_memcasemem((const char *)str, str_len * sizeof(wchar_t), (const char *)needle, needle_len * sizeof(wchar_t), tab);
    free(tab);
    return (const wchar_t*)res;
}