using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MPI;


namespace Rand
{
    class Program
    {
        
        static void Main(string[] args)
        {

            using(new MPI.Environment(ref args))
            {
                
                int procNr = Intercommunicator.world.Size;
                var com = Intercommunicator.world;
                var randomGen=new Random(System.DateTime.Now.Millisecond+com.Rank);
                int no = randomGen.Next(100, 1000); ;
                com.Barrier();
                List<int> arr= com.Gather(no, 0).ToList<int>();
                //if(com.Rank!=0)
                //{

                //    com.Send(no, 0,com.Rank);


                //    Console.WriteLine("Procesul "+com.Rank+" a generat :"+ no );

                //}
                //
                if(com.Rank==0)
                {
                    int maxNo = no, rank =0;
                    //int recVal = 0;
                    //Console.WriteLine("Procesul " + com.Rank +" a generat  :"  + no);
                    //for (int i = 1; i < procNr; ++i)
                    //{
                    //    recVal = com.Receive<int>(i, i);

                    //    if (maxNo < recVal)
                    //    {
                    //        maxNo = recVal;
                    //        rank = i;
                    //    }
                    //    else if(maxNo == recVal)
                    //    {
                    //        rank = Math.Max(rank,i);

                    //    }



                    arr.Sort();
                   
                    

                    Console.WriteLine("----------------------------Numarul maxim  " + arr[arr.Count-1] );
                    
                }
            }
        }
    }
}
