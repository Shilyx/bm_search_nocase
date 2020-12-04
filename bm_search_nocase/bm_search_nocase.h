#ifndef _bm_search_nocase_h
#define _bm_search_nocase_h

#include <tchar.h>

const char* bm_search(const char* str, size_t str_len, const char* needle, size_t needle_len);
const char* bm_isearch(const char* str, size_t str_len, const char* needle, size_t needle_len);
const wchar_t* bm_search16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len);
const wchar_t* bm_isearch16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len);

#endif
