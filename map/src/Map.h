#ifndef MAPTEMPLATE_MAP_H
#define MAPTEMPLATE_MAP_H

#include "BinarySearchTree.h"
#include <iostream>
#include <utility>

namespace TemplateMap {
    template<typename Key, typename Value>
    class MapIterator {
    private:
        Node<Key, Value> *currentNode;
    public:
        MapIterator() : currentNode(nullptr) {};
        MapIterator(Node<Key, Value> *ptrNode);
        bool operator!=(const MapIterator<Key, Value> &it) const;
        bool operator==(const MapIterator<Key, Value> &it) const;
        Node<Key, Value> &operator*();
        Node<Key, Value> *operator->();
        Node<Key, Value> *getCurrentNode() { return currentNode; }
        MapIterator<Key, Value> &operator++();
        MapIterator<Key, Value> operator++(int);
    };

    template<typename Key, typename Value>
    class Map {
    private:
        BinarySearchTree<Key, Value> tree;
        int sizeOfTree;
    public:
        friend class MapIterator<Key, Value>;
        typedef MapIterator<Key, Value> iterator;
        Map() : sizeOfTree(0) {};
        ~Map() = default;;


        iterator begin() const;
        iterator end() const;

        int size() const { return sizeOfTree; }
        bool isEmpty() const;
        iterator insert(Key key, Value value);
        iterator find(Key key);
        iterator erase(iterator toDelete);

        Value &operator[](const Key &key);
        Value &operator[](Key &&key);
        Map<Key, Value> &operator=(const Map &other);
        Map<Key, Value> &operator=(Map &&other) noexcept;
    };

    // MapIterator
    template<typename Key, typename Value>
    MapIterator<Key, Value>::MapIterator(Node<Key, Value> *ptrNode) {
        currentNode = ptrNode;
    }

    template<typename Key, typename Value>
    bool MapIterator<Key, Value>::operator!=(const MapIterator<Key, Value> &it) const {
        return currentNode != it.currentNode;
    }

    template<typename Key, typename Value>
    bool MapIterator<Key, Value>::operator==(const MapIterator<Key, Value> &it) const {
        return currentNode == it.currentNode;
    }

    template<typename Key, typename Value>
    Node<Key, Value> &MapIterator<Key, Value>::operator*() {
        return *currentNode;
    }

    template<typename Key, typename Value>
    Node<Key, Value> *MapIterator<Key, Value>::operator->() {
        return currentNode;
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> &MapIterator<Key, Value>::operator++() {
        currentNode = currentNode->next(currentNode);
        return *this;
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> MapIterator<Key, Value>::operator++(int) {
        MapIterator<Key, Value> res(*this);
        currentNode = currentNode->next(currentNode);
        return res;
    }

    // Map
    template<typename Key, typename Value>
    MapIterator<Key, Value> Map<Key, Value>::begin() const {
        return iterator(tree.min());
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> Map<Key, Value>::end() const {
        return iterator(nullptr);
    }

    template<typename Key, typename Value>
    bool Map<Key, Value>::isEmpty() const {
        return sizeOfTree == 0;
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> Map<Key, Value>::insert(Key key, Value value) {
        if (find(key) == end())
            ++sizeOfTree;
        return iterator(tree.insert(key, value));
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> Map<Key, Value>::find(Key key) {
        return iterator(tree.find(key));
    }

    template<typename Key, typename Value>
    Value &Map<Key, Value>::operator[](const Key &key) {
        Map<Key, Value>::iterator tmp1 = tree.find(key);
        if (tmp1 == end()) {
            Value v;
            // copying key
            Map<Key, Value>::iterator tmp2 = insert(key, v);
            return const_cast<Value &>(tmp2.getCurrentNode()->getValue());
        }
        return const_cast<Value &>(tmp1.getCurrentNode()->getValue());
    }

    template<typename Key, typename Value>
    Value &Map<Key, Value>::operator[](Key &&key) {
        Map<Key, Value>::iterator tmp1 = tree.find(key);
        if (tmp1 == end()) {
            Value v;
            // moving key
            Map<Key, Value>::iterator tmp2 = insert(std::move(key), v);
            return const_cast<Value &>(tmp2.getCurrentNode()->getValue());
        }
        return const_cast<Value &>(tmp1.getCurrentNode()->getValue());
    }

    template<typename Key, typename Value>
    Map<Key, Value> &Map<Key, Value>::operator=(const Map &other) {
        if (this != &other) {
            this->tree = other.tree;
            sizeOfTree = other.sizeOfTree;
            return *this;
        }
        else
            return *this;
    }

    template<typename Key, typename Value>
    MapIterator<Key, Value> Map<Key, Value>::erase(iterator toDelete) {
        if (toDelete != this->end())
            --sizeOfTree;
        return iterator(tree.erase(toDelete.getCurrentNode()));
    }

    template<typename Key, typename Value>
    Map<Key, Value> &Map<Key, Value>::operator=(Map &&other) noexcept {
        if (this != &other) {
            this->tree = other.tree;
            sizeOfTree = other.sizeOfTree;
            other.sizeOfTree = 0;

        }
        return *this;
    }
}

#endif //MAPTEMPLATE_MAP_H