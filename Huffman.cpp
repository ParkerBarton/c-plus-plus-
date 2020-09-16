//
//  Huffman.cpp
//  DS5
//
//  Created by Parker Barton on 11/3/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#include "Huffman.hpp"
#include <map>


std::string HuffmanTree::compress(const std::string str){
    // size of the string 'str'
    int n = str.size();
    HeapQueue<HuffmanNode*, std::vector<HuffmanNode*>> hq;
    std::map<int, char> m;
    // 'freq[]' implemented as hash table
    int freq[26];
    
    // initialize all elements of freq[] to 0
    memset(freq, 0, sizeof(freq));
    
    // accumulate freqeuncy of each character in 'str'
    for (int i = 0; i < n; i++)
        freq[str[i] - 'a']++;
    
    // traverse 'str' from left to right
    for (int i = 0; i < n; i++) {
        
        // if frequency of character str[i] is not
        // equal to 0
        if (freq[str[i] - 'a'] != 0) {
            
            
            m.insert(std::pair<int,char>(freq[str[i] - 'a'], str[i]));
            hq.insert(new HuffmanNode(freq[str[i] - 'a'], str[i]));
            // update frequency of str[i] to 0 so
            freq[str[i] - 'a'] = 0;
        }
    }
    HuffmanNode *top, *left, *right;
    while (hq.size() != 1) {
        
        // Extract the two minimum
        // freq items from min heap
        left = hq.min();
        hq.removeMin();
        
        right = hq.min();
        hq.removeMin();
        
        top = new HuffmanNode('$', left->getFrequency() + right->getFrequency());
        
        top->left = left;
        top->right = right;
        
        hq.insert(top);

    }
    std::string code = getcode(hq.min(), "");
    return code;
}
std::string HuffmanTree::serializeTree() const{
    std::string str;
    return str;
}
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    return inputCode;
}

std::string HuffmanTree::getcode(HuffmanNode *root, std::string str){
    if (!root)
        return str;
    
    if (root->getCharacter() != '$')
        str = ' ';
    
    getcode(root->left, str + "0");
    getcode(root->right, str + "1");
    return  str;
}
