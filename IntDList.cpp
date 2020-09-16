//
//  IntDList2.cpp
//  DS1
//
//  Created by Parker Barton on 9/10/19.
//  Copyright © 2019 Parker Barton. All rights reserved.
//

#include "IntDList.hpp"
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

IntDLList::IntDLList(){  //constructor
    ListHead = new IntDLLNode;
    ListTail = new IntDLLNode;
    ListHead->next = ListTail;
    ListTail->prev = ListHead;
}
IntDLList::~IntDLList(){  //destructor
    while (!isEmpty()) deleteFromHead();
    delete ListHead;
    delete ListTail;
}
void IntDLList::add(IntDLLNode* v, int i){  //function to add a node infront of another
    IntDLLNode* u = new IntDLLNode;
    u->info = i;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}
void IntDLList::addToHead(int i){  //function to add a node at the head
    if (!(isEmpty()) && (i > ListHead->next->info))
        throw invalid_argument("That number is larger than the head value!");
    add(ListHead->next, i);
}
void IntDLList::insertInOrder (int i){  //functionn to add a node in order
    if(isEmpty()){
        addToHead(i);  //checks if head node
        return;
    }
    IntDLLNode* s = ListHead->next;
    while(s != ListTail){
        if(i <= (s->info)){ //finds correct position
            add(s, i);
            break;
        }
        s = s->next;
    }
    if (s==ListTail){
        addToTail(i); //checks if tail node
        return;
    }
    
}
void IntDLList::addToTail(int i){  //function to add a node at the tail
    if (!(isEmpty()) && (i < ListTail->prev->info))
        throw invalid_argument("That number is smaller than the tail value!");
    add(ListTail, i);
}
void IntDLList::remove(IntDLLNode* v){ //function to delete a node
    IntDLLNode* u = v->prev;
    IntDLLNode* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}
int  IntDLList::deleteFromHead(){ //function to delete the head node
    if (isEmpty())
        throw invalid_argument("The list is empty!");
    int i = ListHead->next->info;
    remove(ListHead->next);
    return i;
} // delete the head and return its info;
int  IntDLList::deleteFromTail(){ ////function to delete the tail node
    if (isEmpty())
        throw invalid_argument("The list is empty!");
    int i = ListTail->prev->info;
    remove(ListTail->prev);
    return i;
} // delete the tail and return its info;
void IntDLList::deleteNode(int n){  //function to find a desired node and delete it
    if (isEmpty())
        throw invalid_argument("The list is empty!");
    IntDLLNode* temp = ListHead->next;
    while (temp != ListTail){
        if (temp->info == n) //finds node
            break;
        temp = temp->next;
    }
    if ((temp->next == ListTail) &&  (temp->info != n))
        throw invalid_argument("That element is not in the list!");
    else
        remove(temp);
}
bool IntDLList::isInList(int n) const{
    IntDLLNode* i;
    for(i = ListHead;i->info == n;i=i->next){  //finds if node is in list
    }
    if (i == ListTail)
        return false;
    else
        return true;
}
string IntDLList::addToString() const{
    IntDLLNode* i;
    cout << endl;
    string  p;
    stringstream temp;
    //IntDLLNode* i;
    i = ListHead->next;
    while (i != ListTail){
        temp << i->info;
        i = i->next;
    }
    p = temp.str();
    return p;
}
