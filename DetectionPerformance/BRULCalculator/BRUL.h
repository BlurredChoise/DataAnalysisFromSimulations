#ifndef BRUL_h
#define BRUL_h

#include "TF1.h"
#include <string>

class BRUL
{
 public:
  BRUL();
  ~BRUL();

  void setBRParameterFromCL( double value );
  void setNBackground( unsigned int N_bg );
  void setEfficiency( double eff );
  void setSigma( double sigma );
  void setTimeRange( double t_min, double t_max);
  void setFunctionName( std::string f_name );
  void setSourceActivity( double source_activity );
  TF1* getBRULFunction();
  double getBRValue( double t );

 private:
  double fParamFromCL = 1.0;
  unsigned int fNBackground = 1;
  double fEfficiency = 1.0;
  double fSigma = 1.0;
  double fTimeMin = 0;
  double fTimeMax = 10;//days
  const double kFactor = 1.0 / 8.64;
  std::string fFunctionName = "BRUL_Function";
  double fSourceActivity = 10.0; //MBq
  TF1* fFunction = nullptr;
  
};


#endif
