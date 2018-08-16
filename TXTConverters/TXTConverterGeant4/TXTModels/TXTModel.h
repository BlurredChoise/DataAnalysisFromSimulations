#ifndef TXTModel_h
#define TXTModel_h

#include <vector>
#include <string>
#include <fstream>
#include "../../../Tools/ToolsForG4MC/G4MCHitData/G4MCHitData.h"

class TXTModel
{
 public:
  TXTModel();
  virtual ~TXTModel();
  
  void setOutputFileName( std::string txt_ouput_file_name );
  std::string getTXTOutputFileName();
  std::string getControlHistogramsFileName();

  void setRequiredNumberOfEventsToSave( unsigned int number_of_events_to_save );
  void noticeNextEvent();

  virtual void saveControlHistograms();
  virtual void initControlHistograms();
  virtual void deleteControlHistograms();
  void setHitogramsStatusAsSaved( bool saved );
  bool areHistogramsSavedToFile();

  bool isRequiredEventsNumber();

  virtual void analyzeHitsSet( std::vector< ToolsForG4MC::G4MCHitData >* data );

  void openTXTFile();
  void closeTXTFile();
  std::fstream* getTXTFile();
  bool isTXTFileOpened();

  void displayStatus();

 private:
  unsigned int fRequiredNumberOfEvents = 0;
  unsigned int fCurrentNumberOfEvents = 0;
  std::string fTXTOutputFileName;
  std::string fControlHistogramsFileName;
  std::fstream fTXTFile;
  bool fHistogramsSavedToFile = false;
  bool fTXTFileOpened = false;
};

#endif
