#include <iostream>
#include <queue>
#include <unordered_map>

class HuffmanTreeNode {
public:
    char id;
    unsigned freq;
    HuffmanTreeNode *left, *right;

    HuffmanTreeNode(char id, unsigned freq) {
        this->id = id;
        this->freq = freq;
        left = right = nullptr;
    }
};

class Compare {
public:
    bool operator()(HuffmanTreeNode* l, HuffmanTreeNode* r) {
        return l->freq > r->freq;
    }
};

void encode(HuffmanTreeNode* root, std::string str, std::unordered_map<char, std::string> &huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->id] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanTreeNode *left, *right, *top;
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, Compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new HuffmanTreeNode(data[i], freq[i]));
    }

    while (minHeap.size() != 1) {
        left = minHeap.top(); minHeap.pop();
        right = minHeap.top(); minHeap.pop();

        top = new HuffmanTreeNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    std::unordered_map<char, std::string> huffmanCode;
    encode(minHeap.top(), "", huffmanCode);

    std::cout << "Huffman Codes are :\n";
    for (auto pair : huffmanCode) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);
    buildHuffmanTree(arr, freq, size);

    return 0;
}
