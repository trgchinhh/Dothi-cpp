#include "thuvien.h"

// =========================================
//                KHAI BÁO
// =========================================

int docfile(const char* tenfile, DanhSachKe& dsk, int flag) {
    FILE* f = fopen(tenfile, "rt");
    if (f == NULL){
        cout << "Khong the doc file: " << tenfile << endl;
        return 0;        
    } 
    fscanf(f, "%d", &dsk.sodinh);
    for (int i = 0; i < dsk.sodinh; i++) 
        dsk.dsk[i] = NULL;
    for (int i = 0; i < dsk.sodinh; i++) {
        int m; 
        fscanf(f, "%d", &m); 
        for (int j = 0; j < m; j++) {
            Node* p = new Node;
            p->link = NULL;
            if (flag) 
                fscanf(f, "%d%d", &p->dinhke, &p->trongso);
            else  
                fscanf(f, "%d", &p->dinhke);
            if(dsk.dsk[i] == NULL) 
                dsk.dsk[i] = p;
            else {
                Nodeptr q = dsk.dsk[i];
                while(q->link != NULL){
                    q=q->link;
                }
                q->link=p;
            }
        }
    }
    fclose(f);
    cout << "Da doc file: " << tenfile << endl;
    return 1;
}

void taomoimangvisited(bool visited[], int n){
    fill(visited, visited+n, false);
}

void nhapdinhmuonduyet(DanhSachKe& dsk, int& dinh){
    do {
        cout << "\t(?) Nhap dinh (0 -> " << dsk.sodinh - 1 << "): ";
        cin >> dinh;
        if(dinh > 0 || dinh < dsk.sodinh -1) break;
    } while(1);
}

void taomoidanhsachdinh(DanhSachDinhDaTham& dsd){
    dsd.sodinhdatham = 0;
}

void taomoidanhsachcanh(DanhSachCanh& dsc){
    dsc.socanh = 0;
}

void taomoidanhsachtopo(Topo& topo){
    topo.soluongdinh = 0;
}

void duyetds_dinh(DanhSachDinhDaTham& dsd){
    cout << "Cac dinh trong ds: ";
    for(int i = 0; i < dsd.sodinhdatham; i++){
        cout << dsd.dsd[i] << " ";
    }
    cout << endl;
}

// duyet ds canh 
void duyetds_canh(DanhSachCanh& dsc){
    cout << "Cac canh trong ds:\n";
    for(int i = 0; i < dsc.socanh; i++){
        Canh c = dsc.dsc[i];
        cout << "(" << c.dinhdau << " , "
             << c.dinhcuoi << " , " 
             << c.trongso << ")" << endl;
    }
}

// =========================================
//              LÀM BÀI TẬP
// =========================================

void cau_1(DanhSachKe& dsk, int dinh, bool visited[]){
    queue<int> q;
    q.push(dinh);
    visited[dinh] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << " ";
        Nodeptr p = dsk.dsk[u];
        while(p != NULL){
            int v = p->dinhke;
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
            }
            p=p->link;
        }
    }
}

void cau_2(DanhSachKe& dsk, int v, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc){
    queue<int> q;
    q.push(v);
    visited[v] = true;
    dsd.dsd[dsd.sodinhdatham++] = v;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << " ";
        Nodeptr p = dsk.dsk[u];
        while(p != NULL){
            int v = p->dinhke;
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
                dsd.dsd[dsd.sodinhdatham++] = v;
                Canh c = {u, v, p->trongso};
                dsc.dsc[dsc.socanh++] = c;
            }
            p=p->link;
        }
    }
}

void cau_3(DanhSachKe& dsk, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc){
    for(int i = 0; i < dsk.sodinh; i++){
        taomoimangvisited(visited, MAXDSK);
        dsd.sodinhdatham = 0;
        dsc.socanh = 0;
        cout << "\nDang duyet dinh " << i << ": ";
        cau_2(dsk, i, visited, dsd, dsc);
        cout << endl;
        duyetds_dinh(dsd);
        duyetds_canh(dsc); 
    }
}

void cau_4(DanhSachKe& dsk, int dinh, bool visited[]){
    visited[dinh] = true;
    cout << dinh << " ";
    Nodeptr p = dsk.dsk[dinh];
    while(p != NULL){
        int u = p->dinhke;
        if(!visited[u]){
            cau_4(dsk, u, visited);
        }
        p=p->link;
    }
}

void cau_5(DanhSachKe& dsk, int v, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc){
    visited[v] = true;
    cout << v << " ";
    Nodeptr p = dsk.dsk[v];
    dsd.dsd[dsd.sodinhdatham++] = v;
    while(p != NULL){
        int u = p->dinhke;
        if(!visited[u]){
            Canh c = {v, u, p->trongso};
            dsc.dsc[dsc.socanh++] = c;
            cau_5(dsk, u, visited, dsd, dsc);
        }
        p=p->link;
    } 
}

