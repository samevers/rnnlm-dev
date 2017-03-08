#!/usr/bin/perl

my $oriFile;
my $predictFile;
my $thres = 0;
if(@ARGV >= 2)
{
	$oriFile=$ARGV[0];
	$predictFile=$ARGV[1];
}elsif (@ARGV >= 3)
	$thres = $ARGV[2];

open(oriFIN, $oriFile) || die "ERROR: FAIL TO OPEN ORIGINAL FILE.\n";
open(predictFIN, $predictFile) || die "ERROR: FAIL TO OPEN PREDICT FILE.\n";

my $correct = 0;
my $total = 0;
my %thresAccu = ();
while(my $line = <oriFIN>)
{
	chomp $line;
	my @arr = split /\s+/, $line;
	my $yClass = $arr[$#arr];

	my $line = <predictFIN>;
	chomp $line;
	my $dClass = "";
	if($line =~ /CLASS=(.*?),/)
	{
		$dClass = $1;
	}
	my $portion = 0;
	if($line =~ /thres=(.*?),/)
	{
		$portion = $1;
	}

	if($thres == 0)
	{
		if($dClass eq $yClass)
		{
			$correct ++;
		}
		$thresAccu{$portion}{"correct"}++;
	}else
	{
		if($portion > $thres)
		{
			$correct ++;
		}
	}
	$total ++;
}
close oriFIN;
close predictFIN;


## ACCURACY
my $accu = $correct/($correct+$inCorrect);
print "Thres = ".$thres."Accuracy = ".$accu."\n";

if($thres == 0)
{
	foreach my $p(sort{$b <=> $a} keys %{thresAccu{"correct"}})
	{
		print $p.", ".$thresAccu{"correct"}{$p}."\n";
	}
}
