#include "Semaphore.h"
#include"stdafx.h"

void Semaphore::notify()
{
  std::unique_lock<std::mutex> lock(m);
  count++;
  cv.notify_one();
}

void Semaphore::wait()
{
  std::unique_lock<std::mutex> lock(m);
  while (!count)
  {
    cv.wait(lock);
  }
  count--;
}



