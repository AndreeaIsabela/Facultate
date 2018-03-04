#include"stdafx.h"
#include"ProducerConsumer.h"

int maxNr = 20;
int nrOfThreads = 6;
int producerIndex = 0;
int consumerIndex = 0;
mutex prodMtx;
mutex consMtx;
mutex printMtx;


void print(int produceNr,bool prod)
{
  std::lock_guard<std::mutex> lock(printMtx);
  if(prod)
  {
  cout << "Producing " << produceNr << endl;
  }
  else
  {
    cout << "------------Consuming " << produceNr << endl;
  }
}

void ProducerJob()
{
  ProducerConsumer ProdCons;
  while (producerIndex <= maxNr)
  {
    int number = 0;
    {
      std::lock_guard<std::mutex> lock(prodMtx);
      number = producerIndex;
      producerIndex++;
    }
    if (number <= maxNr)
    {
      ProdCons.Produce(number);
      {
        print(number, true);
      }
      this_thread::sleep_for(chrono::seconds(1));
    }
  }

}
void ConsumerJob()
{
  ProducerConsumer ProdCons;
  while (consumerIndex <= maxNr)
  {
    if (consumerIndex <= maxNr)
    { 
      auto ok = ProdCons.Consume();
      if (ok!=-1 )
      {
        {
          print(ok, false);
          consumerIndex++;
        }
        this_thread::sleep_for(chrono::seconds(2));
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