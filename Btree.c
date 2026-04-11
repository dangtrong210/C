#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. ĐỊNH NGHĨA CẤU TRÚC
struct BTreeNode {
    int *keys;            // Mảng chứa các khóa
    int t;                // Bậc tối thiểu (minimum degree)
    struct BTreeNode **C; // Mảng các con trỏ trỏ đến các nút con
    int n;                // Số lượng khóa hiện tại
    bool leaf;            // true nếu là nút lá
};

// Hàm cấp phát bộ nhớ cho một nút mới
struct BTreeNode* createNode(int t, bool leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    
    // Cấp phát mảng keys (tối đa 2t - 1 khóa)
    newNode->keys = (int *)malloc((2 * t - 1) * sizeof(int));
    
    // Cấp phát mảng con trỏ (tối đa 2t nút con)
    newNode->C = (struct BTreeNode **)malloc((2 * t) * sizeof(struct BTreeNode *));
    newNode->n = 0;
    
    return newNode;
}

// 2. THAO TÁC TÌM KIẾM (SEARCH)
int findKey(struct BTreeNode *node, int k) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k) {
        idx++;
    }
    return idx;
}

struct BTreeNode* search(struct BTreeNode *node, int k) {
    int idx = findKey(node, k);
    // Tìm thấy khóa tại nút hiện tại
    if (idx < node->n && node->keys[idx] == k) {
        return node;
    }
    // Nếu là nút lá mà chưa thấy thì khóa không tồn tại
    if (node->leaf == true) {
        return NULL;
    }
    // Đệ quy tìm ở nút con
    return search(node->C[idx], k);
}

// 3. THAO TÁC CHÈN (INSERT) VÀ TÁCH NÚT (SPLIT)

// Hàm tách nút y (đang đầy) thành 2 nút, đẩy khóa ở giữa lên nút cha (node)
void splitChild(struct BTreeNode *node, int i, struct BTreeNode *y) {
    int t = node->t;
    // Tạo một nút mới z để chứa t-1 khóa cuối cùng của y
    struct BTreeNode *z = createNode(t, y->leaf);
    z->n = t - 1;

    // Chuyển t-1 khóa từ y sang z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    // Nếu y không phải nút lá, chuyển cả các con trỏ tương ứng
    if (y->leaf == false) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }
    y->n = t - 1; // Cập nhật lại số lượng khóa của y

    // Dịch chuyển các con trỏ của nút cha để tạo chỗ cho z
    for (int j = node->n; j >= i + 1; j--) {
        node->C[j + 1] = node->C[j];
    }
    node->C[i + 1] = z;

    // Dịch chuyển các khóa của nút cha để tạo chỗ cho khóa bị đẩy lên từ y
    for (int j = node->n - 1; j >= i; j--) {
        node->keys[j + 1] = node->keys[j];
    }
    node->keys[i] = y->keys[t - 1]; // Đẩy khóa giữa của y lên cha
    node->n = node->n + 1;
}

// Hàm chèn vào nút chưa đầy
void insertNonFull(struct BTreeNode *node, int k) {
    int i = node->n - 1;

    if (node->leaf == true) {
        // Dịch chuyển để tìm chỗ trống và chèn
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n = node->n + 1;
    } else {
        // Tìm nút con để đi xuống
        while (i >= 0 && node->keys[i] > k) {
            i--;
        }
        // Nếu nút con bị đầy, tiến hành tách trước khi đi xuống
        if (node->C[i + 1]->n == 2 * node->t - 1) {
            splitChild(node, i + 1, node->C[i + 1]);
            // Sau khi tách, nút con bị chia làm 2. Quyết định xem sẽ đi xuống nhánh nào.
            if (node->keys[i + 1] < k) {
                i++;
            }
        }
        insertNonFull(node->C[i + 1], k);
    }
}

// Hàm chèn chính (Xử lý cả trường hợp nút gốc bị đầy)
struct BTreeNode* insert(struct BTreeNode *root, int t, int k) {
    // Nếu cây rỗng
    if (root == NULL) {
        root = createNode(t, true);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }
    
    // Nếu nút gốc bị đầy, cây sẽ tăng thêm chiều cao
    if (root->n == 2 * t - 1) {
        struct BTreeNode *s = createNode(t, false);
        s->C[0] = root;
        splitChild(s, 0, root); // Tách nút gốc cũ
        
        // Chọn nhánh để chèn k vào
        int i = 0;
        if (s->keys[0] < k) {
            i++;
        }
        insertNonFull(s->C[i], k);
        return s; // Trả về nút gốc mới
    } else {
        insertNonFull(root, k);
        return root;
    }
}

// 4. HÀM DUYỆT CÂY & MAIN

// Duyệt Inorder (Giữa) để in các khóa theo thứ tự tăng dần
void traverse(struct BTreeNode *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (root->leaf == false) {
                traverse(root->C[i]);
            }
            printf(" %d", root->keys[i]);
        }
        // Duyệt nhánh con cuối cùng
        if (root->leaf == false) {
            traverse(root->C[i]);
        }
    }
}

int main() {
    int t ;
    printf("Nhap bac toi thieu (t) cua B-tree: ");
    scanf("%d", &t);
    struct BTreeNode *root = NULL;

    // Nhập các phần tử vào B-tree
    int n;
    printf("Nhap so luong khoa can chen: ");
    scanf("%d", &n);
    int elements[n];
    for(int i = 0; i < n; i++) {
        printf("Nhap khoa thu %d: ", i + 1);
        scanf("%d", &elements[i]);
    }
    int n_elements = sizeof(elements) / sizeof(elements[0]);
    
    for(int i = 0; i < n_elements; i++) {
        root = insert(root, t, elements[i]);
    }

    // In toàn bộ B-tree
    printf("Duyet B-tree (thu tu tang dan):");
    traverse(root);
    printf("\n\n");

    // Thử truy xuất
    int m;
    printf("Nhap so luong khoa can tim: ");
    scanf("%d", &m);
    int keys_to_find[m];
    for(int i = 0; i < m; i++) {
        printf("Nhap khoa thu %d: ", i + 1);
        scanf("%d", &keys_to_find[i]);
    }
    for(int i = 0; i < m; i++) {
        int k = keys_to_find[i];
        if (search(root, k) != NULL) {
            printf(">> Tim thay khoa %d trong B-tree.\n", k);
        } else {
            printf(">> Khong tim thay khoa %d.\n", k);
        }
    }

    return 0;
}