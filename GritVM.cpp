//
//  GritVM.cpp
//  DS4
//
//  Created by Parker Barton on 10/9/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#include "GritVM.hpp"
using namespace GVMHelper;

//the base constructor
GritVM::GritVM() {
    machineStatus = WAITING;
    accumulator = 0;
}

STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory){
    std::ifstream GVMInput(filename);
    std::string fileIn;
    
    if(GVMInput.is_open()){
        dataMem = initialMemory;
        while(std::getline(GVMInput, fileIn)){
            if(!isalpha(fileIn[0])){
                continue;
            }
            else{
                instructMem.push_back(GVMHelper::parseInstruction(fileIn));
            }
        }
    }
    else{
        throw 1;
    }
    machineStatus = READY;
    return READY;
}

STATUS GritVM::run(){
    if(machineStatus == READY){
        while (machineStatus == RUNNING) {
            //evaluate current instruction and stores jump distance
            long jumpDistance = evaluate(*currentInstruct);
            //advances pointer by the jump distance
            advance(jumpDistance);
        }
    }
    else
        return machineStatus;
    machineStatus = HALTED;
    return machineStatus;
}

std::vector<long> GritVM::getDataMem(){
    return dataMem;
}
STATUS GritVM::reset(){
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    machineStatus = WAITING;
    
    return machineStatus;
}

long GritVM::evaluate(Instruction s) {
    //seperate operation and argument
    INSTRUCTION_SET op = s.operation;
    long arg = s.argument;
    
    //switch-statement to deal with operations
    switch (op) {
        case CLEAR:
            accumulator = 0;
            break;
        case AT:
            accumulator = dataMem[arg];
            break;
        case SET:
            dataMem[arg] = accumulator;
            break;
        case INSERT:
            dataMem.insert(dataMem.begin()+arg, accumulator);
            break;
        case ERASE:
            dataMem.erase(dataMem.begin()+arg);
            break;
        case ADDCONST:
            accumulator += arg;
            break;
        case SUBCONST:
            accumulator -= arg;
            break;
        case MULCONST:
            accumulator *= arg;
            break;
        case DIVCONST:
            accumulator /= arg;
            break;
        case ADDMEM:
            accumulator += dataMem[arg];
            break;
        case SUBMEM:
            accumulator -= dataMem[arg];
            break;
        case MULMEM:
            accumulator *= dataMem[arg];
            break;
        case DIVMEM:
            accumulator /= dataMem[arg];
            break;
        case JUMPREL:
            return arg;
        case JUMPZERO:
            if (accumulator == 0) {return arg;}
            break;
        case JUMPNZERO:
            if (accumulator != 0) {return arg;}
            break;
        case NOOP:
            break;
        case HALT:
            machineStatus = HALTED;
            break;
        case OUTPUT:
            std::cout << accumulator << std::endl;
            break;
        case CHECKMEM:
            if (dataMem.size() < arg) {machineStatus = ERRORED;}
            break;
        default:
            break;
    }
    //returns a default of 1 to jump forward one step
    return 1;
}

void GritVM::advance(long jumpDistance) {
    //if jumpDistance is negative, decrement pointer until jD is 0
    if (jumpDistance < 0) {
        while (jumpDistance != 0) {
            currentInstruct--;
            jumpDistance++;
        }
    }
    
    //jumpDistance is positive or 0, increment pointer until jD is 0
    else {
        while (jumpDistance != 0) {
            currentInstruct++;
            jumpDistance--;
        }
    }
}
