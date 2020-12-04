# bm_search_nocase

```cpp
// case sensitive search
const char* bm_search(const char* str, size_t str_len, const char* needle, size_t needle_len);
// case insensitive search
const char* bm_isearch(const char* str, size_t str_len, const char* needle, size_t needle_len);
// wide-char case sensitive search
const wchar_t* bm_search16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len);
// wide-char case insensitive search
const wchar_t* bm_isearch16(const wchar_t* str, size_t str_len, const wchar_t* needle, size_t needle_len);
```
