defmodule Server do
  def main(_) do
    {:ok, socket} = :gen_tcp.listen(3880, [:binary, backlog: 5])
    loop_accept(socket)
  end

  defp loop_accept(socket) do
    {:ok, client_socket} = :gen_tcp.accept(socket)
    IO.puts("Client connected successfully...")
    case :gen_tcp.recv(client_socket, 0) do
      { :ok, data } ->
        [num1, num2] = String.split(data, ",") |> Enum.map(&String.to_float/1)
        {addition, subtraction, multiplication, division} = perform_computation(num1, num2)
        result = "#{addition},#{subtraction},#{multiplication},#{division}"
        :gen_tcp.send(client_socket, result)
      _ ->
        IO.puts("Error receiving data from client")
    end
    :gen_tcp.close(client_socket)
    loop_accept(socket)
  end

  defp perform_computation(num1, num2) do
    addition = num1 + num2
    subtraction = num1 - num2
    multiplication = num1 * num2
    division = num1 / num2
    {addition, subtraction, multiplication, division}
  end
end
