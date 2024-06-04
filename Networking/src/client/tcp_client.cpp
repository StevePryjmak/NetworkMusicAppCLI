#include <Networking/client/tcp_client.h>

TCPClient::TCPClient(const std::string &address, int port) : socket(io_context) {
    boost::asio::ip::tcp::resolver resolver {io_context};
    endpoints = resolver.resolve(address, std::to_string(port));
}

void TCPClient::run() {
    boost::asio::async_connect(socket, endpoints, [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint ep) {
        if (!ec) {
            {
                std::lock_guard<std::mutex> lk(mutex);
                connected = true;
            }
            cv.notify_one();
            async_read();
        } else {
            if (OnDisconnect) OnDisconnect(); // Notify on connection failure
        }
    });

    io_context.run();
}

void TCPClient::stop() {
    boost::system::error_code ec;
    socket.close(ec);

    if (ec) {
        if (OnDisconnect) OnDisconnect(); //not important
        // process error
    }
}

void TCPClient::Post(const std::string &message) {
    bool queue_idle = outgoing_messages.empty();
    outgoing_messages.push(message);

    if (queue_idle) {
        async_write();
    }
}

void TCPClient::async_read() {
    boost::asio::async_read_until(socket, stream_buf, "\n", [this](boost::system::error_code ec, size_t bytesTransferred) {
        on_read(ec, bytesTransferred);
    });
}

void TCPClient::on_read(boost::system::error_code ec, size_t bytesTransferred) {
    if (ec) {
        stop();
        if (OnDisconnect) OnDisconnect(); 
        return;
    }

    std::stringstream message;
    message << std::istream{&stream_buf}.rdbuf();

    OnMessage(message.str());
    async_read();
}

void TCPClient::async_write() {
    boost::asio::async_write(socket, boost::asio::buffer(outgoing_messages.front()), [this](boost::system::error_code ec, size_t bytesTransferred) {
        on_write(ec, bytesTransferred);
    });
}

void TCPClient::on_write(boost::system::error_code ec, size_t bytesTransferred) {
    if (ec) {
        stop();
        if (OnDisconnect) OnDisconnect();
        return;
    }

    outgoing_messages.pop();

    if (!outgoing_messages.empty()) {
        async_write();
    }
}

std::mutex& TCPClient::get_mutex() {
    return mutex;
}

std::condition_variable& TCPClient::get_CV() {
    return cv;
}

bool TCPClient::is_connected() const {
    return connected;
}

// bool TCPClient::is_logined() const {
//     return logined;
// }

void TCPClient::set_logined(bool value) {
    logined = value;
}

bool TCPClient::is_locked() const {
    return locked;
}

void TCPClient::set_locked(bool value) {
    locked = value;
}
