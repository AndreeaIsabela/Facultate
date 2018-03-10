#include "ProducerConsumer.h"
#include"Semaphore.h"

mutex ProducerConsumer::mtx1;
mutex ProducerConsumer::mtx2;
queue<int> ProducerConsumer::pcQueue =  queue<int>();
Semaphore producer(3);
Semaphore consumer(0);

void ProducerConsumer::Produce(int i)
{
  producer.wait();
  {
    std::lock_guard<std::mutex> lock(mtx1);
    pcQueue.push(i);
  }
  consumer.notify();
 
}

int  ProducerConsumer::Consume()
{
  int temp;
  consumer.wait();
  {
    std::lock_guard<std::mutex> lock(mtx2);
    temp = pcQueue.front();
    pcQueue.pop();
  }
    producer.notify();
  return temp;
}

