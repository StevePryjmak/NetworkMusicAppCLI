#include <Networking/server/tcp_connection.h>
#include <iostream>

TCPConnection::TCPConnection(boost::asio::ip::tcp::socket&& socket)
    : socket(std::move(socket)) {
    boost::system::error_code ec;

    auto endpoint = this->socket.remote_endpoint(ec);
    if (ec) {
        std::cerr << "Failed to get remote endpoint: " << ec.message() << std::endl;
        username = "unknown"; // Default username if endpoint retrieval fails
    } else {
        std::stringstream name;
        name << endpoint;
        username = name.str();
    }
    std::cout << "New connection from: " << username << std::endl;
}




void TCPConnection::Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler) {
    message_handler = std::move(messageHandler);
    error_handler = std::move(errorHandler);

    async_read();
}

void TCPConnection::Post(const std::string &message) {
    bool queueIdle = outgoing_messages.empty();
    outgoing_messages.push(message);

    if (queueIdle) {
        async_write();
    }
}

void TCPConnection::async_read() {
    boost::asio::async_read_until(socket, stream_buf, "\n", [self = shared_from_this()]
    (boost::system::error_code ec, size_t bytesTransferred) {
        self->on_read(ec, bytesTransferred);
    });
}

void TCPConnection::on_read(boost::system::error_code ec, size_t bytesTranferred) {
    if (ec) {
        socket.close(ec);

        error_handler();
        return;
    }

    std::stringstream message;
    message << username << ": " << std::istream(&stream_buf).rdbuf();
    stream_buf.consume(bytesTranferred);

    message_handler(message.str());
    async_read();
}

void TCPConnection::async_write() {
    boost::asio::async_write(socket, boost::asio::buffer(outgoing_messages.front()), [self = shared_from_this()]
            (boost::system::error_code ec, size_t bytesTransferred) {
        self->on_write(ec, bytesTransferred);
    });
}

void TCPConnection::on_write(boost::system::error_code ec, size_t bytesTransferred) {
    if (ec) {
        socket.close(ec);

        error_handler();
        return;
    }

    outgoing_messages.pop();

    if (!outgoing_messages.empty()) {
        async_write();
    }
}




