/*
* This file is part of the Sofia-SIP package
*
* Copyright (C) 2005 Nokia Corporation.
*
* Contact: Pekka Pessi <pekka.pessi@nokia.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation; either version 2.1 of
* the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*
*/

/**@internal
* @file su_bm.c
* @brief Search with Boyer-Moore algorithm
*
* @author Pekka Pessi <Pekka.Pessi@nokia.com>
*
* @date Created: Mon Apr 11 16:35:16 2005 ppessi
*
*/

#include "bm_search_nocase.h"

#include <ctype.h>
#include <stdlib.h>

#ifndef TORTURELOG
#define TORTURELOG(x) (void)0
#endif

struct bw_fwd_table {
    unsigned char table[UCHAR_MAX + 1];
};

typedef struct bw_fwd_table bm_fwd_table_t;

/** Build forward skip table #bm_fwd_table_t for Boyer-Moore algorithm. */
static
bm_fwd_table_t *
bm_memmem_study0(char const *substr, size_t nlen, bm_fwd_table_t *fwd)
{
    size_t i;

    if (nlen >= UCHAR_MAX) {
        substr += nlen - UCHAR_MAX;
        nlen = UCHAR_MAX;
    }

    memset(&fwd->table, (unsigned char)nlen, sizeof fwd->table);

    for (i = 0; i < nlen; i++) {
        fwd->table[(unsigned short)substr[i]] = (unsigned char)(nlen - i - 1);
    }

    return fwd;
}

/** @defgroup su_bm Fast string searching with Boyer-Moore algorithm
*
* The Boyer-Moore algorithm is used to implement fast substring search. The
* algorithm has some overhead caused by filling a table. Substring search
* then requires at most 1 / substring-length less string comparisons. On
* modern desktop hardware, Boyer-Moore algorithm is seldom faster than the
* naive implementation if the searched substring is shorter than the cache
* line.
*
*/

/**@ingroup su_bm
* @typedef struct bw_fwd_table bm_fwd_table_t;
*
* Forward skip table for Boyer-Moore algorithm.
*
*/

#if !HAVE_MEMMEM
/* Naive implementation of memmem() */
static void *
memmem(const void *haystack, size_t haystacklen,
       const void *substr, size_t substrlen)
{
    size_t i;
    char const *hs = haystack;

    for (i = 0; i <= haystacklen - substrlen; i++) {
        if (memcmp(hs + i, substr, substrlen) == 0)
            return (void *)(hs + i);
    }

    return NULL;
}
#endif

/** Search for a substring using Boyer-Moore algorithm.
* @ingroup su_bm
*/
char *
bm_memmem(char const *haystack, size_t hlen,
          char const *substr, size_t nlen,
          bm_fwd_table_t *fwd)
{
    size_t i, j;
    bm_fwd_table_t fwd0[1];

    if (nlen == 0)
        return (char *)haystack;
    if (substr == NULL || haystack == NULL || nlen > hlen)
        return NULL;

    if (nlen == 1) {
        for (i = 0; i < hlen; i++)
            if (haystack[i] == substr[0])
                return (char *)haystack + i;
        return NULL;
    }

    if (!fwd) {
        if (nlen < 8 * sizeof(long)) /* Just guessing */
            return memmem(haystack, hlen, substr, nlen);

        fwd = bm_memmem_study0(substr, nlen, fwd0);
    }

    for (i = j = nlen - 1; i < hlen;) {
        unsigned char h = haystack[i];
        if (h == substr[j]) {
            TORTURELOG(("match \"%s\" at %u\nwith  %*s\"%.*s*%s\": %s\n",
                        haystack, (unsigned)i,
                        (int)(i - j), "", (int)j, substr, substr + j + 1,
                        j == 0 ? "match!" : "back by 1"));
            if (j == 0)
                return (char *)haystack + i;
            i--, j--;
        } else {
            if (fwd->table[h] > nlen - j) {
                TORTURELOG(("match \"%s\" at %u\n"
                            "last  %*s\"%.*s*%s\": (by %u)\n",
                            haystack, (unsigned)i,
                            (int)(i - j), "",
                            (int)j, substr, substr + j + 1, fwd->table[h]));
                i += fwd->table[h];
            } else {
                TORTURELOG(("match \"%s\" at %u\n"
                            "2nd   %*s\"%.*s*%s\": (by %u)\n",
                            haystack, (unsigned)i,
                            (int)(i - j), "",
                            (int)j, substr, substr + j + 1, (unsigned)(nlen - j)));
                i += nlen - j;
            }
            j = nlen - 1;
        }
    }

    return NULL;
}


