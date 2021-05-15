import sys
import re
import pandas as pd
# length = len(sys.argv)
# if length != 2 :
#     print("usage: python3 log_format.py [filepath]\n")
#     exit(-1)

#read_file = open(sys.argv[1],"r")
#write_file = open(sys.argv[1]+'.kv','w');
read_file = open('que_viva_mexico.log')
line = read_file.readline()
i = 0
line = read_file.readline()

ans = []

while line!='':
    flag = 1
    if 'audio' in line:
        flag = 0
        
        while line != '[/FRAME]\n':
            line = read_file.readline()
            #print('---')
    i+=1
    # if i>10000:
    #     print(ans)
    #     exit(0)
    #rint(1)
    #print(line)
    while line != '[FRAME]\n' and line!='':
        if 'pkt_duration=' in line:
            #if 'pkt_duration_time'not in line:
            #print(line)
            #print(re.findall('\d+',line)[0])
            pkt_duration = re.findall('\d+',line)[0]
        if 'pkt_size' in line:
            #print(line)
            #print(re.findall('\d+',line)[0])
            pkt_size = re.findall('\d+',line)[0]
        line = read_file.readline()
        #print(line)
    if flag == 1:
        ans.append(pkt_size)
    print('------')
    line = read_file.readline();
print('finish')
ans = pd.DataFrame(ans)
ans.to_csv('pkt_size.csv')
read_file.close()
#write_file.close()