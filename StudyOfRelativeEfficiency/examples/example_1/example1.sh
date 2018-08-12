#This example show how to set energy threshold cut by calling this option from command line
input_file=$1 #root file with data
../../rel_eff ${input_file} output_exaple_1.root energy_threshold=50.0
