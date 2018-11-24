#!/usr/bin/perl -T

use strict;
use Getopt::Std;
use warnings;

my %opt=();
getopts("sl", \%opt);

open (my $file_0, '<', $ARGV[0]) or die "cmp.pl: cannot open file \'$ARGV[0]\'";
open (my $file_1, '<', $ARGV[1]) or die "cmp.pl: cannot open file \'$ARGV[1]\'";
if ($opt{"l"} && $opt{"s"}) {
    print "you can't use -s and -l together\n";
    exit -1;
}
my ($trash_bin) = "";
if ($ARGV[2]) {
    read($file_0, $trash_bin, $ARGV[2]);
}

if ($ARGV[3]) {
    read($file_1, $trash_bin, $ARGV[3]);
}

my @buff1;
my @buff0;
my $byte = 0;
if ($opt{"l"}) {
    my ($buff_0) = "";
    my ($buff_1) = "";
    my $b_size0;
    my $b_size1;
    my $EOF;
    my $is_diff = 0;
    while (1) {
        $b_size0 = read($file_0, $buff_0, 256);
        $b_size1 = read($file_1, $buff_1, 256);
        @buff1 = split(//, $buff_1);
        @buff0 = split(//, $buff_0);
        
        if (($b_size1 < 256) || ($b_size0 < 256)) {
            if ($b_size1 < $b_size0) {
                $b_size0 = $b_size1;
                $EOF = $ARGV[1];
            } else {
                $EOF = $ARGV[0];
            }
        }

        for (my $i = 0; $i < $b_size0; $i++) {
            $byte++;
            if ($buff1[$i] ne $buff0[$i]) {
                print "$byte $buff0[$i] $buff1[$i]\n";
                $is_diff = 1;
            } 
        }
        if (($is_diff == 0) && (($EOF eq $ARGV[0]) || ($EOF eq $ARGV[1])) ) {exit 0;};
        if ($EOF) {print "cmp: EOF on $EOF\n"; exit 1; }
    }   
}

my $line_1 = 0;
my $line_0 = 0;
my $lines = 0;

my $i;

while (defined($line_1 = <$file_1>) && defined($line_0 = <$file_0>)) {
    if ($line_1 =~ m/$line_0/) {
        $lines++;
        $byte += length $line_0;
    } else {
        $lines++;
        @buff1 = split(//, $line_1);
        @buff0 = split(//, $line_0);
        $i = 0;
        while ($buff0[$i] eq $buff1[$i]) {
            $i++;
        }
        $byte += $i + 1;
        print "$ARGV[0] $ARGV[1] differ: byte $byte, line $lines\n" if !$opt{"s"};
        exit 1;        
    }
}
