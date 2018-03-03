#include"stdafx.h"
#include"ProducerConsumer.h"


int nrOfThreads = 6;
int producerIndex = 0;
int consumerIndex = 0;
mutex prodMtx;
mutex consMtx;
ProducerConsumer ProdCons;


void ProducerJob()
{
  while (producerIndex <= 20)
  {
    std::lock_guard<std::mutex> lock(prodMtx);
    if (producerIndex <= 20)
    {
      cout << "Producing " << producerIndex << endl;
      ProdCons.Produce(producerIndex);
      this_thread::sleep_for(chrono::seconds(1));
      producerIndex++;
    }
  }

}
void ConsumerJob()
{
  while (consumerIndex <= 20)
  {
    std::lock_guard<std::mutex> lock(consMtx);
    if (consumerIndex <= 20)
    { 
      auto ok = ProdCons.Consume();
      if (ok != -1)
      {
      cout << "Consuming " << ok << endl;
      this_thread::sleep_for(chrono::seconds(2));
      consumerIndex++;
      }
    }
  }

}

int main()
{
  queue<int> pcQueue;

  vector<thread> v;

  for (int i = 0; i < nrOfThreads; ++i)
  {
    if (i % 2 == 0)
    {
      v.push_back(thread(ProducerJob));
    }
    else
    {
      v.push_back(thread(ConsumerJob));
    }
  }

  for (auto &it : v)
  {
    it.join();
  }

  return 0;
}