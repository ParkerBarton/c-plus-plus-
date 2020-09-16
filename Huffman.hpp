//
//  Huffman.hpp
//  DS5
//
//  Created by Parker Barton on 11/3/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#ifndef Huffman_hpp
#define Huffman_hpp

#include <stdio.h>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

class HuffmanTree {
public:
    virtual std::string compress(const std::string inputStr);
    virtual std::string serializeTree() const;
    virtual std::string decompress(const std::string inputCode, const std::string serializedTree);
    std::string getcode(HuffmanNode *root, std::string str);
};
#endif /* Huffman_hpp */
