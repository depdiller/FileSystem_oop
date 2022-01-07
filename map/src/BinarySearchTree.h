#ifndef MAPTEMPLATE_BINARYSEARCHTREE_H
#define MAPTEMPLATE_BINARYSEARCHTREE_H

#include "Node.h"

namespace TemplateMap {

    template<typename Key, typename Value>
    class BinarySearchTree {
    private:
        Node<Key, Value> *root;
    public:
        // constructors
        BinarySearchTree() : root(nullptr) {};
        // destructor
        ~BinarySearchTree();
        // methods
        Node<Key, Value> *insert(Key key, Value value);
        Node<Key, Value> *find(Key key) const;
        Node<Key, Value> *min() const;
        Node<Key, Value> *max() const;
        Node<Key, Value> *erase(Node<Key, Value> *toDelete);
        void transplant(Node<Key, Value>  *what, Node<Key, Value>  *with);
//        Node<Key, Value> *next(const Key &);
        Value &getValueByKey(Key key) const;
        Node<Key, Value> *getRoot() const { return root; }

        BinarySearchTree<Key, Value> &operator=(const BinarySearchTree &other);
    };
//    template<typename Key, typename Value>
//    Node<Key, Value> *BinarySearchTree<Key, Value>::next(const Key &key) {
//        Node<Key, Value> *tmp = find(key);
//        return tmp->next(tmp);
//    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::min() const {
        return root->min(root);
    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::max() const {
        return root->max(root);
    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::find(Key key) const {
        return root->search(root, key);
    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::insert(Key key, Value value) {
        root = root->insert(root, key, value);
        return root->search(root, key);
    }

    template<typename Key, typename Value>
    BinarySearchTree<Key, Value>::~BinarySearchTree() {
        root->deleteNodeRecursion(root);
    }

    template<typename Key, typename Value>
    Value &BinarySearchTree<Key, Value>::getValueByKey(Key key) const {
        return root->search(root,key)->getValue();
    }

    template<typename Key, typename Value>
    BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(const BinarySearchTree &other) {
        if (this != &other) {
            if (this->root != nullptr)
                root->deleteNodeRecursion(root);
            if (other.root != nullptr) {
                this->root = this->root->clone(other.root, other.root->getParent());
            }
            else {
                this->root = nullptr;
            }
            return *this;
        }
        else
            return *this;
    }

    template<typename Key, typename Value>
    void BinarySearchTree<Key, Value>::transplant(Node<Key, Value>  *what, Node<Key, Value>  *with) {
        if (what->getParent() == nullptr) {
            this->root = with;
        } else if (what == what->getParent()->getLeft()) {
            what->getParent()->setLeft(with);
        } else {
            what->getParent()->setRight(with);
        }
        if (with != nullptr) {
            with->setParent(what->getParent());
        }
    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::erase(Node<Key, Value> *toDelete) {
        Node<Key, Value> *nextReturn = nullptr;
        if (toDelete != nullptr) {
            if (toDelete->getRight() != nullptr)
                nextReturn = toDelete->min(toDelete->getRight());
            else
                nextReturn = toDelete->getParent();

            if (toDelete->getLeft() == nullptr)
                transplant(toDelete, toDelete->getRight());
            else if (toDelete->getRight() == nullptr)
                transplant(toDelete, toDelete->getLeft());
            else {
                Node<Key, Value> *min = toDelete->min(toDelete->getRight());
                if (min->getParent() != toDelete) {
                    Node<Key, Value> *min1 = min;
                    transplant(min, min1->getRight());
                    min1->setRight(toDelete->getRight());
                    min1->getRight()->setParent(min);
                }
                transplant(toDelete, min);
                min->setLeft(toDelete->getLeft());
                min->getLeft()->setParent(min);
            }
        }
        return nextReturn;
    }
}

#endif //MAPTEMPLATE_BINARYSEARCHTREE_H