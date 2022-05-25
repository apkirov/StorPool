import struct
from functools import partial

theDict = {};
uh1 = 0;


#You may think, that if I read more than 4 bytes at once its will be faster, but its not true. The python interpreter do necessary to speedUP my not very smart peace of code and in fact the slowest part is writing into [dict] 
with open('res.bin', 'rb') as openfileobject:
	for chunk in iter(partial(openfileobject.read, 4), b''):
		uh1 += 1;
		if uh1 % (10 ** 6) == 0:
			print(str(uh1) +  " is done")
		key = struct.unpack('I', chunk)[0];
		if key in theDict:
			theDict[key] += 1
		else:
			theDict[key] = 1
print ("All unique numbers are: %d. From them %d founds only once " %  ( len(theDict.keys()), len( [key for key in theDict.keys() if theDict[key] == 1] ) ) )
