#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cstdio>
using namespace std;

class phuong_tien
{
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);
    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}
int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
double phuong_tien::tinh_phi() const
{
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0
                                                                      : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h)
    {
        if (h < 2)
            tong += gia * (cao_diem ? 1.30 : 0.95);
        else
            tong += gia * 0.90;
    }
    return tong;
}
void phuong_tien::hien_thi() const
{
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe
{
private:
    int ma_bai;
    char kich_thuoc;
    int sucChua;
    phuong_tien **dsPT;
    int soPT;

public:
    bai_xe();
    bai_xe(int ma, char kt);
    ~bai_xe();
    bai_xe(const bai_xe &b);
    bai_xe &operator=(const bai_xe &b);
    int lay_ma() const;
    bool ktDay() const;
    void CNSC(int sucChuaB);
    bool themPT(const phuong_tien &v);
    bool xoaPT(int vID);
    int timSoPT(int vID) const;
    void hien_thi() const;
    bool co_loai(string loai, int &dem, double &tong) const;
    void hien_thi_loai(const string &loai) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), sucChua(1), soPT(0)
{
    dsPT = new phuong_tien *[sucChua];
    for (int i = 0; i < sucChua; ++i)
        dsPT[i] = NULL;
}
bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), soPT(0)
{
    sucChua = kt == 'S' ? 1 : kt == 'M' ? 2
                                        : 3;
    dsPT = new phuong_tien *[sucChua];
    for (int i = 0; i < sucChua; ++i)
        dsPT[i] = NULL;
}
bai_xe::~bai_xe()
{
    for (int i = 0; i < soPT; ++i)
    {
        delete dsPT[i];
        dsPT[i] = NULL;
    }
    delete[] dsPT;
    dsPT = NULL;
}
bai_xe::bai_xe(const bai_xe &b)
    : ma_bai(b.ma_bai), kich_thuoc(b.kich_thuoc), sucChua(b.sucChua), soPT(0)
{
    dsPT = new phuong_tien *[sucChua];
    for (int i = 0; i < sucChua; ++i)
        dsPT[i] = NULL;
    try
    {
        for (int i = 0; i < b.soPT; ++i)
        {
            dsPT[i] = new phuong_tien(*b.dsPT[i]);
            ++soPT;
        }
    }
    catch (...)
    {
        for (int i = 0; i < soPT; ++i)
            delete dsPT[i];
        delete[] dsPT;
        dsPT = NULL;
        throw;
    }
}
bai_xe &bai_xe::operator=(const bai_xe &b)
{
    if (this != &b)
    {
        bai_xe tam(b);
        int m = ma_bai;
        ma_bai = tam.ma_bai;
        tam.ma_bai = m;
        char k = kich_thuoc;
        kich_thuoc = tam.kich_thuoc;
        tam.kich_thuoc = k;
        int c = sucChua;
        sucChua = tam.sucChua;
        tam.sucChua = c;
        int n = soPT;
        soPT = tam.soPT;
        tam.soPT = n;
        phuong_tien **p = dsPT;
        dsPT = tam.dsPT;
        tam.dsPT = p;
    }
    return *this;
}
int bai_xe::lay_ma() const { return ma_bai; }
bool bai_xe::ktDay() const { return soPT >= sucChua; }
void bai_xe::CNSC(int sucChuaB)
{
    if (sucChuaB <= sucChua)
        return;
    phuong_tien **moi = new phuong_tien *[sucChuaB];
    for (int i = 0; i < sucChuaB; ++i)
        moi[i] = NULL;
    for (int i = 0; i < soPT; ++i)
        moi[i] = dsPT[i];
    delete[] dsPT;
    dsPT = moi;
    sucChua = sucChuaB;
}
bool bai_xe::themPT(const phuong_tien &v)
{
    if (timSoPT(v.lay_ma_xe()) != -1)
        return false;
    if (ktDay())
        CNSC(sucChua * 2);
    dsPT[soPT] = new phuong_tien(v);
    ++soPT;
    return true;
}
int bai_xe::timSoPT(int vID) const
{
    for (int i = 0; i < soPT; ++i)
        if (dsPT[i]->lay_ma_xe() == vID)
            return i;
    return -1;
}
bool bai_xe::xoaPT(int vID)
{
    int viTri = timSoPT(vID);
    if (viTri == -1)
        return false;
    delete dsPT[viTri];
    dsPT[viTri] = NULL;
    for (int i = viTri; i < soPT - 1; ++i)
        dsPT[i] = dsPT[i + 1];
    dsPT[soPT - 1] = NULL;
    --soPT;
    return true;
}
void bai_xe::hien_thi() const
{
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << soPT << "/" << sucChua << " xe\n";
    for (int i = 0; i < soPT; ++i)
        dsPT[i]->hien_thi();
}
bool bai_xe::co_loai(string loai, int &dem, double &tong) const
{
    dem = 0;
    tong = 0;
    for (int i = 0; i < soPT; ++i)
    {
        if (dsPT[i]->lay_loai_xe() == loai)
        {
            ++dem;
            tong += dsPT[i]->tinh_phi();
        }
    }
    return dem > 0;
}
void bai_xe::hien_thi_loai(const string &loai) const
{
    bool co = false;
    for (int i = 0; i < soPT; ++i)
    {
        if (dsPT[i]->lay_loai_xe() == loai)
        {
            if (!co)
                cout << "Bai " << ma_bai << ":\n";
            dsPT[i]->hien_thi();
            co = true;
        }
    }
}

