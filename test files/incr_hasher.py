print 'welcome to hasher'
import os
import sys
import random
print sys.argv[1]
in_file=sys.argv[1]
size=os.path.getsize(in_file)
print size
binin=open(in_file,"r")
bytein=binin.read(1)
#print bytein
checksum=0
count=0
correct=0
total=0
prev=0
totalbytes=1
increment=32
#totalbytes+=1
#while bytein:
size/=10
sizetocheck=int(sys.argv[2])
sizetocheck*=512
#size=int(sys.argv[2])
#size*=16
olddata=0
print size
print sizetocheck
for t in range(1,size):
	#print bytein
	if bytein=='%':
		#print bytein
		bytein=binin.read(1)
		totalbytes+=1
		#print bytein
		sec=0
		if bytein=='&':  #assuming now in block to be hashed
			bytein=binin.read(1)
			totalbytes+=1
			#print 'about to enter'+bytein
			#print str(ord(bytein))+" in and increment is"+str(increment)
			if ord(bytein)!=increment:
				print "lost sectors: "+str(ord(bytein))+" in and increment is"+str(increment)+" total bytes: " +str(totalbytes)+"  "+str(ord(bytein)-increment)
				if ord(bytein)!=0:
					#sys.exit(0)
					olddata+=(ord(bytein)-increment)
					increment=ord(bytein)
			increment+=1
			if increment>126:
				increment=32
			while 1:
				#sys.stdout.write(bytein)
				if sec==0:
					checksum=ord(bytein)
					#if bytein!='6':
					#	print 'off '+bytein
					#	olddata+=1
						
				else:
					checksum^=ord(bytein)
				
				sec+=1
				prev=bytein
				
				bytein=binin.read(1)
				totalbytes+=1
				
				#this should break if i find the footer start at wrong point, really needs to be re-worked
				if bytein=='^':
					prev=bytein
					bytein=binin.read(1)
					if bytein=='&':
					
						break
			origchecksum=ord(binin.read(1))			
			#print ' '+hex(checksum)+' '+str(hex(origchecksum))
			if checksum==origchecksum:
				correct+=1
			else:
				print str(total) + "  " + str(checksum) + "  " + str(origchecksum)
			total+=1
	bytein=binin.read(1)
	totalbytes+=1
	#print totalbytes
	if totalbytes>=sizetocheck:
		break
	#if (ord(bytein)!=0x1f)| (bytein!='%'):
	#	sys.stdout.write(bytein)
	#print str(ord(bytein))+' '+bytein
#			count+=1
			#print str(count)+' '+str(t)
#			for i in range(0,505):
#				bytein=ord(binin.read(1))
				#sys.stdout.write(chr(bytein)+" ")
#				if i==0:
#					checksum=bytein
#				else:
#					checksum^=int(bytein)
			#print chr(bytein)
#			bytein=ord(binin.read(1))
#			if checksum==bytein:
#				correct+=1
#			total+=1
#			print hex(checksum)+" "+hex(bytein)
				#sys.stdout.write(bytein)
	#count=count+1
	#print count
	#bytein=binin.read(1)
	
print str(correct-olddata)+" Checksums correct out of "+str(total)+" for a percentage correct of "+str(float(correct-olddata)/(float(total))*100)
	
binin.close