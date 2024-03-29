#include <shared_mutex>
#include <mutex>
using namespace std;

class Llist_node {
 public:  
  Llist_node(int d) {   
    data = d;
    next = NULL;
  }
  
  int data;
  Llist_node *next;
  
};

class CSE113_Stack {
 public:
  
  CSE113_Stack() {
    start = NULL;
  }
  
  int pop() {
    if (start == NULL) {
      return -1;
    }
    mtx.lock();
    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      mtx.unlock();
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL) {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;
    mtx.unlock();
    return ret;
  }

  
  int peek() {
    if (start == NULL) {
      return -1;
    }
    mtx.lock();
    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }
    mtx.unlock_shared();
    return current->data;    
  }
  
  void push(int p) {
    mtx.lock();
    if (start == NULL) {

      start = new Llist_node(p);
      mtx.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new Llist_node(p);
    mtx.unlock();
  }

 private:
  Llist_node *start;
  shared_mutex mtx;

};