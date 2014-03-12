/* 
 * Enough is enough! I have had it with all this spaghetti, all this copying, all this faxing!
 * Copyright (c) 2014 The FoxCoin Foxes
 */ 

#include "main.h"
#include "foxcoinfunction.h"

double getRawHardness(const CBlockIndex* blockindex = NULL)
{
    if (blockindex == NULL)
    {
        if (pindexBest == NULL)
            return 1.0;
        else
            blockindex = pindexBest;
    }

    int nShift = (blockindex->nBits >> 24) & 0xff;

    double dDiff =
        (double)0x0000ffff / (double)(blockindex->nBits & 0x00ffffff);

    while (nShift < 29)
    {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29)
    {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;
}

int GetRawNetworkPawsPS(int lookup)
{
    if (pindexBest == NULL)
        return 0;

    // If lookup is -1, then use blocks since last difficulty change.
    if (lookup <= 0)
        lookup = pindexBest->nHeight;

    // If lookup is larger than chain, then set it to chain length.
    if (lookup > pindexBest->nHeight)
        lookup = pindexBest->nHeight;

    CBlockIndex* pindexPrev = pindexBest;
    for (int i = 0; i < lookup; i++)
        pindexPrev = pindexPrev->pprev;

    double timeDiff = pindexBest->GetBlockTime() - pindexPrev->GetBlockTime();
    double timePerBlock = timeDiff / lookup;

    return (boost::int64_t)(((double)getHardness() * pow(2.0, 32)) / timePerBlock);
}

int getTotalVolume()
{
    int nHeight = pindexBest->nHeight;
    
    if(nHeight < 196000)
    {
        return (nHeight * (250 - ((nHeight * .0000625) + .0000625)));
    }
    else
    {
        return (1960000 * (250 - 120)) + (5 * (nHeight - 1960000));
    }
}

double getAcreReward()
{
    int nHeight = pindexBest->nHeight;
    double nSubsidy = 1;
    
    if(nHeight < 1960000)
    {
       nSubsidy = (250 - (nHeight * 0.000125)); 
    }
    else
    {
        nSubsidy = 5;
    }
    
    return nSubsidy;
}

double GetRawEstimatedNextHardness(const CBlockIndex* blockindex = NULL){
    if (blockindex == NULL)
    {
        if (pindexBest == NULL)
            return 1.0;
        else
            blockindex = pindexBest;
    }

    unsigned int nBits;
    nBits = TrollNeoGetNextWorkRequired(blockindex);

    int nShift = (nBits >> 24) & 0xff;

    double dDiff = (double)0x0000ffff / (double)(nBits & 0x00ffffff);

    while (nShift < 29)
    {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29)
    {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;
}

double GetEstimatedNextHardness()
{
    return GetRawEstimatedNextHardness();
}

double getHardness()
{
    return getRawHardness();
}

int getNetworkPawsPS()
{
    return GetRawNetworkPawsPS(-1);
}
