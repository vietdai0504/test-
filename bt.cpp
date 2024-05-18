#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Hocsinh{
    private:
        string ten, ngaysinh, gioitinh;
        int masv, tuoi, sdt;
    public:
        Hocsinh(int masv = 0, string ten = "", string ngaysinh = "01/01/2000", int tuoi = 0, string gioitinh = "", int sdt = 0) : masv(masv), ten(ten), ngaysinh(ngaysinh), tuoi(tuoi), gioitinh(gioitinh), sdt(sdt) {}
        void getinfo(ifstream& fin)
        {
            string line,number;
            getline(fin,line);
            stringstream ss(line);
            getline(ss,number,',');
            masv = stoi(number);
            getline(ss,ten,',');
            getline(ss,ngaysinh,',');
            getline(ss,number,',');
            tuoi = stoi(number);
            getline(ss,gioitinh,',');
            getline(ss,number,',');
            sdt = stoi(number);
        }
        void display()
        {
            cout<<setw(20)<<left<<"Ma sinh vien"<<"| "<<masv<<endl;
            cout<<setw(20)<<left<<"Ten"<<"| "<<ten<<endl;
            cout<<setw(20)<<left<<"Ngay sinh"<<"| "<<ngaysinh<<endl;
            cout<<setw(20)<<left<<"Tuoi"<<"| "<<tuoi<<endl;
            cout<<setw(20)<<left<<"Gioi tinh"<<"| "<<gioitinh<<endl;
            cout<<setw(20)<<left<<"SDT"<<"| "<<sdt<<endl;
        }
        void add()
        {
            cout<<"Nhap ma sinh vien: "; cin>>masv;
            cin.ignore();
            cout<<"Nhap ten: "; getline(cin,ten);
            cout<<"Nhap ngay sinh:"; getline(cin,ngaysinh);
            cout<<"Nhap tuoi: "; cin>>tuoi;
            cin.ignore();
            cout<<"Gioi tinh: "; getline(cin,gioitinh);
            cout<<"Nhap so dien thoai: "; cin>>sdt;
            cin.ignore();
        }
        int getid()
        {
            return masv;
        }
        int getphone()
        {
            return sdt;
        }
        string getname()
        {
            string name = "";
            for (int i = ten.length() - 1; i>=0; i--)
            {
                if (ten[i] == ' ')
                    break;
                name = ten[i] + name;
            }
            return name;
        }

        void write(ofstream& fout)
        {
            fout<<masv<<","<<ten<<","<<ngaysinh<<","<<tuoi<<","<<gioitinh<<","<<sdt<<","<<endl;
        }
};

class DsHocsinh{
    private:
        const int MAX = 1000;
        int N = 0;
        Hocsinh dshs[1000];
    public:
        void getfull(ifstream& fin)
        {
            string str;
            getline(fin,str);
            while(!fin.eof())
            {
                while(!fin.eof())
                {
                    dshs[N++].getinfo(fin);
                    
                }
            }
        }
        void displayfull(){
            cout<<"======Danh sach sinh vien======\n"<<endl;
            for (int i = 0; i < N; i++)
            {
                cout<<"STT: "<<i + 1<<endl;
                dshs[i].display();
                cout<<endl;
            }
        }
        void addhs()
        {
            dshs[N++].add();
        }
        
        void remove()
        {
            int id_remove;
            bool check = false;
            cout<<"Nhap ma sinh vien muon xoa: "; cin>>id_remove;
            for (int i = 0;i < N; i++)
            {
                if ((dshs[i].getid() == id_remove) && !check)
                {
                    check = true;
                }
                if (check && i+1<N)
                {
                    dshs[i] = dshs[i+1];
                }
            }
            if (!check)
            {
                cout<<"Khong tim thay sinh vien can xoa!!"<<endl;
            }
            else
                N--;
        }

        void swap(Hocsinh& hs1, Hocsinh& hs2)
        {
            Hocsinh hs3 = hs1;
            hs1 = hs2;
            hs2 = hs3;
        }

        void sortName();
        void sortPhone();

        void writefile(ofstream& fout);
};

void DsHocsinh::writefile(ofstream& fout)
{
    for (int i = 0;i < N; i++)
    {
        dshs[i].write(fout);
    }
}

void DsHocsinh::sortPhone()
{
    for (int i = 0 ;i < N - 1; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (dshs[i].getphone() > dshs[j].getphone())
            {
                swap(dshs[i],dshs[j]);
            }
        }
    }
    cout<<"Da sap xep sinh vien theo so dien thoai!"<<endl;
}

void DsHocsinh::sortName()
{
    for (int i = 0;i < N - 1; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (dshs[i].getname() > dshs[j].getname())
            {
                swap(dshs[i],dshs[j]);
            }
        }
    }
    cout<<"Da sap xep theo ten sinh vien!"<<endl;
}

int main()
{
    string namefile;
    cout<<"Nhap file de doc du lieu vao: "; cin>>namefile;
    namefile += ".csv";
    ifstream fin(namefile);
    DsHocsinh sv;
    sv.getfull(fin);
    fin.close();
    int select;
    bool running = true;
    while (running)
    {
        cout<<"=====Moi nhap lua chon====="<<endl;
        cout<<"1. In danh sach sinh vien.\n2. Them sinh vien.\n3. Xoa sinh vien.\n4. Sap xep sinh vien theo so dien thoai.\n5. Sap xep sinh vien theo ten.\n6. Ghi du lieu vao file.\n7. Thoat."<<endl;
        cout<<"Lua chon: "; cin>>select;
        switch (select)
        {
            case 1:
                sv.displayfull();
                break;
            case 2:
                sv.addhs();
                break;
            case 3:
                sv.remove();
                break;
            case 4:
                sv.sortPhone();
                break;
            case 5:
                sv.sortName();
                break;
            case 6:
                {
                    string filename;
                    cout<<"Nhap ten file de ghi du lieu: "; cin>>filename;
                    filename += ".csv";
                    ofstream fout(filename);
                    sv.writefile(fout);
                    fout.close();
                    break;
                }
            case 7:
                cout<<"Da thoat!!"<<endl;
                running = false;
                break;
            default:
                cout<<"Lua chon khong hop le! Vui long nhap lai lua chon!!"<<endl;
                break;
        }
    }
}