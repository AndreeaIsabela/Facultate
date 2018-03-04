#pragma once
#include"stdafx.h"
class ProducerConsumer
{
public:

  void Produce(int i);
  
  int Consume();
  

  static queue<int> pcQueue;
  static bool ableToConsume;
  mutex mtx1,mtx2;
};

