#ifndef REPL_STATE_H
#define REPL_STATE_H

// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is distributed as part of the Cache Replacement Championship     //
// workshop held in conjunction with ISCA'2010.                               //
//                                                                            //
//                                                                            //
// Everyone is granted permission to copy, modify, and/or re-distribute       //
// this software.                                                             //
//                                                                            //
// Please contact Aamer Jaleel <ajaleel@gmail.com> should you have any        //
// questions                                                                  //
//                                                                            //
// /////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cassert>
#include <map>
#include "utils.h"
#include "crc_cache_defs.h"

// Replacement Policies Supported
typedef enum 
{
    CRC_REPL_LRU        = 0,
    CRC_REPL_RANDOM     = 1,
    CRC_REPL_CONTESTANT = 2,
    CRC_REPL_PRP        = 3
} ReplacemntPolicy;

// Replacement State Per Cache Line
typedef struct
{
    UINT32  LRUstackposition;
    UINT32  SHiPstackposition;
    UINT32  RRPV;
    UINT32  signature;
    UINT32  outcome;
    INT32   score;
    
    Addr_t  adres;

    // CONTESTANTS: Add extra state per cache line here

    
} LINE_REPLACEMENT_STATE;


// The implementation for the cache replacement policy
class CACHE_REPLACEMENT_STATE
{

  private:
    UINT32 numsets;
    UINT32 assoc;
    UINT32 replPolicy;
    
    LINE_REPLACEMENT_STATE   **repl;

    COUNTER mytimer;  // tracks # of references to the cache

    // CONTESTANTS:  Add extra state for cache here
    bool originalOut;
    UINT32 originalSig;
    
    map<UINT32, UINT32*> *dataRD;
    map<UINT32, UINT32*>::iterator iter;
    map<UINT32, UINT32*>::iterator trav;
    
  public:
    
    UINT32 *SHCT;
    UINT32 SHCTnum;
    
    // The constructor CAN NOT be changed
    CACHE_REPLACEMENT_STATE( UINT32 _sets, UINT32 _assoc, UINT32 _pol );

    INT32  GetVictimInSet( UINT32 tid, UINT32 setIndex, const LINE_STATE *vicSet, UINT32 assoc, Addr_t PC, Addr_t paddr, UINT32 accessType );
    void   UpdateReplacementState( UINT32 setIndex, INT32 updateWayID );

    void   SetReplacementPolicy( UINT32 _pol ) { replPolicy = _pol; }
    void   IncrementTimer() { mytimer++; }

    void   UpdateReplacementState( UINT32 setIndex, INT32 updateWayID, const LINE_STATE *currLine,
                                   UINT32 tid, Addr_t PC, UINT32 accessType, bool cacheHit );

    ostream&   PrintStats( ostream &out);
    
    void   PrintStat(UINT32 set, UINT32 way, bool cacheHit, Addr_t pc);
    void   PrintStatPRP(UINT32 set, UINT32 way);



  private:
    
    void   InitReplacementState();
    INT32  Get_Random_Victim( UINT32 setIndex );

    INT32  Get_LRU_Victim( UINT32 setIndex );
    
    INT32  Get_SHiP_Victim( UINT32 setIndex );
    
    INT32  Get_PRP_Victim( UINT32 setIndex, Addr_t paadr );
    
    INT32  Get_Score(LINE_REPLACEMENT_STATE replT, UINT32 setIndex);
    
    void   UpdateLRU( UINT32 setIndex, INT32 updateWayID );
    void   UpdateSHiP( UINT32 setIndex, INT32 updateWayID, Addr_t pc, bool hm);
    void   UpdatePRP( UINT32 setIndex, INT32 updateWayID, Addr_t pc, bool hm );
};


#endif
