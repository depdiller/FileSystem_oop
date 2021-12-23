#ifndef MAPTEMPLATE_NODE_H
#define MAPTEMPLATE_NODE_H

namespace TemplateMap {
    template<typename Key, typename Value>
    class Node {
    private:
        Key key;
        Value value;
        Node *parent;
        Node *left;
        Node *right;
    public:
        // constructors
        Node() : parent(nullptr), left(nullptr), right(nullptr) {};
        Node(Key key, Value value, Node *parent);
        // getters
        Key getKey() const { return this->key; }
        const Value &getValue() const { return this->value; }
        Node<Key, Value> *getParent() const { return this->parent; }
        Node<Key, Value> *getLeft() const { return this->left; }
        Node<Key, Value> *getRight() const { return this->right; }
        // methods for tree
        Node<Key, Value> *insert(Node<Key, Value> *head, Key key, Value value);
        Node<Key, Value> *search(Node<Key, Value> *ptrNode, Key key);
        Node<Key, Value> *min(Node<Key, Value> *ptrNode);
        Node<Key, Value> *max(Node<Key, Value> *ptrNode);
        Node<Key, Value> *next(Node<Key, Value> *ptrNode);
        void deleteNode(Node<Key, Value> *ptrNode);
    };

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::insert(Node<Key, Value> *head, Key key, Value value) {
        Node<Key, Value> *newEl, *move_thru = head, *future_parent = nullptr;
        Node<Key, Value> *tmp = head->search(head, key);
        if (tmp == nullptr) {
            newEl = new Node(key, value, nullptr);
            while (move_thru != nullptr) {
                future_parent = move_thru;
                if (newEl->key < move_thru->key)
                    move_thru = move_thru->left;
                else
                    move_thru = move_thru->right;
            }
            newEl->parent = future_parent;
            if (future_parent == nullptr)
                head = newEl;
            else if (newEl->key < future_parent->key)
                future_parent->left = newEl;
            else
                future_parent->right = newEl;
        }
        else
            tmp->value = value;
        return head;
    }

    template<typename Key, typename Value>
    Node<Key, Value>::Node(Key key, Value value, Node *parent) {
        this->key = key;
        this->value = value;
        this->parent = parent;
        left = nullptr;
        right = nullptr;
    }

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::search(Node<Key, Value> *ptrNode, Key key) {
        if (ptrNode == nullptr || key == ptrNode->key)
            return ptrNode;
        else if (key < ptrNode->key)
            return search(ptrNode->left, key);
        else
            return search(ptrNode->right, key);
    }

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::min(Node<Key, Value> *ptrNode) {
        while (ptrNode->left != nullptr) {
            ptrNode = ptrNode->left;
        }
        return ptrNode;
    }

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::max(Node<Key, Value> *ptrNode) {
        while (ptrNode->right != nullptr) {
            ptrNode = ptrNode->right;
        }
        return ptrNode;
    }

    template<typename Key, typename Value>
    void Node<Key, Value>::deleteNode(Node<Key, Value> *ptrNode) {
        if (ptrNode != nullptr) {
            deleteNode(ptrNode->left);
            deleteNode(ptrNode->right);
            delete ptrNode;
        }
    }

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::next(Node<Key, Value> *ptrNode) {
        if (ptrNode->right != nullptr)
            return min(ptrNode->right);
        Node<Key, Value>* tmp = ptrNode->parent;
        while (tmp != nullptr && ptrNode == tmp->right) {
            ptrNode = tmp;
            tmp = tmp->parent;
        }
        return tmp;
    }
}

#endif //MAPTEMPLATE_NODE_H
