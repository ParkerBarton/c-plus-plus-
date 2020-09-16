//
//  main.cpp
//  DS5
//
//  Created by Parker Barton on 11/3/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#include <iostream>
#include "Huffman.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    HuffmanTree t;
    string test = "It is time to unmask the computing community as a Secret Society for the Creation and Preservation of Artificial Complexity";
    string code = t.compress(test);
    cout << code;
    return 0;
}
