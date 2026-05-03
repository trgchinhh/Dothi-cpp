#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// số đỉnh tối đa
const int MAXDSK = 15;
const int MAXDSC = MAXDSK*MAXDSK;

struct Node {
    int dinhke;
    int trongso = 0;
    Node* link;
};
typedef Node* Nodeptr;

struct Canh {
    int dinhdau; 
    int dinhcuoi;
    int trongso = 0;
};

struct DanhSachKe {
    int sodinh = 0;
    Nodeptr dsk[MAXDSK];
};

struct DanhSachCanh {
    int socanh = 0;
    Canh dsc[MAXDSC];
};

struct DanhSachDinhDaTham {
    int sodinhdatham = 0;
    int dsd[MAXDSK];
};

struct Topo {
    int soluongdinh = 0;
    int dstopo[MAXDSK];
};

// =========================================
//                KHAI BÁO
// =========================================

// doc file lay do thi 
int docfile(const char* tenfile, DanhSachKe& dsk, int flag);

// tao moi mang visited
void taomoimangvisited(bool visited[], int n);

// tao moi ds dinh
void taomoidanhsachdinh(DanhSachDinhDaTham& dsd);

// tao moi ds canh 
void taomoidanhsachcanh(DanhSachCanh& dsc);

// tao moi ds topo
void taomoidanhsachtopo(Topo& topo);

// ham nhap dinh 
void nhapdinhmuonduyet(DanhSachKe& dsk, int& dinh);

// duyet ds dinh 
void duyetds_dinh(DanhSachDinhDaTham& dsd);

// duyet ds canh 
void duyetds_canh(DanhSachCanh& dsc);

// =========================================
//              LÀM BÀI TẬP
// =========================================

// cau 1: duyet do thi theo chieu rong bfs
void cau_1(DanhSachKe& dsk, int dinh, bool visited[]);

// cau 2: duyet do thi bfs cua dinh v bat dau va luu cac dinh vao mang av, luu cac canh vao ae
void cau_2(DanhSachKe& dsk, int v, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc);

// cau 3: duyet do thi tất cả đỉnh bfs va luu cac dinh vao mang av, luu cac canh vao ae
void cau_3(DanhSachKe& dsk, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc);

// cau 4: duyet do thi dfs 
void cau_4(DanhSachKe& dsk, int dinh, bool visited[]);

// cau 5: duyet do thi dfs co dinh v bat dau va luu cac dinh vao mang av, luu cac canh vao ae 
void cau_5(DanhSachKe& dsk, int v, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc);

// cau 6: duyet do thi dfs va luu cac dinh vao mang av, luu cac canh vao ae
void cau_6_duyetdfs(DanhSachKe& dsk, int dinh, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc);
void cau_6(DanhSachKe& dsk, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc);

// cau 7: dfs dt vo huong, tra ve so nguyen la thanh phan lien thong
void cau_7_duyetdfs(DanhSachKe& dsk, int dinh, bool visited[]);
int cau_7_dfs(DanhSachKe& dsk, bool visited[]);
// cau 7: bfs dh vo huong, tra ve so nguyen la thanh phan lien thong
int cau_7_bfs(DanhSachKe& dsk, bool visited[]);

// cau 8: dfs dt co huong, kiem tra dt co lien thong manh (chưa làm)
bool cau_8_dfs(DanhSachKe& dsk);

// cau 9: dfs dt co huong, tra ve tap dinh sap xep topo (chưa làm)
void cau_9_dfs_topo(DanhSachKe& dsk, int dinh, bool visited[], Topo& topo);
DanhSachDinhDaTham cau_9(DanhSachKe& dsk, bool visited[], Topo& topo);

// cau 10: sap xep tap canh giam dan theo do thi co trong so
void cau_10(DanhSachCanh& dsc);

// cau 11: kiem tra do thi co phai la 1 cay hay khong
bool kiemtrachutrinh(DanhSachKe& dsk, int dinh, int dinhcha, bool visited[]);
bool cau_11(DanhSachKe& dsk, bool visited[]);
