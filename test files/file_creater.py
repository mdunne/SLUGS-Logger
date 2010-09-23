import sys
import random
print sys.argv[1]
number_of_bytes=sys.argv[1]
file_string=str(int(number_of_bytes))+"_sectors_in_size.bin"
print file_string
number_of_kilobytes=int(sys.argv[1])*512
random.seed(int(sys.argv[1]))
f=open(file_string,"w");
#print range(number_of_kilobytes)
for num in range(number_of_kilobytes):
	s=str(random.randint(0,9))
	f.write(s)

#f.write('+')
f.close()