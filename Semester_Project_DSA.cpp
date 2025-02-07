#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
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

    Friend_node(Friend all_values_in_friend) :data(all_values_in_friend), next(NULL) {} // Initializing Friend object and next pointer here.
};

/// @brief Used addfriend, removefriend, and displayfriend functions here.
class Friend_list // Implementation of Linked list here.
{
public:
    Friend_node* head;

    Friend_list() :head(NULL) {}//Initializing head in the constructor.

    void addingfriend(Friend f)
    {
        Friend_node* newnode = new Friend_node(f); //Creating new node dynamically here.
        newnode->next = head;
        head = newnode; //Initializing new node as head here.
    }

    void removingfriend(const string& name)
    {
        //Creating two nodes here to one to be deleted and other keep track of our link list.
        Friend_node* current = head;
        Friend_node* prev = NULL;

        while (current)
        {
            if (current->data.name == name)//Checking our basic condition here.
            {
                if (prev)
                {
                    prev->next = current->next; //Creating direct link between previous and next node of the node to be deleted, thus skipping it entirely.
                }
                else //The head node is to be deleted.
                {
                    head = current->next;
                }
                delete current; //freeing up head.
                return;
            }
            prev = current; //For traversing through our entire linked list.
            current = current->next;//Same as above comment.
        }
    }
    void merge_test(Friend arr[], int left, int mid, int right)//Used when we copy values from our pointer nodes to arrays(test not used here.)
    {
        int n1 = mid - left + 1; //Dividing into two halves
        int n2 = right - mid;

        Friend* L = new Friend[n1]; //Creating Friend type arrays for storing the relevant data used in Friend structure.
        Friend* R = new Friend[n2];

        for (int i = 0; i < n1; i++)//Basic merge sort logic ahead.
        {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++)
        {
            R[j] = arr[mid + 1 + j];
        }
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i].name <= R[j].name)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void mergesort_test(Friend arr[], int left, int right)//main function used for keep on finding mid of the array we keep on breaking into two halves and then applying sorting and merging. 
    {
        if (left < right)//Base condition
        {
            int mid = left + (right - left) / 2;//For finding mid

            mergesort_test(arr, left, mid);//Recursive call on the left side of the array
            mergesort_test(arr, mid + 1, right);//Recursive call on the right side of the array

            merge_test(arr, left, mid, right);//Calling the merge function which sorts and merges the arrays back.
        }
    }
    Friend_node* merge(Friend_node* left, Friend_node* right)//More efficient merge and merge sort functions.
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->data.name < right->data.name)//Here we check whose name data value is smaller, then entering it first into our array.
        {
            left->next = merge(left->next, right);//Recursively calling left side and returning the smallest value on the end(next node is NULL) node.
            return left;//Giving the value in when left or right is nullptr.
        }
        else
        {
            right->next = merge(left, right->next);//Calling recursively merge function on the left and right of halves of our Friend_node array.
            return right; //returning right value as it is smaller
        }
    }

    Friend_node* mergesort(Friend_node* head)
    {
        if (!head || !head->next)//This conditon satisfies that we atleast have two nodes.
            return head;

        Friend_node* slow = head; //This is used for starting sorting and merging from head.
        Friend_node* fast = head->next;//This is used for starting sorting and merging from the node next to head.

        while (fast && fast->next) //For traversal
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        Friend_node* mid = slow->next; //We initialize mid here.
        slow->next = nullptr;//The mid is currently declared as nullptr here.

        Friend_node* left = mergesort(head);//This is used for recursive call on head pointer
        Friend_node* right = mergesort(mid);//This is used for recursive call on mid pointer.

        return merge(left, right);
    }
    void displayingfriends()//Added newly updated and simplified merge sort function for displaying, as it doesnot create temporary arrays anymore.
    {
        head = mergesort(head);// Sort the linked list directly using the updated mergesort function.
        cout << "Friend List :\n";
        Friend_node* current = head;
        while (current)
        {
            //Printing friend details in alphabetical order.
            cout << "Name: " << current->data.name
                << ", Friendship Level: " << current->data.friendshipLevel << endl;
            current = current->next;//Traversal logic for the sorted linked list.
        }
    }
    bool isFriend(const string& name)
    {
        Friend_node* current = head; //Start from head node.
        while (current)
        {
            if (current->data.name == name)//Main condition used to check whether a specific user is friend then their name will be present in the Friend_node struct.
            {
                return true;//return true as if name matches and found in Friend_node.
            }
            current = current->next;//To perform traversal here.
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

        queuenode(string n) :name(n), next(nullptr) {}
    };

    queuenode* front; //keeping track of both front and rear
    queuenode* rear;

public:
    Friend_queue() :front(nullptr), rear(nullptr) {} //Initializing the values

    void enqueue(string name) //Enqueue function with base condition handling insertin at the rear end.
    {
        queuenode* newNode = new queuenode(name);
        if (!rear) //base conditon.
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    string dequeue() // Dequeue function returning the friend's name
{
    if (!front)
    {
        cout << "No friend requests to process.\n";
        return ""; // Return an empty string if the queue is empty
    }

    queuenode* temp = front;
    string name = temp->name; // Retrieve the name of the friend
    front = front->next;      // Move front ahead

    if (!front) // Update rear if the queue becomes empty
        rear = nullptr;

    delete temp; // Delete the dequeued node
    return name; // Return the dequeued friend's name
}


    void displayrequests() //Displaying all the requests here.
    {
        queuenode* current = front;
        cout << "Friend Requests:\n";
        while (current)
        {
            cout << "- " << current->name << endl;
            current = current->next; //Traversal machnism.
        }
    }
};

class Blocked_friends
{
    struct Stack_node
    {
        string name;
        Stack_node* next;
        Stack_node(string n) : name(n), next(nullptr) {}
    };

    Stack_node* top;       // Main stack for blocked friends
    Stack_node* undoTop;   // Stack for undo history

public:
    Blocked_friends() : top(nullptr), undoTop(nullptr) {}

    void push(string name)
    {
        Stack_node* newnode = new Stack_node(name);
        newnode->next = top;
        top = newnode;

        // Record this block operation in the undo stack
        Stack_node* undoNode = new Stack_node(name);
        undoNode->next = undoTop;
        undoTop = undoNode;
    }

    void pop()
    {
        if (top)
        {
            Stack_node* temp = top;
            top = top->next;
            delete temp;
        }
        else
        {
            cout << "No users to unblock." << endl;
        }
    }

    string top_value()
    {
        if (!top)
        {
            return "";
        }
        return top->name;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    bool is_Blocked(const string& name)
    {
        Stack_node* current = top;
        while (current)
        {
            if (current->name == name)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    string* get_blocked_friends(int& count)
    {
        count = get_blocked_friends_count();
        if (count == 0)
        {
            return nullptr;
        }
        string* blocked_friends = new string[count];
        Stack_node* current = top;
        int index = 0;

        while (current)
        {
            blocked_friends[index++] = current->name;
            current = current->next;
        }

        return blocked_friends;
    }

    int get_blocked_friends_count()
    {
        int count = 0;
        Stack_node* current = top;
        while (current)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    void undo_block()
    {
        if (!undoTop)
        {
            cout << "No block action to undo." << endl;
            return;
        }

        string nameToUnblock = undoTop->name;

        // Remove from the undo stack
        Stack_node* tempUndo = undoTop;
        undoTop = undoTop->next;
        delete tempUndo;

        // Remove from the main stack of blocked friends
        if (top && top->name == nameToUnblock)
        {
            pop();
        }
        else
        {
            Stack_node* current = top;
            Stack_node* prev = nullptr;

            while (current)
            {
                if (current->name == nameToUnblock)
                {
                    if (prev)
                    {
                        prev->next = current->next;
                    }
                    else
                    {
                        top = current->next;
                    }
                    delete current;
                    break;
                }
                prev = current;
                current = current->next;
            }
        }

        cout << "Undo successful: Unblocked " << nameToUnblock << endl;
    }
};

struct AVLTree
{
    struct Node
    {
        Friend data;
        Node* left;
        Node* right;
        int height;
        Node(Friend f) :data(f), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;
    int height(Node* n)
    {
        return n ? n->height : 0;
    }
    int get_balance(Node* n)
    {
        return n ? height(n->left) - height(n->right) : 0;
    }
    Node* rotateright(Node* y)
    {
        Node* x = y->left;
        Node* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    Node* rotateleft(Node* x)
    {
        Node* y = x->right;
        Node* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;

    }
    int balancefactor_updated(Node* n)
    {
        return n ? height(n->left) - height(n->right) : 0;
    }
    Node* insert(Node* node, Friend f)
    {
        if (!node)//our base contion to exist recursion.
            return new Node(f);//Creating a new node at edge to a leaf node.

        if (f.friendshipLevel < node->data.friendshipLevel)
            node->left = insert(node->left, f);//This logic implies for traversal through left subtree.
        else if (f.friendshipLevel > node->data.friendshipLevel)//This logic implies for travesal through right subtree.
            node->right = insert(node->right, f);
        else
            return node;
        node->height = max(height(node->left), height(node->right)) + 1;//updating the height after the node insertion.
        int balance = balancefactor_updated(node);//Getting the new balance factor to check for imbalance.

        if (balance > 1 && f.friendshipLevel < node->left->data.friendshipLevel)
            return rotateright(node);//This implies for LL rotation.(As right child of right subtree(of root with imbalance) is imbalanced with right heavy condition).

        if (balance<-1 && f.friendshipLevel>node->right->data.friendshipLevel)
            return rotateleft(node);//This implies for RR rotaion.(As left child of left subtree(of root with imbalance) is imbalanced with left heavy condition).

        if (balance > 1 && f.friendshipLevel > node->left->data.friendshipLevel)
        {
            node->left = rotateleft(node->left);//First applying left rotation on the left subtree of root where the imbalance appears.
            return rotateright(node);//This here implies for LR rotaion
        }

        if (balance < -1 && f.friendshipLevel < node->right->data.friendshipLevel)
        {
            node->right = rotateright(node->right);//First applying right rotation on the right subtree of root where the imbalance appears.
            return rotateleft(node);//This here implies for RL rotation.
        }
        return node;//Returning node here.
    }

    void inOrder(Node* root)//For displaying names with highest friendship level first.
    {
        if (root)
        {
            inOrder(root->left);//recursion for traversing first into the deepest left most node.
            cout << "Name: " << root->data.name << ", Friendship Level: " << root->data.friendshipLevel << endl;//For displaying the friends levels.
            inOrder(root->right);//recursion for traversing after through the deepest right most node.
        }
    }
    AVLTree() :root(nullptr) {}
    void addfriend(Friend f)//for adding a new object friend of Friend type and inserting through interest level sequences.
    {
        root = insert(root, f);//This is for insert function 
    }
    void displayfriends()//This is for displaying all the names of friends with friendship levels through inorder traversal.
    {
        inOrder(root);//Inorder....traversal applied here.
    }
};

struct Graph {
    int num_of_users;          // Number of users (removed const)
    bool** matrix;             // Adjacency matrix
    string* names_of_users;    // User names

    // Custom Queue Implementation
    class Queue {
        int* arr;
        int front, rear, capacity;

    public:
        Queue(int size) : front(-1), rear(-1), capacity(size) {
            arr = new int[size];
        }

        ~Queue() {
            delete[] arr;
        }

        void enqueue(int val) {
            if (rear == capacity - 1) {
                cout << "Queue overflow\n";
                return;
            }
            if (front == -1) front = 0;
            arr[++rear] = val;
        }

        int dequeue() {
            if (front == -1 || front > rear) {
                cout << "Queue underflow\n";
                return -1;
            }
            return arr[front++];
        }

        bool isEmpty() {
            return front == -1 || front > rear;
        }
    };

    // Custom Stack Implementation
    class Stack {
        int* arr;
        int top, capacity;

    public:
        Stack(int size) : top(-1), capacity(size) {
            arr = new int[size];
        }

        ~Stack() {
            delete[] arr;
        }

        void push(int val) {
            if (top == capacity - 1) {
                cout << "Stack overflow\n";
                return;
            }
            arr[++top] = val;
        }

        int pop() {
            if (top == -1) {
                cout << "Stack underflow\n";
                return -1;
            }
            return arr[top--];
        }

        bool isEmpty() {
            return top == -1;
        }
    };

public:
    Graph(int number) : num_of_users(number) {
        matrix = new bool* [num_of_users];
        names_of_users = new string[num_of_users];
        for (int i = 0; i < num_of_users; ++i) {
            matrix[i] = new bool[num_of_users]();
        }
    }

    ~Graph() {
        for (int i = 0; i < num_of_users; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] names_of_users;
    }

    void settinguser(int index, string name) {
        if (index >= 0 && index < num_of_users) {
            names_of_users[index] = name;
        }
    }

    void addingconnections(int first_user, int second_user) {
        if (first_user >= 0 && first_user < num_of_users &&
            second_user >= 0 && second_user < num_of_users) {
            matrix[first_user][second_user] = matrix[second_user][first_user] = true;
        }
        else {
            cout << "Invalid user index. Connection not possible.\n";
        }
    }

    void displaying_all_connections() {
        cout << "Mutual Friend Connections:\n";
        for (int i = 0; i < num_of_users; ++i) {
            cout << names_of_users[i] << " -> ";
            for (int j = 0; j < num_of_users; ++j) {
                if (matrix[i][j]) {
                    cout << names_of_users[j] << " ";
                }
            }
            cout << endl;
        }
    }

    void suggesting_mutual_friends_bfs(int user_index) {
        if (user_index < 0 || user_index >= num_of_users) {
            cout << "Invalid user index.\n";
            return;
        }

        vector<bool> visited(num_of_users, false); // Use a vector for dynamic size
        Queue q(num_of_users);
        q.enqueue(user_index);
        visited[user_index] = true;

        cout << "Friend Suggestions for " << names_of_users[user_index] << " (BFS):\n";

        while (!q.isEmpty()) {
            int current = q.dequeue();

            for (int i = 0; i < num_of_users; ++i) {
                if (matrix[current][i] && !visited[i]) {
                    visited[i] = true;
                    q.enqueue(i);
                    if (!matrix[user_index][i] && i != user_index) {
                        cout << "- " << names_of_users[i] << endl;
                    }
                }
            }
        }
    }

    void suggesting_mutual_friends_dfs(int user_index) {
        if (user_index < 0 || user_index >= num_of_users) {
            cout << "Invalid user index.\n";
            return;
        }

        vector<bool> visited(num_of_users, false); // Use a vector for dynamic size
        Stack s(num_of_users);
        s.push(user_index);

        cout << "Friend Suggestions for " << names_of_users[user_index] << " (DFS):\n";

        while (!s.isEmpty()) {
            int current = s.pop();

            if (!visited[current]) {
                visited[current] = true;

                for (int i = 0; i < num_of_users; ++i) {
                    if (matrix[current][i] && !visited[i]) {
                        s.push(i);
                        if (!matrix[user_index][i] && i != user_index) {
                            cout << "- " << names_of_users[i] << endl;
                        }
                    }
                }
            }
        }
    }
};

class HashMap {
    struct Node {
        string key;        // Interest
        string value;      // Friend name
        Node* next;        // Pointer to the next node (for separate chaining)
        Node(string k, string v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;          // Array of pointers to linked lists
    int capacity;          // Size of the hash table
    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % capacity;  // Simple polynomial rolling hash
        }
        return hash;
    }

public:
    HashMap(int size) : capacity(size) {
        table = new Node * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            if (current) {
                cout << "Bucket " << i << ": ";
                while (current) {
                    cout << "(" << current->key << ", " << current->value << ") -> ";
                    current = current->next;
                }
                cout << "NULL\n";
            }
        }
    }

    void recommend(string interest) {
        int index = hashFunction(interest);
        Node* current = table[index];
        bool found = false;

        cout << "Friends with interest \"" << interest << "\":\n";
        while (current) {
            if (current->key == interest) {
                cout << "- " << current->value << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No friends found with the interest \"" << interest << "\".\n";
        }
    }
};


void displayMenu() {
    cout << "\n--- Social Network Menu ---\n";
    cout << "1. Add Friend to Friend List\n";
    cout << "2. Remove Friend from Friend List\n";
    cout << "3. Display Friend List\n";
    cout << "4. Add Friend Request\n";
    cout << "5. Process Friend Request\n";
    cout << "6. Display Friend Requests\n";
    cout << "7. Block a User\n";
    cout << "8. Undo Block\n";
    cout << "9. Display Blocked Users\n";
    cout << "10. Add Friend to AVL Tree\n";
    cout << "11. Display Friends in AVL Tree\n";
    cout << "12. Add User to Graph\n";
    cout << "13. Add Connection in Graph\n";
    cout << "14. Display Connections in Graph\n";
    cout << "15. Suggest Friends (BFS)\n";
    cout << "16. Suggest Friends (DFS)\n";
    cout << "17. Add Interest to Hash Map\n";
    cout << "18. Recommend Friends by Interest\n";
    cout << "19. Save to File\n";
    cout << "20. Load from File\n";
    cout << "0. Exit\n";
}

void saveToFile(Graph& graph, Friend_list& friendList) {
    ofstream userFile("user_save.txt");
    ofstream friendFile("friend_save.txt");

    if (!userFile || !friendFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    // Save user data
    Friend_node* current = friendList.head;
    int index = 0;
    while (current) {
        userFile << index << " " << current->data.name << " " << current->data.friendshipLevel << " "
            << current->data.interests[0] << " " << current->data.interests[1] << " " << current->data.interests[2] << "\n";
        current = current->next;
        index++;
    }

    // Save friend connections
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (graph.matrix[i][j]) {
                friendFile << i << " " << j << "\n";
            }
        }
    }

    cout << "Data successfully saved to files.\n";
}

void loadFromFile(Graph& graph, Friend_list& friendList, AVLTree& avlTree) {
    ifstream userFile("users.txt");
    ifstream friendFile("friends.txt");

    if (!userFile || !friendFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    // Load user data
    string line;
    while (getline(userFile, line)) {
        size_t firstSpace = line.find(' ');
        size_t secondSpace = line.find(' ', firstSpace + 1);
        size_t thirdSpace = line.find(' ', secondSpace + 1);
        size_t fourthSpace = line.find(' ', thirdSpace + 1);
        size_t fifthSpace = line.find(' ', fourthSpace + 1);

        if (firstSpace != string::npos && secondSpace != string::npos &&
            thirdSpace != string::npos && fourthSpace != string::npos && fifthSpace != string::npos) {
            int index = stoi(line.substr(0, firstSpace)); // Extract index
            string name = line.substr(firstSpace + 1, secondSpace - firstSpace - 1); // Extract name
            int friendshipLevel = stoi(line.substr(secondSpace + 1, thirdSpace - secondSpace - 1)); // Extract friendship level
            string interest1 = line.substr(thirdSpace + 1, fourthSpace - thirdSpace - 1); // Extract first interest
            string interest2 = line.substr(fourthSpace + 1, fifthSpace - fourthSpace - 1); // Extract second interest
            string interest3 = line.substr(fifthSpace + 1); // Extract third interest

            graph.settinguser(index, name);
            friendList.addingfriend({ name, friendshipLevel, {interest1, interest2, interest3} });
            avlTree.addfriend({ name, friendshipLevel, {interest1, interest2, interest3} });
        }
    }

    // Load friend connections
    int user1, user2;
    while (friendFile >> user1 >> user2) {
        graph.addingconnections(user1, user2);
    }

    cout << "Data successfully loaded from files.\n";
}

int main() {
    Friend_list friendList;
    Friend_queue friendQueue;
    Blocked_friends blocked;
    AVLTree avlTree;
    Graph graph(5);
    HashMap hashMap(10);

    int userCounter = 0; // Counter to track the next available index for adding users

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore newline character

        switch (choice) {
        case 1: {
            string name;
            int level;
            string interests[3];
            cout << "Enter Friend Name: ";
            getline(cin, name);
            cout << "Enter Friendship Level: ";
            cin >> level;
            cin.ignore();
            for (int i = 0; i < 3; i++) {
                cout << "Enter Interest " << (i + 1) << ": ";
                getline(cin, interests[i]);
            }
            friendList.addingfriend({ name, level, {interests[0], interests[1], interests[2]} });
            avlTree.addfriend({ name, level, {interests[0], interests[1], interests[2]} });
            break;
        }
        case 2: {
            string name;
            cout << "Enter Friend Name to Remove: ";
            getline(cin, name);
            friendList.removingfriend(name);
            break;
        }
        case 3:
            friendList.displayingfriends();
            break;
        case 4: {
            string name;
            cout << "Enter Friend Request Name: ";
            getline(cin, name);
            friendQueue.enqueue(name);
            break;
        }
       case 5: {
    string friendName = friendQueue.dequeue(); // Get the dequeued friend's name
    if (friendName.empty()) { // Check if the queue was empty
        cout << "No friend requests to process.\n";
    } else {
        cout << "Processing friend request from: " << friendName << "\n";
        friendList.addingfriend({friendName, 1, {"Default1", "Default2", "Default3"}}); // Add to friend list
        if (userCounter < 5) {
            graph.settinguser(userCounter, friendName);
            cout << "User added to graph at index " << userCounter << ".\n";
            userCounter++;
        } else {
            cout << "Graph is full. User added only to friend list.\n";
        }
    }
    break;
}



        case 6:
            friendQueue.displayrequests();
            break;
        case 7: {
            string name;
            cout << "Enter User to Block: ";
            getline(cin, name);
            blocked.push(name);
            break;
        }
        case 8:
            blocked.undo_block();
            break;
        case 9: {
            int blockedCount = 0;
            string* blockedList = blocked.get_blocked_friends(blockedCount);
            if (blockedList) {
                cout << "Blocked Users:\n";
                for (int i = 0; i < blockedCount; i++) {
                    cout << "- " << blockedList[i] << endl;
                }
                delete[] blockedList;
            }
            else {
                cout << "No blocked users.\n";
            }
            break;
        }
        case 10: {
            string name;
            int level;
            string interests[3];
            cout << "Enter Friend Name: ";
            getline(cin, name);
            cout << "Enter Friendship Level: ";
            cin >> level;
            cin.ignore();
            for (int i = 0; i < 3; i++) {
                cout << "Enter Interest " << (i + 1) << ": ";
                getline(cin, interests[i]);
            }
            avlTree.addfriend({ name, level, {interests[0], interests[1], interests[2]} });
            break;
        }
        case 11:
            avlTree.displayfriends();
            break;
        case 12: {
            if (userCounter >= 5) {
                cout << "Graph is full. Cannot add more users.\n";
            }
            else {
                string name;
                cout << "Enter User Name: ";
                getline(cin, name);
                graph.settinguser(userCounter, name);
                cout << "User added at index " << userCounter << ".\n";
                userCounter++;
            }
            break;
        }
        case 13: {
            int user1, user2;
            cout << "Enter First User Index: ";
            cin >> user1;
            cout << "Enter Second User Index: ";
            cin >> user2;
            graph.addingconnections(user1, user2);
            break;
        }
        case 14:
            graph.displaying_all_connections();
            break;
        case 15: {
            int user_index;
            cout << "Enter User Index: ";
            cin >> user_index;
            graph.suggesting_mutual_friends_bfs(user_index);
            break;
        }
        case 16: {
            int user_index;
            cout << "Enter User Index: ";
            cin >> user_index;
            graph.suggesting_mutual_friends_dfs(user_index);
            break;
        }
        case 17: {
            string interest, name;
            cout << "Enter Interest: ";
            getline(cin, interest);
            cout << "Enter Name: ";
            getline(cin, name);
            hashMap.insert(interest, name);
            break;
        }
        case 18: {
            string interest;
            cout << "Enter Interest: ";
            getline(cin, interest);
            hashMap.recommend(interest);
            break;
        }
        case 19:
            saveToFile(graph, friendList);
            break;
        case 20:
            loadFromFile(graph, friendList, avlTree);
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

//int main() {
//    // Test Friend List functionality
//    Friend_list friendList;
//    Friend friend1 = { "Charlie", 5, {"Gaming", "Coding", "Music"} };
//    Friend friend2 = { "Diana", 7, {"Cooking", "Dancing", "Traveling"} };
//    Friend friend3 = { "Eve", 3, {"Reading", "Hiking", "Swimming"} };
//
//    friendList.addingfriend(friend1);
//    friendList.addingfriend(friend2);
//    friendList.addingfriend(friend3);
//
//    cout << "--- Friend List (Sorted) ---\n";
//    friendList.displayingfriends();
//
//    // Remove a friend
//    friendList.removingfriend("Diana");
//    cout << "--- Friend List After Removing Diana ---\n";
//    friendList.displayingfriends();
//
//    // Test Friend Queue functionality
//    Friend_queue friendQueue;
//    friendQueue.enqueue("Charlie");
//    friendQueue.enqueue("Eve");
//    friendQueue.enqueue("Bob");
//
//    cout << "--- Friend Requests ---\n";
//    friendQueue.displayrequests();
//    friendQueue.dequeue();
//    cout << "--- Friend Requests After Processing ---\n";
//    friendQueue.displayrequests();
//
//    // Test Blocked Friends functionality
//    Blocked_friends blocked;
//    blocked.push("Alice");
//    blocked.push("Charlie");
//    blocked.push("Diana");
//
//    cout << "--- Blocked Friends List ---\n";
//    int blockedCount = 0;
//    string* blockedList = blocked.get_blocked_friends(blockedCount);
//    for (int i = 0; i < blockedCount; i++) {
//        cout << "- " << blockedList[i] << endl;
//    }
//    delete[] blockedList;
//
//    // Undo blocking
//    blocked.undo_block();
//    cout << "--- Blocked Friends After Undo ---\n";
//    blockedList = blocked.get_blocked_friends(blockedCount);
//    for (int i = 0; i < blockedCount; i++) {
//        cout << "- " << blockedList[i] << endl;
//    }
//    delete[] blockedList;
//
//    // Test AVL Tree functionality
//    AVLTree avlTree;
//    avlTree.addfriend(friend1);
//    avlTree.addfriend(friend2);
//    avlTree.addfriend(friend3);
//
//    cout << "--- AVL Tree Friends (Sorted by Friendship Level) ---\n";
//    avlTree.displayfriends();
//
//    // Test Graph functionality
//    Graph graph(5);
//    graph.settinguser(0, "Alice");
//    graph.settinguser(1, "Bob");
//    graph.settinguser(2, "Charlie");
//    graph.settinguser(3, "Diana");
//    graph.settinguser(4, "Eve");
//
//    graph.addingconnections(0, 1);
//    graph.addingconnections(1, 2);
//    graph.addingconnections(2, 3);
//    graph.addingconnections(3, 4);
//
//    cout << "--- Mutual Friend Connections ---\n";
//    graph.displaying_all_connections();
//
//    cout << "--- Friend Suggestions for Alice (BFS) ---\n";
//    graph.suggesting_mutual_friends_bfs(0);
//
//    cout << "--- Friend Suggestions for Alice (DFS) ---\n";
//    graph.suggesting_mutual_friends_dfs(0);
//
//    // Test HashMap functionality
//    HashMap hashMap(10);
//    vector<string> interests = { "Reading", "Cooking", "Gaming", "Traveling", "Music" };
//    hashMap.insert("Reading", "Alice");
//    hashMap.insert("Gaming", "Charlie");
//    hashMap.insert("Cooking", "Diana");
//    hashMap.insert("Traveling", "Bob");
//
//    cout << "--- Hash Map Contents ---\n";
//    hashMap.display();
//
//    cout << "--- Recommendations for 'Gaming' ---\n";
//    hashMap.recommend("Gaming");
//
//    cout << "--- Recommendations for 'Dancing' ---\n";
//    hashMap.recommend("Dancing");
//
//    return 0;
//}