#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <stack>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>


#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"


class HuffmanTree: public HuffmanTreeBase {
public:
std::string compress(const std::string inputStr);
std::string serializeTree() const;
std::string decompress(const std::string inputCode, const std::string serializedTree);

public:
void encodeMap(HuffmanNode *root, std::string str, std::map<char, std::string> &encMap);
std::string Serialize(HuffmanNode *node) const;
HuffmanNode *makeTree(const std::string s) const;

private:
HuffmanNode *rootNode;
};

#endif
