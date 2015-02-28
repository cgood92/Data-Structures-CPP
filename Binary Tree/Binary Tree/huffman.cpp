/***********************************************************************
 * Module:
 *    Lesson 07, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include "pair.h"
#include <vector>
#include "vector.h"
#include "list.h"
#include "set.h"
#include "deque.h"      // your Deque class should be in deque.h
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "bnode.h"     // your BinaryNode class should be in bnode.h

#include <fstream>         // needed for all file I/O programs
using namespace std;
/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman()
{
   char fileName[256];
   //create the tree
   vector <Pair<string, float>> huffCodes;

   //get the filename
   cout << "Enter the filename containing the value frequencies: ";
   cin >> fileName;

   string line;
   ifstream myfile("C:\\Users\\cgood92\\Documents\\CS 235\\Binary Tree\\Binary Tree\\huffman1.txt");
   if (myfile.is_open())
   {
	   while (getline(myfile, line))
	   {
		   Pair<string, float> thisPair; //String: token, float: frequency
		   istringstream(line) >> thisPair;
		   //HuffmanTree thisHuffTree(thisPair);
		   huffCodes.push_back(thisPair);
	   }
	   myfile.close();
   }
   else
   {
	   cout << "Error opening file";
   }

   //int num_items_to_visit = huffCodes.size() - 1;

   //bool exchange_made = false;
   //do
   //{
	  // int last_marker = num_items_to_visit - 1;
	  // for (int i = 0; i <= last_marker; i++)
		 //  if (huffCodes[i].getSecond() > huffCodes[i + 1].getSecond())
		 //  {
			//   Pair<string, float> temp = huffCodes[i];
			//   huffCodes[i] = huffCodes[i + 1];
			//   huffCodes[i + 1] = temp;
			//   exchange_made = true;
		 //  }
		 //  num_items_to_visit--;

   //} while (exchange_made && (num_items_to_visit > 0));

   cout << "Sorted:\n";

   HuffmanTree master;
   HuffmanTree * current = &master;
   Vector <HuffmanTree> dTreesUnused;
   for (int i = 0; i < huffCodes.size(); ++i)
   {
	   dTreesUnused.push_back(HuffmanTree(huffCodes[i]));
	   //cout << dTreesUnused(i).miniTree.data;
   }

   for (VectorIterator<HuffmanTree> it = dTreesUnused.begin(); it != dTreesUnused.end(); ++it)
   {
	   cout << (*it).miniTree.data << endl;
   }
   bool firstTime = true;
   while(dTreesUnused.size() > 1)
   {
	   HuffmanTree lowest;
	   lowest = HuffmanTree();
	   lowest.miniTree.data = Pair<string, float>("", 10000);
	   HuffmanTree secondLowest;
	   secondLowest = HuffmanTree();
	   secondLowest.miniTree.data = Pair<string, float>("", 10001);
	   VectorIterator <HuffmanTree> delOne;
	   VectorIterator <HuffmanTree> delTwo;
	   int i = 0;
	   for (VectorIterator <HuffmanTree> it = dTreesUnused.begin(); it != dTreesUnused.end(); ++it)
	   {
		   cout << "[" << i++ << "] " << &((*it).miniTree) << endl;
	   }
	   cout << "====================\n";
	   for (VectorIterator <HuffmanTree> it = dTreesUnused.begin(); it != dTreesUnused.end(); ++it)
	   {
		   //cout << "Checking to see if " << (*it).miniTree.data.getSecond() << " < " << lowest.miniTree.data.getSecond() << "()" << endl;
		   if ((*it).miniTree.data.getSecond() < lowest.miniTree.data.getSecond())
		   {
			   if (secondLowest.miniTree.data.getSecond() == lowest.miniTree.data.getSecond())
			   {
				   secondLowest = lowest;
				   delTwo = delOne;
			   }
			   else
			   {
				   secondLowest = lowest;
				   delTwo = delOne;
			   }
			   lowest = *it;
			   cout << "<" << (*it).miniTree.data.getFirst() << ", " << (*it).miniTree.data.getSecond() << "> just got chosen as lowest\n";
			   delOne = VectorIterator <HuffmanTree>(it);
		   }
		   else if ((*it).miniTree.data.getSecond() < secondLowest.miniTree.data.getSecond())
		   {
			   secondLowest = *it;
			   cout << "<" << (*it).miniTree.data.getFirst() << ", " << (*it).miniTree.data.getSecond() << "> just got chosen as secondLowest\n";
			   delTwo = VectorIterator <HuffmanTree> (it);
		   }
	   }
	   HuffmanTree * combined = new HuffmanTree();
	   combined->miniTree.addLeft(lowest.miniTree.data);
	   combined->miniTree.addRight(secondLowest.miniTree.data);
	   combined->miniTree.data = Pair<string, float>("", lowest.miniTree.data.getSecond() + secondLowest.miniTree.data.getSecond());
	   if (firstTime)
	   {
		   //combined->miniTree.pParent = &master.miniTree;
	   }

	   cout << &(combined->miniTree) << endl;
	   cout << "====================\n";

	   (*delOne) = *combined;
	   HuffmanTree test;
	   //test.miniTree.data = Pair<string, float>("TEST", 10000);
	   test = (*dTreesUnused.end());
	   (*delTwo) = (*(--(dTreesUnused.end())));
	   //(*delTwo) = *(dTreesUnused.end());
	   dTreesUnused.erase(dTreesUnused.end());
	   i = 0;
	   for (VectorIterator <HuffmanTree> it = dTreesUnused.begin(); it != dTreesUnused.end(); ++it)
	   {
		   cout << "[" << i++ << "] " << &((*it).miniTree) << endl;
	   }
	   firstTime = false;
   }
   master = dTreesUnused[0];

   cout << &master.miniTree;

   return;
}


