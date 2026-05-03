#include "thuvien.h"

void menu(){
    cout << "┌───────────────────┐" << endl;
    cout << "│    MENU DO THI    │" << endl;
    cout << "├───────────────────┘" << endl;
    cout << "│ [00] Thoat chuong trinh" << endl;
    cout << "│ [01] Duyet do thi theo BFS" << endl;
    cout << "│ [02] BFS tu dinh v, luu dinh va canh" << endl;
    cout << "│ [03] BFS toan bo do thi, luu dinh va canh" << endl;
    cout << "│ [04] Duyet do thi theo DFS" << endl;
    cout << "│ [05] DFS tu dinh v, luu dinh va canh" << endl;
    cout << "│ [06] DFS toan bo do thi, luu dinh va canh" << endl;
    cout << "│ [07] Dem thanh phan lien thong (do thi vo huong)" << endl;
    cout << "│ [09] Duyet tap canh da duoc sap xep topo" << endl;
    cout << "│ [10] Sap xep tap canh giam dan theo trong so" << endl;
    cout << "│ [11] Kiem tra do thi la cay" << endl;
    cout << "└───> Nhap lua chon: ";
}

int main(){
    system("cls");
    DanhSachKe dsk1, dsk2;
    if(!docfile("dothi1.txt", dsk1, 1) || !docfile("dothi2.txt", dsk2, 1)){
        cout << "Da xay ra loi khi doc file !" << endl;
        return -1;
    }
    bool visited[MAXDSK];
    DanhSachDinhDaTham dsd1;
    DanhSachCanh dsc1;
    Topo topo;

    DanhSachCanh dscvd; 
    dscvd.socanh = 9;
    dscvd.dsc[0] = {0, 1, 4};
    dscvd.dsc[1] = {0, 2, 2};
    dscvd.dsc[2] = {1, 2, 5};
    dscvd.dsc[3] = {1, 3, 10};
    dscvd.dsc[4] = {2, 3, 3};
    dscvd.dsc[5] = {2, 4, 7};
    dscvd.dsc[6] = {3, 4, 1};
    dscvd.dsc[7] = {3, 5, 6};
    dscvd.dsc[8] = {4, 5, 8};

    while(1){
        system("cls");
        taomoimangvisited(visited, MAXDSK);
        taomoidanhsachdinh(dsd1);
        taomoidanhsachcanh(dsc1);
        taomoidanhsachtopo(topo);
        menu();
        int luachon; cin >> luachon;
        if(luachon == 1){
            int dinh1; nhapdinhmuonduyet(dsk1, dinh1);
            cout << "\nDuyet BFS: "; 
            cau_1(dsk1, dinh1, visited); 
            cout << endl;
        } 
        else if(luachon == 2){
            int dinh2; nhapdinhmuonduyet(dsk1, dinh2);
            cout << "\nDuyet BFS: ";
            cau_2(dsk1, dinh2, visited, dsd1, dsc1);
            cout << endl;
            duyetds_dinh(dsd1);
            duyetds_canh(dsc1);
        } 
        else if(luachon == 3){
            cout << "\nDuyet BFS: ";
            cau_3(dsk1, visited, dsd1, dsc1);
            cout << endl;
        } 
        else if(luachon == 4){
            int dinh4; nhapdinhmuonduyet(dsk1, dinh4);
            cout << "\nDuyet DFS: ";
            cau_4(dsk1, dinh4, visited);
            cout << endl;   
        } 
        else if(luachon == 5){
            int dinh5; nhapdinhmuonduyet(dsk1, dinh5);
            cout << "\nDuyet DFS: ";
            cau_5(dsk1, dinh5, visited, dsd1, dsc1);
            cout << endl;
            duyetds_dinh(dsd1);
            duyetds_canh(dsc1);
        } 
        else if(luachon == 6){
            cout << "\nDuyet BFS: ";
            cau_6(dsk1, visited, dsd1, dsc1);
            cout << endl;
        } 
        else if(luachon == 7){
            cout << endl;
            cout << "[1] Duyệt DFS" << endl;
            cout << "[2] Duyệt BFS" << endl;
            cout << "--> Lua chon: ";
            int chon; cin >> chon;
            if(chon == 1){
                cout << "\nSo thanh phan lien thong: " << cau_7_dfs(dsk1, visited);
            } 
            else {
                cout << "\nSo thanh phan lien thong: " << cau_7_bfs(dsk1, visited);
            }
            cout << endl;
        } 
        else if(luachon == 9){
            cout << "\nTap dinh sau khi duoc sap xep topo\n";
            DanhSachDinhDaTham dsd = cau_9(dsk1, visited, topo);
            duyetds_dinh(dsd); 
            cout << endl;
        } 
        else if(luachon == 10){
            // cho tap canh vi du 
            cout << "\nDanh sach canh sau khi sap xep giam dan theo trong so\n";
            cau_10(dscvd);
            duyetds_canh(dscvd);
            cout << endl;
        } 
        else if(luachon == 11){
            bool dothilacay = cau_11(dsk2, visited);
            cout << boolalpha << "\nDo thi la cay: " << dothilacay << endl;
        } 
        else if(luachon == 0){
            cout << "\nThoat chuong trinh" << endl;
            exit(0);
        } 
        else {
            cout << "\nVui long chon theo menu !" << endl;
        }
        system("pause");
    }
    return 0;
}
