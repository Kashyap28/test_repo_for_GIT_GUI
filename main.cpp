/*

Q.2 In the networking field, imaging that the routers are represented using nodes and the network traffic
and congestion proportion is represented as the edge weight. Implement the shortest path
algorithm that suggests the path from source to the destination. Consider atleast 10 node in the
network.

*/
#include <iostream>
#include<cmath>

using namespace std;


struct Node_of_main_list;//just given a prototype that a struct of this name is there, definition of this struct will be given afterwards


struct Node_of_adj_list{//Node 1 is the pointer of the adjacency list of each node

    string label;
    Node_of_main_list* point_to_mainList_Node;
    Node_of_adj_list* next;//pointing to the next adjacent node of a given node
    int edge_weight;
    Node_of_adj_list(string Label,Node_of_main_list* current,int weight):label(Label),point_to_mainList_Node(current),next(nullptr),edge_weight(weight){}
    //as the node which is added as the neighbour of some vertex in the adj_list should also have link to the original node
};

struct Node_of_main_list{//Node 2 is the  the node of the main list

    string label;
    Node_of_main_list* next;
    Node_of_adj_list* pointToAdjNodeList;
    bool visited;//it will help while traversing to keep track of the nodes which are already processed
    int node_index;
    Node_of_main_list(string Label,int num):label(Label),next(nullptr),pointToAdjNodeList(nullptr),visited(0),node_index(num){}//constructor

};


 struct List{//adjacency list representation of a graph

    Node_of_main_list* head;
    Node_of_main_list* tail;
    int no_of_nodes;

    List():head(nullptr),tail(nullptr),no_of_nodes(0){}//same name as that of class

    Node_of_main_list* appendNode_in_mainList(string Label){//string label will be passed as parameter

        if(head==nullptr){//to create first node of the graph
            head=new Node_of_main_list(Label,no_of_nodes);//Node of main list
            tail=head;
        }
        else{//to create a isolated node in the graph
            tail->next=new Node_of_main_list(Label,no_of_nodes);//superclass pointer pointing to an object of subclass
            tail=tail->next;
        }

        no_of_nodes++;
        return tail;


    }
//newLabel will be added as neighbour of NeighbourVertex
    void insert_Node(string NeighbourVertex,string newLabel,int weight){//new node with newLabel, will be inserted as neighbour of the vertex given in Neighbour Vertex i.e. there will be an edge from NeighbourVertex to the newly created node

        Node_of_main_list* currentNode=head;
        Node_of_main_list* loc=nullptr;
        int present=0;
        while(currentNode!=nullptr){
            if(currentNode->label==newLabel){//if the node which is to be inserted is already present in the list then return
                loc=currentNode;
                present=1;
                break;
            }
            currentNode=currentNode->next;
        }

        if(present==0)
            loc=appendNode_in_mainList(newLabel);
        Node_of_main_list* current=head;

        while(current!=nullptr){

            if(current->label==NeighbourVertex){
                if(current->pointToAdjNodeList==nullptr)
                    current->pointToAdjNodeList=new Node_of_adj_list(newLabel,loc,weight);
                else{
                    Node_of_adj_list* current2=current->pointToAdjNodeList;
                    while(current2->next!=nullptr)
                        current2=current2->next;
                    current2->next=new Node_of_adj_list(newLabel,loc,weight);//newly created node is added as Neighbour Vertex's adjacent node
                }
                break;
            }

            current=current->next;

        }

    }
/*
    void Insertion(string* neighbour_Vertices,int sizeOfArray,string newVertexLabel){//new node with newVertexLabel will be created and it will be added as a neighbour of all the vertices present in newVertexLabel

        for(int i=0;i<sizeOfArray;i++){
            insert_Node(neighbour_Vertices[i],newVertexLabel);

            }

    }*/

     void print_adj_nodes(Node_of_main_list* ptr){
        Node_of_adj_list* current=ptr->pointToAdjNodeList;
        cout<<"\nAdjacent nodes of "<<ptr->label<<" are: ";
        while(current!=nullptr){
            cout<<current->label<<"  ";
            current=current->next;
        }



    }

    void delete_adj_linked_list(Node_of_adj_list* &head){
        //cout<<"Head value is: "<<head->label<<endl;
        if(head->next->next!=nullptr)
            delete_adj_linked_list(head->next);

        if(head->next==nullptr){
            delete head;
            head=nullptr;
            //cout<<"\nreached here!";
        }

          if(head->next->next==nullptr){
            delete head->next;
            head->next=nullptr;
           // cout<<"\n\nValue of head is: "<<head->label<<endl;
        }
    }


    void delete_all_adj_edges(Node_of_main_list* & head){//function for deleting all edges starting from root node
        if(head->pointToAdjNodeList==nullptr)//if head==nullptr then return
            return;
        if(head->pointToAdjNodeList->next==nullptr){
            delete head->pointToAdjNodeList;
            head->pointToAdjNodeList=nullptr;
        }
        else{
            delete_adj_linked_list(head->pointToAdjNodeList);//recursive call to delete the nodes of the linked list
            head->pointToAdjNodeList=nullptr;
        }
    }



    void delete_Edge_btw_two_given_nodes(Node_of_main_list* leftNode,string Label){//deleting an edge
        Node_of_adj_list* A =leftNode->pointToAdjNodeList;

        if(A==nullptr)
            return;

        if(A->label==Label){//similar to deleting a head in linked list
            leftNode->pointToAdjNodeList=A->next;
            delete A;
        }
        else{

            while(A->next!=nullptr){//if you want to delete the nth node then you need to be at (n-1)th node
                if(A->next->label==Label){
                    Node_of_adj_list* ptr=A->next;
                    A->next=A->next->next;
                    delete ptr;
                    break;
                }
                A=A->next;

            }
        }

    }


    void delete_Node(string Label){

        Node_of_main_list* currentNode=head;
        Node_of_main_list* point_to_Prev_node=nullptr;
        int present=0;

        if(currentNode->label==Label){//if the head needs to be deleted
            point_to_Prev_node=nullptr;
            cout<<"\nHead node needs to be deleted:  "<<endl;
            present=1;
        }

        else{
            while(currentNode->next!=nullptr){
                if(currentNode->next->label==Label){//if the node which is to be inserted is already present in the list then return
                    point_to_Prev_node=currentNode;
                    cout<<"Previous node of the node to be deleted is:  "<<point_to_Prev_node->label<<endl;
                    present=1;
                    break;
                }
                currentNode=currentNode->next;
            }

        }

        if(present==0)
            return;
       // if(point_to_Prev_node->next==nullptr)//if the node to be delete is not present then return
           // return;
        //first delete all nodes ending at node whose label= Label, label is string
            Node_of_main_list* current=head;//current pointer pointing to head node of linked list

            while(current!=nullptr){
                if(current->label!=Label)
                    delete_Edge_btw_two_given_nodes(current,Label);//deleting all the edges ending at node to be deleted
                //this->print_adj_nodes(current);
                current=current->next;

            }

        Node_of_main_list* pivot;

        if(point_to_Prev_node!=nullptr){
            delete_all_adj_edges(point_to_Prev_node->next);//deleting all edges starting from the node to be deleted
            Node_of_main_list* ptr= point_to_Prev_node->next;//if you want to delete the nth node then you need to be (n-1)th node
            point_to_Prev_node->next=point_to_Prev_node->next->next;
            pivot=point_to_Prev_node->next;
            delete ptr;

        }

        else{
             delete_all_adj_edges(head);//deleting all edges starting from the node to be deleted
            Node_of_main_list* ptr= head;//if you want to delete the nth node then you need to be (n-1)th node
            head=head->next;
            pivot=head;
            delete ptr;


        }

        while(pivot!=nullptr){
            pivot->node_index-=1;//as if we delete 2nd node that
            pivot=pivot->next;

        }

        no_of_nodes--;

    }

    void print_nodes(){
        Node_of_main_list* current=head;
        cout<<"\nNodes present in graph are: ";
        while(current!=nullptr){
            cout<<current->label<<"  ";
            current=current->next;
        }

    cout<<"\n\n";

    }

    void get_Weight_matrix(int** &arr){//reference to a pointer value

        int n=this->no_of_nodes;
        cout<<"No of nodes is: "<<no_of_nodes<<endl;
        arr=new int*[n];

        for(int i=0;i<n;i++)
            arr[i]=new int[n];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(i==j)
                    arr[i][j]=0;//as there will be no cost to go from vertex i to i
                else
                    arr[i][j]=999999;//an infinite entry denotes that there is no edge from vertex i to vertex j
        }

        Node_of_main_list* current1=head;

        while(current1!=nullptr){
                //cout<<"Value of current1: "<<current1->label<<"    ";
            Node_of_adj_list* current2=current1->pointToAdjNodeList;
            while(current2!=nullptr){
               // cout<<"Value of current2: "<<current2->label<<"  ";
                arr[current1->node_index][current2->point_to_mainList_Node->node_index]=current2->edge_weight;
                current2=current2->next;
                //if(current2!=nullptr)
                    //cout<<"  current2 next index : "<<current2->point_to_mainList_Node->node_index<<" ";
            }
       // cout<<"\n";

            current1=current1->next;
            }

    }


    void get_Adjacency_list(){
        Node_of_main_list* cur=head;
        while(cur!=nullptr){
            print_adj_nodes(cur);
            cur=cur->next;
        }


    }



};


