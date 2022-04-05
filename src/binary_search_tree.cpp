#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value,root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key,root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* curr = find(key,root_);
    if (curr == nullptr) {
      return std::nullopt;
    }
    return curr -> value;
  }

  bool BinarySearchTree::Contains(int key) const {
    if (Find(key) != std::nullopt) {
      return true;
    }
    return false;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    Node* curr= root_;

    while (curr->left !=nullptr) {
      curr= curr->left;
    }
    return curr->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ != nullptr) {
      Node* curr = root_;
      while (curr->right != nullptr) {
        curr = curr->right;
      }
      return curr->value;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      Node* new_ = new Node(key, value);
      node = new_;
    }
    else {
      if (key < node -> key) {
        insert(key, value, node -> left);
      }
      else if (key == node -> key) {
        node -> value = value;
      }
      else {
        insert(key, value, node -> right);
      }
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node != nullptr) {
      if (key < node -> key) {
        return remove(key, node -> left);
      }
      if (node->left != nullptr && node->right == nullptr) {
        Node* left_ = node -> left;
        delete node;
        node = left_;
        return true;
      }
      if (key == node->key) {
        if (node->left != nullptr && node->right != nullptr) {
          Node* min_ = find_min(node->right);
          node -> key = min_ -> key;
          node -> value = min_ -> value;
          return remove(min_ -> key, node -> right);
        }
        Node* right_ = node -> right;
        delete node;
        node = right_;
        return true;
      }
      return remove(key, node -> right);
    }
    return false;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr){
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (key == node->key) {
      return node;
    }
    if (key < node->key) {
      return find(key, node->left);
    }
    if (key > node->key) {
      return find(key, node->right);
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    while(node -> left != nullptr) {
      node = node -> left;
    }
    return node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    while(node -> right != nullptr) {
      node = node -> right;
    }
    return node;
  }
}