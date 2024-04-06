#pragma once
#include "Endpoint.hpp"

#include <sstream>

namespace lush::lushmq {

	endpoint& endpoint::operator=(endpoint const& rhs) {
		this->protocol = rhs.protocol;
		this->address = rhs.address;
		this->port = rhs.port;
		return *this;
	}

	std::string endpoint::AsString() {

		if (protocol == zmq_protocols::inproc || protocol == zmq_protocols::ipc) {
			port.clear();
		}

		std::stringstream ss;
		ss << protocol << "://" << address << ":" << port;

		return ss.str();
	}

}  // namespace lush::lushmq