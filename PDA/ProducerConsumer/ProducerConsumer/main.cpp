#include"stdafx.h"
#include"ProducerConsumer.h"


int nrOfThreads = 6;
int producerIndex = 0;
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
  while (true)
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
  while (true)
  {
      auto ok = ProdCons.Consume();
      if (ok!=-1 )
      {
        {
          std::lock_guard<std::mutex> lock(consMtx);
          print(ok, false);
        }
        this_thread::sleep_for(chrono::seconds(2));
      }
    
  }

}

int main()
{
  vector<thread> v;

  for (int i = 1; i <= nrOfThreads; ++i)
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