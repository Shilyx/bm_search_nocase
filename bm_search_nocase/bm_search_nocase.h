#ifndef _bm_search_nocase_h
#define _bm_search_nocase_h

// douxian 2020.12.4
// ʹ��bm�㷨֧�ֿ��ַ�������֧�ִ�Сдƥ������
// Ҳ֧�ֶ���������
// �������ݵĳ���Ҫ���ⲿ����

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
