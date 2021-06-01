#ifndef _JCOMP_TREE
#define _JCOMP_TREE

namespace jay::compression {
  template <class T_>
  class bintree {
    public:
      template <class T>
      bintree(T value) : value{value}, left{nullptr}, right{nullptr} {}

      template <class T>
      bintree(bintree<T> &other) { *this = other; }

      template <class T>
      bintree<T> &operator=(bintree<T> &other) {
        value = other.value;
        left = new bintree(*other.left);
        right = new bintree(*other.right);
      }

      template <class T>
      void setLeft(T left) { this->left = new bintree(left); }
      template <class T>
      void setRight(T right) { this->right = new bintree(right); }
      template <class T>
      void setLeft(bintree<T> *left) { this->left = left; }
      template <class T>
      void setRight(bintree<T> *right) { this->right = right; }

      ~bintree() {
        if(left != nullptr) delete left;
        if(right != nullptr) delete right;
      }

      T_ value;
      bintree<T_> *left;
      bintree<T_> *right;
  };
}

#endif
