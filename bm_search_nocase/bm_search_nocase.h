#ifndef _bm_search_nocase_h
#define _bm_search_nocase_h

// douxian 2020.12.4
// 使用bm算法支持宽字符搜索，支持大小写匹配搜索
// 也支持二进制搜索
// 搜索数据的长度要从外部传入

#include <tchar.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* bm_search_bin(const char* str, size_t str_len, const char* substr, size_t substr_len);
const char* bm_isearch_bin(const char* str, size_t str_len, const char* substr, size_t substr_len);
const wchar_t* bm_search16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len);
const wchar_t* bm_isearch16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len);

#ifdef __cplusplus
}
#endif

#endif
