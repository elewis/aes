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
        subprocess.Popen(
            [
                "./{}".format(exe),
                "-b", test[3:6],
                "-k", test_path(test, "key"),
                "-i", test_path(test, "in"),
                "-o", test_path(test, "out")
            ],
            stdout = subprocess.PIPE,
            stderr = subprocess.STDOUT
        ).communicate()[0]

        print_diff(test, test_path(test, "out"), test_path(test, "ref"))

def test_path(name, typ):
    return "{}/{}.{}".format(TESTDIR, name, typ)

def print_diff(test, fout, fref):
    with open(fout, "rb") as fout_f:
        with open(fref, "rb") as fref_f:
            output = fout_f.read()
            refput = fref_f.read()

            print("Test: {} ".format(test), end="")
            if (output == refput):
                print("PASS")
            else:
                diff = difflib.ndiff(
                    output.splitlines(),
                    refput.splitlines()
                )
                print("FAIL")
                print("Diff (+ref, -usr):")
                print("".join(diff))

def main():
    run_tests(sys.argv[1])

if __name__ == "__main__":
    main()