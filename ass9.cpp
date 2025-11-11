#include <iostream>
#include <string>
#include <algorithm> // Required for std::max
#include <limits> // Required for numeric_limits
using namespace std;
struct Node {
string keyword;
string meaning;
Node* leP;
Node* right;
Node(string k, string m) {
keyword = k;
meaning = m;
leP = right = nullptr;
}
// Simple destructor
~Node() {}
};
class Dic&onaryBST {
private:
Node* root;
// Helper func&on to free memory
void destroyTree(Node* node) {
if (node) {
destroyTree(node->leP);
destroyTree(node->right);
delete node;
}
}
Node* insert(Node* root, string key, string meaning) {
if (!root) {
return new Node(key, meaning);
}
if (key < root->keyword) {
root->leP = insert(root->leP, key, meaning);
} else if (key > root->keyword) {
root->right = insert(root->right, key, meaning);
} else {
// Duplicate keyword, update meaning
root->meaning = meaning;
}
return root;
}
Node* findMin(Node* root) {
while (root && root->leP != nullptr)
root = root->leP;
return root;
}
Node* deleteNode(Node* root, string key) {
if (!root) return nullptr;
if (key < root->keyword) {
root->leP = deleteNode(root->leP, key);
} else if (key > root->keyword) {
root->right = deleteNode(root->right, key);
} else {
// Node found
if (!root->leP) {
Node* temp = root->right;
delete root;
return temp;
} else if (!root->right) {
Node* temp = root->leP;
delete root;
return temp;
}
// Node with two children: Get the inorder successor (smallest in the right subtree)
Node* temp = findMin(root->right);
root->keyword = temp->keyword;
root->meaning = temp->meaning;
// Delete the inorder successor
root->right = deleteNode(root->right, temp->keyword);
}
return root;
}
void inorder(Node* root) {
if (root) {
inorder(root->leP);
cout << root->keyword << " : " << root->meaning << endl;
inorder(root->right);
}
}
void reverseInorder(Node* root) {
if (root) {
reverseInorder(root->right);
cout << root->keyword << " : " << root->meaning << endl;
reverseInorder(root->leP);
}
}
Node* search(Node* root, string key) {
if (!root || root->keyword == key)
return root;
if (key < root->keyword)
return search(root->leP, key);
else
return search(root->right, key);
}
int height(Node* root) {
if (!root) return 0;
int lh = height(root->leP);
int rh = height(root->right);
return max(lh, rh) + 1;
}
public:
Dic&onaryBST() { root = nullptr; }
// Destructor to clean up memory
~Dic&onaryBST() {
destroyTree(root);
}
void add(string key, string meaning) {
root = insert(root, key, meaning);
}
// FIX: Explicitly check for existence and provide feedback.
void deleteKey(string key) {
Node* result = search(root, key);
if (result) {
root = deleteNode(root, key);
cout << "Keyword \"" << key << "\" deleted.\n";
} else {
cout << "Keyword \"" << key << "\" not found for dele&on.\n";
}
}
void updateMeaning(string key, string newMeaning) {
Node* node = search(root, key);
if (node) {
node->meaning = newMeaning;
cout << "Meaning updated for keyword \"" << key << "\".\n";
} else {
cout << "Keyword not found.\n";
}
}
void displayAscending() {
cout << "\n--- Dic&onary in Ascending order ---\n";
inorder(root);
cout << "-------------------------------------\n";
}
void displayDescending() {
cout << "\n--- Dic&onary in Descending order ---\n";
reverseInorder(root);
cout << "--------------------------------------\n";
}
void maxComparisons() {
int h = height(root);
cout << "Maximum comparisons required to find any keyword (Height of BST): " << h << endl;
}
};
int main() {
Dic&onaryBST dict;
int choice;
string key, meaning;
do {
cout << "\n==============================\n";
cout << "Dic&onary Opera&ons:\n";
cout << "1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Display Ascending\n5.
Display Descending\n6. Max Comparisons\n7. Exit\n";
cout << "Enter choice: ";
if (!(cin >> choice)) {
// Handle non-integer input gracefully
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
choice = 0; // Set to invalid to con&nue loop
}
characters
cin.ignore(numeric_limits<streamsize>::max(), '\n'); // to ignore lePover newline and any extra
switch (choice) {
case 1:
cout << "Enter keyword: ";
getline(cin, key);
cout << "Enter meaning: ";
getline(cin, meaning);
dict.add(key, meaning);
cout << "Keyword added/updated.\n";
break;
case 2:
cout << "Enter keyword to delete: ";
getline(cin, key);
dict.deleteKey(key);
break;
case 3:
cout << "Enter keyword to update: ";
getline(cin, key);
cout << "Enter new meaning: ";
getline(cin, meaning);
dict.updateMeaning(key, meaning);
break;
case 4:
dict.displayAscending();
break;
case 5:
dict.displayDescending();
break;
case 6:
dict.maxComparisons();
break;
case 7:
cout << "Exi&ng...\n";
break;
default:
cout << "Invalid choice!\n";
}
} while (choice != 7);
return 0;
}
