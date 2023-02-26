require 'socket'

s = TCPSocket.new("localhost", 3880)
print "Enter first number: "
num1 = gets.chomp.to_f
print "Enter second number: "
num2 = gets.chomp.to_f
s.puts "#{num1},#{num2}"
result = s.gets.chomp
parts = result.split(",")
puts "Addition: #{parts[0]}"
puts "Subtraction: #{parts[1]}"
puts "Multiplication: #{parts[2]}"
puts "Division: #{parts[3]}"
s.close
