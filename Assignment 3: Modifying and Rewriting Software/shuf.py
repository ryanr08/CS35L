#1/usr/bin/python3

import random, sys
import argparse
import string

class shuf:
	def __init__(self, inputs, repeat, numlines):
		self.inputs = inputs
		self.repeat = repeat
		self.numlines = numlines
	def shuffle(self):
		if ( self.repeat == True ):
			for i in range(0, self.numlines):
				index = random.randint(0, len(self.inputs) - 1)
				print(self.inputs[index])
		else:
			if (len(self.inputs) < self.numlines):
				limit = len(self.inputs)
			else:
				limit = self.numlines
			i = 0
			printedVals = [False] * len(self.inputs)
			while (i < limit):
				index = random.randint(0, len(self.inputs) - 1)
				if (printedVals[index] == False):
					print (self.inputs[index])
					printedVals[index] = True
					i += 1
			 

def main():
	parser = argparse.ArgumentParser(usage="%(prog)s [-h] [-i LO-HI] [-n COUNT] [-r] [file]", description='shuf shuffles its input by outputting a random \
							permutation of its input lines.')

	parser.add_argument("-i", "--input-range", help="Input numbers from a range LO-HI.", action="store", dest="lo_hi", default="")

	parser.add_argument("-n", "--head-count", help="Outputs at most COUNT number of lines.", action="store", dest="count", default=sys.maxsize)
	
	parser.add_argument("-r", "--repeat", help="Repeats output values, that is, selects with replaement", action="store_true", dest="repeat")
	
	options, args = parser.parse_known_args()

	try: 
		numlines = int(options.count)
	except:
		parser.error("invalid COUNT: {0}".format(options.count))
	if ( numlines < 0 ):
		parser.error("invalid COUNT: {0}, cannot be negative".format(options.count))
	try:
		lohi = options.lo_hi
		if (lohi != ""):
			dashIndex = lohi.index('-')
			startNum = int(lohi[0:dashIndex])
			endNum = int(lohi[dashIndex+1:])
			if ( startNum > endNum ):
				parser.error("invalid LO_HI: {0}, LO cannot be > HI".format(options.lo_hi))
			else:
				Inputs = range(startNum, endNum + 1)
			if (len(args) > 0):
				parser.error("Cannot give an input file with -i argument")
	except:
		parser.error("invalid LO_HI: {0}".format(options.lo_hi))
			

	try:
		if (lohi == "" and len(args) == 0):
			Inputs = sys.stdin.readlines()
			Inputs = [s.replace('\n', '') for s in Inputs]
		elif (lohi == "" and args[0] == '-' and len(args) == 1):
			Inputs = sys.stdin.readlines()
			Inputs = [s.replace('\n', '') for s in Inputs]
		elif (lohi == "" and len(args) > 1):
			parser.error("Only up to one non-option argument is allowed")
		elif(len(args) == 1):
			f = open(args[0], 'r')
			Inputs = f.readlines()
			f.close()
			Inputs = [s.replace('\n', '') for s in Inputs]

	except:
		parser.error("invalid file input")
	try:

		generator = shuf(Inputs, options.repeat, numlines)
		generator.shuffle()
	except IOError as err:
		errno, strerror = err.args
		parser.error("I/O error({0}): {1}".format(errno, strerror))	


if __name__ == '__main__':
	main()

