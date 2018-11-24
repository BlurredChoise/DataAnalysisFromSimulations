UNPACKER2:

About:
Tool to unpack the HADES-like .hld binary data into ROOT tree structure.

Prerequisite:
- tinyxml2 installed

Installation:
- Download Unpacker2 directory
- Enter Unpacker2 directory
- mkdir build 
- cd build
- cmake ..
- make 
- Download the tools2 directory
- Adjust the path the Unpacker2 library in rootlogon.c

Tools package description:
	- generate_corrections_TRB3_dataStructureV2: macro used for generating TDC calibration parameters. Run as T->Process on an unpacked in RAW mode root tree with calibration triggers
	- run_analysis: precompiled macro taht runs a sequence of tools required to achieve a root Tree with properly calculated hit times
	- calculate_times: precompiled macro that creates timelines for all the hits on channels
	- calculate_hits: precompiled macro that creates hit objects out of timeline times

Usage:
- prepare an XML file with setup description
- from tools2 run root -l
- type the following command:
  Unpacker2 u("full_path_to_hld_file", "full_path_to_config_file", number_of_evts_to_analyze)

Setup description file:
All fields are required

- main module <READOUT>
  - inside one can specify the board which act as hubs of readout modules as <DATA_SOURCE>
    - <TYPE> possible: TRB2_S, HUB2, TRB3, SHOWER
    - <TRBNET_ADDRESS>, in case of standalone board put 0000
    - <HUB_ADDRESS>
    - <REFERENCE_CHANNEL> 
    - <MODULES> collection of modules connected to the hub 
      - <TYPE> possible: TRB2, HPTDC_HR, HPTDC_VHR, ECAL_ADC, LATTICE_TDC
      - <TRBNET_ADDRESS>
      - <NUMBER_OF_CHANNELS>
      - <CHANNEL_OFFSET>
      - <RESOLUTION>
      - <MEASUREMENT_TYPE> possible TDC, ADC


eg for standalone TRB2 with 4 TDCs running in high resolution:
<?xml version="1.0"?>
<READOUT>
  <DEBUG>OFF</DEBUG>
  <DATA_SOURCE>
    <TYPE>TRB2_S</TYPE>
    <TRBNET_ADDRESS>0000</TRBNET_ADDRESS>
    <HUB_ADDRESS>0372</HUB_ADDRESS>
    <REFERENCE_CHANNEL>31</REFERENCE_CHANNEL>
    <MODULES>
      <MODULE>
	<TYPE>HPTDC_HR</TYPE>
	<TRBNET_ADDRESS>0000</TRBNET_ADDRESS>
	<NUMBER_OF_CHANNELS>32</NUMBER_OF_CHANNELS>
	<CHANNEL_OFFSET>0</CHANNEL_OFFSET>
	<RESOLUTION>100</RESOLUTION>
	<MEASUREMENT_TYPE>TDC</MEASUREMENT_TYPE>
      </MODULE>
      <MODULE>
	<TYPE>HPTDC_HR</TYPE>
	<TRBNET_ADDRESS>0001</TRBNET_ADDRESS>
	<NUMBER_OF_CHANNELS>32</NUMBER_OF_CHANNELS>
	<CHANNEL_OFFSET>32</CHANNEL_OFFSET>
	<RESOLUTION>100</RESOLUTION>
	<MEASUREMENT_TYPE>TDC</MEASUREMENT_TYPE>
      </MODULE>
      <MODULE>
	<TYPE>HPTDC_HR</TYPE>
	<TRBNET_ADDRESS>0002</TRBNET_ADDRESS>
	<NUMBER_OF_CHANNELS>32</NUMBER_OF_CHANNELS>
	<CHANNEL_OFFSET>64</CHANNEL_OFFSET>
	<RESOLUTION>100</RESOLUTION>
	<MEASUREMENT_TYPE>TDC</MEASUREMENT_TYPE>
      </MODULE>
      <MODULE>
	<TYPE>HPTDC_HR</TYPE>
	<TRBNET_ADDRESS>0003</TRBNET_ADDRESS>
	<NUMBER_OF_CHANNELS>32</NUMBER_OF_CHANNELS>
	<CHANNEL_OFFSET>96</CHANNEL_OFFSET>
	<RESOLUTION>100</RESOLUTION>
	<MEASUREMENT_TYPE>TDC</MEASUREMENT_TYPE>
      </MODULE>
    </MODULES>
  </DATA_SOURCE>
</READOUT>
