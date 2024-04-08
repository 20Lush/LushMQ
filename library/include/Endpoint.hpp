#pragma once
#include <string>

namespace lush::lushmq {

	namespace zmq_protocols {

		/** @brief unicast transport using TCP
		 *  @note http://api.zeromq.org/4-2:zmq_tcp
		 */
		constexpr std::string_view tcp = "tcp";

		/** @brief local inter-process communication transport
		 *  @note http://api.zeromq.org/4-2:zmq_ipc
		 */
		constexpr std::string_view ipc = "ipc";

		/** @brief local in-process (inter-thread) communication transport
		 *  @note http://api.zeromq.org/4-2:zmq_inproc
		 */
		constexpr std::string_view inproc = "inproc";

		/** @brief reliable multicast transport using PGM
		 *  @note http://api.zeromq.org/4-2:zmq_pgm
		 */
		constexpr std::string_view pgm = "pgm";

		/** @brief reliable multicast transport using PGM
		 *  @note http://api.zeromq.org/4-2:zmq_pgm
		 */
		constexpr std::string_view epgm = "epgm";

		/** @brief virtual machine communications interface (VMCI)
		 *  @note http://api.zeromq.org/4-2:zmq_vmci
		 */
		constexpr std::string_view vmci = "vmci";

	}  // namespace zmq_protocols

	namespace lmq_ports {

		/** @brief The normal port to use whenever specification isn't necessary
		 */
		constexpr std::string_view normal = "5556";

		// TODO: Should add any more common ports that might be needed. i.e. a specific port for logging...

	}  // namespace lmq_ports

	namespace lmq_addresses {

		/** @brief A wildcardd address used for servers to send multicasts to a particular port, usually on a local net
		 */
		constexpr std::string_view wildcard = "*";

		/** @brief A `localhost` address commonly used for clients to read multicasts from a given port.
		 */
		constexpr std::string_view localhost = "localhost";

		// TODO: Should add any more common addresses that might be needed. i.e. a common hardware specific address...

	} // namespace lmq_addresses

	/** @brief LMQ interface for ZMQ compliant Endpoints for use in socket_t bind operations.
	 * Will silently remove port if the protocol is "inproc" or "ipc"
	 *  @note http://api.zeromq.org/4-2:zmq-connect
	 */
	struct Endpoint {

		/** @brief LMQ interface for ZMQ compliant Endpoints for use in socket_t bind operations.
		 *  @note Endpoint.hpp supplies a namespace of zmq's values. i.e `zmq_protocols::tcp`
		 */
		std::string protocol;

		/** @brief Address. i.e. an IP address(without the :port)
		 *  @note Supports wildcard input here for multicasting
		 */
		std::string address;

		/** @brief Port number (in string for)
		 *  @note Defaults to "5556" a.k.a `lmq_ports::normal` in most cases
		 */
		std::string port;

		/** @brief Default constructor
		 *  @attention protocol=`zmq_protocols::tcp`, address=`lmq_addresses`, port=`lmq_ports::normal`
		 */
		Endpoint() : protocol(zmq_protocols::tcp), address(lmq_addresses::wildcard), port(lmq_ports::normal) {
		}

		/** @brief Copy constructor
		 *  @attention Copys all protocol/address/port information with no reinitialization
		 */
		Endpoint(Endpoint const& original)
		    : protocol(original.protocol),
		      address(original.address),
		      port(original.port) {
		}

		/** @brief Full parameter constructor
		 * 	@note No defaults, must specify all. Consider using the `zmq_protocols` and `lmq_ports` namespaces!
		 */
		Endpoint(std::string _protocol, std::string _address, std::string _port)
		    : protocol(_protocol),
		      address(_address),
		      port(_port) {
		}

		/** @brief Assignment operator. Just copys info from right to left.
		 */
		Endpoint& operator=(Endpoint const& rhs);

		/** @brief Get the Endpoint formatted as a string.
		 *  @attention Clears `port` if the protocol is `inproc` or `ipc`
		 * 	@returns Endpoint information as a full string. i.e. `tcp://localhost:5556`
		 */
		std::string AsString();
	};

}  // namespace lush::lushmq