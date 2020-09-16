//
//  NotationConverter.hpp
//  PP2
//
//  Created by Brandon Bart on 6/6/19.
//  Copyright © 2019 Bart. All rights reserved.
//

#ifndef NotationConverter_hpp
#define NotationConverter_hpp

#include "NotationConverterInterface.hpp"

class NotationConverter : public NotationConverterInterface {
public:
    NotationConverter();
    int prec(std::string o);
    bool isOperator(char c);
    std::string spaced(std::string s);
    
    std::string postfixToInfix(std::string inStr);
    std::string postfixToPrefix(std::string inStr);
    
    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);
    
    std::string prefixToInfix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);
};

typedef std::string Elem;

class DNode {
private:
    Elem elem;
    DNode* prev;
    DNode* next;
    friend class DLinkedList;
};

class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    void addFront(const Elem& e);
    void addBack(const Elem& e);
    void removeFront();
    void removeBack();
    
private:
    DNode* header;
    DNode* trailer;
    
protected:
    void add(DNode* v, const Elem& e);
    void remove(DNode* v);
};

class LinkedDeque {
public:
    LinkedDeque();
    int size() const;
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    
    void insertFront(const Elem& e);
    void insertBack(const Elem& e);
    void removeFront();
    void removeBack();
    
private:
    DLinkedList D;
    int n;
};

#endif /* NotationConverter_hpp */
