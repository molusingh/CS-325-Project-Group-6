#!/usr/bin/python

import os
import sys

# main function called if the python file is executed
def main():
    if len(sys.argv) != 2:
        print("Error: Takes exactly 1 argument")
        return

    inputFile = sys.argv[1]
    solutionFile = inputFile + ".tour"
    
    cmd = "tsp-verifier.py " + inputFile + " " + solutionFile
    os.system(cmd)
        
# executes main function if this file is executed
if __name__ == "__main__":
    main()
