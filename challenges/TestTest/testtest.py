#!/usr/bin/python
# reddit challenge:
# http://www.reddit.com/r/dailyprogrammer/comments/1heozl/070113_challenge_131_easy_who_tests_the_tests/
# 1st try, OOP

class TestTest:
    def __init__(self, testinput, testresult):
        self.input = testinput
        self.result = testresult

    def test(self):
        pass

class ReverseTestTest (TestTest):
    def test(self):
        if (self.input[::-1] == self.result):
            return True
        else:
            return False

class UppercaseTestTest (TestTest):
    def test(self):
        if (self.input.upper() == self.result):
            return True
        else:
            return False

def test():
    infile = open("test_input.txt", "r")
    lines = infile.readlines()
    numTests = int(lines.pop(0))
    tests = list()
    for i in xrange(0,numTests):
        # get data, create appropriate test
        values = lines[i].split()
        ttype = int(values[0])
        inp = values[1]
        res = values[2]

        if ttype == 0:
            tests.append(ReverseTestTest(inp, res))
        if ttype == 1:
            tests.append(UppercaseTestTest(inp, res))

    # testing
    for test in tests:
        if test.test():
            print "Good test data"
        else:
            print "Bad test data"

test()
    
        
