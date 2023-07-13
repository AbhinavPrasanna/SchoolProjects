#include <atomic>

class dekkers_mutex {
public:
  dekkers_mutex() {
    wantstoenter[0].store(false);
    wantstoenter[1].store(false);
    turn.store(0);
  }

  void lock(int tid) {
    wantstoenter[tid].store(true);
    while (wantstoenter[1-tid].load() == true) {
      if (turn.load() != tid) {
        wantstoenter[tid].store(false);
        while (turn.load() != tid) {
        }
        wantstoenter[tid].store(true);
      }
    }
  }

  void unlock(int tid) {
    turn.store(1-tid);
    wantstoenter[tid].store(false);
  }

private:
  std::atomic<bool> wantstoenter[2];
  std::atomic<int> turn;
};
