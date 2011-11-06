#!/usr/bin/perl

use Text::English;

open(MYINPUTFILE, "<test.dat");
my $i = 0;
while(<MYINPUTFILE>) {
	$i++;
	my $line = $_;
	chomp($line);
	if ($i % 2 == 0) {
		@words = split(/\s+/, $line);
		my $size = @words;
		@stems = Text::English::stem(@words);
#		print "size: $size\n";
#		print "@words";
#		print "\n";
#		print "**************************************";
#		print "\n";
		print "@stems\n";
#		print "\n";
	} else {
		print "$line\n";
	}
}
