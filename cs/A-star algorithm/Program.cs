using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI {
    class Program {
        static void Main(string[] args) {


            //测试集1
            {
                Node[] nodes1 = new Node[5];

                Node s = new Node("s", 10);
                Node a = new Node("a", 1);
                Node b = new Node("b", 5);
                Node c = new Node("c", 8);
                Node g = new Node("g", 0);

                nodes1[0] = s;
                nodes1[1] = a;
                nodes1[2] = b;
                nodes1[3] = c;
                nodes1[4] = g;

                Edge[] edges1 = new Edge[6];

                Edge sa = new Edge("s", "a", 6);
                Edge sb = new Edge("s", "b", 3);
                Edge sc = new Edge("s", "c", 1);
                Edge bc = new Edge("b", "c", 1);
                Edge ab = new Edge("a", "b", 1);
                Edge ag = new Edge("a", "g", 8);

                edges1[0] = sa;
                edges1[1] = sb;
                edges1[2] = sc;
                edges1[3] = bc;
                edges1[4] = ab;
                edges1[5] = ag;



                 CLOSE finally_close = A_star.Run(nodes1, edges1, "s", "g",true);
                A_star.Show(finally_close);
            }


            //测试集2
            {
                Node[] nodes2 = new Node[8];

                Node A = new Node("A", 15);
                Node B = new Node("B", 14);
                Node C = new Node("C", 10);
                Node D = new Node("D", 2);
                Node E = new Node("E", 0);
                Node F = new Node("F", 5);
                Node G = new Node("G", 9);
                Node H = new Node("H", 11);

                nodes2[0] = A;
                nodes2[1] = B;
                nodes2[2] = C;
                nodes2[3] = D;
                nodes2[4] = E;
                nodes2[5] = F;
                nodes2[6] = G;
                nodes2[7] = H;

                Edge[] edges2 = new Edge[11];

                edges2[0] = new Edge("A", "B", 3);
                edges2[1] = new Edge("A", "H", 4);
                edges2[2] = new Edge("B", "H", 5);
                edges2[3] = new Edge("B", "C", 4);
                edges2[4] = new Edge("G", "H", 2);
                edges2[5] = new Edge("C", "G", 3);
                edges2[6] = new Edge("C", "D", 8);
                edges2[7] = new Edge("G", "F", 4);
                edges2[8] = new Edge("D", "G", 8);
                edges2[9] = new Edge("D", "F", 3);
                edges2[10] = new Edge("D", "E", 2);


                //CLOSE finally_close = A_star.Run(nodes2, edges2, "A", "E", true);
                //A_star.Show(finally_close);
            }



            //测试集3
            {
                Node[] nodes3 = new Node[6];

                nodes3[0] = new Node("s", 20);
                nodes3[1] = new Node("A", 1);
                nodes3[2] = new Node("B", 4);
                nodes3[3] = new Node("C", 8);
                nodes3[4] = new Node("D", 14);
                nodes3[5] = new Node("t", 18);

                Edge[] edges3 = new Edge[11];

                edges3[0] = new Edge("s", "A", 11);
                edges3[1] = new Edge("s", "B", 9);
                edges3[2] = new Edge("s", "C", 6);
                edges3[3] = new Edge("s", "D", 1);
                edges3[4] = new Edge("A", "B", 1);
                edges3[5] = new Edge("B", "D", 4);
                edges3[6] = new Edge("A", "D", 6);
                edges3[7] = new Edge("A", "C", 3);
                edges3[8] = new Edge("B", "C", 1);
                edges3[9] = new Edge("C", "D", 1);
                edges3[10] = new Edge("A", "t", 18);

                //CLOSE finally_close = A_star.Run(nodes3, edges3, "s", "t", true);
                //A_star.Show(finally_close);

            }


            Console.ReadLine();
        }
    }

  

}
