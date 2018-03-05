#include "ProducerConsumer.h"

bool ProducerConsumer::ableToConsume = false;
queue<int> ProducerConsumer::pcQueue =  queue<int>();

void ProducerConsumer::Produce(int i)
{
  
  std::lock_guard<std::mutex> lock(mtx1);
  pcQueue.push(i);
  ableToConsume = true;

}

int  ProducerConsumer::Consume()
{
  
  while (!pcQueue.size())
  {
    ableToConsume = false;
    return -1;
  }
  std::lock_guard<std::mutex> lock(mtx2);
  auto temp = pcQueue.front();

  pcQueue.pop();
  return temp;
}

