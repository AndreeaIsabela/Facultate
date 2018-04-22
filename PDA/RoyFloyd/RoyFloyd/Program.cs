using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using MPI;
using RoyFloyd;

namespace FloydWarshallAlgorithm
{
    class FloydWarshallAlgo
    {

        public const int cst = 9999;

        private static void Print(int[][] distance, int verticesCount)
        {
            Console.WriteLine("Shortest distances between every pair of vertices:");

            for (int i = 0; i < verticesCount; ++i)
            {
                for (int j = 0; j < verticesCount; ++j)
                {
                    if (distance[i][j] == cst)
                        Console.Write("cst".PadLeft(7));
                    else
                        Console.Write(distance[i][j].ToString().PadLeft(7));
                }

                Console.WriteLine();
            }
        }

        public static void FloydWarshall(int[][] graph, int verticesCount, int nrOfProc, int myRank)
        {
            var com = Communicator.world;
            
            for (int k = 0; k < verticesCount; ++k)
            { 
                for (int i = myRank; i <= myRank; ++i)
                { 
                    for (int j = 0; j < verticesCount; ++j)
                    {
                        if (graph[i][k] + graph[k][j] < graph[i][j])
                            graph[i][j] = graph[i][k] + graph[k][j];
                    }
                    var pair = new Pair();
                    pair.Value = graph[i];
                    pair.Line = i;
                    var perechi = com.Allgather<Pair>(pair);
                    foreach(var pereche in perechi)
                    {
                        graph[pereche.Line] = pereche.Value;
                    }
                }
                    
            }
            if(myRank == 0)
            {
                Print(graph, verticesCount);
            }
        }

        static void Main(string[] args)
        {
            using (new MPI.Environment(ref args))
            {
                int nrOfProc = Communicator.world.Size;
                int myRank = Communicator.world.Rank;



                int[][] graph = 
                    
                    
                    {
                       new int[]  { 0,   3,  6, 15 },
                       new int[]   { cst, 0,   -2, cst },
                         new int[] { cst, cst, 0 , 2 },
                         new int[] { 1, cst, cst, 0 }
                           };

                FloydWarshall(graph, 4, nrOfProc, myRank);
            }
        }
    }
}