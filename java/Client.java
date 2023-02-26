import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 3880);
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter first number: ");
            double num1 = Double.parseDouble(userInput.readLine());
            System.out.print("Enter second number: ");
            double num2 = Double.parseDouble(userInput.readLine());
            output.println(num1 + "," + num2);
            String result = input.readLine();
            String[] parts = result.split(",");
            System.out.println("Addition: " + parts[0]);
            System.out.println("Subtraction: " + parts[1]);
            System.out.println("Multiplication: " + parts[2]);
            System.out.println("Division: " + parts[3]);
            output.close();
            input.close();
            socket.close();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
