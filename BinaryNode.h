/**
 * @file BinaryNode.h
 * @brief BinaryNode header that declares BinaryNode class.
 *        A class of nodes for a threaded BST.
 * @author William Susanto and Robel Messele
 */
#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

template <class ItemType> class BinaryNode {
private:
  ItemType item;                       // Data portion
  BinaryNode<ItemType> *leftChildPtr;  // Pointer to left child
  BinaryNode<ItemType> *rightChildPtr; // Pointer to right child
  bool isThreadedLeft;  // true if the left pointer of a node points to its
                        // inorder predecessor
  bool isThreadedRight; // true if the right pointer of a node points to its
                        // inorder successor
public:
  /**
   * @brief Constructor
   *
   * @pre none
   * @post BinaryNode with null objects
   */
  BinaryNode();

  /**
   * @brief Constructor
   *
   * @pre none
   * @post BinaryNode with item
   * @param anItem node item
   */
  BinaryNode(const ItemType &);

  /**
   * @brief Get Item
   *
   * @pre Existing BinaryNode object
   * @post return node item
   * @return ItemType node item
   */
  ItemType getItem() const;

  /**
   * @brief Set Item
   *
   * @pre Existing BinaryNode object
   * @post node item equals parameter
   * @param anItem node item
   */
  void setItem(const ItemType &);

  /**
   * @brief Get left child pointer
   *
   * @pre Existing BinaryNode object
   * @post Left child of parent node
   * @return node pointer
   */
  BinaryNode<ItemType> *getLeftChildPtr() const;

  /**
   * @brief Get right child pointer
   *
   * @pre Existing BinaryNode object
   * @post right child of parent node
   * @return node pointer
   */
  BinaryNode<ItemType> *getRightChildPtr() const;

  /**
   * @brief Set left child pointer
   *
   * @pre Existing BinaryNode pointer
   * @post Left child pointer equals parameter
   * @param leftPtr pointer to set left child to
   */
  void setLeftChildPtr(BinaryNode<ItemType> *leftPtr);

  /**
   * @brief Set right child pointer
   *
   * @pre Existing BinaryNode pointer
   * @post right child pointer equals parameter
   * @param rightPtr pointer to set right child to
   */
  void setRightChildPtr(BinaryNode<ItemType> *rightPtr);

  /**
   * @brief Get if left threaded
   *
   * @pre Existing BinaryNode pointer
   * @post return if left threaded
   */
  bool getLeftThread();

  /**
   * @brief Get if right threaded
   *
   * @pre Existing BinaryNode pointer
   * @post return if right threaded
   */
  bool getRightThread();

  /**
   * @brief Set left threaded
   *
   * @pre Existing BinaryNode pointer
   * @post set left threaded to param
   * @param isThreaded param for left threaded
   */
  void setLeftThread(const bool isThreaded);

  /**
   * @brief Set right threaded
   *
   * @pre Existing BinaryNode pointer
   * @post set right threaded to param
   * @param isThreaded param for right threaded
   */
  void setRightThread(const bool isThreaded);
}; // end BinaryNode

#include "BinaryNode.cpp"
#endif
