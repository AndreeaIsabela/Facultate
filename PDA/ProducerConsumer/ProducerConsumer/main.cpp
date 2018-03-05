#include"stdafx.h"
#include"ProducerConsumer.h"

int maxNr = 20;
int nrOfThreads = 3;
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

void Producer()
{
  ProducerConsumer ProdCons;
  while (producerIndex <= maxNr)
  {
    int threadIndex = 0;
    {
      std::lock_guard<std::mutex> lock(prodMtx);
      threadIndex = producerIndex;
      producerIndex++;
    }
    
      ProdCons.Produce(threadIndex);
      {
        print(threadIndex, true);
      }
      this_thread::sleep_for(chrono::seconds(1));
    
  }

}
void Consumer()
{
  ProducerConsumer ProdCons;
  while (consumerIndex <= maxNr)
  {
      auto ok = ProdCons.Consume();
      if (ok!=-1 )
      {
        {
          print(ok, false);
          std::lock_guard<std::mutex> lock(consMtx);
          consumerIndex++;
        }
        this_thread::sleep_for(chrono::seconds(2));
      }
    
  }

}

int main()
{
  vector<thread> v;

  for (int i = 1; i < nrOfThreads; ++i)
  {
    
      v.push_back(thread(Producer));
    
      v.push_back(thread(Consumer));
    
  }

  for (auto &it : v)
  {
    it.join();
  }

  return 0;
}