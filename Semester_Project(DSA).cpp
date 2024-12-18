#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct User // Using structure to represent a user
{
    string name;
    string interests[3]; // We have fixed-size array(3) for interests.
};

struct Friend // Using structure to represent a friend
{
    string name;
    int friendshipLevel;
    string interests[3]; // We also have fixed-size(3) array for interests.
};

struct Friend_node //This is our struct for a link list node.
{
    Friend data;
    Friend_node* next;

    Friend_node(Friend all_values_in_friend):data(all_values_in_friend),next(NULL){} // Initializing Friend object and next pointer here.
};
/// @brief Used addfriend, removefriend, and displayfriend functions here.
class Friend_list // Implementation of Linked list here.
{
public:
    Friend_node* head;

    Friend_list():head(NULL){}//Initializing head in the constructor.

    void addingfriend(Friend f)
    {
        Friend_node* newnode=new Friend_node(f); //Creating new node dynamically here.
        newnode->next=head;
        head=newnode; //Initializing new node as head here.
    }

    void removingfriend(const string& name)
    {
        //Creating two nodes here to one to be deleted and other keep track of our link list.
        Friend_node* current=head; 
        Friend_node* prev=NULL;

        while(current)
        {
            if(current->data.name==name)//Checking our basic condition here.
            {
                if(prev)
                {
                    prev->next=current->next; //Creating direct link between previous and next node of the node to be deleted, thus skipping it entirely.
                }
                else //The head node is to be deleted.
                {
                    head=current->next;
                }
                delete current; //freeing up head.
                return;
            }
            prev=current; //For traversing through our entire linked list.
            current=current->next;//Same as above comment.
        }
    }
        void merge_test(Friend arr[], int left, int mid, int right)//Used when we copy values from our pointer nodes to arrays(test not used here.)
    {
        int n1=mid-left+1; //Dividing into two halves
        int n2=right-mid;

        Friend* L=new Friend[n1]; //Creating Friend type arrays for storing the relevant data used in Friend structure.
        Friend* R=new Friend[n2];

        for(int i=0;i<n1;i++)//Basic merge sort logic ahead.
        {
            L[i] = arr[left+ i];
        }
        for(int j=0;j<n2;j++)
        {
            R[j]=arr[mid+1+j];
        }
        int i=0,j=0,k=left;
        while(i<n1&&j<n2)
        {
            if(L[i].name<=R[j].name)
            {
                arr[k]=L[i];
                i++;
            }
            else
            {
                arr[k]=R[j];
                j++;
            }
            k++;
        }
        while(i<n1)
        {
            arr[k]=L[i];
            i++;
            k++;
        }
        while(j<n2)
        {
            arr[k]=R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void mergesort_test(Friend arr[], int left, int right)//main function used for keep on finding mid of the array we keep on breaking into two halves and then applying sorting and merging. 
    {
        if(left<right)//Base condition
        {
            int mid=left+(right-left)/2;//For finding mid

            mergesort_test(arr,left,mid);//Recursive call on the left side of the array
            mergesort_test(arr,mid+1,right);//Recursive call on the right side of the array

            merge_test(arr,left,mid,right);//Calling the merge function which sorts and merges the arrays back.
        }
    }
    Friend_node* merge(Friend_node* left, Friend_node* right)//More efficient merge and merge sort functions.
    {
    if(!left) 
    return right;
    if(!right) 
    return left;

    if(left->data.name<right->data.name)//Here we check whose name data value is smaller, then entering it first into our array.
    {
        left->next=merge(left->next, right);//Recursively calling left side and returning the smallest value on the end(next node is NULL) node.
        return left;//Giving the value in when left or right is nullptr.
    }
    else
    {
        right->next=merge(left, right->next);//Calling recursively merge function on the left and right of halves of our Friend_node array.
        return right; //returning right value as it is smaller
    }
}

    Friend_node* mergesort(Friend_node* head)
    {
    if(!head||!head->next)//This conditon satisfies that we atleast have two nodes.
    return head;

    Friend_node* slow=head; //This is used for starting sorting and merging from head.
    Friend_node* fast=head->next;//This is used for starting sorting and merging from the node next to head.

    while(fast&&fast->next) //For traversal
    {
        slow=slow->next;
        fast=fast->next->next;
    }

    Friend_node* mid=slow->next; //We initialize mid here.
    slow->next=nullptr;//The mid is currently declared as nullptr here.

    Friend_node* left=mergesort(head);//This is used for recursive call on head pointer
    Friend_node* right=mergesort(mid);//This is used for recursive call on mid pointer.

    return merge(left, right);
}
  void displayingfriends()//Added newly updated and simplified merge sort function for displaying, as it doesnot create temporary arrays anymore.
{
    head=mergesort(head);// Sort the linked list directly using the updated mergesort function.
    cout<<"Friend List (Alphabetically Sorted):\n";
    Friend_node* current=head;
    while(current)
    {
        //Printing friend details in alphabetical order.
        cout<<"Name: "<<current->data.name
            <<", Friendship Level: "<<current->data.friendshipLevel<<endl;
        current=current->next;//Traversal logic for the sorted linked list.
    }
}
         bool isFriend(const string&name)
        {
        Friend_node*current=head; //Start from head node.
        while(current)
        {
            if(current->data.name==name)//Main condition used to check whether a specific user is friend then their name will be present in the Friend_node struct.
            {
                return true;//return true as if name matches and found in Friend_node.
            }
            current=current->next;//To perform traversal here.
        }
        return false;//Return false if our while loop terminates out of if condition.
    }
    };

    class Friend_queue //Class created handling friend requests through queue structure.
{
    struct queuenode //The node we have use for our queue data structure.
    {
        string name;
        queuenode* next;

        queuenode(string n):name(n),next(nullptr){}
    };

    queuenode* front; //keeping track of both front and rear
    queuenode* rear;  

public:
    Friend_queue():front(nullptr), rear(nullptr){} //Initializing the values

    void enqueue(string name) //Enqueue function with base condition handling insertin at the rear end.
    {
        queuenode* newNode=new queuenode(name);
        if(!rear) //base conditon.
        {
            front=rear=newNode;
            return;
        }
        rear->next=newNode;
        rear=newNode;
    }

    void dequeue() //Dequeue function handling deletion at the front end
    {
        if(!front)
        {
            cout<<"No friend requests to process.\n";
            return;
        }

        queuenode* temp=front; 
        front=front->next; //Moving front ahead.

        if(!front) //Base conditon
            rear=nullptr;

        cout<<"Processed friend request from: "<<temp->name<<endl; //Dequeued successfully massage.
        delete temp; //Deleted our temporary node here.
    }

    void displayrequests() //Displaying all the requests here.
    {
        queuenode* current=front;
        cout<<"Friend Requests:\n";  
        while(current)
        {
            cout<<"- "<<current->name<<endl;
            current=current->next; //Traversal machnism.
        }
    }
};
class Blocked_friends
{
    struct Stack_node //This is our node for the stack data structure.
    {
        string name;
        Stack_node* next;
        Stack_node(string n):name(n),next(nullptr){}
    };
    Stack_node* top; 

public:
    Blocked_friends():top(nullptr){}

    void push(string name) //Using push function to insert nodes into our stack.
    {
        Stack_node* newnode=new Stack_node(name); //Creating new node dynamically here.
        newnode->next=top;
        top=newnode;
    }

    void pop()
    {
        if(top)
        {
            Stack_node* temp=top; //Deleting top if it existing then the node before it becomes the new top.
            top=top->next;
            delete temp;
        }
        else //When our stack is empty.
        {
            cout<<"No users to unblock."<<endl;
        }
    }

    string top_value(){
    if(!top)
    {
        return ""; // Return empty string if the stack is empty
    }
    return top->name;
}
    bool isEmpty()
    {
        return top==NULL; //Checking whether our stack is empty or not.
    }

    bool is_Blocked(const string& name)
    {
        Stack_node* current=top;
        while(current)
        {
            if(current->name==name)
            {
                return true;
            }
            current=current->next;
        }
        return false;
    }
     string* get_blocked_friends(int& count) //For the retrieval all blocked friends as an array.
    {
        count=get_blocked_friends_count(); //Used here for getting the number of blocked friends.
        if(count==0)
        {
            return nullptr; //We are returning a nullptr if there are no blocked friends.
        }
        string* blocked_friends=new string[count];//Here we dynamically allocate an array of type string and size current for storing the names of our blocked friends.
        Stack_node* current=top;//Creating a current node of stack_node type and inserting top node value into it. 
        int index=0;//Index for our newly created node here.

        while(current)
        {
            blocked_friends[index++]=current->name;//We used our new array for copying names into the array
            current=current->next;//Traversal logic here.
        }

        return blocked_friends; //We are returning our newly made array with all the blocked friends record.
    }
    int get_blocked_friends_count() // Retrieve the count of blocked friends
    {
        int count=0;
        Stack_node* current=top;
        while(current)
        {
            count++;//We used this here for incrementing the count for each node
            current=current->next;//Travesal logic
        }
        return count;
    }
};
class AVLTree
{
    struct Node
    {
        Friend data;
        Node* left;
        Node* right;
        int height;
        Node(Friend f):data(f),left(nullptr),right(nullptr),height(1){}
    };
    Node* root;
    int height(Node* n)
    {
        return n? n->height:0;
    }
    int get_balance(Node* n)
    {
        return n? height(n->left)-height(n->right):0;
    }
    Node* rotateright(Node* y)
    {
        Node* x=y->left;
        Node* T=x->right;
        x->right=y;
        y->left=T;
        y->height=max(height(y->left), height(y->right))+1;
        x->height=max(height(x->left), height(x->right))+1;
        return x;
    }
    Node* rotateleft(Node* x)
    {
        Node* y=x->right;
        Node* T=y->left;
        y->left=x;
        x->right=T;
        x->height=max(height(x->left), height(x->right))+1;
        y->height=max(height(y->left), height(y->right))+1;
        return y;
        
    }
    int balancefactor_updated(Node* n)
    {
        return n?height(n->left)-height(n->right):0;
    }
    Node* insert(Node* node,Friend f)
    {
        if(!node)//our base contion to exist recursion.
            return new Node(f);//Creating a new node at edge to a leaf node.

        if(f.friendshipLevel<node->data.friendshipLevel)
            node->left=insert(node->left,f);//This logic implies for traversal through left subtree.
        else if(f.friendshipLevel>node->data.friendshipLevel)//This logic implies for travesal through right subtree.
            node->right=insert(node->right,f);
        else
        return node;
        node->height=max(height(node->left),height(node->right))+1;//updating the height after the node insertion.
        int balance=balancefactor_updated(node);//Getting the new balance factor to check for imbalance.

        if(balance>1&&f.friendshipLevel<node->left->data.friendshipLevel)
            return rotateright(node);//This implies for LL rotation.(As right child of right subtree(of root with imbalance) is imbalanced with right heavy condition).

        if(balance<-1&&f.friendshipLevel>node->right->data.friendshipLevel)
            return rotateleft(node);//This implies for RR rotaion.(As left child of left subtree(of root with imbalance) is imbalanced with left heavy condition).

        if(balance>1&&f.friendshipLevel>node->left->data.friendshipLevel)
        {
            node->left=rotateleft(node->left);//First applying left rotation on the left subtree of root where the imbalance appears.
            return rotateright(node);//This here implies for LR rotaion
        }

        if(balance<-1&&f.friendshipLevel<node->right->data.friendshipLevel)
        {
            node->right=rotateright(node->right);//First applying right rotation on the right subtree of root where the imbalance appears.
            return rotateleft(node);//This here implies for RL rotation.
        }
        return node;//Returning node here.
    }

    void inOrder(Node* root)//For displaying names with highest friendship level first.
    {
        if(root)
        {
            inOrder(root->left);//recursion for traversing first into the deepest left most node.
            cout<<"Name: "<<root->data.name<<", Friendship Level: "<<root->data.friendshipLevel<<endl;//For displaying the friends levels.
            inOrder(root->right);//recursion for traversing after through the deepest right most node.
        }
    }
    AVLTree():root(nullptr){}
    void addfriend(Friend f)//for adding a new object friend of Friend type and inserting through interest level sequences.
    {
        root=insert(root,f);//This is for insert function 
    }
    void displayfriends()//This is for displaying all the names of friends with friendship levels through inorder traversal.
    {
        inOrder(root);//Inorder....traversal applied here.
    }
    };
    class Graph
{
    int num_of_users; // Used for number of users.
    bool** matrix;    // Using 2D adjacency matrix here of the type bool.
    string* names_of_users; // Used for users' name storage.

public:
    Graph(int number) : num_of_users(number)
    {
        matrix = new bool*[num_of_users];
        names_of_users = new string[num_of_users];
        for (int i = 0; i < num_of_users; ++i)
        {
            matrix[i] = new bool[num_of_users]();
        }
    }

    ~Graph()
    {
        for (int i = 0; i < num_of_users; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;          // Managing dynamically allocated memory efficiently thus preventing memory leak.
        delete[] names_of_users; // Managing dynamically allocated memory efficiently thus preventing memory leak.
    }

    void settinguser(int index, string name)
    {
        if (index >= 0 && index < num_of_users)
        { // Adding user name to our string array if the index value is valid.
            names_of_users[index] = name;
        }
    }

    void addingconnections(int first_user, int secound_user) // Also known as "edges".
    {
        if (first_user >= 0 && first_user < num_of_users && secound_user >= 0 && secound_user < num_of_users) // For checking whether a connection between nodes is possible or not.
        {
            matrix[first_user][secound_user] = matrix[secound_user][first_user] = true; // As we used an undirected graph, thus our edges are pointing in both directions.
        }
        else
        {
            cout << "Invalid user index.\nThus connection (Edge) not possible" << endl;
        }
    }

    void displaying_all_connections() // Use BFS for displaying connections.
    {
        cout << "Mutual Friend Connections (BFS Traversal):\n";
        bool* visited = new bool[num_of_users]();
        int* queue = new int[num_of_users];

        for (int start_user = 0; start_user < num_of_users; ++start_user)
        {
            if (!visited[start_user])
            {
                int front = 0, rear = 0;
                queue[rear++] = start_user;
                visited[start_user] = true;

                while (front < rear)
                {
                    int current_user = queue[front++];
                    cout << names_of_users[current_user] << " -> ";

                    for (int neighbor = 0; neighbor < num_of_users; ++neighbor)
                    {
                        if (matrix[current_user][neighbor] && !visited[neighbor])
                        {
                            queue[rear++] = neighbor;
                            visited[neighbor] = true;
                        }
                    }
                }
                cout << endl;
            }
        }

        delete[] visited;
        delete[] queue;
    }

    void suggesting_mutual_friends(int user_index)
    {
        cout << "Mutual Friend Suggestions for " << names_of_users[user_index] << ":\n";
        for (int i = 0; i < num_of_users; ++i)
        {
            if (matrix[user_index][i])
            {
                for (int j = 0; j < num_of_users; ++j)
                {
                    if (matrix[i][j] && !matrix[user_index][j] && j != user_index) // The condition used in skipping user_index typed in.
                    {
                        cout << "-" << names_of_users[j] << endl;
                    }
                }
            }
        }
    }
};
    int main()
    {
    // Create some users and friends
    User user1={"Alice",{"Reading", "Cooking", "Hiking"}};
    User user2={"Bob",{"Gaming", "Swimming", "Traveling"}};
    
    Friend friend1={"Charlie",5, {"Gaming", "Coding", "Music"}};
    Friend friend2={"Diana",7, {"Cooking", "Dancing", "Traveling"}};
    
    // Friend List Test
    Friend_list friendList;
    friendList.addingfriend(friend1);
    friendList.addingfriend(friend2);
    friendList.displayingfriends();

    // Queue Test
    Friend_queue friendQueue;
    friendQueue.enqueue("Charlie");
    friendQueue.enqueue("Diana");
    friendQueue.displayrequests();
    friendQueue.dequeue();

    // Blocked Friends Test
    Blocked_friends blocked;
    blocked.push("Charlie");
    if (blocked.is_Blocked("Charlie")) {
        cout << "Charlie is blocked.\n";
    }
    Blocked_friends blocked;

    // Add blocked friends
    blocked.push("Alice");
    blocked.push("Bob");
    blocked.push("Charlie");
    
    // Get and display all blocked friends
    int blockedCount=0;
    string* blockedList=blocked.get_blocked_friends(blockedCount);
    if(blockedList)
    {
        cout<<"Blocked Friends List:\n";
        for (int i=0;i<blockedCount;i++)
        {
            cout<<"- "<<blockedList[i]<<endl;
        }
        delete[] blockedList;//Free the dynamically allocated memory
    }
    else
    {
        cout<<"No blocked friends."<<endl;
    }
    // Get and display the count of blocked friends
    cout<<"Total Blocked Friends: "<<blockedCount<<endl;
    return 0;
}
