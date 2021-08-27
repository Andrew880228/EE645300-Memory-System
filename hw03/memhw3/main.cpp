//
//  main.cpp
//  memhw3
//
//  Created by 楊宇羲 on 2021/6/20.
//

#include <iostream>
#include <vector>

using namespace std;

typedef struct REQ {
    int serial;
    int proc;
    int banknum;
    int row;
    bool del;
}REQ;

typedef struct BANK {
    REQ curr;
    int time;
    bool hm;
}BANK;

void ReadInput(void);
void PrintOutput(REQ buff);
bool CheckDone(void);
int FCFS(int i);
int FR_FCFS(int i);

int process, Bsize, Qsize, Pol, hitl, missl, cap, R;
int t = 0;
bool done = 0;
vector<REQ> Q;
BANK *bank;

int main(void)
{
    int index = -1;
    ReadInput();
    
    while (!done) {
        
        REQ buff;
        
        for (int i = 0; i < Q.size(); i++) {
            if (Q[i].del == 1) Q.erase(Q.begin() + i);
        }
        
        for (int i = 0; i < Bsize; i++) {
            
            bank[i].time--;
            
            if (bank[i].time <= 0 && !Q.empty()) {
                
                if (Pol == 0) index = FCFS(i);
                else if (Pol == 1) index = FR_FCFS(i);
                
                if (index != -1) {
                    if (bank[i].curr.row == Q[index].row) {
                        bank[i].time = hitl;
                        bank[i].hm = 1;
                    } else {
                        bank[i].time = missl;
                        bank[i].hm = 0;
                    }
                    bank[i].curr = Q[index];
                    Q[index].del = 1;
                }
                
            }
        }
        
        if (Q.size() < Qsize && R > 0) {
            cin>>buff.serial>>buff.proc>>buff.banknum>>buff.row;
            buff.del = 0;
            R--;
            Q.push_back(buff);
        } else buff.serial = -1;
        
        if (!CheckDone()) PrintOutput(buff);
        else done = 1;
    }
    
    return 0;
}

void ReadInput(void)
{
    cin>>process>>Bsize>>Qsize>>Pol>>hitl>>missl>>cap>>R;
    cout<<process<<endl<<Bsize<<endl<<Qsize<<endl<<Pol<<endl<<hitl<<endl<<missl<<endl;
    cout<<cap<<endl<<R<<endl;
    
    bank = new BANK[Bsize];
    
    for (int i = 0; i < Bsize; i++) {
        bank[i].curr.serial = -1;
        bank[i].curr.proc = -1;
        bank[i].curr.banknum = -1;
        bank[i].curr.row = -1;
        bank[i].hm = 0;
        bank[i].time = 0;
    }
}

int FCFS(int i)
{
    int flag = 0;
    int index = -1;
    
    for (int j = 0; j < Q.size() && flag == 0; j++) {
        if (Q[j].banknum == i) {
            flag = 1;
            index = j;
        }
    }
    
    return index;
}

int FR_FCFS(int i)
{
    bool flag = 0;
    bool flag2 = 0;
    int index = -1;
    
    for (int j = 0; j < Q.size() && flag2 == 0; j++) {
        if (Q[j].banknum == i && flag == 0) {
            flag = 1;
            index = j;
        }
        if (Q[j].banknum == i && Q[j].row == bank[i].curr.row) {
            flag2 = 1;
            index = j;
        }
    }
    
    return index;
}

bool CheckDone(void)
{
    int done = 1;
    
    for (int i = 0;i < Bsize; i++) {
        if (bank[i].time > 0) done = 0;
    }
    if (Q.size() != 0) done = 0;
    
    return done;
}

void PrintOutput(REQ buff)
{
    int check;
    
    cout<<t;
    if (t < 10) cout<<"      ";
    else if (t < 100) cout<<"     ";
    else if (t < 1000) cout<<"    ";
    else cout<<"   ";
    if (buff.serial != -1) {
        cout<<"t"<<buff.serial;
        if (buff.serial < 10) cout<<"    P";
        else if (buff.serial < 100)cout<<"   P";
        else if (buff.serial < 1000) cout<<"  P";
        else cout<<" P";
        cout<<buff.proc;
        if (buff.proc < 10) cout<<" B"<<buff.banknum;
        else cout<<"B"<<buff.banknum;
        cout<<" ("<<buff.row;
        if (buff.row < 10) cout<<" )";
        else cout<<")";
    } else {
        cout<<"                ";
    }
    
    for (int i = 0; i < Bsize; i++) {
        if (bank[i].time > 0) {
            
            if (bank[i].hm == 1) check = hitl;
            else check = missl;
            
            if (bank[i].time == check) {
                cout<<"   t"<<bank[i].curr.serial;
                if (bank[i].curr.serial < 10) cout<<"    P";
                else if (bank[i].curr.serial < 100)cout<<"   P";
                else if (bank[i].curr.serial < 1000) cout<<"  P";
                else cout<<" P";
                cout<<bank[i].curr.proc;
                if (bank[i].curr.proc < 10) cout<<" B"<<bank[i].curr.banknum;
                else cout<<"B"<<bank[i].curr.banknum;
                cout<<" ("<<bank[i].curr.row;
                if (bank[i].curr.row < 10) cout<<" )";
                else cout<<")";
            }
            else if (bank[i].time == 1) {
                cout<<"    -------------- ";
            }
            else if (bank[i].time < check) cout<<"   |              |";
            else cout<<"                   ";
            
        } else cout<<"                   ";
    }
    cout<<endl;
    t++;
}
