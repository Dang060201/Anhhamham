#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc nút trong danh sách liên kết đơn
struct Node {
    int data;
    struct Node* next; //con trỏ next để trỏ đến nút kế tiếp trong danh sách
};

// Hàm để tạo một nút mới trả về con trỏ struct Node*
struct Node* createNode(int data) { 
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // ép kiểu trả về là struct Node* vì hàm malloc trả về void
    if (newNode == NULL) {
        printf("Khong du bo nho!\n");
        exit(1); // thoái khỏi chương trình ngay lập tức trả về mã lỗi là 1
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm để thêm một nút vào cuối danh sách
void appendNode(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* lastNode = *headRef;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

// Hàm để duyệt và in ra các phần tử trong danh sách
void traverse(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    // Thêm các nút vào danh sách
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);

    // Duyệt và in ra danh sách
    traverse(head);

    return 0;
}
