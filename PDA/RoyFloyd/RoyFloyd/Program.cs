using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using MPI;

namespace FloydWarshallAlgorithm
{
    class FloydWarshallAlgo
    {

        public const int cst = 9999;

        private static void Print(int[,] distance, int verticesCount)
        {
            Console.WriteLine("Shortest distances between every pair of vertices:");

            for (int i = 0; i < verticesCount; ++i)
            {
                for (int j = 0; j < verticesCount; ++j)
                {
                    if (distance[i, j] == cst)
                        Console.Write("cst".PadLeft(7));
                    else
                        Console.Write(distance[i, j].ToString().PadLeft(7));
                }

                Console.WriteLine();
            }
        }

        public static void FloydWarshall(int[,] graph, int verticesCount, int nrOfProc, int myRank)
        {


            int[,] distance = new int[verticesCount, verticesCount];

            for (int i = 0; i < verticesCount; ++i)
                for (int j = 0; j < verticesCount; ++j)
                    distance[i, j] = graph[i, j];

            if (myRank != 0)
            {

                for (int k = 0; k < verticesCount; ++k)
                {

                    for (int i = myRank - 1; i < verticesCount; i += nrOfProc - 1)
                    {
                        for (int j = 0; j < verticesCount; ++j)
                        {
                            if (distance[i, k] + distance[k, j] < distance[i, j])
                                distance[i, j] = distance[i, k] + distance[k, j];
                        }
                    }
                }

                Communicator.world.Send<int[,]>(distance, 0, myRank);
            }

            if (myRank == 0)
            {


                for (int i = 1; i < nrOfProc; ++i)
                {
                    int[,] receivedGraph = Communicator.world.Receive<int[,]>(i, i);

                    for (int k = 0; k < verticesCount; ++k)
                        for (int j = 0; j < verticesCount; ++j)
                        {
                            if(distance[k, j] > receivedGraph[k, j])
                            {
                                distance[k, j] = receivedGraph[k, j];
                            }
                        }


                }
                Print(distance, verticesCount);
            }
        }

        static void Main(string[] args)
        {
            using (new MPI.Environment(ref args))
            {
                int nrOfProc = Communicator.world.Size;
                int myRank = Communicator.world.Rank;



                int[,] graph = {
                         { 0,   3,  6, 15 },
                         { cst, 0,   -2, cst },
                         { cst, cst, 0 , 2 },
                         { 1, cst, cst, 0 }
                           };

                FloydWarshall(graph, 4, nrOfProc, myRank);
            }
        }
    }
}