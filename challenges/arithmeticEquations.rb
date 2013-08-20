#!/usr/bin/ruby
# arithmetic equations
# reddit challenge:
# http://www.reddit.com/r/dailyprogrammer/comments/1k7s7p/081313_challenge_135_easy_arithmetic_equations/

class Challenge
  def initialize(min, max)
    @operatorsToStrings = { 0 => "+", 1 => "-", 2 => "*" }
    @operatorList = createOperatorList()
    @argumentList = createArgumentList(min, max)
    @challengeString = formatChallenge()
    @result = eval(@challengeString)
  end
  
  def createOperatorList()
    operatorList = []
    3.times do
      operatorList << rand(0..2)
    end    
    return operatorList
  end

  def createArgumentList(min, max)
    argumentList = []
    4.times do
      argumentList << rand(min..max)
    end
    return argumentList
  end

  def formatChallenge()
    challengeString = ""
    4.times do |i| 
      challengeString <<  @argumentList[i].to_s  << " " <<  @operatorsToStrings[ @operatorList[i] ].to_s << " "
    end
    return challengeString
  end
  
  attr_reader :challengeString
  attr_reader :result
  
end

# get min and max as first input
input = gets.chomp
inSplit = input.split
min = inSplit[0].to_i
max = inSplit[1].to_i

c = Challenge.new(min, max)

while (input.to_s != "q")
  puts c.challengeString
  input = gets.chomp
  # check input string for non-numeric values or emptyness first!
  if input.length < 1 or input.to_s == "q" then break end
  if input.to_i == c.result
    puts "Correct!"
    c = Challenge.new(min, max)
  else
    puts "Incorrect! Try again or exit with 'q'"
  end
end
