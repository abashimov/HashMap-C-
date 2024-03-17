#include<iostream>
#include<vector>
using namespace std;

class HashMap{
    // Internal structure representing a node in the hash map
    struct Node{
        int key;        // Key of the node
        string value;   // Value associated with the key
        Node* next;     // Pointer to the next node in case of collisions
        
        // Constructor to initialize the node
        Node(int k, string v){
            key = k;
            value = v;
            next = nullptr;
        }
    };
    
    vector<Node*> buckets;  // Vector of buckets to store the nodes
    int size;               // Size of the hash map
    
public:
    // Constructor to initialize the hash map
    HashMap(){
        size = 100; // Initial size of the hash map
        buckets = vector<Node*>(size, nullptr); // Initialize buckets with nullptr
    }
    
    // Function to calculate hash value for a given key
    int hash(int key){
        return key % size;
    }
    
    // Function to insert a key-value pair into the hash map
    void insert(int key, string value) {
        int index = hash(key);  // Calculate index using hash function
        Node* newNode = new Node(key, value);  // Create a new node
        
        // If the bucket is empty, insert the new node
        if (!buckets[index]) {
            buckets[index] = newNode;
        } else {
            // Handle collision by traversing the linked list
            Node* curr = buckets[index];
            while (curr->next) {
                // If key already exists, update the value and return
                if (curr->key == key) {
                    curr->value = value;
                    delete newNode;
                    return;
                }
                curr = curr->next;
            }
            // Insert the new node at the end of the linked list
            curr->next = newNode;
        }
    }

    // Function to retrieve the value associated with a given key
    string get(int key){
        int index = hash(key);
        Node* curr = buckets[index];
        while(curr){
            if(curr->key==key){
                return curr->value;
            }
            curr = curr->next;
        }
        return ""; // Return empty string if key is not found
    }
    
    // Function to remove a key-value pair from the hash map
    void remove(int key){
        int index = hash(key);
        Node* curr = buckets[index];
        Node* prev = nullptr;
        while(curr){
            if(curr->key==key){
                // If the node to be removed is not the head of the linked list
                if(prev){
                    prev->next = curr->next;
                }else{ // If the node to be removed is the head of the linked list
                    buckets[index] = curr->next;
                }
                delete curr; // Delete the node
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};

int main() {
    // Create an instance of HashMap
    HashMap hashMap;

    // Insert key-value pairs
    hashMap.insert(1, "10");
    hashMap.insert(2, "20");
    hashMap.insert(3, "30");

    // Retrieve values using keys
    cout << "Value for key 1: " << hashMap.get(1) << endl;
    cout << "Value for key 2: " << hashMap.get(2) << endl;
    cout << "Value for key 3: " << hashMap.get(3) << endl;

    // Try to retrieve a non-existent key
    cout << "Value for key 4: " << hashMap.get(4) << endl;

    // Update the value for an existing key
    hashMap.insert(2, "25");
    cout << "Updated value for key 2: " << hashMap.get(2) << endl;

    // Remove a key-value pair
    hashMap.remove(2);
    cout << "Value for key 2 after removal: " << hashMap.get(2) << endl;

    // Try to retrieve a removed key
    cout << "Value for key 2 (after removal): " << hashMap.get(2) << endl;

    return 0;
}
