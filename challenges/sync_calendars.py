#!/usr/bin/python
# reddit challenge:
# http://www.reddit.com/r/dailyprogrammer/comments/1dx3wj/050813_challenge_123_intermediate_synchronizing/
# 1st try

import math

def lunarMonthsToJulianDays(months):
    # 1 month = 29.53059 days
    return round(months * 29.53059)

def julianYearsToJulianDays(years):
    return math.floor(years * 365.25)

def syncCalendar(m, n):
    lunarDays = lunarMonthsToJulianDays(n)
    julianDays = julianYearsToJulianDays(m)
    if(lunarDays == julianDays):
        return julianDays
    else:
        return 0

# find largest difference, where M <= 500 (let n < 10000)
# result: 169476.0 with m = 464, n = 5739
# optimize?
def findLargest():
    bigdiff = 0
    for m in xrange(0, 501):
        for n in xrange(0, 10000):
            diff = syncCalendar(m, n)
            if  diff > bigdiff:
                bigdiff = diff
        
    return bigdiff
        

def test():
    print syncCalendar(38, 470)
    print findLargest()
    

test()

