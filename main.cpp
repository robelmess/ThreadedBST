/**
 * @file main.cpp
 * @brief Tests the ThreadedBST class implementation
 * @author William Susanto and Robel Messele
 */
#include "ThreadedBST.h"
#include <iostream>

int main()
{

  int n;
  cout << " Please enter n, the number of nodes and values: " << endl;
  cin >> n;
  if (n == -3)
  {
    return 0;
  }
  ThreadedBST<int> tree(n);
  cout << " " << tree << endl;

  cout << " Please enter a number to remove or \n type -1 to create a new tree \n type -2 to create a new tree without even values \n type -3 to exit program";
  cin >> n;
  if (n == -1)
  {
    main();
  }
  if (n > 0)
  {
    BinaryNode<int> *temp = tree.rootPtr;
    tree.removeNode(temp, n);
    cout << tree << endl;
  }

  if (n == -2)
  {
    ThreadedBST<int> tree2(tree);
    cout << tree2 << endl;
  }

  if (n == -3)
  {
    return 0;
  }

  main();
  return 0;
}