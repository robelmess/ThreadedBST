/**
 * @file ThreadedBST.cpp
 * @brief ThreadedBST header that declares ThreadedBST class
 * @author William Susanto and Robel Messele
 */
#include "ThreadedBST.h"

/**
 * @brief Default constructor
 *
 * @pre none
 * @post ThreadedBST with null objects
 */
template <typename ItemType> ThreadedBST<ItemType>::ThreadedBST() {
  rootPtr = nullptr;
}

/**
 * @brief n constructor
 *
 * @pre none
 * @post ThreadedBST with nodes from 1 to n
 * @param n max int in tree
 */
template <typename ItemType> ThreadedBST<ItemType>::ThreadedBST(const int &n) {
  rootPtr = nullptr;
  if (n > 0) {
    insert(1, n);
    setThread(rootPtr);
  }
}

/**
 * @brief Recursively halves and adds midpoint from m to n
 *
 * @pre Existing ThreadedBST
 * @post ThreadedBST with nodes from m to n
 * @param m min int of sequence
 * @param n max int of sequence
 */
template <typename ItemType>
void ThreadedBST<ItemType>::insert(const int &m, const int &n) {
  int mid = (n + m) / 2;
  if (mid != m && mid != n) {
    add(rootPtr, mid);
    insert(m, mid - 1);
    insert(mid + 1, n);
  } else {
    add(rootPtr, n);
    if (m != n) {
      add(rootPtr, m);
    }
  }
}

/**
 * @brief Deep copy constructor
 *
 * @pre none
 * @post Deep copy of tree param
 * @param tree tree to copy
 */
template <typename ItemType>
ThreadedBST<ItemType>::ThreadedBST(const ThreadedBST<ItemType> &tree) {
  rootPtr = nullptr;
  if (tree.count > 0) {
    insert(1, tree.count);
    setThread(rootPtr);
  }
  removeEven();
}

/**
 * @brief Destructor
 *
 * @pre none
 * @post Empty tree and deallocate memory
 */
template <typename ItemType> ThreadedBST<ItemType>::~ThreadedBST() {
  clear(rootPtr);
}

/**
 * @brief Get depth
 *
 * @pre none
 * @post return tree depth
 * @return int depth
 */
template <typename ItemType> int ThreadedBST<ItemType>::getDepth() const {
  return log2(count + 1);
}

/**
 * @brief Adds new node to tree
 *
 * @pre none
 * @post new node is added to tree and returned
 * @param node tree pointer
 * @param data data of new node
 * @return BinaryNode<ItemType>* pointer to new node
 */
template <typename ItemType>
BinaryNode<ItemType> *ThreadedBST<ItemType>::add(BinaryNode<ItemType> *node,
                                                 const ItemType &newEntry) {
  // 1. If the tree is empty, return a new, single node
  if (node == nullptr) {
    count++;
    if (rootPtr == nullptr) {
      rootPtr = new BinaryNode<ItemType>(newEntry);
      return rootPtr;
    }
    return new BinaryNode<ItemType>(newEntry);
  }
  BinaryNode<ItemType> *temp = nullptr;

  // 2. Otherwise, recur down the tree
  if (newEntry < node->getItem()) {
    temp = add(node->getLeftChildPtr(), newEntry);
    node->setLeftChildPtr(temp);
  } else {
    temp = add(node->getRightChildPtr(), newEntry);
    node->setRightChildPtr(temp);
  }
  // return the (unchanged) node pointer
  return node;
}

/**
 * @brief Removes node with given data if exists
 *
 * @pre none
 * @post removes node if exists and returns inorder successor
 * @param node tree pointer
 * @param data data of node to remove
 * @return BinaryNode<ItemType>* inorder successor of removed node
 */
template <typename ItemType>
BinaryNode<ItemType> *
ThreadedBST<ItemType>::removeNode(BinaryNode<ItemType> *node, int data) {
  BinaryNode<int> *parent = nullptr; // parent of removed node
  BinaryNode<int> *ptr = node;       // pointer for removed node

  // Set true if key is found
  bool found = false;

  // Search data in tree and find node to be removed and its parent
  while (ptr != nullptr) {
    if (data == ptr->getItem()) {
      found = true;
      break;
    }
    parent = ptr;
    if (data < ptr->getItem()) {
      if (!(ptr->getLeftThread()))
        ptr = ptr->getLeftChildPtr();
      else
        break;
    } else {
      if (!(ptr->getRightThread()))
        ptr = ptr->getRightChildPtr();
      else
        break;
    }
  }

  if (!found) {
    cout << "Data not present in tree" << endl;
    return nullptr;
  }
  // Two Children
  else if (!(ptr->getLeftThread()) && !(ptr->getRightThread()) &&
           ptr->getLeftChildPtr() != nullptr &&
           ptr->getRightChildPtr() != nullptr) {
    node = caseC(node, ptr);
  }

  // Only Left Child
  else if (!(ptr->getLeftThread()) && ptr->getLeftChildPtr() != nullptr) {
    node = caseB(parent, ptr);
  }

  // Only Right Child
  else if (!(ptr->getRightThread()) && ptr->getRightChildPtr() != nullptr) {
    node = caseB(parent, ptr);
  }
  // No Children
  else {
    node = caseA(node, parent, ptr);
  }

  count--;
  return node;
}

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
template <typename ItemType>
BinaryNode<int> *ThreadedBST<ItemType>::caseA(BinaryNode<int> *node,
                                              BinaryNode<int> *parent,
                                              BinaryNode<int> *ptr) {
  // If node to be removed is rootPtr
  if (parent == nullptr) {
    rootPtr = nullptr;
    delete node;
    node = nullptr;
  }
  // If node to be removed is left of its parent
  else if (ptr == parent->getLeftChildPtr()) {
    if (ptr->getLeftChildPtr() != nullptr) {
      parent->setLeftThread(true);
    }
    parent->setLeftChildPtr(ptr->getLeftChildPtr());
  } else {
    if (ptr->getRightChildPtr() != nullptr) {
      parent->setRightThread(true);
    }
    parent->setRightChildPtr(ptr->getRightChildPtr());
  }

  // Free memory and return inorder successor of removed node
  if (node != nullptr) {
    delete ptr;
  }
  ptr = nullptr;
  return parent;
}

