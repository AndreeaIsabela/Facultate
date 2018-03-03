#include "ProducerConsumer.h"

void ProducerConsumer::Produce(int i)
{
  std::lock_guard<std::mutex> lock(mtx1);
  pcQueue.push(i);
  ableToConsume = true;
}

int  ProducerConsumer::Consume()
{
  std::lock_guard<std::mutex> lock(mtx2);
  while (ableToConsume == false)
  {
    return -1;
  }
  while (!pcQueue.size())
  {
    ableToConsume = false;
    return -1;
  }
  auto temp = pcQueue.front();
  pcQueue.pop();
  return temp;
}

