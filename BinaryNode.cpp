/**
 * @file BinaryNode.cpp
 * @brief BinaryNode header that declares BinaryNode class
 * @author William Susanto and Robel Messele
 */
#include "BinaryNode.h"

/**
 * @brief Constructor
 *
 * @pre none
 * @post BinaryNode with null objects
 */
template <class ItemType> BinaryNode<ItemType>::BinaryNode() {
  item = -1;
  leftChildPtr = nullptr;
  rightChildPtr = nullptr;
  isThreadedLeft = false;
  isThreadedRight = false;
}

/**
 * @brief Constructor
 *
 * @pre none
 * @post BinaryNode object with item
 * @param anItem node item
 */
template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem) {
  item = anItem;
  leftChildPtr = nullptr;
  rightChildPtr = nullptr;
  isThreadedLeft = false;
  isThreadedRight = false;
}

/**
 * @brief Get Item
 *
 * @pre Existing BinaryNode object
 * @post return node item
 * @return ItemType node item
 */
template <class ItemType> ItemType BinaryNode<ItemType>::getItem() const {
  return item;
}

/**
 * @brief Set Item
 *
 * @pre Existing BinaryNode object
 * @post node item equals parameter
 * @param anItem node item
 */
template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem) {
  item = anItem;
}

/**
 * @brief Get left child pointer
 *
 * @pre Existing BinaryNode object
 * @post Left child of parent node
 * @return node pointer
 */
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getLeftChildPtr() const {
  return leftChildPtr;
}

/**
 * @brief Get right child pointer
 *
 * @pre Existing BinaryNode object
 * @post right child of parent node
 * @return node pointer
 */
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getRightChildPtr() const {
  return rightChildPtr;
}

/**
 * @brief Set left child pointer
 *
 * @pre Existing BinaryNode pointer
 * @post Left child pointer equals parameter
 * @param leftPtr pointer to set left child to
 */
template <class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType> *leftPtr) {
  leftChildPtr = leftPtr;
}

/**
 * @brief Set right child pointer
 *
 * @pre Existing BinaryNode pointer
 * @post right child pointer equals parameter
 * @param rightPtr pointer to set right child to
 */
template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType> *rightPtr) {
  rightChildPtr = rightPtr;
}

/**
 * @brief Get if left threaded
 *
 * @pre Existing BinaryNode pointer
 * @post return if left threaded
 */
template <class ItemType> bool BinaryNode<ItemType>::getLeftThread() {
  return isThreadedLeft;
}

/**
 * @brief Get if right threaded
 *
 * @pre Existing BinaryNode pointer
 * @post return if right threaded
 */
template <class ItemType> bool BinaryNode<ItemType>::getRightThread() {
  return isThreadedRight;
}

/**
 * @brief Set left threaded
 *
 * @pre Existing BinaryNode pointer
 * @post set left threaded to param
 * @param isThreaded param for left threaded
 */
template <class ItemType>
void BinaryNode<ItemType>::setLeftThread(const bool isThreaded) {
  isThreadedLeft = isThreaded;
}

/**
 * @brief Set right threaded
 *
 * @pre Existing BinaryNode pointer
 * @post return if right threaded
 * @param isThreaded param for right threaded
 */
template <class ItemType>
void BinaryNode<ItemType>::setRightThread(const bool isThreaded) {
  isThreadedRight = isThreaded;
}