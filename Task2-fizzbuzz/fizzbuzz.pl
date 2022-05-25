#!/usr/bin/perl
use strict;
=pod Star desciption
To Star this just run 
perl fizzbuzz.pl

=cut


my $hDevBy3 = { map {$_ => "A" } (3,6,9) };
my $hDevBy5 = { map {$_ => "B" } (0,5) };

grep (fizzbuzz($_), (1 .. 100));


sub fizzbuzz {
	my $treeDigitsnumber = sprintf('%03d', shift);
	my ($first, $second, $third) = split(//, $treeDigitsnumber);
	my $next = sprintf('%03d', $first + $second + $third);
	my ($first2, $second2, $third2) = split(//, $next);
	print  $treeDigitsnumber .' -- '.   ( $hDevBy3->{$third2}.$hDevBy5->{$third} ||  $treeDigitsnumber) ."\n";
	return 0;

}




