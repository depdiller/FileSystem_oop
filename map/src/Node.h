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
        ~Node() = default;;
        // getters
        const Key &getKey() const { return this->key; }
        const Value &getValue() const { return this->value; }
        Node<Key, Value> *getParent() const { return this->parent; }
        Node<Key, Value> *getLeft() const { return this->left; }
        Node<Key, Value> *getRight() const { return this->right; }
        // setters
        Node<Key, Value> &setParent(Node<Key, Value> *parent);
        Node<Key, Value> &setLeft(Node<Key, Value> *left);
        Node<Key, Value> &setRight(Node<Key, Value> *right);
        // methods for tree
        Node<Key, Value> *insert(Node<Key, Value> *head, Key key, Value value);
        Node<Key, Value> *search(Node<Key, Value> *ptrNode, Key key);
        Node<Key, Value> *min(Node<Key, Value> *ptrNode);
        const Node<Key, Value> *min(const Node<Key, Value> *ptrNode) const;
        Node<Key, Value> *max(Node<Key, Value> *ptrNode);
        Node<Key, Value> *next(Node<Key, Value> *ptrNode);
        const Node<Key, Value> *next(const Node<Key, Value> *ptrNode) const;
        Node<Key, Value> *clone(Node<Key, Value> *node, Node<Key, Value> *parent);
        void deleteNodeRecursion(Node<Key, Value> *ptrNode);
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
    void Node<Key, Value>::deleteNodeRecursion(Node<Key, Value> *ptrNode) {
        if (ptrNode != nullptr) {
            deleteNodeRecursion(ptrNode->left);
            deleteNodeRecursion(ptrNode->right);
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

    template<typename Key, typename Value>
    Node<Key, Value> *Node<Key, Value>::clone(Node<Key, Value> *node, Node<Key, Value> *parent) {
        if (node != nullptr) {
            auto *point = new Node(node->getKey(), node->getValue(), parent);
            point->left = this->clone(node->getLeft(), point);
            point->right = this->clone(node->getRight(), point);
            return point;
        }
        return nullptr;
    }

    template<typename Key, typename Value>
    Node<Key, Value> &Node<Key, Value>::setParent(Node<Key, Value> *parent) {
        this->parent = parent;
        return *this;
    }

    template<typename Key, typename Value>
    Node<Key, Value> &Node<Key, Value>::setLeft(Node<Key, Value> *left) {
        this->left = left;
        return *this;
    }

    template<typename Key, typename Value>
    Node<Key, Value> &Node<Key, Value>::setRight(Node<Key, Value> *right) {
        this->right = right;
        return *this;
    }

    template<typename Key, typename Value>
    const Node<Key, Value> *Node<Key, Value>::next(const Node<Key, Value> *ptrNode) const {
        if (ptrNode->right != nullptr)
            return min(const_cast<const Node<Key, Value>*>(ptrNode->right));
        const Node<Key, Value>* tmp = ptrNode->parent;
        while (tmp != nullptr && ptrNode == tmp->right) {
            ptrNode = tmp;
            tmp = tmp->parent;
        }
        return tmp;
    }

    template<typename Key, typename Value>
    const Node<Key, Value> *Node<Key, Value>::min(const Node<Key, Value> *ptrNode) const {
        while (ptrNode->left != nullptr) {
            ptrNode = ptrNode->left;
        }
        return const_cast<const Node<Key, Value>*>(ptrNode);
    }
}

#endif //MAPTEMPLATE_NODE_H
