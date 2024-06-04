#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>


class TCPClient {
private:
    boost::asio::io_context io_context {};
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::resolver::results_type endpoints;
    boost::asio::streambuf stream_buf{65536};
    std::queue<std::string> outgoing_messages {};

    std::mutex mutex;
    std::condition_variable cv;
    bool connected = false;
    bool logined = false;

    void async_read();
    void on_read(boost::system::error_code ec, size_t bytesTransferred);
    void async_write();
    void on_write(boost::system::error_code ec, size_t bytesTransferred);

public:
    TCPClient(const std::string& address, int port);

    void run();
    void stop();
    void Post(const std::string& message);

    std::function<void(std::string)> OnMessage;
    std::function<void()> OnDisconnect;

    std::mutex& get_mutex();
    std::condition_variable& get_CV();
    bool is_connected() const;

    bool locked = false; // When user send request to server main therd gona be loked until server response
    bool is_logined() const { return logined;};



    void set_logined(bool value) ;
    bool is_locked() const ;
    void set_locked(bool value);

};

