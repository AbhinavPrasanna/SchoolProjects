#include <shared_mutex>
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
    mutx.lock();
    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      mutx.unlock();
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
    mutx.unlock();
    return ret;
  }

  
  int peek() {
    if (start == NULL) {
      return -1;
    }
    mutx.lock();
    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }
    return current->data;    
  }
  
  void push(int p) {
    mutx.lock();
    if (start == NULL) {
      start = new Llist_node(p);
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new Llist_node(p);
  }

  void swaptop(int to_swap) {
    mutx.lock();
    if (start == NULL) {
      mutx.unlock();
      return;
    }
    start->data = to_swap;
  }

 private:
  Llist_node *start;  
  shared_mutex mutx;
};
