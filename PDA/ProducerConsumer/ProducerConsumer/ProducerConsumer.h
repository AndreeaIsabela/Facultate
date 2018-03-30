#pragma once
#include"stdafx.h"
#include"Semaphore.h"
class ProducerConsumer
{
public:

  void Produce(int i);
  
  int Consume();
  

  static queue<int> pcQueue;
  static bool ableToConsume;
  static mutex mtx1,mtx2;
  static std::condition_variable producer;
  static std::condition_variable consumer;
  static int  max ;
};

