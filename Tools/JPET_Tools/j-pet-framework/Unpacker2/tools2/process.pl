#!/usr/bin/perl -w

use threads;
use threads::shared;

my $file   = $ARGV[0];

my @threads;

open(DAT, $file);
@data = <DAT>;
close(DAT);

chomp(@data);

my $size = scalar(@data);

for(my $i = 0; $i < $size; $i++) {
	print "Creating thread for $data[$i]\n\n";
	
	$threads[$i] = threads->create(sub { `root -l -b -q 'process.c("$data[$i]", "/home/guplab/Unpacker/tools2/conf_trb3_pandaRAW.xml", 100000000000)'`});
	
	
}

for(my $i = 0; $i < $size; $i++) {
	$threads[$i]->join();
}

print("\n\n -------------- Done ------------ \n\n");
