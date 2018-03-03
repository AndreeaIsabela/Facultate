#pragma once
#include"stdafx.h"
class ProducerConsumer
{
public:


  void Produce(int i);
  
  int Consume();
  

  queue<int> pcQueue;
  bool ableToConsume = false;
  mutex mtx1,mtx2;
};

