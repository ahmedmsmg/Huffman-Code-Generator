// Names: Ahmed Ghoneim U91248135

#include "HuffmanTree1.hpp"


std::string HuffmanTree::compress(const std::string inputStr) {

//a map will be used to store characters as the keys and the thier
//associated frequencies as the values
std::map <char, size_t> char_map;
std::map <char, size_t>::const_iterator iterate;

//frequencies for each character
for (std::string::const_iterator iter = inputStr.begin(); iter != inputStr.end(); iter++) {
char_map[*iter] += 1;
}

//The characters and their frequencies are inserted into a priority queue
HeapQueue<HuffmanNode*, HuffmanNode::Compare> queue;
for (iterate = char_map.begin(); iterate != char_map.end(); iterate++) {
HuffmanNode* new_pair_node;
new_pair_node = new HuffmanNode(iterate->first, iterate->second);
queue.insert(new_pair_node);
}
//the tree is constructed untill only 1 node remains in the heap
while(queue.size() != 1) {


HuffmanNode *firstNode;
firstNode = queue.min();
queue.removeMin();

HuffmanNode *secondNode;
secondNode = queue.min();
queue.removeMin();

//new frequency value of the parent node and children nodes
size_t new_freq = firstNode->getFrequency() + secondNode->getFrequency();
HuffmanNode *newParent = new HuffmanNode('\0', new_freq, nullptr, firstNode, secondNode);


queue.insert(newParent);
}


std::map<char, std::string> encMap;

//the new root node of the heap
HuffmanNode *heap = queue.min();

std::string binaryCode = "";
encodeMap(heap, binaryCode, encMap);

std::string compressedStr = "";

for (std::string::const_iterator iter = inputStr.begin(); iter != inputStr.end(); iter++) {
compressedStr = compressedStr + encMap[*iter];
}

//private data memeber of Huffman pointer node
//is given a value of the root of the heap
rootNode = heap;

return compressedStr;
}


//helper function for the compress function it takes in the reference to the map,
//a temporary iterator string, and the root node of the heap,
void HuffmanTree::encodeMap(HuffmanNode *root, std::string str, std::map<char, std::string> &huffmanCodeMap) {


if (root == nullptr) {
return;
}

if (root->isLeaf()) {
huffmanCodeMap[root->getCharacter()] = str;
}

//recursive calls of the function

encodeMap(root->left, str + "0", huffmanCodeMap);
encodeMap(root->right, str + "1", huffmanCodeMap);
}


std::string HuffmanTree::Serialize(HuffmanNode *node) const {
std::string result = "";

//if the node is at a branch, the function recurses, appending B
//to the string to indicate the presence of the branch at this point
if (node->isBranch()) {
result = result + Serialize(node->left) + Serialize(node->right) + "B";
return result;
} else { //else if at a leaf, the character from this leaf is appended to the string
result = result + "L" + node->getCharacter();
return result;
}
}


//main serialize function
std::string HuffmanTree::serializeTree() const {

std::string output = Serialize(rootNode);
return output;
}



HuffmanNode *HuffmanTree::makeTree(const std::string s) const {
size_t parentFreq;
//an stl stack is used to manage the chars and the associated branch indicators
std::stack<HuffmanNode*> treeStack;


for (std::string::const_iterator iter = s.begin(); iter != s.end(); iter++) {
if (*iter == 'L') {
iter++;
HuffmanNode *nodeToInsert = new HuffmanNode(*iter, 0);
treeStack.push(nodeToInsert);
}
else {
HuffmanNode *rightNode = treeStack.top();
treeStack.pop();
HuffmanNode *leftNode = treeStack.top();
treeStack.pop();
parentFreq = leftNode->getFrequency() + rightNode->getFrequency();
HuffmanNode *parentNode = new HuffmanNode('\0', parentFreq, nullptr, leftNode, rightNode);

treeStack.push(parentNode);
}
}
return treeStack.top();
}



std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {

std::string decodedStr = "";
HuffmanNode *rootTree = makeTree(serializedTree);

//stl iterators used to ensure accuracy
HuffmanNode *it = rootNode;
//if 0 is met in the binary code, the iterator goes down to the left child
//if 1 is met, the iterator goes down to the right child
for (std::string::const_iterator iter = inputCode.begin(); iter != inputCode.end(); iter++) {

if (*iter == '0') {
it = it->left;
if (it->isLeaf()) {
decodedStr += it->getCharacter();
it = rootTree;
}
} else {
it = it->right;
if (it->isLeaf()) {
decodedStr += it->getCharacter();
it = rootTree;
}
}
}
return decodedStr;
}
