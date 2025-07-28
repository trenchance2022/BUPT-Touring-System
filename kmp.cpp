#include "kmp.h"

// 构建部分匹配表
vector<int> buildPartialMatchTable(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);

    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// KMP算法进行字符串匹配
bool kmpSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = buildPartialMatchTable(pattern);

    int i = 0;  // 索引text的指针
    int j = 0;  // 索引pattern的指针
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            // 匹配成功
            return true;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    // 匹配失败
    return false;
}

bool kmpPatternMatch(const vector<string>& patterns, const string& text) {
    for (const string& pattern : patterns) {
        // 使用你之前提供的 KMP 算法进行字符串匹配
        if (kmpSearch(text, pattern)) {
            return true;  // 匹配到任意一个模式串，返回true
        }
    }
    return false;  // 未匹配到任何模式串，返回false
}


