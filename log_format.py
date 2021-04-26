import sys

length = len(sys.argv)
if length != 2 :
    print("usage: python3 log_format.py [filepath]\n")
    exit(-1)

log_file = open(sys.argv[1],"r")


log_file.close()