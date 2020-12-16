/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* r = t->right;
    Node* temp = r->left;
    t->right = temp;
    r->left = t;
    t->height = std::max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = r;
    t->height = std::max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * l = t->left;
    Node * temp = l->right;
    t->left = temp;
    l->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    t = l;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL){
        return;
    }
    int b = (heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right));
    if(b == -2){
        int r = (heightOrNeg1(subtree->right->left)-heightOrNeg1(subtree->right->right));
        if(r == -1){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    if(b == 2){
        int l = (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right));
        if(l == 1){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        subtree = new Node(key, value);
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
    }
    else if(key >= subtree->key){
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree->right = NULL;
            subtree->left = NULL;
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* r = subtree->right;
            Node* l = subtree->left;
            if(l != NULL){
                delete subtree;
                subtree = l;
            }
            else if(r != NULL){
                delete subtree;
                subtree = r;
            }
            else{
                delete subtree;
                subtree = NULL;
            }
        }
        // your code here
    }
    rebalance(subtree);
}