void cau_6_duyetdfs(DanhSachKe& dsk, int dinh, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc){
    visited[dinh] = true;
    cout << dinh << " ";
    Nodeptr p = dsk.dsk[dinh];
    dsd.dsd[dsd.sodinhdatham++] = dinh;
    while(p != NULL){
        int u = p->dinhke;
        if(!visited[u]){
            Canh c = {dinh, u, p->trongso};
            dsc.dsc[dsc.socanh++] = c;
            cau_6_duyetdfs(dsk, u, visited, dsd, dsc);
        }
        p=p->link;
    } 
}

void cau_6(DanhSachKe& dsk, bool visited[], DanhSachDinhDaTham& dsd, DanhSachCanh& dsc){
    for(int i = 0; i < dsk.sodinh; i++){
        taomoimangvisited(visited, MAXDSK);
        dsd.sodinhdatham = 0;
        dsc.socanh = 0;
        if(!visited[i]){
            cout << "\nDang duyet dinh " << i << ": ";
            cau_6_duyetdfs(dsk, i, visited, dsd, dsc);
            cout << endl;
            duyetds_dinh(dsd);
            duyetds_canh(dsc); 
        }
    }
}

void cau_7_duyetdfs(DanhSachKe& dsk, int dinh, bool visited[]){
    visited[dinh] = true;
    Nodeptr p = dsk.dsk[dinh];
    while(p != NULL){
        int u = p->dinhke;
        if(!visited[u]){
            cau_7_duyetdfs(dsk, u, visited);            
        }
        p=p->link;
    }
}

int cau_7_dfs(DanhSachKe& dsk, bool visited[]){
    int dem = 0;
    for(int i = 0; i < dsk.sodinh; i++){
        if(!visited[i]){
            dem++;
            cau_7_duyetdfs(dsk, i, visited);
        }
    }
    return dem;
}

int cau_7_bfs(DanhSachKe& dsk, bool visited[]){
    int dem = 0;
    for(int i = 0; i < dsk.sodinh; i++){
        if(!visited[i]){
            dem++;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                Nodeptr p = dsk.dsk[u];
                while(p != NULL){
                    int v = p->dinhke;
                    if(!visited[v]){
                        q.push(v);
                        visited[v] = true;
                    }
                    p=p->link;
                }
            }
        }
    }
    return dem;
}

void cau_9_dfs_topo(DanhSachKe& dsk, int dinh, bool visited[], Topo& topo){
    visited[dinh] = true;
    Nodeptr p = dsk.dsk[dinh];
    while(p != NULL){
        int u = p->dinhke;
        if(!visited[u]){
            cau_9_dfs_topo(dsk, u, visited, topo);
        }
        p=p->link;
    }
    topo.dstopo[topo.soluongdinh++] = dinh;
}

DanhSachDinhDaTham cau_9(DanhSachKe& dsk, bool visited[], Topo& topo){
    DanhSachDinhDaTham dsd;
    for(int i = 0; i < dsk.sodinh; i++){
        if(!visited[i]){
            cau_9_dfs_topo(dsk, i, visited, topo);
        }
    }
    for(int i = topo.soluongdinh - 1; i >= 0; i--){
        dsd.dsd[dsd.sodinhdatham++] = topo.dstopo[i]; 
    }
    return dsd;
}

void cau_10(DanhSachCanh& dsc){
    for(int i = 0; i < dsc.socanh - 1; i++){
        for(int j = 0; j < dsc.socanh - i - 1; j++){
            if(dsc.dsc[j].trongso < dsc.dsc[j+1].trongso){
                swap(dsc.dsc[j], dsc.dsc[j+1]);
            }
        }
    }
}

bool kiemtrachutrinh(DanhSachKe& dsk, int dinh, int dinhcha, bool visited[]){
    visited[dinh] = true;
    Nodeptr p = dsk.dsk[dinh];
    while(p != NULL){
        int v = p->dinhke;
        if(!visited[v]){
            if(kiemtrachutrinh(dsk, v, dinh, visited)){
                return true;
            }
        } 
        // gap dinh da tham ma khong phai dinh cha -> co chu trinh 
        else if(v != dinhcha){
            return true;
        }
        p=p->link;
    }
    return false;
}

bool cau_11(DanhSachKe& dsk, bool visited[]){
    if (kiemtrachutrinh(dsk, 0, -1, visited)){
        return false;
    }
    for (int i = 0; i < dsk.sodinh; i++){
        if (!visited[i]){
            return false;
        }
    }
    return true;
}
