#include "ProducerConsumer.h"
#include"stdafx.h"

mutex ProducerConsumer::mtx1;
mutex ProducerConsumer::mtx2;
queue<int> ProducerConsumer::pcQueue =  queue<int>();
//Semaphore ProducerConsumer::producer(3);
//Semaphore ProducerConsumer::consumer(0);
std::condition_variable ProducerConsumer::producer;
std::condition_variable ProducerConsumer::consumer;
int ProducerConsumer::max = 5;
mutex mtxP, mtxC;

void ProducerConsumer::Produce(int i)
{
  { 
  std::unique_lock<std::mutex> lock1(mtxP);
    if (pcQueue.size() == max) {
      producer.wait(lock1);
    }
  }
  {
    std::lock_guard<std::mutex> lock(mtx1);
    pcQueue.push(i);
  }
  consumer.notify_one();
 
}

int  ProducerConsumer::Consume()
{
  int temp;
  {
    std::unique_lock<std::mutex> lock2(mtxC);
    if (pcQueue.size() == 0) {
      consumer.wait(lock2);
    }
  }

  {
    std::lock_guard<std::mutex> lock(mtx2);
    temp = pcQueue.front();
    pcQueue.pop();
  }
    producer.notify_one();
  return temp;
}

