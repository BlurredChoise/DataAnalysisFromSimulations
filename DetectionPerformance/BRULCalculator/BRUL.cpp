#include "BRUL.h"
#include "TMath.h"

BRUL::BRUL() { }

BRUL::~BRUL() { if ( fFunction != nullptr ) { delete fFunction; } }

void BRUL::setBRParameterFromCL( double value ) { fParamFromCL = value; }

void BRUL::setNBackground( unsigned int N_bg ) { fNBackground = N_bg; }

void BRUL::setEfficiency( double eff ) { fEfficiency = eff; }

void BRUL::setSigma( double sigma ) { fSigma = sigma; }

void BRUL::setTimeRange( double t_min, double t_max) { fTimeMin = t_min; fTimeMax = t_max; }

void BRUL::setFunctionName( std::string f_name ) { fFunctionName = f_name; }

void BRUL::setSourceActivity( double source_activity ) { fSourceActivity = source_activity; }

double BRUL::getBRValue( double t ) { return ( TMath::Sqrt( fNBackground ) * fParamFromCL / ( fEfficiency * fSourceActivity * t * fSigma ) ) * kFactor * TMath::Power( 10.0, -10.0 ); }

TF1* BRUL::getBRULFunction() 
{ 
 if ( fFunction == nullptr )
 {
  auto generatorBRUL = [ = ]( double * args, double * params )->double{ return getBRValue( args[ 0 ] ); };
  fFunction = new TF1( fFunctionName.c_str(), generatorBRUL, fTimeMin, fTimeMax, 0 );
 }
 return fFunction;
}
