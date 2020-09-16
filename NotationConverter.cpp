//
//  NotationConverter.cpp
//  PP2
//
//  Created by Brandon Bart on 6/6/19.
//  Copyright © 2019 Bart. All rights reserved.
//

#include "NotationConverter.hpp"
#include <cctype>
#include <iostream>
#include <algorithm>

NotationConverter::NotationConverter(){}

//determines and returns precedence of operator
int NotationConverter::prec(std::string o) {
    if (o == "*" || o == "/")
        return 2;
    else if (o == "+" || o == "-")
        return 1;
    else
        return -1;
}

//determines if char is operator
bool NotationConverter::isOperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

//places spaces between each char in string
std::string NotationConverter::spaced(std::string s) {
    std::string spacedString;
    for (auto iter : s)
    {
        spacedString += iter;
        spacedString += ' ';
    }
    
    //return new string without last space;
    return spacedString.substr(0,spacedString.length()-1);
}

std::string NotationConverter::postfixToInfix(std::string inStr) {
    LinkedDeque ld;
    std::string outStr;

    for (char c : inStr) {
        //convert char into a new string for use later
        std::string s(1,c);
        
        //if char is operand, push to queue
        if (isalpha(c)) {
            ld.insertBack(s);
        }
        
        //ignore whitespace
        else if (c == ' '){}
        
        //checks if char is operator
        else if (isOperator(c)) {
            std::string op2 = ld.back(); //get second operand
            ld.removeBack();
            
            std::string op1 = ld.back(); //get first operand
            ld.removeBack();
            
            //add both operands combined with operator as a string to queue
            ld.insertBack("(" + op1 + " " + c + " " + op2 + ")");
        }
        
        //invalid character
        else
            throw(0);
    }
    return ld.back();
}

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    //convert postfix to infix
    inStr = postfixToInfix(inStr);
    //convert infix to prefix
    inStr = infixToPrefix(inStr);
    
    return inStr;
}

std::string NotationConverter::infixToPostfix(std::string inStr) {
    LinkedDeque ld;
    std::string outStr;

    for (char c : inStr) {
        //convert char into a new string for use later
        std::string s(1,c);
        
        //if char is operand, push to output
        if (isalpha(c))
            outStr += c;
    
        //ignores each whitespace
        else if (c == ' '){}
        
        else if (c == '(')
            ld.insertBack(s);
        
        //pushes everything between pair of parentheses in queue to output
        else if (c == ')') {
            while (!ld.empty() && ld.back() != "(") {
                outStr += ld.back();
                ld.removeBack();
            }
            if (ld.back() == "(")
                ld.removeBack();
        }
        
        //check if operator
        else if (isOperator(c)){
            //if precedence of operator is less than that of the back of queue, push
            while (!ld.empty() && prec(s) <= prec(ld.back())) {
                outStr += ld.back();
                ld.removeBack();
            }
            ld.insertBack(s);
        }
        //invalid character
        else
            throw(0);
    }
    
    //push the rest of queue to output
    while (!ld.empty()) {
        if(ld.back() != "(" && ld.back() != ")")
            outStr += ld.back();
        ld.removeBack();
    }
    return spaced(outStr);
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    //reverse infix string
    std::reverse(inStr.begin(), inStr.end());
    
    //turn each parentheses
    for (int i = 0; i < inStr.length(); i++) {
        if (inStr[i] == '(') {
            inStr[i] = ')';
        }
        else if (inStr[i] == ')') {
            inStr[i] = '(';
        }
    }
    
    //convert reversed infix to postfix
    std::string s = infixToPostfix(inStr);
    
    //reverse postfix to get prefix
    std::reverse(s.begin(), s.end());
    
    return s;
}

std::string NotationConverter::prefixToInfix(std::string inStr) {
    LinkedDeque ld;
    std::reverse(inStr.begin(), inStr.end());
    
    for (char c : inStr) {
        std::string s(1, c);
        
        //checks if operand, pushes it onto queue
        if (isalpha(c)) {
            ld.insertBack(s);
        }
        
        //ignore whitespace
        else if (c == ' ') {}
        
        //check if operator
        else if (isOperator(c)) {
            std::string op1 = ld.back(); //get first operand
            ld.removeBack();
            std::string op2 = ld.back(); //get second operand
            ld.removeBack();
            
            //combine both operands with operator as a string to queue
            ld.insertBack("(" + op1 + " " + c + " " + op2 + ")");
        }
        
        //invalid character
        else
            throw(0);
    }
    return ld.back();
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    //convert prefix to infix
    inStr = prefixToInfix(inStr);
    //convert infix to postfix
    inStr = infixToPostfix(inStr);
    
    return inStr;
}

//constructor for doubly linked list
DLinkedList::DLinkedList() {
    //sentinel node creation
    header = new DNode;
    trailer = new DNode;
    //linking sentinels
    header->next = trailer;
    trailer->prev = header;
}

//deconstructor
DLinkedList::~DLinkedList() {
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

bool DLinkedList::empty() const {
    return (header->next == trailer);
}

const Elem& DLinkedList::front() const {
    return header->next->elem;
}

const Elem& DLinkedList::back() const {
    return trailer->prev->elem;
}

//insert new node before v
void DLinkedList::add(DNode* v, const Elem& e) {
    DNode* u = new DNode; u->elem = e; //new node creation
    //node linking
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}

void DLinkedList::addFront(const Elem& e) {
    add(header->next, e);
}

void DLinkedList::addBack(const Elem& e) {
    add(trailer, e);
}

//remove node v
void DLinkedList::remove(DNode* v) {
    DNode* u = v->prev;
    DNode* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

void DLinkedList::removeFront() {
    remove(header->next);
}

void DLinkedList::removeBack() {
    remove(trailer->prev);
}

//constructor for Linked Deque
LinkedDeque::LinkedDeque() {
    n = 0;
}

int LinkedDeque::size() const {
    return n;
}

bool LinkedDeque::empty() const {
    return D.empty();
}

const Elem& LinkedDeque::front() const {
    return D.front();
}

const Elem& LinkedDeque::back() const {
    return D.back();
}

void LinkedDeque::insertFront(const Elem& e) {
    D.addFront(e); n++;
}

void LinkedDeque::insertBack(const Elem& e) {
    D.addBack(e); n++;
}

void LinkedDeque::removeFront() {
    if (empty()) { throw(0); }
    D.removeFront(); n--;
}

void LinkedDeque::removeBack() {
    if (empty()) { throw(0); }
    D.removeBack(); n--;
}
