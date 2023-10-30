// BST implementation using linked list
#include <iostream>
using namespace std;

// Structure for node of tree
struct node
{
    int data;
    node *left = nullptr;
    node *right = nullptr;
};
node *root = nullptr;

// Function prototypes
int menu(void);
void insertTree(int value);
void deleteTree(int value);
void preTraverse(node *current);
void inTraverse(node *current);
void postTraverse(node *current);
void freeTree(node *current);


int main(void)
{
    int value; // This will be used during insertion and deletion

    while (true)
    {
        int choice = menu();

        switch (choice)
        {
            case 1:
                cout << endl << "Enter the element to be inserted: ";
                cin >> value;

                insertTree(value);

                break;

            case 2:
                cout << endl << "Enter the value of the node to delete: ";
                cin >> value;

                deleteTree(value);

                break;

            case 3:
				if (root == nullptr)
				{
					cout << endl << "Tree is empty" << endl;
					break;
				}
				
                cout << endl;
                preTraverse(root);
                cout << endl;

                break;

            case 4:
				if (root == nullptr)
				{
					cout << endl << "Tree is empty" << endl;
					break;
				}

                cout << endl;
                inTraverse(root);
                cout << endl;
                
                break;

            case 5:
				if (root == nullptr)
				{
					cout << endl << "Tree is empty" << endl;
					break;
				}

                cout << endl;
                postTraverse(root);
                cout << endl;

                break;

            case 6:
                freeTree(root);
                return 0;
        }
    }
}


// Function to take choice of user
int menu(void)
{
    cout << endl << "Enter your choice:" << endl
         << "1. Insert" << endl
         << "2. Delete" << endl
         << "3. Preorder Traversal" << endl
         << "4. Inorder Traversal" << endl
         << "5. Postorder Traversal" << endl
         << "6. Exit" << endl;
    
    int choice;
    cin >> choice;

    return choice;
}


// Function to insert node
void insertTree(int value)
{
    node *newNode = new node;
    newNode->data = value;

	// If the node is root node
    if (root == nullptr)
    {
        root = newNode;
        return;
    }

    // Finding the location of parent to insert
	node *parent = nullptr;
    node *curr = root;
    while (curr != nullptr)
	{
		parent = curr;
		if (value < curr->data)
			curr = curr->left;
		else
			curr = curr->right;
	}

	// Inserting the node
	if (value < parent->data)
		parent->left = newNode;
	else
		parent->right = newNode;
}


// Function to delete the given valued node
void deleteTree(int value)
{
    if (root == nullptr) // Checking if tree is empty
    {
        cout << endl << "Tree is empty" << endl;
        return;
    }

	// Finding the node to delete
	node *pred = nullptr;
	node *curr = root;
	while (curr != nullptr)
	{
		if (value == curr->data)
			break;

		pred = curr;

		if (value < curr->data)
			curr = curr->left;
		else
			curr = curr->right;
	}

	// Node is not found
	if (curr == nullptr)
	{
		cout << endl << "Node not found" << endl;
		return;
	}

	// Root element is deleted
	if (pred == nullptr)
	{
		node *temp;
		if (curr->left == nullptr) // If only no child or only right child is present
			temp = curr->right;

		else if (curr->right == nullptr) // If only left child is present
			temp = curr->left;

		else // Both the child are present
		{
			node *succ = curr->right;
			while (succ->left != nullptr)
				succ = succ->left;
			succ->left = curr->left;
			temp = curr->right;
		}

		// Assigning new root node
		root = temp;

		cout << endl << "The deleted element is " << curr->data << endl;
		delete curr;

	  	return;
	}

	// Finding the way to restructure tree
	node *temp; // Node attached in place of deleted node
	if (curr->left == nullptr) // If only no child or only right child is present
		temp = curr->right;

	else if (curr->right == nullptr) // If only left child is present
		temp = curr->left;

	else // Both the child are present
	{
		node *succ = curr->right;
		while (succ->left != nullptr)
			succ = succ->left;
		succ->left = curr->left;
		temp = curr->right;
	}

	// Assigning new node to parent of deleted node
	if (curr == pred->left)
		pred->left = temp;
	else
		pred->right = temp;

	cout << endl << "The deleted element is " << curr->data << endl;
	delete curr;
}


// Functions for traversal
void preTraverse(node *current)
{
    if (current == nullptr)
        return;

    cout << current->data << " ";
    preTraverse(current->left);
    preTraverse(current->right);
}

void inTraverse(node *current)
{
    if (current == nullptr)
        return;
        
    inTraverse(current->left);
    cout << current->data << " ";
    inTraverse(current->right);
}

void postTraverse(node *current)
{
    if (current == nullptr)
        return;
        
    postTraverse(current->left);
    postTraverse(current->right);
    cout << current->data << " ";
}


// Function to free the memory allocated before quitting
void freeTree(node *current)
{
    if (current == nullptr)
        return;

    freeTree(current->left);
    freeTree(current->right);
    delete current;
}