int main()
{
    List graph1;//graph1 is an object of this class
    graph1.appendNode_in_mainList("A");
    graph1.insert_Node("A","B",4);
    graph1.insert_Node("A","E",10);
    graph1.insert_Node("A","G",14);
    graph1.insert_Node("B","F",7);
    graph1.insert_Node("B","C",3);
    graph1.insert_Node("C","B",1);
    graph1.insert_Node("C","D",1);
    graph1.insert_Node("C","F",2);
    graph1.insert_Node("C","I",3);
    graph1.insert_Node("D","F",1);
    graph1.insert_Node("D","E",2);
    graph1.insert_Node("D","H",5);
    graph1.insert_Node("H","J",4);
    graph1.insert_Node("I","J",3);



    int** arr;
    graph1.get_Weight_matrix(arr);

    graph1.print_nodes();

    cout<<"\n\Weight matrix of the given graph is: \n";
    for(int i=0;i<graph1.no_of_nodes;i++){
        for(int x=0;x<graph1.no_of_nodes;x++){
             if(arr[i][x]==999999)
                cout<<" "<<-1<<" ";//-1 to indicate that it is not reachable
            else
                cout<<"  "<<arr[i][x]<<" ";
        }
        cout<<"\n";

    }
   // cout<<"\n\n\Caluc: \n";

    for(int k=0;k<graph1.no_of_nodes;k++){//Floyd Warshall's Shortest path algo for finding shortest distance between any two pairs
        for(int i=0;i<graph1.no_of_nodes;i++){
            for(int x=0;x<graph1.no_of_nodes;x++){
                arr[i][x]=min(arr[i][x],arr[i][k]+arr[k][x]);//checking whether using k as intermediate vertex is there any shortest path available
                //cout<<arr[i][x]<<" ";

            }

        }


    }

    cout<<"\n\nThe shortest path matrix is: \n";
    for(int i=0;i<graph1.no_of_nodes;i++){
         for(int x=0;x<graph1.no_of_nodes;x++){
            if(arr[i][x]==999999)
                cout<<" "<<-1<<" ";//-1 to indicate that it is not reachable
            else
                cout<<"  "<<arr[i][x]<<" ";
        }
        cout<<"\n";

    }



    return 0;
}