int nhapSo(const string &thongBao, int minVal, int maxVal)
{
    int x;
    while (true)
    {
        cout << thongBao;
        if (cin >> x)
        {
            if (cin.peek() == '\n' || cin.peek() == EOF)
            {
                if (x >= minVal && x <= maxVal)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return x;
                }
            }
        }
        if (cin.eof())
            throw ios_base::failure("Ket thuc du lieu nhap");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Du lieu khong hop le. nhap lai\n";
    }
}
char nhapKichThuoc()
{
    string kt;
    while (true)
    {
        cout << "Kich thuoc (S/M/L): ";
        if (!(cin >> kt))
            throw ios_base::failure("Ket thuc du lieu nhap");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (kt == "S" || kt == "M" || kt == "L")
            return kt[0];
        cout << "Kich thuoc khong hop le\n";
    }
}
string nhapLoai()
{
    string loai;
    while (true)
    {
        cout << "Loai (Car/Motorcycle/Bicycle): ";
        if (!(cin >> loai))
            throw ios_base::failure("Ket thuc du lieu nhap");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (loai == "Car" || loai == "Motorcycle" || loai == "Bicycle")
            return loai;
        cout << "Loai xe khong hop le\n";
    }
}

class SystemInterface
{
private:
    int sucChuaBai;
    bai_xe **baixe;
    int soBai;

public:
    SystemInterface();
    ~SystemInterface();
    SystemInterface(const SystemInterface &s);
    SystemInterface &operator=(const SystemInterface &s);
    void CNSCSystem(int sucChuaB);
    void runMenu();
    bool ktTrungBai(int pID) const;
    bool ktTrungXe(int vID) const;
    int taoNgauNhien();
};

