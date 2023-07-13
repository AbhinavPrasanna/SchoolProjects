#include <atomic>

class IOQueue {
 public:
  IOQueue() {
    front = end = 0;
    list = nullptr;
  }


  // Use this function to initialize the queue to
  // the size that you need.
  void init(int size) {
    list = new int[size];
  }

  // enqueue the element e into the queue
  void enq(int e) {
      int reserved_index = atomic_fetch_add(&end, 1);
      list[reserved_index] = e;
  }

  // return a value from the queue.
  // return -1 if there is no more values
  // from the queue.
  int deq() {
    if((end.load()-front.load())>0){
      int reserved_index = atomic_fetch_add(&front, 1);
      return list[reserved_index];
    }
    else{
      return -1;
    }
  }

  // return 32 values from the queue. The
  // values should be returned through
  // the array passed in.
  // return 0 if successful. return 1 if not
  // i.e. if the queue does not have 32 elements
  int deq_32(int ret[32]) {
    if (end.load() == front.load()){
      return 1;
    }
    for (int i = 0; i < 32; i++) {
       int idx = std::atomic_fetch_add(&front, 1);
			 return list[idx];
    }
    return 0;
  }

 private:
  std::atomic_int front;
  std::atomic_int end;
  int* list;
  // Give me some private variables
};
/*class InputOutputQueue { private:
atomic_int front; atomic_int end; int list[SIZE];
public: InputOutputQueue() {
        front = end = 0;
     }
void enq(int x) {
int reserved_index = atomic_fetch_add(&end, 1); list[reserved_index] = x;
}
void deq() {
int reserved_index = atomic_fetch_add(&front, 1); return list[reserved_index];
}
int size() {
return end.load() - front.load();
} }*/
