/*
平衡二叉树(Balanced binary tree)：平衡二叉树是解决普通BST可能退化问题的关键数据结构。
一、定义：
    平衡二叉树是满足以下条件的二叉排序树：
        是二叉排序树（左<根<右）
        任意节点的左右子树高度差不超过1
        每个子树也是平衡二叉树

二、平衡因子
    1.定义：平衡因子 = 左子树高度 - 右子树高度

    2.特点：平衡二叉树要求每个节点的平衡因子绝对值 ≤ 1，即：
        平衡因子 = {-1, 0, 1} 表示平衡
        平衡因子 = 2 或 -2 表示不平衡，需要调整

    3.平衡二叉树等价定义：每个节点的平衡因子绝对值 ≤ 1的二叉排序树

三、最小不平衡子树：当对平衡二叉树插入节点导致其不平衡，那么从插入点开始向上回溯，第一个失衡的点。
        注：对失衡的平衡二叉树进行调整时，需要先找到最小不平衡子树。

三、AVL树：
    1.定义：最经典、最严格的平衡二叉树实现就是AVL树(注：近似平衡的还有红黑树等)。

    2.核心思想：在二叉排序树的基础上，通过平衡因子监控树的平衡状态，在插入/删除时通过旋转操作动态
        调整树结构，使树高保持在对数级别，从而保证所有操作的最坏时间复杂度为O(log n)。

四、AVL树的实现————旋转操作（保持平衡的关键）
    1. 右旋(LL型不平衡)：
            插入在左子树的左子树导致失衡，则先寻找最小不平衡子树这个节点，然后向下找下一个节点，
        以该节点为轴，顺时针旋转。

    2. 左旋(RR型不平衡)：
            插入在右子树的右子树导致失衡，则先寻找最小不平衡子树这个节点，然后向下找下一个节点，
        以该节点为轴，逆时针旋转。

    3. 先左旋后右旋(LR型不平衡)：
            插入在左子树的右子树导致失衡，则先寻找最小不平衡子树这个节点，然后向下找下一个节点，将
        该节点与插入节点构成的图形旋转，直到插入节点位置与该节点互换，再按插入节点为轴顺时针旋转。

    4. 先右旋后左旋(RL型不平衡)：
            插入在右子树的左子树导致失衡，则先寻找最小不平衡子树这个节点，然后向下找下一个节点，将
        该节点与插入节点构成的图形旋转，直到插入节点位置与该节点互换，再按插入节点为轴逆时针旋转。

五、优缺点总结
    1.优点
        最坏情况性能有保证：所有操作时间复杂度稳定为O(log n)
        查找效率高：适合查找密集的应用
        结构紧凑：相比BST，不会退化成链表
        有序性：中序遍历可得有序序列

    2.缺点
        实现复杂：插入删除需要维护平衡因子和旋转
        存储开销：每个节点需要额外存储高度信息
        旋转开销：频繁插入删除时旋转操作较多
        略微不平衡：严格平衡可能增加旋转次数

六、应用场景
    数据库索引：早期数据库使用AVL树作为内存索引
    内存中的有序集合：C++的std::map、Java的TreeMap（使用红黑树，类似原理）
    几何计算：区间树、线段树等数据结构的基础
    编译器实现：符号表管理
    路由表：网络路由器中的路由查找

七、实际使用建议
    1.选择AVL树的情况：
        查找操作远多于插入删除
        需要最坏情况性能保证
        数据相对静态

    2.现代替代方案：
        跳表（Skip List）：概率平衡，实现简单
        B+树：数据库索引主流
        哈希表+链表：O(1)平均查找
*/
#include <stdio.h>
#include <stdlib.h>


// ============================== AVL树的结构和基本操作 ================================
// AVL树节点定义
typedef struct AVLNode {
    int key;                    // 关键字
    int height;                 // 节点高度（平衡因子由此计算）
    struct AVLNode *left;       // 左孩子
    struct AVLNode *right;      // 右孩子
} AVLNode, *AVLTree;

// 获取节点高度
int getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// 计算平衡因子
int getBalanceFactor(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 更新节点高度
void updateHeight(AVLNode* node) {
    if (node == NULL) return;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 中序遍历打印
void inOrder(AVLNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d(h=%d, bf=%d) ", root->key, root->height, getBalanceFactor(root));
        inOrder(root->right);
    }
}

// 前序遍历打印
void preOrder(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


// ============================ 旋转操作（保持平衡的关键）===========================
// 右旋（LL型不平衡）
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // 执行旋转
    x->right = y;
    y->left = T2;
    
    // 更新高度（先更新子节点，再更新父节点）
    updateHeight(y);
    updateHeight(x);
    
    return x;  // 返回新的根
}

// 左旋（RR型不平衡）
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // 执行旋转
    y->left = x;
    x->right = T2;
    
    // 更新高度
    updateHeight(x);
    updateHeight(y);
    
    return y;  // 返回新的根
}