SystemInterface::SystemInterface() : sucChuaBai(5), soBai(0)
{
    baixe = new bai_xe *[sucChuaBai];
    for (int i = 0; i < sucChuaBai; ++i)
        baixe[i] = NULL;
}
SystemInterface::~SystemInterface()
{
    for (int i = 0; i < soBai; ++i)
    {
        delete baixe[i];
        baixe[i] = NULL;
    }
    delete[] baixe;
    baixe = NULL;
}
SystemInterface::SystemInterface(const SystemInterface &s)
    : sucChuaBai(s.sucChuaBai), soBai(0)
{
    baixe = new bai_xe *[sucChuaBai];
    for (int i = 0; i < sucChuaBai; ++i)
        baixe[i] = NULL;
    try
    {
        for (int i = 0; i < s.soBai; ++i)
        {
            baixe[i] = new bai_xe(*s.baixe[i]);
            ++soBai;
        }
    }
    catch (...)
    {
        for (int i = 0; i < soBai; ++i)
            delete baixe[i];
        delete[] baixe;
        baixe = NULL;
        throw;
    }
}
SystemInterface &SystemInterface::operator=(const SystemInterface &s)
{
    if (this != &s)
    {
        SystemInterface tam(s);
        int c = sucChuaBai;
        sucChuaBai = tam.sucChuaBai;
        tam.sucChuaBai = c;
        int n = soBai;
        soBai = tam.soBai;
        tam.soBai = n;
        bai_xe **p = baixe;
        baixe = tam.baixe;
        tam.baixe = p;
    }
    return *this;
}
void SystemInterface::CNSCSystem(int sucChuaB)
{
    if (sucChuaB <= sucChuaBai)
        return;
    bai_xe **moi = new bai_xe *[sucChuaB];
    for (int i = 0; i < sucChuaB; ++i)
        moi[i] = NULL;
    for (int i = 0; i < soBai; ++i)
        moi[i] = baixe[i];
    delete[] baixe;
    baixe = moi;
    sucChuaBai = sucChuaB;
}
bool SystemInterface::ktTrungBai(int pID) const
{
    for (int i = 0; i < soBai; ++i)
        if (baixe[i]->lay_ma() == pID)
            return true;
    return false;
}
bool SystemInterface::ktTrungXe(int vID) const
{
    for (int i = 0; i < soBai; ++i)
        if (baixe[i]->timSoPT(vID) != -1)
            return true;
    return false;
}
int SystemInterface::taoNgauNhien()
{
    int id;
    do
    {
        id = 1 + rand() % 999;
    } while (ktTrungBai(id) || ktTrungXe(id));
    return id;
}
void SystemInterface::runMenu()
{
    try
    {
        while (true)
        {
            cout << "\n===== QUAN LY BAI DO XE =====\n"
                 << "1. Tao bai do\n2. Them xe\n3. Xoa bai do\n"
                 << "4. Lay xe ra\n5. Hien thi tat ca bai do\n"
                 << "6. Hien thi xe theo bai\n7. Liet ke xe theo loai\n"
                 << "8. Bao cao phi trung binh\n9. Thoat\n";
            int chon = nhapSo("Chon: ", 1, 9);
            switch (chon)
            {
            case 1:
            {
                if (soBai == sucChuaBai)
                    CNSCSystem(sucChuaBai * 2);
                int ma = nhapSo("Ma bai: ", 1, numeric_limits<int>::max());
                if (ktTrungBai(ma))
                {
                    cout << "Trung ID bai " << ma << ", da tao ma bai ngau nhien\n";
                    ma = taoNgauNhien();
                }
                char kt = nhapKichThuoc();
                baixe[soBai] = new bai_xe(ma, kt);
                ++soBai;
                cout << "Da tao bai " << ma << "\n";
                break;
            }
            case 2:
            {
                if (soBai == 0)
                {
                    cout << "Chua co bai do nao\n";
                    break;
                }
                int viTri = 0;
                for (int i = 0; i < soBai; ++i)
                {
                    if (!baixe[i]->ktDay())
                    {
                        viTri = i;
                        break;
                    }
                }
                int ma = nhapSo("Ma xe: ", 1, numeric_limits<int>::max());
                if (ktTrungXe(ma))
                {
                    cout << "Trung ID xe " << ma << ", da sinh ma xe ngau nhien";
                    ma = taoNgauNhien();
                }
                string loai = nhapLoai();
                int gio = nhapSo("Gio vao (0-23): ", 0, 23);
                int tg = nhapSo("Thoi luong (1-23): ", 1, 23);
                phuong_tien v(ma, loai, gio, tg);
                if (baixe[viTri]->themPT(v))
                {
                    cout << "Da them xe " << ma << " vao bai " << baixe[viTri]->lay_ma()
                         << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                }
                break;
            }
            case 3:
            {
                int ma = nhapSo("Ma bai can xoa: ", 1, numeric_limits<int>::max());
                int viTri = -1;
                for (int i = 0; i < soBai; ++i)
                {
                    if (baixe[i]->lay_ma() == ma)
                    {
                        viTri = i;
                        break;
                    }
                }
                if (viTri == -1)
                {
                    cout << "Khong tim thay bai\n";
                    break;
                }
                delete baixe[viTri];
                baixe[viTri] = NULL;
                for (int i = viTri; i < soBai - 1; ++i)
                    baixe[i] = baixe[i + 1];
                baixe[soBai - 1] = NULL;
                --soBai;
                cout << "Da xoa bai " << ma << "\n";
                break;
            }
            case 4:
            {
                int ma = nhapSo("Ma xe can lay ra: ", 1, numeric_limits<int>::max());
                bool ok = false;
                for (int i = 0; i < soBai; ++i)
                {
                    if (baixe[i]->xoaPT(ma))
                    {
                        ok = true;
                        break;
                    }
                }
                cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5:
            {
                if (soBai == 0)
                    cout << "Chua co bai do\n";
                for (int i = 0; i < soBai; ++i)
                    baixe[i]->hien_thi();
                break;
            }
            case 6:
            {
                int ma = nhapSo("Ma bai: ", 1, numeric_limits<int>::max());
                bool timThay = false;
                for (int i = 0; i < soBai; ++i)
                {
                    if (baixe[i]->lay_ma() == ma)
                    {
                        baixe[i]->hien_thi();
                        timThay = true;
                        break;
                    }
                }
                if (!timThay)
                    cout << "Khong tim thay bai\n";
                break;
            }
            case 7:
            {
                string loai = nhapLoai();
                int tongDem = 0;
                for (int i = 0; i < soBai; ++i)
                {
                    int d = 0;
                    double s = 0;
                    if (baixe[i]->co_loai(loai, d, s))
                    {
                        baixe[i]->hien_thi_loai(loai);
                        tongDem += d;
                    }
                }
                if (tongDem == 0)
                    cout << "Khong co xe thuoc loai nay\n";
                break;
            }
            case 8:
            {
                string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
                for (int t = 0; t < 3; ++t)
                {
                    int dem = 0;
                    double tong = 0;
                    for (int i = 0; i < soBai; ++i)
                    {
                        int d = 0;
                        double s = 0;
                        baixe[i]->co_loai(loai_arr[t], d, s);
                        dem += d;
                        tong += s;
                    }
                    cout << loai_arr[t] << ": ";
                    if (dem == 0)
                        cout << "khong co xe\n";
                    else
                        cout << dem << " xe | TB: $" << fixed
                             << setprecision(2) << tong / dem << "\n";
                }
                break;
            }
            case 9:
                return;
            }
        }
    }
    catch (const ios_base::failure &)
    {
        cout << "Thoat chuong trinh.\n";
    }
}

int main()
{
    SystemInterface s;
    s.runMenu();
    return 0;
}
