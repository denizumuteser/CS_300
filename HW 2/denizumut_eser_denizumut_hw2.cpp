#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "BS_Tree.h"
#include "AVL_Tree.h"

using namespace std;
//Deniz Umut Eser
//please execute in release mode, not in debug mode.

struct item
{
	string title;
	string info;

	bool operator > (const item& rhs) const
	{
		return title > rhs.title;
	}
	bool operator < (const item& rhs) const
	{
		return title < rhs.title;
	}
	friend ostream& operator << (ostream& o, const item& i)
	{
		o << i.title;
		return o;
	}
};

struct sectionBST
{
	string title;
	BinarySearchTree<item> itemTree;

	bool operator > (const sectionBST& rhs) const 
	{
		return title > rhs.title;
	}
	bool operator < (const sectionBST& rhs) const 
	{
		return title < rhs.title;
	}
	friend ostream& operator << (ostream& o, const sectionBST& i)
	{
		o << i.title;
		return o;
	}
};

struct sectionAVL
{
	string title;
	AvlTree<item> itemTree;

	bool operator > (const sectionAVL& rhs) const
	{
		return title > rhs.title;
	}
	bool operator < (const sectionAVL& rhs) const
	{
		return title < rhs.title;
	}
	friend ostream& operator << (ostream& o, const sectionAVL& i)
	{
		o << i.title;
		return o;
	}
};


