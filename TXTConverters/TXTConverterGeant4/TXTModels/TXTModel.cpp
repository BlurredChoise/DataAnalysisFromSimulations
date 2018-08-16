#include<iostream>
#include "TXTModel.h"

TXTModel::TXTModel() {}

TXTModel::~TXTModel() { closeTXTFile(); }
  
void TXTModel::setOutputFileName( std::string txt_ouput_file_name )
{
 fTXTOutputFileName = txt_ouput_file_name + ".txt";
 fControlHistogramsFileName = txt_ouput_file_name + "_control_histograms.root";
}

std::string TXTModel::getTXTOutputFileName() { return fTXTOutputFileName; }

std::string TXTModel::getControlHistogramsFileName() { return fControlHistogramsFileName; }

void TXTModel::setRequiredNumberOfEventsToSave( unsigned int number_of_events_to_save ) { fRequiredNumberOfEvents = number_of_events_to_save; }

void TXTModel::noticeNextEvent() { ++fCurrentNumberOfEvents; }

void TXTModel::saveControlHistograms() {}

void TXTModel::initControlHistograms() {}

void TXTModel::deleteControlHistograms() {}

void TXTModel::setHitogramsStatusAsSaved( bool saved ) { fHistogramsSavedToFile = saved; }

bool TXTModel::areHistogramsSavedToFile() { return fHistogramsSavedToFile; }

bool TXTModel::isRequiredEventsNumber() { return fCurrentNumberOfEvents == fRequiredNumberOfEvents; }

void TXTModel::analyzeHitsSet( std::vector< ToolsForG4MC::G4MCHitData >* ) {}

void TXTModel::openTXTFile() 
{ 
 fTXTFile.open( fTXTOutputFileName.c_str(), std::ios::out );
 fTXTFileOpened = true; 
}

void TXTModel::closeTXTFile() 
{ 
 if ( fTXTFileOpened )
  fTXTFile.close(); 
 fTXTFileOpened = false; 
}

bool TXTModel::isTXTFileOpened() { return fTXTFileOpened; }

std::fstream* TXTModel::getTXTFile() { return &fTXTFile; }

void TXTModel::displayStatus() { std::cout << " Number of saved events to file: " << fCurrentNumberOfEvents << " from " << fRequiredNumberOfEvents << " required." << std::endl; }
