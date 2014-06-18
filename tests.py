#!/usr/bin/env python3

import os
import sys
import subprocess
import difflib

TESTDIR = os.path.abspath(os.path.dirname(__file__)) + '/tests'

def run_tests(exe):
    tests = set()
    for f in os.listdir(TESTDIR):
        testname = f.split('.')[0]
        tests.add(testname)

    print()

    for test in sorted(list(tests)):
        infile = open("tests/{}.in".format(test), 'r')
        outfile = open("tests/{}.out".format(test), 'w')

        cmd = "./{}".format(exe)
        subprocess.Popen([cmd], stdin=infile, stdout=outfile, stderr=subprocess.STDOUT).communicate()[0]

        infile.close()
        outfile.close()

        outfile = open("tests/{}.out".format(test), 'r')
        reffile = open("tests/{}.ref".format(test), 'r')

        output = outfile.readlines()
        refput = reffile.readlines()

        print("Test: {} ".format(test), end="")
        if (''.join(output) == ''.join(refput)):
            print("PASS")
            print()
        else:
            print("FAIL")
            print("Diff (+ref, -usr):")
            print(''.join(difflib.Differ().compare(output, refput)))

        outfile.close()
        reffile.close()

def main():
    run_tests(sys.argv[1])

if __name__ == "__main__":
    main()