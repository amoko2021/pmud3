#include <iostream>
#include <string>
#include <math.h>

using namespace std;

struct Pexactly
{
    string ps;
    string x;
    int cnt;
};
typedef struct Pexactly PEXACTLY;

void _erase_f0(string &s)
{
    int index = s.find('1', 0);
    s.erase(0, index);
}

void _erase_fl(string &s)
{
    for(int i = s.length() - 1; i >= 0; i --)
    {
        if(s[i] == '0')
        {
            s.erase(i);
        }
        else
        {
            break;
        }
    }
}

void _enter(string &Px, string &Rx, int &s)
{
    do
    {
        cout << "=== Enter P(x) larger or equal R(x): [binary] and s(int) ===";
        cout << "\nEnter P(x): "; cin >> Px; //_erase_f0(Px);
        cout << "Enter R(x): "; cin >> Rx; //_erase_f0(Rx);
        cout << "Enter s: "; cin >> s;
    } while(Px.length() < Rx.length());
}

void _XOR(string &x, string r, int rl)
{
    for(int i = 0; i < rl; i++)
    {
        if(x[i] == r[i])
        {
            x[i] = '0';
        }
        else
        {
            x[i] = '1';
        }
    }
    _erase_f0(x);
}

int W(string s)
{
    int dem  = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '1')
        {
            dem++;
        }
    }
    return dem;
}

void _to_right(string &s)
{
    char tam = s[s.length()-1];
    for(int i = s.length() - 2; i >= 0; i--)
    {
        s[i+1] = s[i];
    }
    s[0] = tam;
}

void _to_left(string &a)
{
    char x = a[0];
    for(int i = 0; i < a.length()-1; i++)
    {
        a[i] = a[i+1];
    }
    a[a.length()-1] = x;
}

void _cut(string &a, string &b)
{
    a.insert(a.length(), b);
    b.erase(0);
}

PEXACTLY find_near_Pd(string Px, int Pl, string Rx, int Rl, int s, int count_loop, string &m)
{
    PEXACTLY Pd; Pd.ps = m; Pd.cnt = count_loop;


    if(count_loop >= 50)
    {
        cout << "\nMa nhap sai, hay nhap lai!";
        Pd.ps = "0";
        Pd.x = "0";
        return Pd;
    }

    // fake data
    string p = Px;
    _erase_f0(p);
    int pl = p.length();

    //cout << "\n==P luc nay: " << p;

    // xat 4 cua p cho x
    string x = p.substr(0, Rl);
    p.erase(0, Rl); pl = pl - Rl;

    _XOR(x, Rx, Rl);

    _erase_f0(x);

//    if(x.length() == 0)
//    {
//        x = '0';
//    }
    //cout << "P luc nay la: " << p;
    if(p.length() <= 0)  // ======= het p de them
    {

        if(W(x) <= s) // 1.=========  het p de them va thoa man w < s, ko can dich
        {
            //cout << "\nVao t/h 1";
            Pd.x = x;
            return Pd;
        }
        else //2. =========== het p de them nhung ko thoa man w < s den --> DICH
        {
            //cout << "\n===vao t/h 2";
            _to_right(m);
            count_loop++;
            return find_near_Pd(m, Pl, Rx, Rl, s, count_loop, m);
        }
    }
    else // con p de them
    {
        _cut(x, p);  // them
        _erase_f0(x);
        if(x.length() < Rl)
        {
            if(W(x) <= s) // ======= 3.  trong 1 lan them nhung x.p ngan, w < s
            {
                //cout << "\nvao t/h 3";
                Pd.x = x;
                return Pd;
            }
            else
            {
                //==========  4. =====  con P de them  nuwng W > s
                //cout << "\nVao t/h 4";
                _to_right(m);
                count_loop++;
                return find_near_Pd(m, Pl, Rx, Rl, s, count_loop, m);
            }
        }
        else // 5. =========== trong 1 lan co them x.p va ko can dich
        {
            //cout << "\nVao t/h 5";
            int xl = x.length();
            return find_near_Pd(x, xl, Rx, Rl, s, count_loop, m);
        }
    }

}

string add_binary(string a, string b)
{
    int bl = b.length() - 1;
    for(int i = a.length() - 1; i > 0; i--)
    {
        if(bl < 0)
        {
            break;
        }
        else
        {
            if(a[i] == b[bl])
            {
                a[i] = '0';
            }
            else
            {
                a[i] = '1';
            }
            bl--;
        }
    }
    return a;
}

void _cut(string &a, string &b, int i)
{
    a += b[0];
    b.erase(0, i);
}

string find_Q(string pChia, string Px, string Rx, string &Q)
{

    _cut(pChia, Px, 1);

    if(pChia.length() < Rx.length())
    {
        Q += "0";
        if(Px.length() == 0)
        {
            return Q;
        }
        return find_Q(pChia, Px, Rx, Q);
    }
    else
    {
        _XOR(pChia, Rx, Rx.length());
        Q += "1";
        _erase_f0(pChia);
        if(Px.length() == 0)
        {
            return Q;
        }
        return find_Q(pChia, Px, Rx, Q);
    }
}

int factorial(int n)
{
    int giai_thua = 1;
    for(int i = 1; i <= n; i++)
    {
        giai_thua *= i;
    }
    return giai_thua;
}

int find_c(int s, int n)
{
    int tich = 1;
    for(int i = n-s+1; i <= n; i++)
    {
        tich *= i;
    }
    int kq = tich / factorial(s);
    return kq;
}

int tong_xich_ma(int k, int n)
{
    int tong  = 0;
    for(int i = 1; i <= k; i++)
    {
        tong += find_c(i, n);
    }
    return tong;
}

int find_k(int s, int n)
{
    int k = 0;

    int thuong = 1 + tong_xich_ma(s, n);

    for(int i = 1; i <= n; i++)
    {
        if(pow(2, i) >= thuong)
        {
            k = n - i;
            break;
        }
    }
    return k;
}

int main()
{
    //khai bao
    string Px, Rx; int s;
    // nhap lieu
    _enter(Px, Rx, s);
    int Pl = Px.length();
    int Rl = Rx.length();
    int count_loop = 0;
    string m = Px;

    // tinh toan tim Ps va x va so lan dich
    PEXACTLY n = find_near_Pd(Px, Pl, Rx, Rl, s, count_loop, m);

    // in thong bao
    cout << "\n=========================";
    cout << "\n======== Ps : " << n.ps;
    cout << "\n======== x : " << n.x;
    cout << "\n======== Number of moves : " << n.cnt;
    cout << "\n=========================";

    // cong Ps va x => Pd chua dich
    string Pd = add_binary(n.ps, n.x);
    //cout << "\n\nPd don't move: " << Pd;

    // dich Pd
    for(int i = 1; i <= n.cnt; i++)
    {
        _to_left(Pd);
    }

    // in ket qua
    cout << "\n\n=========================";
    cout << "\nPd moved: " << Pd;

    string tam;
    string Q;
    string h = find_Q(tam, Pd, Rx, Q);
    _erase_f0(h);
    cout << "\nMa khong he thong Q(x): " << h;
    cout << "\n=========================";

    int k = find_k(s, Pl);
    string Qx = Pd.substr(0, k);
    cout << "\nMa he thong Q(x): " << Qx;
    return 0;
}
