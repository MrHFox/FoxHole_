#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include "foxcoinfunction.h"
#include <sstream>
#include <string>

using namespace json_spirit;

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
    
    setFixedSize(400, 420);
    
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(updateStatistics()));
}

int heightPrevious = -1;
int connectionPrevious = -1;
int volumePrevious = -1;
double rewardPrevious = -1;
double netPawratePrevious = -1;
double pawratePrevious = -1;
double hardnessPrevious = -1;

void StatisticsPage::updateStatistics()
{    
    double pHardness = getHardness();
    int pPawrate = getNetworkPawsPS();
    double pPawrate2 = 0.000;
    int nHeight = pindexBest->nHeight;
    int lPawrate = this->model->getHashrate();
    double lPawrate2 = 0.000;
    double nSubsidy = getAcreReward();
    double nextHardness = GetEstimatedNextHardness();
    int volume = getTotalVolume();
    int peers = this->model->getNumConnections();
    lPawrate2 = ((double)lPawrate / 1000);
    pPawrate2 = ((double)pPawrate / 1000);  
    QString height = QString::number(nHeight);
    QString subsidy = QString::number(nSubsidy, 'f', 6);
    QString hardness = QString::number(pHardness, 'f', 6);
    QString QnextHardness = QString::number(nextHardness, 'f', 6);
    QString pawrate = QString::number(pPawrate2, 'f', 3);
    QString Qlpawrate = QString::number(lPawrate2, 'f', 3);
    QString QPeers = QString::number(peers);
    QString qVolume = QLocale(QLocale::English).toString(volume);
    if(nHeight > heightPrevious)
    {
        ui->heightBox->setText("<b><font color=\"green\">" + height + "</font></b>");
    } else {
    ui->heightBox->setText(height);
    }
    
    if(nSubsidy < rewardPrevious)
    {
        ui->rewardBox->setText("<b><font color=\"red\">" + subsidy + "</font></b>");
    } else {
    ui->rewardBox->setText(subsidy);
    }
    
    if(pHardness > hardnessPrevious)
    {
        ui->diffBox->setText("<b><font color=\"green\">" + hardness + "</font></b>");        
    } else if(pHardness < hardnessPrevious) {
        ui->diffBox->setText("<b><font color=\"red\">" + hardness + "</font></b>");
    } else {
        ui->diffBox->setText(hardness);        
    }
    
    if(nextHardness > pHardness)
    {
        ui->nextBox->setText("<b><font color=\"green\">" + QnextHardness + "</font></b>");        
    } else if(nextHardness < pHardness) {
        ui->nextBox->setText("<b><font color=\"red\">" + QnextHardness + "</font></b>"); 
    } else {
        ui->nextBox->setText(QnextHardness);        
    }
    
    if(pPawrate2 > netPawratePrevious)
    {
        ui->pawrateBox->setText("<b><font color=\"green\">" + pawrate + " KH/s</font></b>");             
    } else if(pPawrate2 < netPawratePrevious) {
        ui->pawrateBox->setText("<b><font color=\"red\">" + pawrate + " KH/s</font></b>");        
    } else {
        ui->pawrateBox->setText(pawrate + " KH/s");        
    }
    
    if(lPawrate > pawratePrevious)
    {
        ui->localBox->setText("<b><font color=\"green\">" + Qlpawrate + " KH/s</font></b>");             
    } else if(lPawrate < pawratePrevious) {
        ui->localBox->setText("<b><font color=\"red\">" + Qlpawrate + " KH/s</font></b>");        
    } else {
        ui->localBox->setText(Qlpawrate + " KH/s");      
    }
    
    if(peers > connectionPrevious)
    {
        ui->connectionBox->setText("<b><font color=\"green\">" + QPeers + "</font></b>");             
    } else if(peers < connectionPrevious) {
        ui->connectionBox->setText("<b><font color=\"red\">" + QPeers + "</font></b>");        
    } else {
        ui->connectionBox->setText(QPeers);  
    }

    if(volume > volumePrevious)
    {
        ui->volumeBox->setText("<b><font color=\"green\">" + qVolume + " FOX" + "</font></b>");             
    } else if(volume < volumePrevious) {
        ui->volumeBox->setText("<b><font color=\"red\">" + qVolume + " FOX" + "</font></b>");        
    } else {
        ui->volumeBox->setText(qVolume + " FOX");  
    }
    updatePrevious(nHeight, nSubsidy, pHardness, pPawrate2, lPawrate, peers, volume);
}

void StatisticsPage::updatePrevious(int nHeight, double nSubsidy, double pHardness, double pPawrate2, double lPawrate, int peers, int volume)
{
    heightPrevious = nHeight;
    rewardPrevious = nSubsidy;
    hardnessPrevious = pHardness;
    netPawratePrevious = pPawrate2;
    pawratePrevious = lPawrate;
    connectionPrevious = peers;
    volumePrevious = volume;
}

void StatisticsPage::setModel(ClientModel *model)
{
    this->model = model;
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}