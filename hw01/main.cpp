#include <iostream>
#include "replacement_state.h"
using namespace std;

void ReadData(CACHE_REPLACEMENT_STATE *cacheReplState);

int set, way, pol;
int serial, hitset, hitway, SHCTnum;
int *SHCT;
Addr_t pc;
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
    cin>>cacheReplState->SHCTnum>>operation;
    
    int vic;
    
    cacheReplState->SHCT = new unsigned int[cacheReplState->SHCTnum];
    for (int i = 0; i < cacheReplState->SHCTnum; i++) cacheReplState->SHCT[i] = 1;
    for (int i = 0; i < SHCTnum; i++) SHCT[i] = 1;
    
    cout<<set<<endl
        <<way<<endl
        <<pol<<endl
        <<cacheReplState->SHCTnum<<endl
        <<operation;
    
    for (int i = 0; i < operation; i++) {
        cin>>serial>>pc>>hitset>>hit;
        if (hit == 1) {
            cin>>hitway;
            cout<<endl<<serial<<" "<<pc<<" "<<hitset<<" Hit "<<hitway;
            cacheReplState->UpdateReplacementState(hitset, hitway, 0, serial, pc, pol, hit);
        } else {
            cout<<endl<<serial<<" "<<pc<<" "<<hitset<<" Replace ";
            hitway = cacheReplState->GetVictimInSet(serial, hitset, 0, way, pc, 0, 2);
            cout<<hitway;
            cacheReplState->UpdateReplacementState(hitset, hitway, 0, serial, pc, pol, hit);
        }
        //cout<<endl;
        cacheReplState->PrintStat(hitset, hitway, hit, pc);
    }
}

