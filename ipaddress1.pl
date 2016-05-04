#--Advanced Socket Programming in Perl Language

use strict;
use warnings;
use IO::Socket::INET;

my $local_ipaddress = get_local_ipaddress();

print "Local IP Address: $local_ipaddress\n";

sub get_local_ipaddress
{
	my $socket = IO::Socket::INET->new
	(
		Proto => 'TCP',
		PeerAddr => '198.41.0.4',
		PeerPort => '80', #dns
	);

	my $local_ipaddress = $socket -> sockhost;
	return $local_ipaddress;
}
