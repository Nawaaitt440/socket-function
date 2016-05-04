
#!/usr/bin/perl -w
#Filename: socketfunc3server.pl


use strict;
use Socket;

#use port 7890 as default

my $port = shift || 7890;
my $proto = getprotobyname('TCP');
my $server = "localhost"; #Host IP running the server

#create a socket

socket(SOCKET, PF_INET, SOCK_STREAM, $proto)
	or die "Socket unvailable $!\n";
setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR, 1)
	or die "Socket Option cannot reuse the address $!\n";

#bind to a port --> listen

bind(SOCKET, pack_sockaddr_in($port, inet_aton($server)))
	or die "Cannot bind to port $port! \n";

listen(SOCKET, 5) or die "Listen Port: $port!  \n";
	print "Server start on port: $port! \n";

#accept the connection

my $client_addr;
while($client_addr = accept(NEW_SOCKET, SOCKET))
{
	#send them a message --> close connection
	my $name = gethostbyaddr($client_addr, AF_INET);
	print NEW_SOCKET "Hi from server";
	print "Connection had received from $name! \n";
	close NEW_SOCKET;
}
