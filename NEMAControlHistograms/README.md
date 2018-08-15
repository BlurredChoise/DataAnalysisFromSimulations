# NEMA Control

Creates 3 2D histograms for NEMA phantom.
This program uses a coordinate of gamma's emission point.
This program takes from each one event only first scatter ( it doesn't matter from which track ).
Additionaly this program checks how this histograms look like for conndition: track1 and track 2 scattered.

**This example use data collected by Global Actor from GATE**

## How to build
```
mkdir build
cmake ..
make
```

## How to run
```
./nema_ch input_file.root output_file.root
```


