#include <iostream>
using namespace std;

struct Node{
    Node* next;
    int value;
    Node(int val): value(val), next(nullptr){};
};

struct LinkedList{
    Node* head, *tail;

    LinkedList(): head(nullptr), tail(nullptr){}; 

    ~LinkedList(){
        while(head!=nullptr){
            Node* temp = head;
            head = head->next;
            //Deference head to get to the first element then take the next address
            delete temp;
        }
    };
};

//Target is an address already
void insertTail(Node*& head, Node*& tail, Node*& target){
    if(head == nullptr){
        head = target;
    }
    else{
        tail->next = target;
    }
    tail = target;
    return;
};

//Assume input a list of integer

int main(){
    int n;
    LinkedList ma;
    Node *fast, *slow;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int vtemp;
        cin >> vtemp;
        Node* newNode = new Node(vtemp);
        insertTail(ma.head, ma.tail, newNode);
    }

    
    return 0;
}