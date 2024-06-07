#include <Networking/client/tcp_client.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <conio.h> 

std::atomic<bool> disconnected {false}; // Atomic flag to track disconnection

int main(int argc, char* argv[]) {
    TCPClient client {"localhost", 1337};

    client.OnMessage = [&](const std::string& message) {
        std::cout << message;
        client.set_locked(false);
        if (message == "logined\n")  client.set_logined(true);
        if (message == "logged_out\n") client.set_logined(false);
        client.get_CV().notify_one();
        std::lock_guard<std::mutex> lk(client.get_mutex());
    };

    client.OnDisconnect = []() {
        std::cout << "You have been disconnected from the server. Try to connect again." << std::endl;
        disconnected = true;
        std::terminate();
    };

    std::cout << "Connecting to the server..." << std::endl;

    std::thread t{[&client] () { client.run(); }};

    {
        std::unique_lock<std::mutex> lk(client.get_mutex());
        client.get_CV().wait(lk, [&client] { return client.is_connected(); });
    }

    if (disconnected) {
        t.join();
        return -1;
    }

    std::cout << "Connected to the server." << std::endl;



// Log in or sign in options -------------------------------------------------------
    while (true) {
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Sign in" << std::endl;

        int option;
        std::cin >> option;

        if (option == 1) {
            std::string username;
            std::string password;

            std::cout << "Enter your username: ";
            std::cin >> username;

            std::cout << "Enter your password: ";
            std::cin >> password;

            client.set_locked(true);
            client.Post("Log_in " + username + " " + password + "\n");

        } else if (option == 2) {
            std::string name;
            std::string username;
            std::string password;

            std::cout << "Enter your name: ";
            std::cin >> name;

            std::cout << "Enter your username: ";
            std::cin >> username;

            std::cout << "Enter your password: ";
            std::cin >> password;

            client.set_locked(true);
            client.Post("Sign_in " + name + " " + username + " " + password + "\n");
        } else {
            std::cout << "Invalid option selected" << std::endl;
            continue;
        }

        {
            std::unique_lock<std::mutex> lk(client.get_mutex());
            client.get_CV().wait(lk, [&client] { return !client.is_locked(); });
        }



        while (true && client.is_logined()) {
            std::string message;
            std::getline(std::cin, message);

            if (message == "\\q" || disconnected) break;
            message += "\n";
            system("cls");
            client.Post(message + " \n");
            std::cout << "Waiting for server responce" << std::endl;
        }
    }

//---------------------------------------------------------------------------------

    client.stop();
    t.join();

    if (disconnected) {
        return -1;
    }

    return 0;
}