/**
 * @brief Remove a node with one child
 *
 * @pre a node with one child
 * @post removes node and returns inorder successor
 * @param parent parent of removed node
 * @param ptr pointer for removed node
 * @return BinaryNode<int>* inorder successor of removed node
 */
template <typename ItemType>
BinaryNode<int> *ThreadedBST<ItemType>::caseB(BinaryNode<int> *parent,
                                              BinaryNode<int> *ptr) {
  BinaryNode<int> *child;
  // Checks if the child node to be deleted has a left child.
  // Also indicates whether node is leftmost of rootptr
  if (ptr->getLeftThread() == false && ptr->getLeftChildPtr() != nullptr) {
    child = ptr->getLeftChildPtr();
  }
  // The child node to be removed has a right child.
  else {
    child = ptr->getRightChildPtr();
  }
  // if node to be removed is the tree root.
  if (parent == nullptr) {
    rootPtr = child;
    // the node is the left child of its parent.
  } else if (ptr == parent->getLeftChildPtr()) {
    parent->setLeftChildPtr(child);
  }
  // the node is the right child of its parent.
  else {
    parent->setRightChildPtr(child);
  }
  // Find the successor and predecessor of the node
  BinaryNode<int> *s = inorderSucc(ptr);
  BinaryNode<int> *p = inorderPred(ptr);

  // If the ptr has left subtree.
  if (ptr->getLeftThread() == false && p != nullptr) {
    p->setRightChildPtr(s);
  }
  // If the ptr has right subtree.
  else {
    if (ptr->getRightThread() == false && s != nullptr)
      s->setLeftChildPtr(p);
  }
  // Updates left thread boolean variables
  if (rootPtr->getLeftThread()) {
    rootPtr->setLeftThread(false);
    // Updates right thread boolean variables
  } else if (rootPtr->getRightThread()) {
    rootPtr->setRightThread(false);
  }
  // Free memory
  delete ptr;
  ptr = nullptr;
  // return succesor
  return s;
}

/**
 * @brief Remove a node with two children
 *
 * @pre a node with two children
 * @post removes node and returns inorder successor
 * @param node tree pointer
 * @param ptr pointer for removed node
 * @return BinaryNode<int>* inorder successor of removed node
 */
template <typename ItemType>
BinaryNode<int> *ThreadedBST<ItemType>::caseC(BinaryNode<int> *node,
                                              BinaryNode<int> *ptr) {
  // Find inorder successor and its parent.
  BinaryNode<int> *parsucc = ptr;
  BinaryNode<int> *succ = ptr->getRightChildPtr();

  // Find leftmost child of successor
  while (succ->getLeftChildPtr() != nullptr && !(succ->getLeftThread())) {
    parsucc = succ;
    succ = succ->getLeftChildPtr();
  }

  ptr->setItem(succ->getItem());

  if (succ->getLeftThread() && succ->getRightThread()) {
    node = caseA(node, parsucc, succ);
  } else {
    node = caseB(parsucc, succ);
  }
  return node;
}

/**
 * @brief Returns inorder successor of node
 *
 * @pre none
 * @post returns inorder successor of node
 * @param ptr node to get inorder successor of
 * @return BinaryNode<int>* inorder successor of node
 */
template <typename ItemType>
BinaryNode<int> *ThreadedBST<ItemType>::inorderSucc(BinaryNode<int> *ptr) {
  // If successor thread is found returns successor
  if (ptr->getRightThread()) {
    return ptr->getRightChildPtr();
  }

  // If successor contains a smaller left child node
  // Returns left most child node of successor
  ptr = getLeftMost(ptr->getRightChildPtr());
  return ptr;
}

/**
 * @brief Returns inorder predecessor of node
 *
 * @pre none
 * @post returns inorder predecessor of node
 * @param ptr node to get inorder predecessor of
 * @return BinaryNode<int>* inorder predecessor of node
 */
