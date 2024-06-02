#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <queue>


using boost::asio::ip::tcp;
using MessageHandler = std::function<void(std::string)>;
using ErrorHandler = std::function<void()>;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

private:
    boost::asio::ip::tcp::socket socket;
    std::string username;

    std::queue<std::string> outgoing_messages;
    boost::asio::streambuf stream_buf {65536};

    MessageHandler message_handler;
    ErrorHandler error_handler;


    explicit TCPConnection(boost::asio::ip::tcp::socket&& socket);
    // Wait for a new message from client
    void async_read();
    void on_read(boost::system::error_code ec, size_t bytesTranferred);

    void async_write();
    void on_write(boost::system::error_code ec, size_t bytesTransferred);

public:
    using pointer = std::shared_ptr<TCPConnection>;
    static pointer Create(boost::asio::ip::tcp::socket&& socket) {
        return pointer(new TCPConnection(std::move(socket)));
    }

    inline const std::string& get_username() const { return username; }

    tcp::socket& Socket() {
        return socket;
    }

    void Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler);
    void Post(const std::string& message);
};








