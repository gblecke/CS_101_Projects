#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "exceptions.h"
#include "dll.h"

class Queue {
private:
    Dll store;
public:
    Queue() { store.clear(); } // create an empty queue
    void enqueue(int value) { // add an item to the back of the queue
      store.insert(store.size(), value);
    }
    int dequeue() { 
       if(store.size() == 0) {
          throw InvalidOperationException("Queue empty.");
       }
       return store.remove(0); 
    } // remove the value at the front of the queue and return its value 
    int peek() { 
       if(store.size() == 0) {
          throw InvalidOperationException("Queue empty.");
       }
       return store.at(0); 
    } // return the value at the front of the queue, keeping it in the queue
    int size() const { return store.size(); } // return how many items are in the queue
    bool empty() const { return store.empty(); } // return if the queue is empty
    void display(ostream &os) const { store.display(os); } // write the contents of the queue to the ostream
};

ostream &operator<<(ostream &os, const Queue &queue) { // write the contents of the queue to the ostream
   queue.display(os);
   return os;
}

#endif