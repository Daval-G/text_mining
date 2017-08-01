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

def check_word(dist, word): 
    p1 = Popen(["echo", "approx %d %s"%(i, word)], stdout=PIPE)
    p2 = Popen(["./ref/linux64/TextMiningApp", "./dict.bin"], stdin=p1.stdout, \
                                                              stdout=PIPE,     \
                                                              stderr=DEVNULL)
    p3 = Popen(["echo", "approx %d %s"%(i, word)], stdout=PIPE)
    p4 = Popen(["./build/TextMiningApp", "./build/dict.bin"], stdin=p3.stdout, \
                                                  stdout=PIPE,     \
                                                  stderr=DEVNULL)

    return p2.communicate() ==  p4.communicate()

########### UNIT TESTS ###########
print(bcolors.HEADER + "Unit tests are computing..." + bcolors.ENDC)

########## RANDOM TESTS ##########
print(bcolors.HEADER + bcolors.OKBLUE + "Random tests are computing..." + bcolors.ENDC)

seed(int(argv[1]) if len(argv) > 1 else None)
fails = 0
total = 0
maxim = 1e10
steps = 30000
start = randint(0, steps - 1)
with open("./words.txt", "r") as file:
    for line in file:
        total += 1
        if ((start + total) % steps != 0):
            continue

        word = line.split()[0]
        for i in range(2):
            if (not check_word(i, word)):
                fails += 1
                if (fails > maxim):
                    continue
                print(bcolors.WARNING + "echo approx %d %s"%(i, word) + bcolors.ENDC)

total *= 2
color  = bcolors.OKBLUE if (fails == 0) else bcolors.FAIL
print(color + "%.2f%% passed."%(100 * (total - fails) / total) + bcolors.ENDC)
