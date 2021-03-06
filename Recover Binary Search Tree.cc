/*
http://leetcode.com/onlinejudge#question_99

Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. 
Could you devise a constant space solution?

*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// =========================================================
// version 1, iterative version (with stack and vector)
// 340 milli secs pass large judge
// time complexity o(n), space complexity o(n)

class Solution {
public:
    // find misplaced node and swap the values
    void recoverTree(TreeNode *root) {
        vector<TreeNode *> nodes; // vector to store the inorder traversal sequence
        stack<TreeNode *> mid, right; // stacks to store the middle and right node
        TreeNode *left = root;
        
        // iterative version of inorder traversal
        while(left || !mid.empty()) {
            if(left) {
                mid.push(left);
                right.push(left->right);
                left = left->left;
            } else {
                nodes.push_back(mid.top());
                left = right.top();
                mid.pop();
                right.pop();
            }
        }
        
        TreeNode *err1=NULL, *err2=NULL;
        for(int i=1; i<nodes.size(); ++i)
            if(nodes[i-1]->val > nodes[i]->val) {
                if(!err1) err1 = nodes[i-1];
                err2 = nodes[i];
            }
        
        swap(err1->val, err2->val);
    }
};

// =========================================================
// version 2, recursive (in stack)
// 324 milli secs pass large judge
// time complexity o(n), space complexity o(log(n))

class Solution {
public:
    // find misplaced node and swap the values
    void recoverTree(TreeNode *root) {
        TreeNode *prev=NULL, *err1=NULL, *err2=NULL;
        recoverTree(root, prev, err1, err2);
        swap(err1->val, err2->val);
    }
    
    // use inorder traversal to find the misplaced node in the BST
    void recoverTree(TreeNode *root, TreeNode* &prev, 
                     TreeNode* &err1, TreeNode* &err2) {
        if(!root) return;
        
        recoverTree(root->left, prev, err1, err2);
           
        if(prev && prev->val > root->val) {
            if(!err1) err1 = prev; 
            err2=root;
        }
        prev = root;
            
        recoverTree(root->right, prev, err1, err2);
    }
};


// =========================================================
// version 3, Morris in-order traversal using threading, iterative, no stack
// 276 milli secs pass large judge
// time complexity o(n), space complexity o(1)

class Solution {
public:
    // find misplaced node and swap the values
    void recoverTree(TreeNode *root) {
        TreeNode *prev=NULL, *err1=NULL, *err2=NULL;
        
        while (root != NULL) {
            if (root->left==NULL) {             // 1) this node has no predecessor at left subtree
            
                if(prev && prev->val > root->val) {
                    if(!err1) err1 = prev;      // remember misplaced nodes
                    err2=root;
                }
                prev = root;                    // remember predecessor
                root = root->right;             // go to successor
            } else {
                TreeNode *p = root->left;       // find predecessor from left subtree
                while (p->right!=NULL && p->right!=root)
                    p = p->right;
                    
                if (p->right == NULL) {        // 2-1) if predecessor is not traverse yet
                    p->right = root;                // link the predecessor to current node
                    root = root->left;              // traverse the left subtree
                } else {                        // 2-2) if predecessor is traversed
                    p->right = NULL;                // unlink the predecessor
                    
                    if (prev && prev->val > root->val) {
                        if(!err1) err1 = prev;      // remember misplaced nodes
                        err2=root;
                    }
                    prev = root;                    // remember predecessor
                    root = root->right;             // go to successor
                } // end of: if (p->right == NULL)
            } // end of: if(root->left==NULL)
        } // end of: while (root != NULL)
        
        swap(err1->val, err2->val);
    } //  end of: void recoverTree(TreeNode *root)
};