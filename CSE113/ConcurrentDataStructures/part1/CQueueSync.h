#include <atomic>

class CQueue {
 public:

  CQueue() {

  }

  void enq(float e) {
    box.store(e);
    flag.store(true);
    while(flag){
      // spin
    }
  }

  float deq() {
    float temp;
    while(!flag){
      // spin
    }
    temp = box.load();
    flag.store(false);
    return temp;
  }
  
 private:
  std::atomic<float> box;
  std::atomic<bool> flag;
};
