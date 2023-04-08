#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"

class DllNode {
public:
    int value;
    DllNode *prev;
    DllNode *next;
};

class Dll {
private:
    DllNode *head;
    DllNode *tail;
    int len;
public:
    Dll(){
        head = new DllNode();
        tail = new DllNode();
        len = 0;
    }; // create an empty list
    Dll(const Dll &src) {
       head = new DllNode();
       DllNode *newNode = head;
       DllNode *srcNode = src.head;
       len = src.len;
       for(int i = 0; i < len; i++) {
          newNode->next = new DllNode();
          newNode->next->prev = newNode;
          newNode->value = srcNode->value;
          newNode = newNode->next;
          srcNode = srcNode->next;
       }
       tail = newNode;
    }
    Dll(const int arr[], int size) { // create a linked list containing the elements of the array
      len = size;
      DllNode *currNode;
      DllNode *prevNode;
      head->value = arr[0];
      prevNode = head;
      for(int i = 1; i < size; i ++) {
         currNode->value = arr[i];
         currNode->prev = prevNode;
         prevNode->next = currNode;
         currNode = currNode->next;
         prevNode = prevNode->next;
      }
    }
    Dll &operator=(const Dll &src) { // create a deep copy of the src list
      head = new DllNode();
      DllNode *newNode = head;
      DllNode *srcNode = src.head;
      len = src.len;
      for(int i = 0; i < len; i++) {
         newNode->next = new DllNode();
         newNode->next->prev = newNode;
         newNode->value = srcNode->value;
         newNode = newNode->next;
         srcNode = srcNode->next;
      }
      tail = newNode;
      return *this;
    }
    
    ~Dll() { // free all memory
      DllNode *currNode;
      DllNode *succNode;
      currNode = tail;
      for(int i = 0; i < len; i++) {
         succNode = currNode;
         currNode = currNode->prev;
         free(succNode);
      }
      free(currNode);
    }

    bool empty() const { // return if the list is empty in O(1)
      if(head == NULL || len == 0) {
         return true;
      } else {
         return false;
      }
    }
    int size() const { return len; } // return how many items are in the list in O(1)

    int &at(int rank) { // return a reference to the value of the list at a rank/index
      if(rank < 0 || rank > (len - 1)) {
         throw IndexOutOfRangeException("at(): Index was outside the bounds of the linked list.", rank);
      }
      DllNode *currNode;
      currNode = head;
      for(int i = 0; i < len; i++) {
         if(i == rank) {
            return currNode->value;
         }
         currNode = currNode->next;
      }
      int *temp = 0;
      return *temp;
    }
    void insert(int rank, int value) { // insert a value at the rank/index
      if(rank < 0 || rank > len) {
         throw IndexOutOfRangeException("insert(): Index was outside the bounds of the linked list.", rank);
      }
      
      if(len == 0) {
        DllNode *newNode = new DllNode();
        newNode->value = value;
        head = newNode;
        tail = newNode;
      } else if(rank == len){
        DllNode *newNode = new DllNode();
        newNode->value = value;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
      } else if(len == 2 && rank == 1) {
         DllNode *newNode = new DllNode();
         newNode->value = value;
         newNode->next = tail;
         newNode->prev = head;
         tail->prev = newNode;
         head->next = newNode;
      } else {
         int i;
         DllNode *currNode;
         currNode = head->next;
         DllNode *prevNode;
         for(i = 1; i < len; i++) {
            if(i == rank) {
               prevNode = currNode->prev;
               break;
            } else {
               currNode = currNode->next;
            }
         }
         DllNode *newNode = new DllNode();
         newNode->value = value;
         newNode->next = currNode;
         newNode->prev = prevNode;
         currNode->prev = newNode;
         prevNode->next = newNode;
      }
      len++;
    }
    int remove(int rank) { // remove the node at the rank/index and return its value
      if(rank < 0 || rank >= len) {
         throw IndexOutOfRangeException("remove(): Index was outside the bounds of the linked list.", rank);
      }
      int temp;
      DllNode *currNode;
      currNode = head;
      DllNode *prevNode;
      DllNode *succNode;
      if(rank == 0) {
         currNode = head;
         succNode = head->next;
         succNode->prev = NULL;
         head = succNode;
         len--;
         temp = currNode->value;
         free(currNode);
         return temp;
      } else if(rank == len - 1) {
         currNode = tail;
         prevNode = tail->prev;
         prevNode->next = NULL;
         tail = prevNode;
         len--;
         temp = currNode->value;
         free(currNode);
         return temp;
      } else {
         currNode = currNode->next;
         for(int i = 1; i < (len - 1); i++) {
            if(i == rank) {
               prevNode = currNode->prev;
               succNode = currNode->next;
               prevNode->next = succNode;
               succNode->prev = prevNode;
               temp = currNode->value;
               free(currNode);
               len--;
               return temp;
            }
         }
      }
      return 0;
    }

    void clear() {   // reset the list to an empty list
      DllNode *currNode = new DllNode();
      DllNode *succNode = new DllNode();
      currNode = tail;
      for(int i = 0; i < len; i++) {
         succNode = currNode;
         currNode = currNode->prev;
         free(succNode);
         succNode = new DllNode();
      }
      head = new DllNode();
      tail = new DllNode();
      len = 0;
    }
    void display(ostream &os) const { // write the contents of the list to the ostream
      if(len == 2) {
         os << "[ " << head->value << " " << tail->value << " ]";
      } else if(len == 0) {
         os << "[ ]";
      } else {
         DllNode *currNode = new DllNode();
         currNode = head;
         int arr[len];
         os << "[ ";
         for(int i = 0; i < len; i++) {
            arr[i] = currNode->value;
            currNode = currNode->next;
         }
         for(int i = 0; i < len; i++) {
            os << arr[i] << " ";
         }
         os << "]";
      }
    }
};

ostream &operator<<(ostream &os, const Dll &list) { // write the contents of the list to the ostream
   list.display(os);
   return os;
}

#endif