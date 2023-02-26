require 'socket'

server = TCPServer.new("", 3880)
puts "Waiting for client connection..."
client = server.accept
puts "Client connected successfully: #{client.addr}"
while true
    data = client.gets.chomp
    break if !data
    num1, num2 = data.split(",").map(&:to_f)
    addition = num1 + num2
    subtraction = num1 - num2
    multiplication = num1 * num2
    division = num1 / num2
    puts "Send the results back to the client...\n"
    client.puts "#{addition},#{subtraction},#{multiplication},#{division}"
end

client.close
server.close
