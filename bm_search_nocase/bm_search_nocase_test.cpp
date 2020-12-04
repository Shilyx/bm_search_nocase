/*
 *  @file  : bm_search_nocase.cpp
 *  @author: shilyx
 *  @date  : 2020-12-04 10:42:41.499
 *  @note  : Generated by SlxTemplates
 */

#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <strstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "bm_search_nocase.h"

int main(int argc, char *argv[]) {
    const char *str = "bm_Nosearch_nocasebm_search_nocase";
    const char *needle = "no";
    const wchar_t *strW = L"bm_Nosearch_nocasebm_search_nocase";
    const wchar_t *needleW = L"no";
    cout << bm_search(str, strlen(str), needle, strlen(needle)) << endl;
    cout << bm_isearch(str, strlen(str), needle, strlen(needle)) << endl;
    wcout << bm_search16(strW, wcslen(strW), needleW, wcslen(needleW)) << endl;
    wcout << bm_isearch16(strW, wcslen(strW), needleW, wcslen(needleW)) << endl;

    return 0;
}