template <typename ItemType>
BinaryNode<int> *ThreadedBST<ItemType>::inorderPred(BinaryNode<int> *ptr) {
  // If predessor thread is found returns predecessor
  if (ptr->getLeftThread()) {
    return ptr->getLeftChildPtr();
  }

  // If parameter node is leftmost the predessor is nullptr
  // Returns nullptr
  if (ptr == getLeftMost(rootPtr)) {
    return nullptr;
  }

  // If predecessor contains a larger right child node
  // Returns right most child node of predecessor
  ptr = getRightMost(ptr->getLeftChildPtr());
  return ptr;
}

/**
 * @brief Empty tree and deallocate memory
 *
 * @pre none
 * @post tree is emptied and memory is deallocated
 * @param node tree pointer
 */
template <typename ItemType>
void ThreadedBST<ItemType>::clear(BinaryNode<ItemType> *node) {
  // Node is not empty
  if (node != nullptr) {
    // Node has left child
    if (!(node->getLeftThread())) {
      // Calls clear on left child
      clear(node->getLeftChildPtr());
    }
    // Node has right child
    if (!(node->getRightThread())) {
      // Calls clear on right child
      clear(node->getRightChildPtr());
    }
    // Deletes left child pointer
    node->setLeftChildPtr(nullptr);
    // Deletes right child pointer
    node->setRightChildPtr(nullptr);

    // Node has no used pointers or children
    if (node->getLeftChildPtr() == nullptr &&
        node->getRightChildPtr() == nullptr) {
      // Deletes node
      delete node;
      node = nullptr;
    }
  }
}

// gets the leftmost node in the threaded BST
// Returns the leftmost node in the tree
/**
 * @brief Get the leftmost node of given tree
 *
 * @pre none
 * @post returns leftmost node
 * @param node tree pointer
 * @return BinaryNode<ItemType>* leftmode node
 */
template <typename ItemType>
BinaryNode<ItemType> *
ThreadedBST<ItemType>::getLeftMost(BinaryNode<ItemType> *node) const {
  // Node is empty
  if (node == nullptr) {
    // Returns empty node
    return nullptr;
  }
  // While there is a possible left child to access
  // Checks if left child node is a thread or already left most of tree
  while (node->getLeftChildPtr() != nullptr && !(node->getLeftThread())) {
    // Iterates to left child ptr
    node = node->getLeftChildPtr();
  }
  // Returns left most node
  return node;
}

/**
 * @brief Get the rightmost node of given tree
 *
 * @pre none
 * @post returns rightmost node
 * @param node tree pointer
 * @return BinaryNode<ItemType>* rightmode node
 */
template <typename ItemType>
BinaryNode<ItemType> *
ThreadedBST<ItemType>::getRightMost(BinaryNode<ItemType> *node) const {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->getRightChildPtr() != nullptr && !(node->getRightThread())) {
    node = node->getRightChildPtr();
  }
  return node;
}

/**
 * @brief Set tree threads
 *
 * @pre none
 * @post tree turns into ThreadedBST
 * @param node tree pointer
 */
template <typename ItemType>
void ThreadedBST<ItemType>::setThread(BinaryNode<ItemType> *node) {
  if (node != nullptr) {
    if (!(node->getLeftThread()) && node != getLeftMost(rootPtr)) {
      BinaryNode<ItemType> *tempLeft = getRightMost(node->getLeftChildPtr());
      tempLeft->setRightChildPtr(node);
      tempLeft->setRightThread(true);
      setThread(node->getLeftChildPtr());
    }
    if (!(node->getRightThread()) && node != getRightMost(rootPtr)) {
      BinaryNode<ItemType> *tempRight = getLeftMost(node->getRightChildPtr());
      tempRight->setLeftChildPtr(node);
      tempRight->setLeftThread(true);
      setThread(node->getRightChildPtr());
    }
  }
}

/**
 * @brief Remove even nodes
 *
 * @pre none
 * @post tree with odd nodes
 */
template <typename ItemType> void ThreadedBST<ItemType>::removeEven() {
  BinaryNode<ItemType> *node =
      getLeftMost(rootPtr); // traverses through tree (inorder)
  BinaryNode<ItemType> *temp;
  while (node != nullptr) {           // if current position can move right
    if ((node->getItem() % 2) == 0) { // current position has even value
      temp = removeNode(rootPtr, node->getItem()); // removes even value node
    } else {
      temp = inorderSucc(node);
    }
    node = nullptr;
    node = temp;
  }
}

/**
 * @brief Outputs tree using inorder traversal
 *
 * @pre none
 * @post inorder output of tree
 */
template <typename ItemType> void ThreadedBST<ItemType>::inorderTraverse() {
  // start from the leftmost node
  BinaryNode<ItemType> *node = getLeftMost(rootPtr);
  while (node) {
    // print the current node
    cout << node->getItem() << " ";

    // go to the inorder successor
    node = inorderSucc(node);
  }
}