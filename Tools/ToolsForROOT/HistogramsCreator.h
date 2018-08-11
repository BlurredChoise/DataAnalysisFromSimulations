#ifndef HistogramsCreator_h
#define HistogramsCreator_h
#include "TH1F.h"
#include "TH2F.h"
#include <string>

namespace ToolsForROOT
{
 /**
 Author: Mateusz Bała
 E-mail: bala.mateusz@gmail.com
 About: This is simple static class which provides histograms creating methods
 **/
 class HistogramsCreator
 {
  public:
   static TH1F* getTH1F( std::string histogram_name_and_title, unsigned int bins_number, double x_min_value, double x_max_value, std::string axis_x_title, std::string axis_y_title );
   static TH2F* getTH2F( std::string histogram_name_and_title, unsigned int bins_number_axis_x, double x_min_value, double x_max_value, unsigned int bins_number_axis_y, double y_min_value, double y_max_value, std::string axis_x_title, std::string axis_y_title );

   static void createTwoTH1F( TH1F* histogram_1, TH1F* histogram_2, std::string histogram_1_name_and_title, std::string histogram_2_name_and_title, unsigned int bins_number, double x_min_value, double x_max_value, std::string axis_x_title, std::string axis_y_title );

   static void createTwoTH2F( TH2F* histogram_1, TH2F* histogram_2, std::string histogram_1_name_and_title, std::string histogram_2_name_and_title, unsigned int bins_number_axis_x, double x_min_value, double x_max_value, unsigned int bins_number_axis_y, double y_min_value, double y_max_value, std::string axis_x_title, std::string axis_y_title );
 };
};

#endif
