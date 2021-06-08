
#include <iostream>
#include <map>
#include "replacement_state.h"
using namespace std;

void ReadData(CACHE_REPLACEMENT_STATE *cacheReplState);

int set, way, pol;
int serial, hitset, hitway, SHCTnum;
int *SHCT;
Addr_t adres;
bool hit;

int main()
{
    
    int i, j;
    cin >> set >> way >> pol;
    CACHE_REPLACEMENT_STATE * cacheReplState = new CACHE_REPLACEMENT_STATE( set, way, pol);
    ReadData(cacheReplState);
    return 0;
}

void ReadData(CACHE_REPLACEMENT_STATE *cacheReplState)
{
    int operation;
    cin>>operation;
    
    int vic;
    
    cout<<set<<endl
        <<way<<endl
        <<pol<<endl
        <<operation;
    
    for (int i = 0; i < operation; i++) {
        cin>>serial>>hitset>>hit;
        if (hit == 1) {
            cin>>hitway;
            cout<<endl<<serial<<" "<<hitset<<" Hit "<<hitway;
            cacheReplState->UpdateReplacementState(hitset, hitway, 0, serial, 0, pol, hit);
        } else {
            cin>>adres;
            hitway = cacheReplState->GetVictimInSet(serial, hitset, 0, way, 0, adres, 0);
            cout<<endl<<serial<<" "<<hitset<<" Miss Replace "<<hitway;
            cacheReplState->UpdateReplacementState(hitset, hitway, 0, serial, 0, pol, hit);
        }
        cacheReplState->PrintStatPRP(hitset, hitway);
    }
}

