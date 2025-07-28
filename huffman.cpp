#include "huffman.h"

using namespace std;

// 生成哈夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencyMap) {
    // 创建叶子节点，并放入数组
    HuffmanNode* nodes[256];
    int count = 0;
    for (const auto& entry : frequencyMap) {
        nodes[count++] = new HuffmanNode(entry.first, entry.second);
    }

    while (count > 1) {
        // 找到频率最小的两个节点
        int min1 = 0, min2 = 1;
        for (int i = 2; i < count; ++i) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        // 创建新节点，合并两个最小频率的节点
        HuffmanNode* newNode = new HuffmanNode('$', nodes[min1]->frequency + nodes[min2]->frequency);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        // 将新节点加入数组
        nodes[min1] = newNode;
        nodes[min2] = nodes[count - 1];
        count--;
    }

    // 返回根节点
    return nodes[0];
}

// 生成哈夫曼编码表
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr)
        return;

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// 编码字符串为哈夫曼编码
string encodeHuffman(string input, const unordered_map<char, string>& huffmanCodes) {
    string encodedString = "";

    for (char c : input) {
        encodedString += huffmanCodes.at(c);
    }

    return encodedString;
}

// 解码Huffman编码的字符串
string decodeHuffman(const unordered_map<char, string>& huffmanCodes, string encodedString) {
    string decodedString = "";  // 用于保存解码后的字符串
    string currentCode = "";    // 用于保存当前正在处理的编码片段

    unordered_map<string, int> codeLengths;
    for (const auto& entry : huffmanCodes) {
        codeLengths[entry.second] = entry.second.size();
    }

    // 对于每个比特（'0' 或 '1'）
    for (char bit : encodedString) {
        currentCode += bit;  // 将当前比特加到编码片段中


        // 检查是否有与当前编码片段相匹配的编码
        auto lengthIt = codeLengths.find(currentCode);
        if (lengthIt != codeLengths.end() && currentCode.size() == lengthIt->second) {
            for (const auto& entry : huffmanCodes) {
                if (entry.second == currentCode) {
                    decodedString += entry.first;  // 将对应的字符添加到解码结果中
                    currentCode = "";  // 重置编码片段为空，准备处理下一个编码片段
                    break;
                }
            }
        }
    }


    /*
        // 遍历Huffman编码表
        for (const auto& entry : huffmanCodes) {
            // 检查是否有与当前编码片段相匹配的编码
            if (entry.second == currentCode) {
                decodedString += entry.first;  // 将对应的字符添加到解码结果中
                currentCode = "";  // 重置编码片段为空，准备处理下一个编码片段
                break;
            }
        }
    */

    return decodedString;  // 返回解码后的字符串
}

// 保存哈夫曼编码表到JSON文件
void saveHuffmanCodesToJSON(const unordered_map<char, string>& huffmanCodes, const string& fileName) {
    cJSON* jsonRoot = cJSON_CreateObject();

    for (const auto& entry : huffmanCodes) {
        cJSON_AddStringToObject(jsonRoot, std::string(1, entry.first).c_str(), entry.second.c_str());
    }

    ofstream file(fileName);
    if (file.is_open()) {
        file << cJSON_Print(jsonRoot);
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }

    cJSON_Delete(jsonRoot);
}

// 从JSON文件加载哈夫曼编码表
unordered_map<char, string> loadHuffmanCodesFromJSON(const string& fileName) {
    unordered_map<char, string> huffmanCodes;

    ifstream file(fileName);

    /*
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cJSON* jsonRoot = cJSON_Parse(line.c_str());
            if (jsonRoot) {
                cJSON* jsonItem = jsonRoot->child;
                while (jsonItem) {
                    huffmanCodes[jsonItem->string[0]] = jsonItem->valuestring;
                    jsonItem = jsonItem->next;
                }
                cJSON_Delete(jsonRoot);
            } else {
                cerr << "Error parsing JSON file." << endl;
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for reading." << endl;
    }
    */

    
    if (file.is_open()) {
        string jsonString((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        cJSON* jsonRoot = cJSON_Parse(jsonString.c_str());
        if (jsonRoot) {
            cJSON* jsonItem = jsonRoot->child;
            while (jsonItem) {
                huffmanCodes[jsonItem->string[0]] = jsonItem->valuestring;
                jsonItem = jsonItem->next;
            }
            cJSON_Delete(jsonRoot);
        } else {
            cerr << "Error parsing JSON file." << endl;
        }
    } else {
        cerr << "Unable to open file for reading." << endl;
    }

    return huffmanCodes;
}





void compressString(string inputString, int ID) {
    // 统计字符频率
    unordered_map<char, int> frequencyMap;
    for (char c : inputString) {
        frequencyMap[c]++;
    }

    // 生成哈夫曼树
    HuffmanNode* root = buildHuffmanTree(frequencyMap);

    // 生成哈夫曼编码表
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 编码
    string encodedString = encodeHuffman(inputString, huffmanCodes);

    // 保存哈夫曼编码表到JSON文件
    saveHuffmanCodesToJSON(huffmanCodes, "data/huffmanCodes_" + to_string(ID) + ".json");

    // 将二进制字符串转换为实际的二进制数据并写入文件
    writeBinaryFile("data/compressedString_" + to_string(ID) + ".bin", encodedString);

    // 释放动态分配的内存
    delete root;
}

string decompressString(int ID) {
    // 从JSON文件加载哈夫曼编码表
    unordered_map<char, string> huffmanCodes = loadHuffmanCodesFromJSON("data/huffmanCodes_" + to_string(ID) + ".json");

    // 从二进制文件中读取实际的二进制数据并转换为二进制字符串
    string encodedString = readBinaryFile("data/compressedString_" + to_string(ID) + ".bin");

    // 解码
    string decodedString = decodeHuffman(huffmanCodes, encodedString);

    return decodedString;

}


void writeBinaryFile(const string& fileName, const string& binaryData) {
    ofstream file(fileName, ios::binary);

    if (file.is_open()) {
        // 写入二进制数据的长度（实际有效的位数）
        size_t actualBits = binaryData.size();
        file.write(reinterpret_cast<const char*>(&actualBits), sizeof(size_t));

        // 计算需要在右侧填充零的位数
        size_t padding = (8 - (actualBits % 8)) % 8;

        // 写入二进制字符串转换为二进制数据
        char currentByte = 0;
        for (size_t i = 0; i < binaryData.size(); ++i) {
            // 设置当前位置的二进制位
            currentByte |= (binaryData[i] - '0') << (7 - (i % 8));

            // 如果已经处理了8位二进制数据，将其写入文件并重新初始化
            if ((i + 1) % 8 == 0 || i == binaryData.size() - 1) {
                file.write(&currentByte, sizeof(char));
                currentByte = 0;
            }
        }

        file.close();
    } else {
        cerr << "Unable to open binary file for writing." << endl;
    }
}

string readBinaryFile(const string& fileName) {
    ifstream file(fileName, ios::binary);

    if (file.is_open()) {
        // 读取实际有效的位数
        size_t actualBits;
        file.read(reinterpret_cast<char*>(&actualBits), sizeof(size_t));

        // 读取二进制数据
        string binaryData;
        char currentByte;

        for (size_t i = 0; i < (actualBits + 7) / 8; ++i) {
            file.read(&currentByte, sizeof(char));
            for (int j = 7; j >= 0 && binaryData.size() < actualBits; --j) {
                binaryData += ((currentByte >> j) & 1) + '0';
            }
        }

        file.close();

        return binaryData;
    } else {
        cerr << "Unable to open binary file for reading." << endl;
        return "";
    }
}
