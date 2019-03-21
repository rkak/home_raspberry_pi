#! /usr/bin/env python

import sys
from socket import *

PORT=1999

BUFSIZE=1024

def main():
	client()

def client():
	host='192.168.0.2'
	port=PORT
	addr=host,port
	s = socket(AF_INET, SOCK_DGRAM)
	s.bind((host, port))
	print 'UDP client ready, reading'
	while 1:
		data, fromaddr=s.recvfrom(BUFSIZE)
                data2, fromaddr2=s.recvfrom(BUFSIZE)
		print 'client received %r from %r' % (data, fromaddr)
                print 'client2 received %r from %r' % (data2, fromaddr2)
main()


