import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(3880);
            while (true) {
                System.out.println("Waiting for client connection...");
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected successfully...");
                BufferedReader input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter output = new PrintWriter(clientSocket.getOutputStream(), true);
                String[] parts = input.readLine().split(",");
                double num1 = Double.parseDouble(parts[0]);
                double num2 = Double.parseDouble(parts[1]);

                // Perform the computation
                double addition = num1 + num2;
                double subtraction = num1 - num2;
                double multiplication = num1 * num2;
                double division = num1 / num2;

                System.out.println("Send the results back to the client...\n");
                output.println(addition + "," + subtraction + "," + multiplication + "," + division);
                output.close();
                input.close();
                clientSocket.close();
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
