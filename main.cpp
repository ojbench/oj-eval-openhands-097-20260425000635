
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build BST from level order traversal array
TreeNode* buildBSTFromLevelOrder(const vector<int>& levelOrder) {
    if (levelOrder.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(levelOrder[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < levelOrder.size()) {
        TreeNode* current = q.front();
        q.pop();
        
        // Insert left child
        if (i < levelOrder.size()) {
            TreeNode* leftChild = new TreeNode(levelOrder[i]);
            current->left = leftChild;
            q.push(leftChild);
            i++;
        }
        
        // Insert right child
        if (i < levelOrder.size()) {
            TreeNode* rightChild = new TreeNode(levelOrder[i]);
            current->right = rightChild;
            q.push(rightChild);
            i++;
        }
    }
    
    return root;
}

// Convert the binary tree to a proper BST by inserting values in BST order
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }
    
    return root;
}

// Build proper BST from level order values
TreeNode* buildProperBST(const vector<int>& values) {
    TreeNode* root = nullptr;
    for (int val : values) {
        root = insertIntoBST(root, val);
    }
    return root;
}

// Find k-th largest element using reverse inorder traversal
int kthLargest(TreeNode* root, int k, int& count) {
    if (root == nullptr) return -1;
    
    // Traverse right subtree first (larger elements)
    int right = kthLargest(root->right, k, count);
    if (count == k) return right;
    
    // Process current node
    count++;
    if (count == k) return root->val;
    
    // Traverse left subtree
    return kthLargest(root->left, k, count);
}

// Parse input format: root = [1,2,3], cnt = 2
void parseInput(vector<int>& rootValues, int& cnt) {
    string line;
    getline(cin, line);
    
    // Extract root array
    size_t rootStart = line.find('[');
    size_t rootEnd = line.find(']');
    if (rootStart != string::npos && rootEnd != string::npos) {
        string rootStr = line.substr(rootStart + 1, rootEnd - rootStart - 1);
        stringstream ss(rootStr);
        string token;
        
        while (getline(ss, token, ',')) {
            // Remove whitespace and convert to int
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
            if (!token.empty()) {
                rootValues.push_back(stoi(token));
            }
        }
    }
    
    // Extract cnt
    size_t cntStart = line.find("cnt =");
    if (cntStart != string::npos) {
        string cntStr = line.substr(cntStart + 6);
        cnt = stoi(cntStr);
    }
}

int main() {
    vector<int> rootValues;
    int cnt;
    
    parseInput(rootValues, cnt);
    
    // Build BST
    TreeNode* root = buildProperBST(rootValues);
    
    // Find k-th largest element
    int count = 0;
    int result = kthLargest(root, cnt, count);
    
    cout << result << endl;
    
    return 0;
}
