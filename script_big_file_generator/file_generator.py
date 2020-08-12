from base64 import b64encode
import os
import sys

TOTAL_FILE_SIZE_IN_GB = 0.15
WRITES_PER_GB = 1024 * 1024 / 4

if 2 != len(sys.argv):
    print('Usage: python gen_file.py <path>')
    exit()

# f = open(sys.argv[1], 'wb')
f = open(sys.argv[1], 'w')              # we want able to write strings, not bytes


for i in range(int(WRITES_PER_GB * TOTAL_FILE_SIZE_IN_GB)):
    d = os.urandom(4096)                        # create a string which in size of 4096 bytes (single chunk)
    # f.write(d)                                # problem: we want to get unicode 8 or ascii
    f.write(b64encode(d).decode('utf-8'))       # decode the bytes to string
    # print(b64encode(d).decode('utf-8'))

f.close()