void sectionMenu(string section, BinarySearchTree<sectionBST>& BstNotebook, AvlTree<sectionAVL>& AvlNotebook)
{
	int choice = 0;
	cout << endl;
	cout << "Selected section -> " << section << endl;
	cout << "Please enter an input between [1 - 7]:" << endl;
	cout << "1- Display the items [AVL]" << endl;
	cout << "2- Display the items [BST]" << endl;
	cout << "3- Display the information of a item" << endl;
	cout << "4- Add new item" << endl;
	cout << "5- Update the information of a item" << endl;
	cout << "6- Delete an item" << endl;
	cout << "7- Return to main menu" << endl;
	while (choice != 7)
	{
		cout << "Input: ";
		cin >> choice;
		string item_to_find, new_item_name;

		sectionBST search_section;
		sectionAVL search_section2;

		search_section.title = section;
		search_section2.title = section;

		sectionAVL sectionA = AvlNotebook.find(search_section2);
		sectionBST sectionB = BstNotebook.find(search_section);
		if (choice == 1) //Display the items [AVL]
		{
			cout << endl;
			cout << "*****" << endl;
			sectionA.itemTree.printTree();
			cout << "*****" << endl << endl;
		}
		else if (choice == 2) //Display the items [BST]
		{
			cout << endl;
			cout << "*****" << endl;
			sectionB.itemTree.printTree();
			cout << "*****" << endl << endl;
		}

		else if (choice == 3) //Display item information
		{
			cout << "Enter the title of the item: ";
			cin >> item_to_find;
			item item_obj;
			item foundA, foundB;
			item_obj.title = item_to_find;
			
			//Find item
			auto startA = chrono::high_resolution_clock::now();
			foundA = sectionA.itemTree.find(item_obj);
			auto endA = chrono::high_resolution_clock::now();
			long long timerA = (endA - startA).count() / 1000.0;
			cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;

			auto startB = chrono::high_resolution_clock::now();
			foundB = sectionB.itemTree.find(item_obj);
			auto endB = chrono::high_resolution_clock::now();
			long long timerB = (endB - startB).count() / 1000.0;
			cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;

			if (foundA.title == item_to_find) //if item is found
				cout << foundA.info << endl << endl;
			else //Item not found
				cout << "Invalid title." << endl << endl;
		}

		else if (choice == 4) //Add new item
		{
			cout << "Enter a title for the item: ";
			cin >> new_item_name;
			item new_item, to_find;
			new_item.title = new_item_name;

			//Check if item exist or not
			to_find = sectionB.itemTree.find(new_item);

			if (to_find.title == new_item_name)
			{
				cout << "Item \"" << new_item_name << "\" already exists in the \"" << sectionB.title << "\"." << endl << endl;
			}
			else
			{
				cout << "Enter a description for the item: ";
				string description;
				cin >> description;
				new_item.info = description;

				//Insert new item with given description
				auto startA = chrono::high_resolution_clock::now();
				sectionAVL sectionA = AvlNotebook.find(search_section2);
				sectionA.itemTree.insert(new_item);
				AvlNotebook.remove(AvlNotebook.find(search_section2));
				AvlNotebook.insert(sectionA);
				auto endA = chrono::high_resolution_clock::now();
				long long timerA = (endA - startA).count() / 1000.0;
				cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;
				
				auto startB = chrono::high_resolution_clock::now();
				sectionBST sectionB = BstNotebook.find(search_section);
				sectionB.itemTree.insert(new_item);
				BstNotebook.remove(BstNotebook.find(search_section));
				BstNotebook.insert(sectionB);
				auto endB = chrono::high_resolution_clock::now();
				long long timerB = (endB - startB).count() / 1000.0;
				cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;
				
				cout << "The new item \"" << new_item.title << "\" has been inserted." << endl << endl;
			}
		}
		else if (choice == 5) //Update existing item
		{
			cout << "Enter the title for the item: ";
			cin >> new_item_name;
			item new_item, foundA, foundB;
			new_item.title = new_item_name;

			//Find item
			auto startA = chrono::high_resolution_clock::now();
			foundA = sectionA.itemTree.find(new_item);
			auto endA = chrono::high_resolution_clock::now();
			long long timerA = (endA - startA).count() / 1000.0;
			cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;

			auto startB = chrono::high_resolution_clock::now();
			foundB = sectionB.itemTree.find(new_item);
			auto endB = chrono::high_resolution_clock::now();
			long long timerB = (endB - startB).count() / 1000.0;
			cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;

			if (foundA.title == new_item_name) //If item exists
			{
				cout << "Enter the new information: ";
				string description;
				cin >> description;
				foundA.info = description;
				foundB.info = description;

				//remove old section and insert new section with updated item info
				sectionA.itemTree.remove(foundA);
				sectionA.itemTree.insert(foundA);

				AvlNotebook.remove(sectionA);
				AvlNotebook.insert(sectionA);

				sectionB.itemTree.remove(foundB);
				sectionB.itemTree.insert(foundB);

				BstNotebook.remove(sectionB);
				BstNotebook.insert(sectionB);
				cout << "The content " << new_item_name << " has updated." << endl << endl;
			}
			else
			{
				cout << "Item \"" << new_item_name << "\" does not exist in the \"" << section << "\"." << endl << endl;
			}
		}
		else if (choice == 6) //Remove an item
		{
			cout << "Enter the title of the item: ";
			cin >> new_item_name;
			item to_delete, to_delete2, new_item;
			new_item.title = new_item_name;
			long long timerA = 0.0, timerB = 0.0;

			auto startA = chrono::high_resolution_clock::now();
			to_delete2 = sectionA.itemTree.find(new_item);
			auto endA = chrono::high_resolution_clock::now();
			timerA += (endA - startA).count() / 1000.0;

			auto startB = chrono::high_resolution_clock::now();
			to_delete = sectionB.itemTree.find(new_item);
			auto endB = chrono::high_resolution_clock::now();
			timerB += (endB - startB).count() / 1000.0;

			if (to_delete.title == new_item_name) //if item exists
			{
				//remove item and update section

				auto startA = chrono::high_resolution_clock::now();
				
				sectionA.itemTree.remove(to_delete2);
				AvlNotebook.remove(sectionA);
				AvlNotebook.insert(sectionA);
				auto endA = chrono::high_resolution_clock::now();
				timerA += (endA - startA).count() / 1000.0;
				cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;
				timerA = 0.0;


				auto startB = chrono::high_resolution_clock::now();
				
				sectionB.itemTree.remove(to_delete);
				BstNotebook.remove(sectionB);
				BstNotebook.insert(sectionB);
				auto endB = chrono::high_resolution_clock::now();
				timerB += (endB - startB).count() / 1000.0;
				cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;
				timerB = 0.0;

				cout << "The item \"" << new_item_name << "\" has been deleted." << endl << endl;
			}
			else
			{
				cout << "Item \"" << new_item_name << "\" does not exist in the \"" << section << "\"." << endl << endl;
			}
		}
		else if (choice == 7) //Return to menu
		{
		cout << endl;
		cout << "MENU" << endl;
		cout << "Please enter an input between [1 - 6]:" << endl;
		cout << "1- Display the sections [AVL]" << endl;
		cout << "2- Display the sections [BST]" << endl;
		cout << "3- Select a section" << endl;
		cout << "4- Add new section" << endl;
		cout << "5- Delete a section" << endl;
		cout << "6- Exit" << endl;
		return;
		}
	}
}

