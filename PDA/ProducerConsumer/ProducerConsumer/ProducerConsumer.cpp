#include "ProducerConsumer.h"
#include"Semaphore.h"

mutex ProducerConsumer::mtx1;
mutex ProducerConsumer::mtx2;
queue<int> ProducerConsumer::pcQueue =  queue<int>();
Semaphore producer(3);
Semaphore consumer(0);

void ProducerConsumer::Produce(int i)
{
  producer.Down();
  {
    std::lock_guard<std::mutex> lock(mtx1);
    pcQueue.push(i);
  }
  consumer.Up();
 
}

int  ProducerConsumer::Consume()
{
  int temp;
  consumer.Down();
  {
    std::lock_guard<std::mutex> lock(mtx2);
    temp = pcQueue.front();
    pcQueue.pop();
  }
    producer.Up();
  return temp;
}

