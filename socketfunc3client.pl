#!/usr/bin/perl -w
#File Name: socketfunc3client.pl

use strict;  #generates a compile-time error if access a variable without declaration
use Socket;

#initialize host and port;

my $host = shift || 'localhost';
my $port = shift || 7890;
my $server = "localhost"; #host ip running the server

#create socket -->> connect to the port

socket(SOCKET, PF_INET, SOCK_STREAM,(getprotobyname('TCP'))[2])
	or die "Cannot connect to the port $port! \n";

my $line;

while($line = <SOCKET>)
{
	print "$line! \n";

}

close SOCKET or die "Close Port: $!\n";
