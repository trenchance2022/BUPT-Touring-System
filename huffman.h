#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include "cJSON.h"

using namespace std;

// 定义哈夫曼树节点
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}

    // 析构函数用于释放动态分配的内存
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// 生成哈夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencyMap);

// 生成哈夫曼编码表
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes);

// 编码字符串为哈夫曼编码
string encodeHuffman(string input, const unordered_map<char, string>& huffmanCodes);

// 解码哈夫曼编码为原始字符串
string decodeHuffman(const unordered_map<char, string>& huffmanCodes, string encodedString);

// 保存哈夫曼编码表到JSON文件
void saveHuffmanCodesToJSON(const unordered_map<char, string>& huffmanCodes, const string& fileName);

// 从JSON文件加载哈夫曼编码表
unordered_map<char, string> loadHuffmanCodesFromJSON(const string& fileName);

// 写入二进制文件
void writeBinaryFile(const string& fileName, const string& binaryData);

// 从二进制文件中读取实际的二进制数据并转换为二进制字符串
string readBinaryFile(const string& fileName);

// 压缩字符串并保存编码表和二进制文件
void compressString(string inputString, int ID);

// 从编码表和二进制文件中解压缩字符串
string decompressString(int ID);

#endif // HUFFMAN_H
