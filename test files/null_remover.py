import sys
import random
print sys.argv[1]
number_of_bytes=sys.argv[1]
f=open(sys.argv[1],"r");
fout=open("denulled_"+sys.argv[1],"w");
lines=f.readlines()
for num in range(len(lines)):
	s=lines[num]
	s=s.replace('\0','')
	fout.write(s)

#f.write('+')
f.close()
fout.close()