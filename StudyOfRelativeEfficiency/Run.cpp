#include <iostream>
#include "REAnalysis.h"
#include "REDataCreator.h"
#include "../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"
#include "../Tools/ParametersReader/ParametersReader.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: Start file for program.
File: Run.cpp
**/

void configureAnalysis( REAnalysis* rea, Tools::ParametersReader& pr )
{
 if ( pr.isParam( "sigma_energy_threshold" ) )
  rea->setSigmaEnergyThreshold( pr.getDouble( "sigma_energy_threshold" ) );

 if ( pr.isParam( "mean_energy_threshold" ) )
  rea->setMeanEnergyThreshold( pr.getDouble( "mean_energy_threshold" ) );

 if ( pr.isParam( "use_energy_threshold_smearing" ) )
  rea->useSmearingEnergyThreshold( pr.getBool( "use_energy_threshold_smearing" ) );

 if ( pr.isParam( "analysis_normal_distribution_range" ) )
 {
  std::pair<double, double> xrange = pr.getDoublePair( "analysis_normal_distribution_range" );
  rea->setNormalDistributionRange( xrange.first, xrange.second );
 }

 if ( pr.isParam( "use_time_separation" ) )
  rea->useHitsSeparationByTime( pr.getBool( "use_time_separation" ) );

 if ( pr.isParam( "analysis_seed" ) )
  rea->setSeed( static_cast<unsigned int>( pr.getInt( "analysis_seed" ) ) );

 if ( pr.isParam( "energy_threshold" ) )
  rea->setEnergyDepositionCondition( pr.getDouble( "energy_threshold" ) );
}

void configureCreator( REDataCreator* rdc, Tools::ParametersReader& pr )
{
 if ( pr.isParam( "sigma_z" ) )
  rdc->setSigmaZ( pr.getDouble( "sigma_z" ) );

 if ( pr.isParam( "sigma_time" ) )
  rdc->setSigmaTime( pr.getDouble( "sigma_time" ) );
 
 if ( pr.isParam( "use_z_smearing" ) )
  rdc->useSmearingZ( pr.getBool( "use_z_smearing" ) );
 
 if ( pr.isParam( "use_time_smearing" ) )
  rdc->useSmearingTime( pr.getBool( "use_time_smearing" ) );
 
 if ( pr.isParam( "use_energy_deposition_smearing" ) )
  rdc->useSmearingEnergyDeposition( pr.getBool( "use_energy_deposition_smearing" ) );

 if ( pr.isParam( "dc_seed" ) )
  rdc->setSeed( static_cast<unsigned int>( pr.getInt( "dc_seed" ) ) );

 if ( pr.isParam( "dc_normal_distribution_range" ) )
 {
  std::pair<double, double> xrange = pr.getDoublePair( "dc_normal_distribution_range" );
  rdc->setNormalDistributionRange( xrange.first, xrange.second );
 }
}

int main(int argc, char *argv[])
{
 //We require minimum 2 arguments - input_file_name output_file_name [configuration_file or command] [comands]
 if ( argc < 3 )
 {
  std::cout << "Inccorect number of parameters" << std::endl;
  return 1;
 }
 
 std::string input_file_name( argv[ 1 ] );
 std::string output_file_name( argv[ 2 ] );

 Tools::ParametersReader pr;
 if ( argc > 3 )
 {
  pr.extractParameters( argc, argv, 3 );
  pr.displayAllParams();
 }
 REAnalysis rea;
 REDataCreator rdc;
 ToolsForGATE::GlobalActorReader gar;

 rea.setCreator( &rdc );
 rdc.setReader( &gar );

 configureAnalysis( &rea, pr );
 configureCreator( &rdc, pr );

 rea.displayStatus();
 rdc.displayStatus();

 gar.execute( input_file_name, &rea, &rdc );
 rea.saveHistograms( output_file_name );
}
