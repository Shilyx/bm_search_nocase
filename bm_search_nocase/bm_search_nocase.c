#include "bm_search_nocase.h"
#include "su_bm.h"
#include <malloc.h>

const char* bm_search_bin(const char* str, size_t str_len, const char* substr, size_t substr_len) {
    bm_fwd_table_t *tab = bm_memmem_study(substr, substr_len);
    const char *res = bm_memmem(str, str_len, substr, substr_len, tab);
    free(tab);
    return res;
}

const char* bm_isearch_bin(const char* str, size_t str_len, const char* substr, size_t substr_len) {
    bm_fwd_table_t *tab = bm_memcasemem_study(substr, substr_len);
    const char *res = bm_memcasemem(str, str_len, substr, substr_len, tab);
    free(tab);
    return res;
}

const wchar_t* bm_search16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len) {
    bm_fwd_table_t *tab = bm_memmem_study((const char *)substr, substr_len * sizeof(wchar_t));
    const char *res = bm_memmem((const char *)str, str_len * sizeof(wchar_t), (const char *)substr, substr_len * sizeof(wchar_t), tab);
    free(tab);
    return (const wchar_t*)res;
}

const wchar_t* bm_isearch16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len) {
    bm_fwd_table_t *tab = bm_memcasemem_study((const char *)substr, substr_len * sizeof(wchar_t));
    const char *res = bm_memcasemem((const char *)str, str_len * sizeof(wchar_t), (const char *)substr, substr_len * sizeof(wchar_t), tab);
    free(tab);
    return (const wchar_t*)res;
}