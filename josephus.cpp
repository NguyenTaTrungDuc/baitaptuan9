#include <iostream>

using namespace std;

// Một Node đại diện cho 1 người chơi
struct Node {
    int data;
    Node* next;
};

// Hàm tạo danh sách liên kết vòng gồm N người
Node* VongTron(int N) {
    if (N <= 0) return nullptr;
    
    Node* head = new Node{1, nullptr};
    Node* prev = head;
    
    for (int i = 2; i <= N; ++i) {
        Node* newNode = new Node{i, nullptr};
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Nối người cuối với người đầu tạo thành vòng khép kín
    
    return head;
}

// Hàm mô phỏng trò chơi Josephus
int NguoiChienThang(int N, int M) {
    if (N <= 0) return 0;

    Node* curr = VongTron(N);
    Node* prev = curr;
    
    while (prev->next != curr) {
        prev = prev->next;
    }

    while (curr->next != curr) {
        for (int i = 0; i < M; ++i) {
            prev = curr;
            curr = curr->next;
        }
        
        Node* temp = curr;
        prev->next = curr->next;
        curr = curr->next;      
        
        delete temp;
    }
    
    int winner = curr->data;
    delete curr;
    
    return winner;
}

int main() {
    int N;
    cout << "Nhap so nguoi choi N: ";
    cin >> N;
    
    cout << "--- Ket qua voi N = " << N << " ---" << endl;
    cout << "Neu M = 1 -> Nguoi chien thang la: " << NguoiChienThang(N, 1) << endl;
    cout << "Neu M = 2 -> Nguoi chien thang la: " << NguoiChienThang(N, 2) << endl;
    cout << "Neu M = 3 -> Nguoi chien thang la: " << NguoiChienThang(N, 3) << endl;

    return 0;
}