/** Build forward skip table for Boyer-Moore algorithm */
static
bm_fwd_table_t *
bm_memcasemem_study0(char const *substr, size_t nlen, bm_fwd_table_t *fwd)
{
    size_t i;

    if (nlen >= UCHAR_MAX) {
        substr += nlen - UCHAR_MAX;
        nlen = UCHAR_MAX;
    }

    for (i = 0; i < UCHAR_MAX; i++)
        fwd->table[i] = (unsigned char)nlen;

    for (i = 0; i < nlen; i++) {
        unsigned char n = tolower(substr[i]);
        fwd->table[n] = (unsigned char)(nlen - i - 1);
    }

    return fwd;
}

/** Search for substring using Boyer-Moore algorithm.
* @ingroup su_bm
*/
char *
bm_memcasemem(char const *haystack, size_t hlen,
              char const *substr, size_t nlen,
              bm_fwd_table_t *fwd)
{
    size_t i, j;
    bm_fwd_table_t fwd0[1];

    if (nlen == 0)
        return (char *)haystack;
    if (substr == 0 || haystack == 0 || nlen > hlen)
        return NULL;

    if (nlen == 1) {
        for (i = 0; i < hlen; i++)
            if (haystack[i] == substr[0])
                return (char *)haystack + i;
        return NULL;
    }

    if (!fwd) {
        fwd = bm_memcasemem_study0(substr, nlen, fwd0);
    }

    for (i = j = nlen - 1; i < hlen;) {
        unsigned char h = haystack[i], n = substr[j];
        if (isupper(h))
            h = tolower(h);
        if (isupper(n))
            n = tolower(n);

        if (h == n) {
            TORTURELOG(("match \"%s\" at %u\n"
                        "with  %*s\"%.*s*%s\": %s\n",
                        haystack, (unsigned)i,
                        (int)(i - j), "", (int)j, substr, substr + j + 1,
                        j == 0 ? "match!" : "back by 1"));
            if (j == 0)
                return (char *)haystack + i;
            i--, j--;
        } else {
            if (fwd->table[h] > nlen - j) {
                TORTURELOG(("match \"%s\" at %u\n"
                            "last  %*s\"%.*s*%s\": (by %u)\n",
                            haystack, (unsigned)i,
                            (int)(i - j), "", (int)j, substr, substr + j + 1,
                            fwd->table[h]));
                i += fwd->table[h];
            } else {
                TORTURELOG(("match \"%s\" at %u\n"
                            "2nd   %*s\"%.*s*%s\": (by %u)\n",
                            haystack, (unsigned)i,
                            (int)(i - j), "", (int)j, substr, substr + j + 1,
                            (unsigned)(nlen - j)));
                i += nlen - j;
            }
            j = nlen - 1;
        }
    }

    return NULL;
}

const char* bm_search_bin(const char* str, size_t str_len, const char* substr, size_t substr_len) {
    bm_fwd_table_t tagtab;
    bm_fwd_table_t *tab = bm_memmem_study0(substr, substr_len, &tagtab);
    const char *res = bm_memmem(str, str_len, substr, substr_len, tab);
    return res;
}

const char* bm_isearch_bin(const char* str, size_t str_len, const char* substr, size_t substr_len) {
    bm_fwd_table_t tagtab;
    bm_fwd_table_t *tab = bm_memcasemem_study0(substr, substr_len, &tagtab);
    const char *res = bm_memcasemem(str, str_len, substr, substr_len, tab);
    return res;
}

const wchar_t* bm_search16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len) {
    bm_fwd_table_t tagtab;
    bm_fwd_table_t *tab = bm_memmem_study0((const char *)substr, substr_len * sizeof(wchar_t), &tagtab);
    const char *res = bm_memmem((const char *)str, str_len * sizeof(wchar_t), (const char *)substr, substr_len * sizeof(wchar_t), tab);
    return (const wchar_t*)res;
}

const wchar_t* bm_isearch16_bin(const wchar_t* str, size_t str_len, const wchar_t* substr, size_t substr_len) {
    bm_fwd_table_t tagtab;
    bm_fwd_table_t *tab = bm_memcasemem_study0((const char *)substr, substr_len * sizeof(wchar_t), &tagtab);
    const char *res = bm_memcasemem((const char *)str, str_len * sizeof(wchar_t), (const char *)substr, substr_len * sizeof(wchar_t), tab);
    return (const wchar_t*)res;
}

const char* bm_search(const char* str, size_t str_len, const char* substr) {
    return bm_search_bin(str, str_len, substr, strlen(substr));
}

const char* bm_isearch(const char* str, size_t str_len, const char* substr) {
    return bm_isearch_bin(str, str_len, substr, strlen(substr));
}

const wchar_t* bm_search16(const wchar_t* str, size_t str_len, const wchar_t* substr) {
    return bm_search16_bin(str, str_len, substr, wcslen(substr));
}

const wchar_t* bm_isearch16(const wchar_t* str, size_t str_len, const wchar_t* substr) {
    return bm_isearch16_bin(str, str_len, substr, wcslen(substr));
}
