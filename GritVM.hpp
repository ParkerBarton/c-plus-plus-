//
//  GritVM.hpp
//  DS4
//
//  Created by Parker Barton on 10/9/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#ifndef GritVM_hpp
#define GritVM_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GritVMBase.hpp"
#include <list>
#include <vector>
#include <string>


class GritVM : GritVMInterface{
private:
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator
    currentInstruct; STATUS machineStatus;
    long accumulator;
    long evaluate(Instruction s);
    void advance(long jumpDistance);
public:
    STATUS              load(const std::string filename, const std::vector<long> &initialMemory);
    STATUS              run();
    std::vector<long>   getDataMem();
    STATUS              reset();
//STATUS reset();
//void printVM(bool printData, bool printInstruction);
    
};


#endif /* GritVM_hpp */
