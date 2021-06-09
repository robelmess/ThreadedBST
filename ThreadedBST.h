/**
 * @file ThreadedBST.h
 * @brief ThreadedBST header that declares ThreadedBST class.
 *        Implementation of a threaded BST.
 * @author William Susanto and Robel Messele
 */

#ifndef THREADEDBST_
#define THREADEDBST_

#include "BinaryNode.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

template <typename ItemType> class ThreadedBST {
  /**
   * @brief Outputs tree using inorder traversal
   *
   * @pre none
   * @post inorder output of tree
   * @param output object to output to
   * @param ThreadedBST tree to output
   * @return ostream& output
   */
  friend ostream &operator<<(ostream &output,
                             ThreadedBST<ItemType> &ThreadedBST) {
    ThreadedBST.inorderTraverse();
    return output;
  }

private:
  BinaryNode<ItemType> *rootPtr;
  int count = 0;

public:
  /**
   * @brief Default constructor
   *
   * @pre none
   * @post ThreadedBST with null objects
   */
  ThreadedBST();

  /**
   * @brief n constructor
   *
   * @pre none
   * @post ThreadedBST with nodes from 1 to n
   * @param n max int in tree
   */
  ThreadedBST(const int &n);

  /**
   * @brief Recursively halves and adds midpoint from m to n
   *
   * @pre Existing ThreadedBST
   * @post ThreadedBST with nodes from m to n
   * @param m min int of sequence
   * @param n max int of sequence
   */
  void insert(const int &m, const int &n);

  /**
   * @brief Deep copy constructor
   *
   * @pre none
   * @post Deep copy of tree param
   * @param tree tree to copy
   */
  ThreadedBST(const ThreadedBST<ItemType> &tree);

  /**
   * @brief Destructor
   *
   * @pre none
   * @post Empty tree and deallocate memory
   */
  ~ThreadedBST();

  /**
   * @brief Get depth
   *
   * @pre none
   * @post return tree depth
   * @return int depth
   */
  int getDepth() const;

  /**
   * @brief Adds new node to tree
   *
   * @pre none
   * @post new node is added to tree and returned
   * @param node tree pointer
   * @param data data of new node
   * @return BinaryNode<ItemType>* pointer to new node
   */
  BinaryNode<ItemType> *add(BinaryNode<ItemType> *node, const ItemType &data);

  /**
   * @brief Removes node with given data if exists
   *
   * @pre none
   * @post removes node if exists and returns inorder successor
   * @param node tree pointer
   * @param data data of node to remove
   * @return BinaryNode<ItemType>* inorder successor of removed node
   */
  BinaryNode<ItemType> *removeNode(BinaryNode<ItemType> *node, int data);

  /**
   * @brief Remove a node with no children
   *
   * @pre a node with no children
   * @post removes node and returns inorder successor
   * @param node tree pointer
   * @param parent parent of removed node
   * @param ptr pointer for removed node
   * @return BinaryNode<int>* inorder successor of removed node
   */
  BinaryNode<int> *caseA(BinaryNode<int> *node, BinaryNode<int> *parent,
                         BinaryNode<int> *ptr);

  /**
   * @brief Remove a node with one child
   *
   * @pre a node with one child
   * @post removes node and returns inorder successor
   * @param parent parent of removed node
   * @param ptr pointer for removed node
   * @return BinaryNode<int>* inorder successor of removed node
   */
  BinaryNode<int> *caseB(BinaryNode<int> *parent, BinaryNode<int> *ptr);

  /**
   * @brief Remove a node with two children
   *
   * @pre a node with two children
   * @post removes node and returns inorder successor
   * @param node tree pointer
   * @param ptr pointer for removed node
   * @return BinaryNode<int>* inorder successor of removed node
   */
  BinaryNode<int> *caseC(BinaryNode<int> *node, BinaryNode<int> *ptr);

  /**
   * @brief Returns inorder successor of node
   *
   * @pre none
   * @post returns inorder successor of node
   * @param ptr node to get inorder successor of
   * @return BinaryNode<int>* inorder successor of node
   */
  BinaryNode<int> *inorderSucc(BinaryNode<int> *ptr);

  /**
   * @brief Returns inorder predecessor of node
   *
   * @pre none
   * @post returns inorder predecessor of node
   * @param ptr node to get inorder predecessor of
   * @return BinaryNode<int>* inorder predecessor of node
   */
  BinaryNode<int> *inorderPred(BinaryNode<int> *ptr);

  /**
   * @brief Empty tree and deallocate memory
   *
   * @pre none
   * @post tree is emptied and memory is deallocated
   * @param node tree pointer
   */
  void clear(BinaryNode<ItemType> *node);

  /**
   * @brief Get the leftmost node of given tree
   *
   * @pre none
   * @post returns leftmost node
   * @param node tree pointer
   * @return BinaryNode<ItemType>* leftmode node
   */
  BinaryNode<ItemType> *getLeftMost(BinaryNode<ItemType> *node) const;

  /**
   * @brief Get the rightmost node of given tree
   *
   * @pre none
   * @post returns rightmost node
   * @param node tree pointer
   * @return BinaryNode<ItemType>* rightmode node
   */
  BinaryNode<ItemType> *getRightMost(BinaryNode<ItemType> *node) const;

  /**
   * @brief Set tree threads
   *
   * @pre none
   * @post tree is threaded
   * @param node tree pointer
   */
  void setThread(BinaryNode<ItemType> *node);

  /**
   * @brief Remove even nodes
   *
   * @pre none
   * @post tree with odd nodes
   */
  void removeEven();

  /**
   * @brief Outputs tree using inorder traversal
   *
   * @pre none
   * @post inorder output of tree
   */
  void inorderTraverse();
}; // end ThreadedBST

#include "ThreadedBST.cpp"
#endif
