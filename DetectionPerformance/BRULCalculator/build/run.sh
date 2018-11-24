tmin=0.001
tmax=1000
sigma_oPs=0.3
sigma_pPs=0.7

prompt_eff_3=1.40514
prompt_eff_4=5.36894

#Dodałęm nowe wartosci
echo "${tmin} ${tmax} ${sigma_oPs} ${sigma_pPs}" 

./brul_calc 1 ${prompt_eff_3} ${tmin} ${tmax} ${sigma_pPs} pPs_3_layers.png 50 0.388207 70  0.334131 100 0.264925
./brul_calc 1 ${prompt_eff_3} ${tmin} ${tmax} ${sigma_oPs} oPs_3_layers.png 50 0.001923 70 0.000918 100 0.00024
./brul_calc 0 ${prompt_eff_3} ${tmin} ${tmax} ${sigma_pPs} pPs_4_gammas_3_layers.png 50 0.000015 70 0.000002
./brul_calc 0 ${prompt_eff_3} ${tmin} ${tmax} ${sigma_oPs} oPs_4_gammas_3_layers.png 50 0.000015 70 0.000002


./brul_calc 1 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_pPs} pPs_4_layers.png 50 2.22945 70 1.91942 100 1.51872
./brul_calc 1 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_oPs} oPs_4_layers.png 50 0.086972 70 0.043199 100 0.012146
./brul_calc 0 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_pPs} pPs_4_gammas_4_layers.png 50 0.001736 70 0.000283 100 0.000004
./brul_calc 0 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_oPs} oPs_4_gammas_4_layers.png 50 0.001736 70 0.000283 100 0.000004
./brul_calc 0 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_pPs} pPs_5_gammas_4_layers.png 50 0.000007
./brul_calc 0 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_oPs} oPs_5_gammas_4_layers.png 50 0.000007

#Tutaj wykresy eta dla podwojnych rozporszen
./brul_calc 1 ${prompt_eff_3} ${tmin} ${tmax} ${sigma_pPs} pPs_3_layers_2sc.png 50 0.002766 70  0.001357 100 0.000357

./brul_calc 1 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_pPs} pPs_4_layers_2sc.png 50 0.071608 70 0.035767 100 0.009468
./brul_calc 1 ${prompt_eff_4} ${tmin} ${tmax} ${sigma_oPs} oPs_4_layers_2sc.png 50 0.000144 70 0.000006


