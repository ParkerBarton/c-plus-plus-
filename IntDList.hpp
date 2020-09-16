#ifndef INTDLIST_H
#define INTDLIST_H
#include "IntDList_node.hpp"
#include <string>
using namespace std;
class IntDLList 
{
public:
    IntDLList(); 
    ~IntDLList();
    int isEmpty() const 
    {
        return ListHead->next == ListTail;
    }
    void add(IntDLLNode*, int);
    void addToHead(int);
    void insertInOrder (int);
    void addToTail(int);
    void remove(IntDLLNode*);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    string addToString() const;

private:
    IntDLLNode* ListHead;
    IntDLLNode* ListTail;
};

#endif /* INTDLIST_H */
