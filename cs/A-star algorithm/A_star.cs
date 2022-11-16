using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace AI {
    class Node {

        public string node_name;
        public int comsume;
        public int distance;
        public string parents_name;
        public int H;

        public Node() {

        }

        public Node(string name, int H) {
            this.node_name = name;
            this.comsume = 0;
            this.distance = 0;
            this.parents_name = " ";
            this.H = H;
        }


        public Node[] GetNeighbourNode(Node node, Edge[] edge, Node[] all_nodes) {
            //输入：node当前节点，edge所有边的集，all_node所有节点的集
            //输出：所有与node相邻的节点的数组

            Node[] neighbour_node = new Node[100];
            for(int i = 0; i < 100; i++) {
                neighbour_node[i] = new Node();
            }
            int count = 0;

            foreach (Edge e in edge) {
                if (e.node1 == node.node_name) {
                    neighbour_node[count] = GetNode(e.node2, all_nodes);
                    count++;
                } else if (e.node2 == node.node_name) {
                    neighbour_node[count] = GetNode(e.node1, all_nodes);
                    count++;
                }
            }
            return neighbour_node;
        }

        public Node FindMinConsumeNode(OPEN open) {
            //输入：当前OPEN表
            //输出：当前OPEN表中consume值最小的节点

            int consume_temp = int.MaxValue;
            Node node_min = new Node();

            foreach (Node node in open.list) {
                if (node.comsume < consume_temp) {
                    node_min = node;
                    consume_temp = node.comsume;
                }
            }
            return node_min;
        }

        public Node GetNode(string node_name, OPEN open) {
            //输入：要查找的节点名字，当前OPEN表
            //输出：名字对应的节点实体

            foreach (Node n in open.list) {
                if (n.node_name == node_name) {
                    return n;
                }
            }
            return null;
        }
        public Node GetNode(string node_name, CLOSE close) {
            //输入：要查找的节点名字，当前CLOSE表
            //输出：名字对应的节点实体

            foreach (Node n in close.list) {
                if (n.node_name == node_name) {
                    return n;
                }
            }
            return null;
        }
        public Node GetNode(string node_name, Node[] nodes) {
            //输入：要查找的节点名字，全体节点成员
            //输出：名字对应的节点实体

            foreach (Node n in nodes) {
                if (n.node_name == node_name) {
                    return n;
                }
            }
            return null;
        }

    }

    class Edge {

        public string node1;
        public string node2;
        public int cost;

        public Edge() {

        }
        public Edge(string node1,string node2,int cost) {
            this.node1 = node1;
            this.node2 = node2;
            this.cost = cost;
        }

        public int GetEdgeCost(string node1,string node2,Edge[] edges) {
            int cost = -1;
            foreach (Edge e in edges) {
                if (( ( e.node1 == node1 ) && ( e.node2 == node2 ) ) || ( ( e.node2 == node1 ) && ( e.node1 == node2 ) )) {
                    cost = e.cost;
                }
            }
            return cost;
        }

    }

    class OPEN {

        public Node[] list;

        public OPEN() {
            this.list = new Node[100];
            for(int i = 0; i < 100; i++) {
                this.list[i] = new Node();
                this.list[i].comsume = int.MaxValue;
            }
            foreach (Node n in list) {
                n.distance = int.MaxValue;
            }
        }

        public OPEN Remove(string node_name,OPEN open) {
            //输入：要删除的节点名，当前OPEN表
            //输出：删除节点后整理好的OPEN表

            int node_position = 0;
            foreach(Node n in open.list) {
                if(n.node_name == node_name) {
                    break;
                } 
                else {
                    node_position++;
                }
            }

            //不存在该节点则退出返回原表
            if (( node_position == 0 ) && ( open.list[0].node_name != node_name )) {
                return open;
            }

            //整理队列，position之后的节点前移
            int position_plus_one = node_position + 1;
            while (position_plus_one < 99) {
                open.list[node_position] = open.list[position_plus_one];
                position_plus_one++;
                node_position++;
            }
            open.list[99].distance = int.MaxValue;
            return open;
        }

        public  OPEN Append(Node node,OPEN open) {
            //输入：节点名字，当前OPEN表
            //输出：新增节点后的OPEN表

            //列表已满无法增加，返回NULL
            if (open.list[99].distance < int.MaxValue) {
                return null;
            }

            //找到空闲的第一个位置
            int free_position = 0;
            foreach(Node n in open.list) {
                if (n.distance == int.MaxValue) {
                    break;
                } 
                else {
                    free_position++;
                }
            }

            //插入节点并返回OPEN表
            open.list[free_position] = node;
            return open;
        }

        public bool IsEmpty(OPEN open) {
            //判断OPEN表是否为空

            if (open.list[0].distance == int.MaxValue) {
                return true;
            } 
            else {
                return false;
            }
        }

        public bool IsExist(string node_name,OPEN open) {
            //查找OPEN表中是否存在节点node_name

            foreach(Node n in open.list) {
                if(n.node_name == node_name) {
                    return true;
                }
            }

            return false;
        }
        
    }//class OPEN

    class CLOSE {

        public Node[] list;

        public CLOSE() {
            this.list = new Node[100];
            for(int i = 0; i < 100; i++) {
                this.list[i] = new Node();
                this.list[i].comsume = int.MaxValue;
            }
            foreach(Node n in list) {
                n.distance = int.MaxValue;
            }
        }

        public CLOSE Remove(string node_name,CLOSE close) {
            //输入：要删除的节点名，当前OPEN表
            //输出：删除节点后整理好的OPEN表

            int node_position = 0;
            foreach (Node n in close.list) {
                if (n.node_name == node_name) {
                    break;
                } else {
                    node_position++;
                }
            }

            //不存在该节点则退出返回原表
            if (( node_position == 0 ) && ( close.list[0].node_name != node_name )) {
                return close;
            }

            //整理队列，position之后的节点前移
            int position_plus_one = node_position + 1;
            while (position_plus_one < 99) {
                close.list[node_position] = close.list[position_plus_one];
                position_plus_one++;
                node_position++;
            }
            close.list[99].distance = int.MaxValue;
            return close;
        }

        public CLOSE Append(Node node,CLOSE close) {
            //输入：节点名字，当前OPEN表
            //输出：新增节点后的OPEN表

            //列表已满无法增加，返回NULL
            if (close.list[99].distance < int.MaxValue) {
                return null;
            }

            //找到空闲的第一个位置
            int free_position = 0;
            foreach (Node n in close.list) {
                if (n.distance == int.MaxValue) {
                    break;
                } else {
                    free_position++;
                }
            }

            //插入节点并返回OPEN表
            close.list[free_position] = node;
            return close;
        }

        public bool IsExist(string node_name,CLOSE close) {
            //查找close表中是否存在节点node_name

            foreach (Node n in close.list) {
                if(n.node_name == node_name) {
                    return true;
                }
            }

            return false;
        }

        public static void Show(CLOSE close) {
            //打印出CLOSE表中的所有路径

            foreach(Node n in close.list) {
                if (n.comsume != int.MaxValue) {
                    Console.WriteLine(n.parents_name + ">>" + n.node_name 
                        + "        " + n.node_name + "的comsume值(fn)：" +n.comsume.ToString() 
                        + "\t累计distance值(实际路径耗散)：" + n.distance.ToString());
                }            
            }
        }

    }//class CLOSE

    class A_star {

        public A_star() {

        }

        public static CLOSE Run(Node[] nodes, Edge[] edges, string start_name, string end_name,bool show_process=false) {
            //A*算法
            //输入：点集nodes,边集edges,起始点名start_name,终结点名end_name
            //输出：最终CLOSE表

            //初始化
            Node NodeFunction = new Node();
            Edge EdgeFunction = new Edge();
            OPEN OPENFunction = new OPEN();
            CLOSE CLOSEFunction = new CLOSE();

            OPEN open = new OPEN();
            CLOSE close = new CLOSE();

            Node now_node = NodeFunction.GetNode(start_name, nodes);
            now_node.comsume = now_node.H;//Console.WriteLine(now_node.comsume.ToString());
            now_node.distance = 0;
            now_node.parents_name = now_node.node_name;

            //将起始点放到OPEN表中，此时OPEN表为空
            close = CLOSEFunction.Append(now_node, close);

            //设置循环计数器
            int loop_count = 0;

            //主循环：当OPEN中非空时，或第一次循环OPEN表空而CLOSE表只有一个节点时，要扩展
            while ((OPENFunction.IsEmpty(open) != true) || (close.list[1].comsume == int.MaxValue)) {

                loop_count++;
                Node[] childrennode = NodeFunction.GetNeighbourNode(now_node, edges, nodes);

                foreach(Node n in childrennode) {

                    //计算每个child_node的consume值
                    int child_consume = now_node.distance 
                        + n.H 
                        + EdgeFunction.GetEdgeCost(now_node.node_name, n.node_name,edges);

                    //分类处理每个child_node
                    //不在两表中，则加入OPEN表
                    if ((OPENFunction.IsExist(n.node_name, open) == false) 
                        && (CLOSEFunction.IsExist(n.node_name, close) == false)) {

                        n.comsume = child_consume;
                        n.parents_name = now_node.node_name;//需要指定parents?
                        open = OPENFunction.Append(n, open);
                    }

                    //在OPEN表中，则对比原consume值，新consume值更小则更新其consume,parents
                    else if (OPENFunction.IsExist(n.node_name, open) == true) {

                        if (child_consume < n.comsume) {
                            n.comsume = child_consume;
                            n.parents_name = now_node.node_name;
                        }
                    }

                    //在CLOSE表中，则对比原consume值，新consume值更小则更新其consume,parents,并将该结点从CLOSE移到OPEN
                    else if (CLOSEFunction.IsExist(n.node_name, close) == true) {

                        if(child_consume < n.comsume) {
                            n.comsume = child_consume;
                            n.parents_name = now_node.node_name;
                            n.distance = int.MaxValue;
                            close = CLOSEFunction.Remove(n.node_name,close);
                            open = OPENFunction.Append(n, open);
                        }
                    }

                }//end foreach

                //确定要扩展的节点，从OPEN表中找出consume值最小的
                Node expand_node = NodeFunction.FindMinConsumeNode(open);

                //记录扩展点的耗散distance = 父节点的distance + 两节点边的耗散值(g(n+1)=g(n)+e)
                expand_node.distance = NodeFunction.GetNode(expand_node.parents_name, nodes).distance
                                                        + EdgeFunction.GetEdgeCost(expand_node.node_name, expand_node.parents_name,edges);

                //将扩展节点作为主节点，将他由OPEN表移至CLOSE表
                now_node = expand_node;
                open = OPENFunction.Remove(now_node.node_name, open);
                close = CLOSEFunction.Append(now_node, close);

                if (show_process == true) {
                    Console.WriteLine("CLOSE表第" + loop_count.ToString() + "次循环");
                    CLOSE.Show(close);
                    Console.WriteLine("\n\n\n\n");
                }
            }

            //返回目标CLOSE表
            return close;
        }

        public static void Show(CLOSE close) {
            Console.WriteLine("最终路径图（a>>b表示a指向b的路径）：");
            CLOSE.Show(close);
        }



    }
   




}//namespace


