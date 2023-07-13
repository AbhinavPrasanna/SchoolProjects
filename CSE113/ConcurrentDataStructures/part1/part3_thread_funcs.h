
void memory_load_thread_func(float *a, int size) {
  for (int i = 0; i < size; i+=8) {
    // Implement me!
      float load[8];
      for(int j=0;j<8;j++){
          load[j] = a[i+j];
      }
      memory_to_trig.enq_8(load);
  }
}

void trig_thread_func(int size) {

  for (int i = 0; i < size; i+=8) {
    //Implement me!
      float consume[8];
      memory_to_trig.deq_8(consume); // Memory_To_Trig deq queue 1 2 3 4 5 6 7 8 
      float to_store[8];

      // DOALL loop
      for (int j = 0; j < 8; j++){
          to_store[j] = cos(consume[j]);
      }
      trig_to_memory.enq_8(to_store);

  }
}

void memory_store_thread_func(float *a, int size) {

  for (int i = 0; i < size; i+=8) {
    // Implement me!
      float to_store[8];
      trig_to_memory.deq_8(a);

      // DOALL loop
      for (int j = 0; j < 8; j++){
          a[i+j] = to_store[j];
      }
  }
}