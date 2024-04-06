#include <string>

namespace lush::lushmq {

	namespace zmq_protocols {

		constexpr std::string_view tcp = "tcp";
		constexpr std::string_view ipc = "icp";
		constexpr std::string_view inproc = "inproc";
		constexpr std::string_view pgm = "pgm";
		constexpr std::string_view epgm = "epgm";
		constexpr std::string_view vmci = "vmci";

	}  // namespace zmq_protocols

    namespace lmq_ports {

		constexpr std::string_view normal = "5556";

	}  // namespace zmq_protocols

	struct endpoint {

		std::string protocol;
		std::string address;
		std::string port;

		endpoint() : protocol(zmq_protocols::tcp), address("*"), port(lmq_ports::normal) {
		}

        endpoint(endpoint const& original) : protocol(original.protocol), address(original.address), port(original.port) {
        }

        endpoint(std::string _protocol, std::string _address, std::string _port) : protocol(_protocol), address(_address), port(_port) {
        }

		endpoint& operator=(endpoint const& rhs) {
            this->protocol = rhs.protocol;
            this->address = rhs.address;
            this->port = rhs.port;
            return *this;
        }

	};

}  // namespace lush::lushmq