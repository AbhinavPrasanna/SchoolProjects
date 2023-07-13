#include <atomic>

#define CQUEUE_SIZE 2048

class CQueue {
 public:

    CQueue() {
      h.store(0);
      t.store(0);

  }

  void enq(float e) {
    while (true){
      if(((h + 1) % CQUEUE_SIZE) != (t % CQUEUE_SIZE)){
        break;
      }
    }

    buffer[h % CQUEUE_SIZE] = e;
    h.store((h+1) % CQUEUE_SIZE);
  }

  float deq() {
    while(true){
      if(h != t){
        break;
      }
    }

    float temp = buffer[t % CQUEUE_SIZE];
    t.store((t+1) % CQUEUE_SIZE);
    return temp;
  }

  int size() {
    return (CQUEUE_SIZE - (t - h)) % CQUEUE_SIZE;
  }

   void deq_8(float e[8]) {
      while(this->size()<9){}
      for (int i = 0; i < 8; i++) {
           e[i] = deq();
      }
  }

  void enq_8(float e[8]) {
      while (CQUEUE_SIZE - this->size() < 9){}
      for (int i = 0; i < 8; i++){
          enq(e[i]);
         
      }
  }
  
 private:
  std::atomic_int h;
  std::atomic_int t;
  std::atomic<float> buffer[CQUEUE_SIZE];
};
