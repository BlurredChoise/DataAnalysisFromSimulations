# Study Of Relative Efficiency
**Author: Mateusz Bała**
**E-mail: bala.mateusz@gmail.com**

## Build

**ATTENTION: Before first call of cmake please set variable ROOT_INSTALLATION_DIRECTOR in CMakeList.txt file**

```
mkdir build
cd build
cmake ..
make
```

## Executing commands
In build directory you can find two exaples bash scripts - both can be called like this (here example1) :
```
bash example1.sh my_input_data_file.root
```

## Commands
You can give commands in two ways - from command line or from configuration file.
A proper way of call commands is:
```
./rel_eff input_data_fie.root output_data_file.root [ empty or first command or configuration file name ] [ another commands ]
```
Some examples:
1. Calling without additional commands:
```
./rel_eff input_data_fie.root output_data_file.root
```
in this situation program run analyze data file **input_data_fie.root** with default confiuration and save data to **output_data_file.root**

2. Calling with additional command:
```
./rel_eff input_data_fie.root output_data_file.root energy_threshold=50.0
```
in this case program save only data for this with energy deposition higher than energy threshold equals 50.0 keV

3. Calling with additional command and configuration file:
```
./rel_eff input_data_fie.root output_data_file.root conf.txt energy_threshold=50.0
```
Let's suppose our configuration file looks like below:
```
use_z_smearing=true
sigma_z=2.0
use_energy_deposition_smearing=true
```
In this case program will smear **z** position of hit with sigma 2.0 cm ( gauss distribution has here range from +/- sigma ) and energy deposition. Additionaly like in the point 2 program accept only hits with energy deposition greater than 50.0 keV.

## Enable commands

The commands are divided into two types: 
1. commands for the section preparing data for analysis
2. commands for the analysis section

**Commands for the section preparing data for analysis**

**use_z_smearing** - use smearing of z position of hit
**sigma_z** - value of simga for smearing of z position of hit ( sigma unit is **cm** )
**use_time_smearing** - use smearing of hit's time
**sigma_time** - value of simga for smearing of hit's time ( sigma unit is **ns** )
**use_energy_deposition_smearing** - use smearing of energy deposition
by default, gaussian distribution for smearing is +/- sigma. - by default, gaussian distribution for smearing is +/- sigma. You can change this range by calling for example:
```
dc_normal_distribution_range=-1.5,3.0
```
in this case range of gaussian distribution is from -1.5 * sigma to 3.0 * sigma for all smearings ( z, time, energy deposition ).
**dc_seed** - you can repeat simulation for the same random numbers if you use fixed value of seed for random numbers generator ( if you use positive integers ). By defaul, seed is equal zero - this means each one call of analysis finish with different results.

**Commands for the analysis section**

**use_energy_threshold_smearing** - use smearing of energy threshold
**mean_energy_threshold** - mean value of gaussian distribution for energy threshold smearing ( unit is keV )
**sigma_energy_threshold** - sigma of gaussian distribution for energy threshold smearing ( unit is keV )
**energy_threshold** - constant value of energy threshold - if you use smearing of energy threshold this value is not taken under consideration during analysis ( unit is keV )
**analysis_normal_distribution_range** - by default, gaussian distribution for smearing is +/- sigma. This command control range  gaussian distribution for energy threshold smearing
**use_time_separation** - by default, analysis categorize hits by the theirs track ID - to change it and use time categorization call this command **ATTENTION: this command doen not works now**
**analysis_seed** - works in the same way like **dc_seed** but only for energy threshold smearing







