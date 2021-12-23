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
        Node<Key, Value> *search(Key key) const;
        Node<Key, Value> *min() const;
        Node<Key, Value> *max() const;
//        Node<Key, Value> *next(const Key &);
        Value &getValueByKey(Key key) const;
        Node<Key, Value> *getRoot() const { return root; }
    };
//    template<typename Key, typename Value>
//    Node<Key, Value> *BinarySearchTree<Key, Value>::next(const Key &key) {
//        Node<Key, Value> *tmp = search(key);
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
    Node<Key, Value> *BinarySearchTree<Key, Value>::search(Key key) const {
        return root->search(root, key);
    }

    template<typename Key, typename Value>
    Node<Key, Value> *BinarySearchTree<Key, Value>::insert(Key key, Value value) {
        root = root->insert(root, key, value);
        return root->search(root, key);
    }

    template<typename Key, typename Value>
    BinarySearchTree<Key, Value>::~BinarySearchTree() {
        root->deleteNode(root);
    }

    template<typename Key, typename Value>
    Value &BinarySearchTree<Key, Value>::getValueByKey(Key key) const {
        return root->search(root,key)->getValue();
    }
}


#endif //MAPTEMPLATE_BINARYSEARCHTREE_H