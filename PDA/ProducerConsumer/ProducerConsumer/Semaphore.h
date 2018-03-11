#pragma once
#include"stdafx.h"
class Semaphore
{
public:
  Semaphore() {};
  Semaphore(int N) :count(N) {};
  ~Semaphore() {};

  void Up();
  void Down();
 
private:
  std::mutex m;
  std::condition_variable cv;
  unsigned int count = 0;
};

