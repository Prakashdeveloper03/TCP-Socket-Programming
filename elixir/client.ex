defmodule Client do
  def main(_) do
    {:ok, socket} = :gen_tcp.connect(:localhost, 3880, [:binary, active: false])
    {:ok, _input} = :gen_tcp.recv(socket, 0)
    {:ok, _output} = :gen_tcp.send(socket, "#{get_numbers()}\n")
    result = String.trim(:gen_tcp.recv(socket, 0))
    [addition, subtraction, multiplication, division] = String.split(result, ",")
    IO.puts("Addition: #{addition}")
    IO.puts("Subtraction: #{subtraction}")
    IO.puts("Multiplication: #{multiplication}")
    IO.puts("Division: #{division}")
    :gen_tcp.close(socket)
  end

  defp get_numbers() do
    IO.puts("Enter first number: ")
    num1 = IO.gets("") |> String.trim() |> String.to_float()
    IO.puts("Enter second number: ")
    num2 = IO.gets("") |> String.trim() |> String.to_float()
    "#{num1},#{num2}"
  end
end
