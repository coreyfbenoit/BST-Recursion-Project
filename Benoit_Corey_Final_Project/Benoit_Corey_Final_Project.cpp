/*
 * Corey Benoit
 * Final Project
 * Data Structures & Algorithms
 * 12/3/2019
 */

#include <iostream>
#include<string>

struct starNode
{
	std::string name;
	double distance;
	struct starNode* leftChild,* rightChild;
};

// Prototypes
struct starNode* newNode(std::string name, double distance);
struct starNode* insert(struct starNode* node, std::string name, double distance);
struct starNode* deleteStar(struct starNode* root, double distance);
void printStars(struct starNode* root);
struct starNode* find(starNode* root, double distance);


int main()
{
	// Start star node tree
	struct starNode* root = NULL;
	root = insert(root, "Kypten's Star", 12.78);
	insert(root, "EZ Aquarii", 11.27);
	insert(root, "WISE 1541-225", 13.70);
	insert(root, "Wolf 359", 7.78);
	insert(root, "Tau Centi", 11.89);

	char choice;
	std::string name;
	double distance;

	// Describe program
	std::cout << "This program will sort a list of stars by their distance from the sun.";
	std::cout << "The user will be able to insert new stars and delete existing ones.";
	std::cout << "WARNING: As this is a demonstration of a potential use of a binary search tree,";
	std::cout << "this program is only designed to contain one of each distance value. As such, if";
	std::cout << "the user enters in a duplicate distance value, the star will not be added to the ";
	std::cout << "tree." << std::endl;
	std::cout << "================================================================================" << std::endl;
	std::cout << std::endl;

	// Display stars
	printStars(root);

	// Allow for instertion & deletion of stars
	while (true)
	{
		// Request input
		std::cout << "Select a choice from the listing below:" << std::endl;
		std::cout << "I) Insert new star. ( Remember, entering a duplicate distance will result in the";
		std::cout << "                      star not being added to the tree." << std::endl;
		std::cout << "D) Delete current star" << std::endl;
		std::cout << "F) Find star by distance from sun (in lightyears)" << std::endl;
		std::cout << "P) Print out list of all stars in tree." << std::endl;
		std::cin >> choice;

		// Input validation
		while (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cin.ignore();
			std::cout << "Invalid input." << std::endl;

			std::cout << "Select a choice from the listing below:" << std::endl;
			std::cout << "I) Insert new star. ( Remember, entering a duplicate distance will" << std::endl;
			std::cout << "                      result in the star not being added to the tree." << std::endl;
			std::cout << "D) Delete current star";
			std::cout << "F) Find star by distance from sun (in lightyears)" << std::endl;
			std::cout << "P) Print out list of all stars in tree." << std::endl;
			std::cin >> choice;
		}

		if (toupper(choice) == 'I')
		{
			// Request star name
			std::cout << "Enter the star name:";
			std::cin >> name;

			// Validate name
			while (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cin.ignore();
				std::cout << "Invalid input." << std::endl;
				std::cout << "Enter the star name:";
				std::cin >> name;
			}

			// Request distance from the sun
			//std::cin.clear();
			//std::cin.ignore();
			//std::cin.ignore();
			std::cout << "Enter the star's distance from the sun:";
			std::cin >> distance;

			// Validate distance
			while (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cin.ignore();
				std::cout << "Invalid input." << std::endl;
				std::cout << "Enter the star name:";
				std::cin >> distance;
			}

			// Insert star into BST
			insert(root, name, distance);
			std::cout << "Star has been added to the tree." << std::endl;
			std::cout << std::endl;
		}
		else if (toupper(choice) == 'D')
		{
			std::cout << "Enter star name to delete:";
			std::cin >> distance;

			// Validate star name
			while (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cin.ignore();
				std::cout << "Invalid input." << std::endl;

				std::cout << "Enter star name to delete:";
				std::cin >> name;
			}

			deleteStar(root, find(root, distance)->distance);
			std::cout << "Star has been deleted" << std::endl;
			std::cout << std::endl;
		}
		else if (toupper(choice) == 'F')
		{
			std::cout << "Enter star distance to find:";
			std::cin >> distance;

			// Validate star name
			while (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cin.ignore();
				std::cout << "Invalid input." << std::endl;

				std::cout << "Enter star distance to find:";
				std::cin >> distance;
			}

			starNode* star = find(root, distance);
			if (star == NULL)
			{
				std::cout << "Star not found." << std::endl;
				std::cout << std::endl;
			}
			else
				std::cout << star->name << " is " << star->distance << " lightyears from earh" << std::endl;
		}
		else if (toupper(choice) == 'P')
		{
			printStars(root);
		}
		else
			std::cout << "Invalid input." << std::endl;
	}
}

// Definitions
// Create new star node
struct starNode* newNode(std::string name, double distance)
{
	struct starNode* temp = new starNode;
	temp->name = name;
	temp->distance = distance;
	temp->leftChild = temp->rightChild = NULL;
	return temp;
}

// Insert a node in the tree. Ordered by distance
struct starNode* insert(struct starNode* node, std::string name, double distance)
{
	if (node == NULL)
		return newNode(name, distance);

	if (distance < node->distance)
		node->leftChild = insert(node->leftChild, name, distance);
	else if (distance > node->distance)
		node->rightChild = insert(node->rightChild, name, distance);

	return node;
}

// Delete node
struct starNode* deleteStar(struct starNode* root, double distance)
{
	if (root == NULL)
		return root;

	/*
	 * Deletion can take place in one of three cases:
	 * Case 1: Node is a leaf ( has no children)
	 * Case 2: Node has 1 child
	 * Case 3: Node has 2 children 
	 */

	// Case 1: Node is a leaf ( has no children) or Case 2: has only 1 child
	// Traverse the tree to find the star
	if (distance < root->distance)
		root->leftChild = deleteStar(root->leftChild, distance);
	else if (distance > root->distance)
		root->rightChild = deleteStar(root->rightChild, distance);
	else
	{
		// Node has 0 or 1 child in right child
		if (root->leftChild == NULL)
		{
			starNode* temp = root->rightChild;
			delete root;
			return temp;
		}
		// Node has 1 child in left child
		else if (root->rightChild == NULL)
		{
			starNode* temp = root->leftChild;
			delete root;
			return temp;
		}

		// Case 3: Node has 2 children
		// Get in order successor in right subtree
		starNode* succ = root->rightChild;
		while (succ && succ->leftChild != NULL)
			succ = succ->leftChild;
		
		// Copy successors's name & distance to this star node
		root->name = succ->name;
		root->distance = succ->distance;

		// Delete inorder successor
		root->rightChild = deleteStar(root->rightChild, succ->distance);
	}
	return root;
}

// Display the stars in order of their distance from Earth
void printStars(struct starNode* root)
{
	if (root != NULL)
	{
		printStars(root->leftChild);
		std::cout << root->name << " : " << root->distance << " ly" << std::endl;
		printStars(root->rightChild);
	}
}

// Find node by distance from earth
struct starNode* find(starNode* root, double distance)
{
	if (root == NULL || root->distance == distance)
		return root;

	if (root->distance < distance)
		return find(root->rightChild, distance);

	return find(root->leftChild, distance);
}