void mainMenu(BinarySearchTree<sectionBST> &BstNotebook, AvlTree<sectionAVL> &AvlNotebook)
{
	cout << "MENU" << endl;
	cout << "Please enter an input between [1 - 6]:" << endl;
	cout << "1- Display the sections [AVL]" << endl;
	cout << "2- Display the sections [BST]" << endl;
	cout << "3- Select a section" << endl;
	cout << "4- Add new section" << endl;
	cout << "5- Delete a section" << endl;
	cout << "6- Exit" << endl;
	bool running = true;
	while (running)
	{
		int choice;
		string section;
		cout << "Input: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << endl;
			cout << "*****" << endl;
			AvlNotebook.printTree();
			cout << "*****" << endl << endl;
		}
		else if (choice == 2)
		{
			cout << endl;
			cout << "*****" << endl;
			BstNotebook.printTree();
			cout << "*****" << endl << endl;
		}
		else if (choice == 3)
		{
			cout << "Enter the title of the section: ";
			cin >> section;
			sectionBST search_section;
			search_section.title = section;
			sectionBST sectionB = BstNotebook.find(search_section);
		
			if (sectionB.title != section)
				cout << "Invalid title!" << endl << endl;

			else
				sectionMenu(section, BstNotebook, AvlNotebook);
		}
		else if (choice == 4)
		{
			cout << "Enter a title for the section: ";
			cin >> section;
			sectionBST insert_section;
			sectionAVL insert_section2;
			insert_section.title = section;
			insert_section2.title = section;

			sectionBST sectionB = BstNotebook.find(insert_section);

			if (sectionB.title == section)
			{
				cout << "Section \"" << section << "\" already exists." << endl << endl;
			}
			else
			{
				AvlNotebook.insert(insert_section2);
				BstNotebook.insert(insert_section);
				cout << "The new section \"" << section << "\" has been inserted." << endl << endl;
			}
		}
		else if (choice == 5)
		{
			cout << "Enter a title for the section: ";
			cin >> section;
			sectionBST delete_section;
			sectionAVL delete_section2;
			delete_section.title = section;
			delete_section2.title = section;

			sectionBST sectionB = BstNotebook.find(delete_section);

			if (sectionB.title != section)
			{
				cout << "Section \"" << section << "\" does not exist." << endl << endl;
			}
			else
			{
				AvlNotebook.remove(delete_section2);
				BstNotebook.remove(delete_section);
				cout << "The section has been deleted." << endl << endl;
			}
		}
		else if (choice == 6)
		{
			cout << endl;
			cout << "Terminating...";
			running = false;
		}		
	}
}

int main()
{
	cout << "Welcome to the Notes" << endl << endl;

	//initilize two notebooks, one BST one AVL tree
	BinarySearchTree<sectionBST> BstNotebook;
	AvlTree<sectionAVL> AvlNotebook;
	
	//read text file which contains data to insert notebooks
	string filename = "data.txt", line, line2, line_item, line_item_info, currentSection = "";
	ifstream input;
	input.open(filename);

	bool running = true;
	
	sectionBST newSection;
	sectionAVL newSection2;

	long long timerB = 0.0, timerA = 0.0;

	//insert data into notebooks
	while (getline(input, line))
	{
		if (line[0] != '-') //section name
		{
			item new_item;

			sectionBST newSection;
			newSection.title = line;
			sectionAVL newSection2;
			newSection2.title = line;

			while (getline(input, line_item))
			{
				if (line_item[0] != '-') //line has section name
				{
					//insert section to AVL
					auto startA = chrono::high_resolution_clock::now();
					AvlNotebook.insert(newSection2);
					auto endA = chrono::high_resolution_clock::now();
					timerA += (endA - startA).count() / 1000.0;
					cout << "Section \"" << newSection2.title << "\" has been inserted into the AVL notebook." << endl;
					cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;
					timerA = 0.0;

					//insert section to BST
					auto startB = chrono::high_resolution_clock::now();
					BstNotebook.insert(newSection);
					auto endB = chrono::high_resolution_clock::now();
					timerB += (endB - startB).count() / 1000.0;
					cout << "Section \"" << newSection.title << "\" has been inserted into the BST notebook." << endl;
					cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;
					timerB = 0.0;
					cout << endl;

					newSection.itemTree.makeEmpty();
					newSection2.itemTree.makeEmpty();

					newSection.title = line_item;
					newSection2.title = line_item;

				}
				else //line has item name
				{
					item new_item;
					line_item = line_item.substr(1);
					line_item_info = line_item.substr(line_item.find('-') + 1);
					line_item = line_item.substr(0, line_item.find('-'));
					new_item.title = line_item;
					new_item.info = line_item_info;

					//insert item to a AVL section
					auto startA = chrono::high_resolution_clock::now();
					newSection2.itemTree.insert(new_item);
					auto endA = chrono::high_resolution_clock::now();
					timerA += (endA - startA).count() / 1000.0;

					//insert item to a BST section
					auto startB = chrono::high_resolution_clock::now();
					newSection.itemTree.insert(new_item);
					auto endB = chrono::high_resolution_clock::now();
					timerB += (endB - startB).count() / 1000.0;
				}
			}
			//insert section to AVL
			auto startA = chrono::high_resolution_clock::now();
			AvlNotebook.insert(newSection2);
			auto endA = chrono::high_resolution_clock::now();
			timerA += (endA - startA).count() / 1000.0;
			cout << "Section \"" << newSection2.title << "\" has been inserted into the AVL notebook." << endl;
			cout << "[AVL] Elapsed time: " << timerA << " microseconds" << endl;
			timerA = 0.0;

			//insert seection to BST
			auto startB = chrono::high_resolution_clock::now();
			BstNotebook.insert(newSection);
			auto endB = chrono::high_resolution_clock::now();
			timerB += (endB - startB).count() / 1000.0;
			cout << "Section \"" << newSection.title << "\" has been inserted into the BST notebook." << endl;
			cout << "[BST] Elapsed time: " << timerB << " microseconds" << endl;
			timerB = 0.0;
			cout << endl;
			currentSection = line;
		}
	}
	//start main menu
	mainMenu(BstNotebook, AvlNotebook);
	return 0;
}