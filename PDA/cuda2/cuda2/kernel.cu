

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>


#define N 4
#define graph(row,col) graph[row*N+col]


const int inf = 9999;



int graph[N*N] = { 0,   3,  6, 15 ,inf, 0,   -2, inf ,inf, inf, 0 , 2 , 1, inf, inf, 0 };

void printGraph(int graph[]) {

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
    {
      if (graph(i, j) == inf)
        std::cout << "inf ,";
      else
        std::cout << graph(i, j) << ", ";
    }
    std::cout << std::endl;
  }

}

__global__ void RoyFloyd(int *graph, int k)
{
  int i = threadIdx.x;
  for (int j = 0; j < N; ++j)
  {
    if (graph(i, k) + graph(k, j) < graph(i, j))
      graph(i, j) = graph(i, k) + graph(k, j);
  }

}

int main()
{
  int* d_roy;
  cudaMalloc(&d_roy, N*N * sizeof(int));
  cudaMemcpy(d_roy, graph, N * N * sizeof(int), cudaMemcpyHostToDevice);


  for (int k = 0; k < N; ++k)
  {
    int* d_k;
    cudaMalloc(&d_k, sizeof(int));
    cudaMemcpy(d_k, &k, sizeof(int), cudaMemcpyHostToDevice);

    RoyFloyd << <1, N > >>(d_roy, *d_k);

  }
    cudaMemcpy(graph, d_roy, N * N * sizeof(int), cudaMemcpyDeviceToHost);

  printGraph(graph);


  return 0;
}
