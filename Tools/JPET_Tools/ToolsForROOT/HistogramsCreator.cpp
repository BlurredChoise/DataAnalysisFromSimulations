#include "HistogramsCreator.h"

namespace ToolsForROOT
{
 TH1F* HistogramsCreator::getTH1F( std::string histogram_name_and_title, unsigned int bins_number, double x_min_value, double x_max_value, std::string axis_x_title, std::string axis_y_title )
 {
  TH1F* histogram = new TH1F( histogram_name_and_title.c_str(), histogram_name_and_title.c_str(), bins_number, x_min_value, x_max_value );
  histogram->GetXaxis()->SetTitle( axis_x_title.c_str() );
  histogram->GetYaxis()->SetTitle( axis_y_title.c_str() );
  return  histogram;
 }

 TH2F* HistogramsCreator::getTH2F( std::string histogram_name_and_title, unsigned int bins_number_axis_x, double x_min_value, double x_max_value, unsigned int bins_number_axis_y, double y_min_value, double y_max_value, std::string axis_x_title, std::string axis_y_title )
 {
  TH2F* histogram = new TH2F( histogram_name_and_title.c_str(), histogram_name_and_title.c_str(), bins_number_axis_x, x_min_value, x_max_value, bins_number_axis_y, y_min_value, y_max_value );
  histogram->GetXaxis()->SetTitle( axis_x_title.c_str() );
  histogram->GetYaxis()->SetTitle( axis_y_title.c_str() );
  return  histogram; 
 }

 TH3F* HistogramsCreator::getTH3F( std::string histogram_name_and_title, unsigned int bins_number, double xyz_min_value, double xyz_max_value, std::string axis_x_title, std::string axis_y_title,  std::string axis_z_title )
 {
  TH3F* histogram = new TH3F( histogram_name_and_title.c_str(), histogram_name_and_title.c_str(), bins_number, xyz_min_value, xyz_max_value, bins_number, xyz_min_value, xyz_max_value, bins_number, xyz_min_value, xyz_max_value );
  histogram->GetXaxis()->SetTitle( axis_x_title.c_str() );
  histogram->GetYaxis()->SetTitle( axis_y_title.c_str() );
  histogram->GetYaxis()->SetTitle( axis_z_title.c_str() );
  return  histogram;
 }

 void HistogramsCreator::createTwoTH1F( TH1F* histogram_1, TH1F* histogram_2, std::string histogram_1_name_and_title, std::string histogram_2_name_and_title, unsigned int bins_number, double x_min_value, double x_max_value, std::string axis_x_title, std::string axis_y_title )
 {
  histogram_1 = getTH1F( histogram_1_name_and_title, bins_number, x_min_value, x_max_value, axis_x_title, axis_y_title );
  histogram_2 = getTH1F( histogram_2_name_and_title, bins_number, x_min_value, x_max_value, axis_x_title, axis_y_title );
 }

 void HistogramsCreator::createTwoTH2F( TH2F* histogram_1, TH2F* histogram_2, std::string histogram_1_name_and_title, std::string histogram_2_name_and_title, unsigned int bins_number_axis_x, double x_min_value, double x_max_value, unsigned int bins_number_axis_y, double y_min_value, double y_max_value, std::string axis_x_title, std::string axis_y_title )
 {
  histogram_1 = getTH2F( histogram_1_name_and_title, bins_number_axis_x, x_min_value, x_max_value, bins_number_axis_y, y_min_value, y_max_value, axis_x_title, axis_y_title);
  histogram_2 = getTH2F( histogram_2_name_and_title, bins_number_axis_x, x_min_value, x_max_value, bins_number_axis_y, y_min_value, y_max_value, axis_x_title, axis_y_title);
 }
};
