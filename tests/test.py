from sys import argv
from random import seed, randint
from subprocess import Popen, PIPE, STDOUT

try:
    from subprocess import DEVNULL
except ImportError:
    import os
    DEVNULL = open(os.devnull, 'wb')

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

seed(int(argv[1]) if len(argv) > 1 else None)

fails = 0
total = 0
maxim = 1e10
steps = 10000
start = randint(0, steps - 1)
with open("./words.txt", "r") as file:
    for line in file:
        total += 1
        if ((start + total) % steps != 0):
            continue

        word = line.split()[0]
        for i in range(3):
            p1 = Popen(["echo", "approx %d %s"%(i, word)], stdout=PIPE)
            p2 = Popen(["./ref/linux64/TextMiningApp", "./dict.bin"], stdin=p1.stdout, \
                                                                      stdout=PIPE, \
                                                                      stderr=DEVNULL)
            p3 = Popen(["echo", "approx %d %s"%(i, word)], stdout=PIPE)
            p4 = Popen(["./TextMiningApp", "./dict.bin"], stdin=p3.stdout, \
                                                          stdout=PIPE, \
                                                          stderr=DEVNULL)
            
            out2 = p2.communicate()[0]
            out4 = p4.communicate()[0]
            if (out2 != out4):
                fails += 1
                if (fails > maxim):
                    continue
                print(bcolors.WARNING + "echo approx %d %s"%(i, word) + bcolors.ENDC)

total *= 3
if (fails == 0):
    print(bcolors.OKBLUE + "100% passed." + bcolors.ENDC)
else:
    print(bcolors.FAIL + "%.2f%% passed."%((total - fails) / total) + bcolors.ENDC)
