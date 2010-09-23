import sys
import random
print sys.argv[1]
number_of_bytes=sys.argv[1]
file_string=str(int(number_of_bytes))+"_sectors_in_size.bin"
print file_string
sector_size=512-2-2-1-2
number_of_kilobytes=int(sys.argv[1])*sector_size
print str(number_of_kilobytes)
startchar=32
random.seed(int(sys.argv[1]))
f=open(file_string,"w");
#print range(number_of_kilobytes)
for num in range(number_of_kilobytes):
	if num%sector_size==0:
		startchar+=1
		if startchar>126:
			startchar=32
	s=chr(startchar)#str(random.randint(0,9))
	f.write(s)

#f.write('+')
f.close()