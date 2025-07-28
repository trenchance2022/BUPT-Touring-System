#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 构建部分匹配表
vector<int> buildPartialMatchTable(const string& pattern);

// KMP算法进行字符串匹配
bool kmpSearch(const string& text, const string& pattern);

bool kmpPatternMatch(const vector<string>& patterns, const string& text);

#endif // KMP_H
