import os
import sys
import random
print sys.argv[1]
print sys.argv[2]
in_file=sys.argv[1]
out_file=sys.argv[2]
fin=open(in_file,"r")
fout=open(out_file,"r")
#print range(number_of_kilobytes)
filein=fin.read(1)
fileout=fout.read(1)
fileout=fout.read(1)
total=1
correct=0
while filein:
	filein=fin.read(1)
	fileout=fout.read(1)
	if filein == fileout:
		correct+=1
	#else:
		#fileout=fout.read(1)
		#break
	total=total+1
	#print total%1024
	if total%1024==0:	
		#sys.stdout.write(str(correct)+" "+str(total)+" "+str((float(correct)/float(total)))+" "+str(filein)+str(fileout)+"\n")
		sys.stdout.write(str((float(correct)/float(total))*100)+"\r")

print "\n"+str(correct)+" out of "+str(total)+" for a percentage correct of "+str((float(correct)/float(total))*100.0)+"%"

	

#f.write('+')
fin.close()
fout.close()