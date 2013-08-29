#!/usr/bin/env python
import time
import socket
import struct
import sys
import string
s = socket.socket()
s.connect(('127.0.1.1',12345))
while True:
	s.send(struct.pack("iii",1,4,string.atoi(sys.argv[1])))
	ss = struct.unpack("i",s.recv(4))[0]
	print "recv",ss,len(sys.argv[1])
	
	if str(ss) != sys.argv[1]:
		print ss,sys.argv[1]
		break
	time.sleep(1)
