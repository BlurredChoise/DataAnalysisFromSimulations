#ifndef FILTER_H
#define FILTER_H
#include <JPetUserTask/JPetUserTask.h>
#include <vector>
#include <JPetStatistics/JPetStatistics.h>
#include "AnalysisData.h"
#include <string>
#include <JPetParams/JPetParams.h>

/**
Każda klasa powinnna mieć opis, mówiący co robi dany filter.
Opis powinien zaczynać się tak:
@FilterDescriptionStart
Tutaj powinie byc opis co robi filter. Potem wykorzystywałby to parser.
@FilterDescriptionEnd
**/
class Filter
{
 public:
  Filter( JPetStatistics& stats, JPetParams& params );
  virtual ~Filter();
  virtual bool initStatistics() = 0;
  virtual bool filterData( std::vector<AnalysisData>& data ) = 0;
  int getIndex() const;
 public:
  void add1DHist( std::string histogram_name_and_title, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name );
  void add1DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name );
  void fill1DHist( std::string histogram_name, double& value );
  void add2DHist( std::string histogram_name_and_title, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name );
  void add2DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name );
  void add2DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number_x, double min_value_x, double max_value_x, int bins_number_y, double min_value_y, double max_value_y, std::string axis_x_name, std::string axis_y_name );
  void fill2DHist( std::string histogram_name, double& value_x, double& value_y );
  bool fillDoubleParameter( std::string parameter_key, double& param_value );
  bool fillIntParameter(  std::string parameter_key, int& param_value );
  bool fillUnsignedIntParameter(  std::string parameter_key, unsigned int& param_value );
  bool setIndexForFilter( std::string parameter_key );
  void noticeFor1DHists( std::string histogram_name_before, std::string histogram_name_after,  bool passed , double value);
  void noticeFor2DHists( std::string histogram_name_before, std::string histogram_name_after,  bool passed , double value_x, double value_y);
  void setName( std::string filter_name );
  std::string getName();
  void coutLine();

  bool getBoolParamValue( std::string param_key );

 /**
  Tutaj dodatkowo powinny być zdefiniowane funkcje set dla konkretnych ustawiń
 **/
 /**
  private:
  Każda potomna klasa powinna mieć zmienne w ostaci std::string będące nazwami histogramów
  W ten sposób pozbęde się błedów typu, że podałem błędną nzwe histogramu.
  Nazwa zmiennej reprezentujące histogram powinna mieć postać fH1NazwaHistogramu dla 1D histogramu, fH2NazwaHistogramu dla 2D histogramu
 **/
 private:
  JPetStatistics* fFiltersStatistics;
  JPetParams* fFiltersParameters;
  int fIndex;
  std::string fName;
};

#endif
