/* 
 * Copyright (c) 2014 The FoxCoin Foxes
 */

#ifndef FOXCOINFUNCTION_H
#define	FOXCOINFUNCTION_H

double getHardness();
double GetEstimatedNextHardness();
double getReward();
double getAcreHardness(int);
double getTxTotalValue(std::string);
double convertCoins(int64);

int getTotalVolume();
int getNetworkPawsPS();
int getAcreTime(int);
int getAcrenBits(int);
int getAcreNonce(int);
int acresInPastHours(int);
int getAcrePawrate(int);

std::string getInputs(std::string);
std::string getOutputs(std::string);
std::string getAcreHash(int);
std::string getAcreMerkle(int);

const CBlockIndex* getAcreIndex(int);

#endif