// 先左旋后右旋（LR型不平衡）
AVLNode* leftRightRotate(AVLNode* z) {
    z->left = leftRotate(z->left);  // 先对左孩子左旋
    return rightRotate(z);           // 再对根右旋
}

// 先右旋后左旋（RL型不平衡）
AVLNode* rightLeftRotate(AVLNode* z) {
    z->right = rightRotate(z->right);  // 先对右孩子右旋
    return leftRotate(z);              // 再对根左旋
}


// =========================== 查找操作（与普通BST完全相同）===========================
// 递归查找
AVLNode* AVL_Search(AVLNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    
    if (key < root->key) {
        return AVL_Search(root->left, key);
    } else {
        return AVL_Search(root->right, key);
    }
}

// 迭代查找
AVLNode* AVL_Search_Iter(AVLNode* root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}


// ================================ 插入操作 =====================================
AVLNode* AVL_Insert(AVLNode* root, int key) {
    // 1. 标准BST插入
    if (root == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;  // 新节点高度为1
        return newNode;
    }
    
    if (key < root->key) {
        root->left = AVL_Insert(root->left, key);
    } else if (key > root->key) {
        root->right = AVL_Insert(root->right, key);
    } else {
        return root;  // 重复值不插入
    }
    
    // 2. 更新当前节点高度
    updateHeight(root);
    
    // 3. 获取平衡因子
    int balance = getBalanceFactor(root);
    
    // 4. 根据平衡因子进行旋转调整
    // LL情况
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    
    // RR情况
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    
    // LR情况
    if (balance > 1 && key > root->left->key) {
        return leftRightRotate(root);
    }
    
    // RL情况
    if (balance < -1 && key < root->right->key) {
        return rightLeftRotate(root);
    }
    
    return root;  // 如果不需要调整，返回原节点
}


// ================================ 删除操作 =====================================
// 查找最小节点（用于删除有两个孩子的节点时）
AVLNode* findMin(AVLNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

AVLNode* AVL_Delete(AVLNode* root, int key) {
    // 1. 标准BST删除
    if (root == NULL) return root;
    
    if (key < root->key) {
        root->left = AVL_Delete(root->left, key);
    } else if (key > root->key) {
        root->right = AVL_Delete(root->right, key);
    } else {
        // 找到要删除的节点
        // 情况1：无子节点或只有一个子节点
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {  // 无子节点
                temp = root;
                root = NULL;
            } else {  // 有一个子节点
                *root = *temp;  // 复制子节点内容
            }
            free(temp);
        } else {
            // 情况2：有两个子节点
            // 找到右子树的最小节点（后继）
            AVLNode* temp = findMin(root->right);
            // 用后继的值替换当前节点
            root->key = temp->key;
            // 删除后继节点
            root->right = AVL_Delete(root->right, temp->key);
        }
    }
    
    // 如果树为空
    if (root == NULL) return root;
    
    // 2. 更新当前节点高度
    updateHeight(root);
    
    // 3. 获取平衡因子
    int balance = getBalanceFactor(root);
    
    // 4. 根据平衡因子进行旋转调整
    // LL情况
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // LR情况
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        return leftRightRotate(root);
    }
    
    // RR情况
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // RL情况
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        return rightLeftRotate(root);
    }
    
    return root;
}



int main() {
    AVLNode* root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};
    
    printf("插入序列: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", keys[i]);
        root = AVL_Insert(root, keys[i]);
    }
    printf("\n");
    
    printf("中序遍历(包含高度和平衡因子): ");
    inOrder(root);
    printf("\n");
    
    printf("前序遍历: ");
    preOrder(root);
    printf("\n");
    
    // 演示删除
    printf("\n删除30后:\n");
    root = AVL_Delete(root, 30);
    printf("中序遍历: ");
    inOrder(root);
    printf("\n");
    
    printf("删除40后:\n");
    root = AVL_Delete(root, 40);
    printf("中序遍历: ");
    inOrder(root);
    printf("\n");
    
    return 0;
}