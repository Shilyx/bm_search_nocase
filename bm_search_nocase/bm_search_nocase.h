#ifndef _bm_search_nocase_h
#define _bm_search_nocase_h

#include <tchar.h>

const char* bm_search(const char* str, const char* str_search);
const char* bm_isearch(const char* str, const char* str_search);
const wchar_t* bm_search16(const wchar_t* str, const wchar_t* str_search);
const wchar_t* bm_isearch16(const wchar_t* str, const wchar_t* str_search);

#endif
