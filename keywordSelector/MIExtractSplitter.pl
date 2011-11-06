#!/usr/bin/perl

use POSIX;

my $filename = $ARGV[0];
my $percentage = $ARGV[1];
#print "opening $filename\n";
open(MYINPUTFILE, "<$filename");
my %keywords;
my $first = 1;
my $label = "";
while(<MYINPUTFILE>) {
	$line = $_;
	chomp($line);
	if ($line =~ /\*\*\* (\w+) \*\*\*/) {
		$label = $1;
		$first = 0;
		#print "label: $label\n";
	} elsif ($first != 1) {
		#print "pushing $line to $label\n";
		push @{ $keywords{$label} }, $line;
	}
}
for my $key (keys %keywords) {
	my $size = @{$keywords{$key}};
	my $start = floor($size - $percentage * $size / 100 + 0.5);
	print "*** $key ***\n";
	foreach (@{$keywords{$key}}[$start..$size]) {
		print "$_\n";
	}
}
