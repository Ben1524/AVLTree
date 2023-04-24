#include<iostream>
#include<vector>
#include<string>

using namespace std;

typedef struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
}*AVLTreePtr;

class AVLTree {
public:
    AVLTree()=default;
    void insert(int key);
    // 删除AVL中值为key的节点
    AVLTreePtr deleteAVLNode(int key,AVLTreePtr node=root);
    int height(AVLTreePtr node);
    bool searchAVL(int key);
    AVLTreePtr rotateLeft(AVLTreePtr node);
    AVLTreePtr rotateRight(AVLTreePtr node);
    AVLTreePtr insertHelper(AVLTreePtr node, int key);
    int getBalance(AVLTreePtr node);
    AVLTreePtr minValueNode(AVLTreePtr node);
    void POSTTraversal(AVLTreePtr node=root)
    {
        if (node == NULL) {
            return;
        }
        POSTTraversal(node->left);
        POSTTraversal(node->right);
        cout << node->key << " ";
    }
    void INTraversal(AVLTreePtr node=root)
    {
        if (node == NULL) {
            return;
        }
        INTraversal(node->left);
        cout << node->key << " ";
        INTraversal(node->right);
    }
    void PRETraversal(AVLTreePtr node=root)
    {
        if (node == NULL) {
            return;
        }
        cout << node->key << " ";
        PRETraversal(node->left);
        PRETraversal(node->right);
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void traversal(string order)
    {
        if (isEmpty())
        {
            cout << "Empty" << endl;
            return;
        } else
        {
            if (order == "PRE")
            {
                PRETraversal();
            } else if (order == "IN")
            {
                INTraversal();
            } else if (order == "POST")
            {
                POSTTraversal();
            } else
            {
                cout << "Invalid order!" << endl;
            }
        }
    }
    private:
     static AVLTreePtr root;
};
inline
void AVLTree::insert(int key) {
    root = insertHelper(root, key);
}
inline
int AVLTree::height(AVLTreePtr node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }
inline
int AVLTree::getBalance(AVLTreePtr node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
bool AVLTree::searchAVL(int key) {
    AVLTreePtr current = root;
    while (current != NULL) {
        if (key == current->key) {
            return true;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}
AVLTreePtr AVLTree::rotateLeft(AVLTreePtr node) {
        AVLTreePtr rightChild = node->right;
        AVLTreePtr leftGrandChild = rightChild->left;

        rightChild->left = node;
        node->right = leftGrandChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        return rightChild;
}
AVLTreePtr AVLTree::rotateRight(AVLTreePtr node) {
        AVLTreePtr leftChild = node->left;
        AVLTreePtr rightGrandChild = leftChild->right;

        leftChild->right = node;
        node->left = rightGrandChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

        return leftChild;
}
AVLTreePtr AVLTree::insertHelper(AVLTreePtr node, int key){
        if (node == NULL) {
            AVLTreePtr newNode = new AVLNode;
            newNode->key = key;
            newNode->height = 1;
            newNode->left = newNode->right = NULL;
            return newNode;
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertHelper(node->right, key);
        }
        else {
            // Duplicate key, do nothing
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            // Left-Left case
            return rotateRight(node);
        }
        else if (balance > 1 && key > node->left->key) {
            // Left-Right case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else if (balance < -1 && key > node->right->key) {
            // Right-Right case
            return rotateLeft(node);
        }
        else if (balance < -1 && key < node->right->key) {
            // Right-Left case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
}
AVLTreePtr AVLTree::deleteAVLNode(int key,AVLTreePtr node) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = deleteAVLNode(key,node->left);
    }
    else if (key > node->key) {
        node->right = deleteAVLNode( key,node->right);
    }
    else {
        // Found the node to be deleted
        if(node==root&&node->left==NULL&&node->right==NULL)
        {
            delete node;
            root=NULL;
            return root;
        }
        if (node->left == NULL) {
            AVLTreePtr temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {
            AVLTreePtr temp = node->left;
            delete node;
            return temp;
        }
        AVLTreePtr temp = minValueNode(node->right);
        node->key = temp->key;
        node->right = deleteAVLNode(temp->key,node->right);
        if (node == NULL) {
        return node;
    }
}
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    else if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    else if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}


AVLTreePtr AVLTree::minValueNode(AVLTreePtr node) {
    AVLTreePtr current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
AVLTreePtr AVLTree:: root=NULL;
int main()
{
    AVLTree T;
    vector<string> v;
    string temp=" ";
    while(temp!="PRE"&&temp != "IN"&&temp != "POST")
    {
        cin>>temp;
        v.push_back(temp);
    }
    int data;
    for(int i=0;i<v.size()-1;i++)
    {
        data=stoi(v[i].substr(1));
        if(v[i][0]=='A'&&T.searchAVL(data)==false)
        {
            T.insert(data);
        }
        else if(v[i][0]=='D'&&T.searchAVL(data)==true)
        {
            T.deleteAVLNode(data);
        }
    }
    T.traversal(v[v.size()-1]);
}