//**********************************************************************//
// Algorithms and data structures - Assignment 2						            //
// Submission Date: 28th March 2014										                  //
// Author: Alexandre Benoit (ab7012)									                  //
// Purpose:	Code operates using functions/procedures on a binary tree	  //
//**********************************************************************//

// List of functions to implement:
// 1. Returns total number of nodes in the binary tree
// 2. Returns the number of node with even data fields
// 3. Returns pointer to the node containing the maximum value
// 4. Returns the height of the binary tree
// 5. Returns if the binary tree is sorted or not

#include <iostream>

using namespace std;

// The structure to store each node of the tree is defined as follows:
struct CP {
	int id;			// ID of the Node
	int data;		// Positive Integer Data Value
	CP * left;		// Pointer to the Left Sub-tree
	CP * right;		// Pointer to the Right Sub-tree
};

typedef CP * CPPtr;

// Function Declaration
void constructStructure(CPPtr &hdTree);					// builds the tree
int number_nodes(CPPtr hdTree);							// returns the total number of nodes
int even_data(CPPtr hdTree);							// returns the number of nodes with even data values
CPPtr max_value(CPPtr hdTree);							// returns a pointer to the node with the highest data value
int height_tree(CPPtr hdTree);							// returns the height of the binary tree
bool ordered_check(CPPtr hdTree, int min, int max);		// returns if the binary tree is sorted or not


int main()
{
	// Declare a pointer to the head of the tree
	CPPtr hdTree = NULL, maximum_node = NULL;
	int nb_nodes, nb_even_data, height;

	// Construct the tree structure
	constructStructure(hdTree);

	// Calculate the total number of nodes in the tree and print in console
	nb_nodes = number_nodes(hdTree);
	cout << "The number of nodes is: " << nb_nodes << "." << endl;

	// Calculate the number of nodes with even data values
	nb_even_data = even_data(hdTree);
	cout << "The number of nodes whose data field is even is: " << nb_even_data << "." <<endl;

	// Calculates the maximum data value and ID of the node it is stored in
	maximum_node = max_value(hdTree);
	cout << "The maximum value of the tree is: " << maximum_node->data << " in node with ID: " << maximum_node->id << "." << endl;

	// Calculates the height of the binary tree
	height = height_tree(hdTree);
	cout << "The height of the tree is: " << height << "." << endl;

	// Determines if the binary tree is sorted or not
	if (ordered_check(hdTree, 1, 200) == true) cout << "The binary tree is ordered." << endl;
	else if (ordered_check(hdTree, 1, 200) == false) cout << "The binary tree is not ordered." << endl;
	else cout << "Error in determining if the tree is sorted..." << endl;

	cout << endl << "Press ENTER to terminate... ";
	cin.get(); // freezes console window

	return 0;
}

// This function generates an instance of the structure. The SP pointer points to the head of the tree
void constructStructure(CPPtr &SP){
	// Declare a structure with 5 nodes
	/*CPPtr SP0 = NULL;

	// Build the structure tree
	// State 0
	SP0 = new CP;
	SP0->id = 1;
	SP0->data = 12;
	SP0->left = NULL;
	SP0->right = NULL;

	// Make the head pointer to point to the head of the tree
	SP = SP0;
	*/
}

// This function returns the number of nodes in the tree
int number_nodes(CPPtr hdTree){
	if (hdTree != NULL) {	// checks if the node exists
			return (number_nodes(hdTree->left) + number_nodes(hdTree->right) + 1);
		}					// using recursion, add the size of the left and right sub-trees and then add 1 for the current node
	return 0;
}

// This function returns the number of nodes in the structure whose data field is even
int even_data(CPPtr hdTree){
	if (hdTree != NULL) {	// checks if the node exists
		if (hdTree->data % 2 == 0)
			return even_data(hdTree->left) + even_data(hdTree->right) + 1;
		else				// add the size of the left and right sub-trees and then add 1 for the current node
			return even_data(hdTree->left) + even_data(hdTree->right) + 0;
	}
	return 0;
}

//This function returns a pointer to the node containing the maximum data value
CPPtr max_value(CPPtr hdTree){
	if (hdTree != NULL) {
		CPPtr right_max = NULL, left_max = NULL;
		right_max = new CP;
		left_max = new CP;

		// Special case: No children
		if (hdTree->left == NULL && hdTree->right == NULL)
			return hdTree;

		// Gets, using recursion, the max value from the sub-trees with hdTree->left and hdTree->right as roots
		if (hdTree->left != NULL)
			left_max = max_value(hdTree->left);
		if (hdTree->right != NULL)
			right_max = max_value(hdTree->right);

		// Return right_max if it's the largest
		if (right_max->data >= left_max->data && right_max->data >= hdTree->data)
			return right_max;
		// Return left_max if it's the largest
		else if (left_max->data >= right_max->data && left_max->data >= hdTree->data)
			return left_max;
		// Or else returns the current node's value as it is the biggest
		else return hdTree;
	}
	return NULL;
}

// This function returns the height of the tree
int height_tree(CPPtr hdTree){
	if (hdTree != NULL) {
		if (hdTree->left != NULL || hdTree->right != NULL){ // necessary as height on 1 node tree is 0
			int left_height = height_tree(hdTree->left);	// calculates using recursion the height of the left sub-tree
			int right_height = height_tree(hdTree->right); // calculates using recursion the height of the right sub-tree
			if (left_height > right_height) return left_height + 1; // returns the largest between the two, plus one for the root
			else return right_height + 1;
		}
		return 0;
	}
}

// This function evaluates if the binary tree is sorted or not
bool ordered_check(CPPtr hdTree, int min, int max) {
	if (hdTree == NULL)  // we use the min and max values to keep track of the upper and lower boundaries of the sub-trees
		return true;	 // ...as looking at the children is not enough
	if (hdTree->data > min && hdTree->data < max){	// we use recursion to check that all the nodes are sorted, the new min or max is passed as argument
		if (ordered_check(hdTree->left, min, hdTree->data) && ordered_check(hdTree->right, hdTree->data, max))
			return true; // if all the child nodes respect the min and max boundaries even as they get closer together, the binary tree is sorted
	}
	return false;		 // else, the function returns false to say it is not sorted
}
