import sys

length = len(sys.argv)
if length != 2 :
    print("usage: python3 log_format.py [filepath]\n")
    exit(-1)

read_file = open(sys.argv[1],"r")
write_file = open(sys.argv[1]+'.kv','w');

line = read_file.readline()
while line != '':
    if '[FRAME]' in line:
        line = read_file.readline()
        if 'video' in line:
            while line != '[\FRAME]':
                if 'pkt_duration' in line:
                    if 'pkt_duration_time'not in line:
                        print(line)
                if 'pkt_size' in line:
                    print(line)
                line = read_file.readline()
        
    line = read_file.readline();
    

read_file.close()
write_file.close()