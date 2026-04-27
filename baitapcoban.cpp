#include <iostream>
#include <cstring> 

using namespace std;

// KHAI BÁO DỮ LIỆU

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    int maSV;
    char hoTen[50];
    int gioiTinh;   // 1 = Nam ; 0 = Nữ
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

// Hàm khởi tạo danh sách
void InitList(List &l) {
    l.first = NULL;
    l.last = NULL;
}


// NHẬP VÀO DANH SÁCH SINH VIÊN VÀ SẮP XẾP TĂNG DẦN THEO MÃ SINH VIÊN
// Hàm nhập thông tin sinh viên
void NhapSinhVien(SinhVien &sv) {
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV; 
    cin.ignore();
    
    cout << "Nhap ho ten: ";
    cin.getline(sv.hoTen, 50);
    
    cout << "Nhap gioi tinh (1: Nam, 0: Nu): ";
    cin >> sv.gioiTinh;
    
    cout << "Nhap ngay sinh (ngay thang nam cach nhau boi dau cach): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
    
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, 100);
    
    cout << "Nhap lop: ";
    cin.getline(sv.lop, 12);
    
    cout << "Nhap khoa: ";
    cin.getline(sv.khoa, 7);
}

// Hàm in ra sinh viên
void InSinhVien(SinhVien sv) {
    cout << "Ma SV: " << sv.maSV << " | Ho ten: " << sv.hoTen 
         << " | Ngay sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << endl;
}

// Hàm so sánh ngày sinh của sinh viên
int SoSanhNgaySinh(Ngay d1, Ngay d2) {
    if (d1.nam != d2.nam) return d1.nam - d2.nam;
    if (d1.thang != d2.thang) return d1.thang - d2.thang;
    return d1.ngay - d2.ngay;
}


// THÊM SINH VIÊN VÀO DANH SÁCH ĐỒNG THỜI SẮP XẾP THEO ĐÚNG THỨ TỰ
void ThemCoSapXep(List &l, SinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = NULL;

    if (l.first == NULL) {
        l.first = l.last = newNode;
        return;
    }

    if (sv.maSV < l.first->data.maSV) {
        newNode->link = l.first;
        l.first = newNode;
        return;
    }

    Node* prev = l.first;
    Node* curr = l.first->link;
    
    while (curr != NULL && curr->data.maSV < sv.maSV) {
        prev = curr;
        curr = curr->link;
    }

    newNode->link = curr;
    prev->link = newNode;

    if (curr == NULL) {
        l.last = newNode;
    }
}

// Hàm in danh sách sinh viên
void InDanhSach(List l) {
    Node* p = l.first;
    if (p == NULL) cout << "Danh sach rong!" << endl;
    while (p != NULL) {
        InSinhVien(p->data);
        p = p->link;
    }
}


// IN RA SINH VIÊN CÓ CÙNG NGÀY SINH
void InSinhVienCungNgaySinh(List l) {
    bool timThayBatKy = false;

    for (Node* p = l.first; p != NULL; p = p->link) {
        bool daXuLy = false;
        for (Node* check = l.first; check != p; check = check->link) {
            if (SoSanhNgaySinh(p->data.ngaySinh, check->data.ngaySinh) == 0) {
                daXuLy = true;
                break;
            }
        }
        if (daXuLy) continue; 

        bool coNguoiGiong = false;
        for (Node* q = p->link; q != NULL; q = q->link) {
            if (SoSanhNgaySinh(p->data.ngaySinh, q->data.ngaySinh) == 0) {
                if (!coNguoiGiong) {
                    cout << "\n--- Nhom sinh vien sinh ngay " << p->data.ngaySinh.ngay << "/" 
                         << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << " ---\n";
                    InSinhVien(p->data);
                    coNguoiGiong = true;
                    timThayBatKy = true;
                }
                InSinhVien(q->data); 
            }
        }
    }

    if (!timThayBatKy) {
        cout << "\nKhong tim thay sinh vien cung ngay sinh\n";
    }
}


// XOÁ SINH VIÊN CÓ CÙNG NGÀY SINH

void XoaTheoNgaySinh(List &l, Ngay d) {
    Node* prev = NULL;
    Node* curr = l.first;
    
    while (curr != NULL) {
        if (SoSanhNgaySinh(curr->data.ngaySinh, d) == 0) {
            Node* temp = curr;
            if (prev == NULL) { 
                l.first = curr->link;
                if (l.first == NULL) l.last = NULL;
                curr = l.first;
            } else { 
                prev->link = curr->link;
                if (curr->link == NULL) l.last = prev; 
                curr = prev->link;
            }
            delete temp;
        } else {
            prev = curr;
            curr = curr->link;
        }
    }
}

void LoaiBoSinhVienCungNgaySinh(List &l) {
    Node* curr = l.first;
    while (curr != NULL) {
        Ngay d = curr->data.ngaySinh;
        int dem = 0;
        
        for (Node* t = l.first; t != NULL; t = t->link) {
            if (SoSanhNgaySinh(d, t->data.ngaySinh) == 0) dem++;
        }
        
        if (dem > 1) {
            XoaTheoNgaySinh(l, d);
            curr = l.first; 
        } else {
            curr = curr->link; 
        }
    }
    cout << "\nDa loai bo cac sinh vien co cung ngay sinh." << endl;
}


// HÀM MAIN
int main() {
    List ListSV;
    InitList(ListSV);

    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "\n--- Nhap thong tin sinh vien thu " << i + 1 << " ---\n";
        NhapSinhVien(sv);
        ThemCoSapXep(ListSV, sv); 
    }

    cout << "\n*) DANH SACH SINH VIEN (SAP XEP TANG DAN THEO MA SINH VIEN):\n";
    InDanhSach(ListSV);

    cout << "\n*) IN RA SINH VIEN CO CUNG NGAY SINH";
    InSinhVienCungNgaySinh(ListSV);

    cout << "\n*) XOA SINH VIEN CO CUNG NGAY SINH";
    LoaiBoSinhVienCungNgaySinh(ListSV);
    cout << "\n*) Danh sach sau khi loai bo:\n";
    InDanhSach(ListSV);

    return 0;
}