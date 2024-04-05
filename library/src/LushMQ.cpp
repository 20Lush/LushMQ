#include "LushMQ.hpp"

#include <zmq.hpp>

#include "version.hpp"

namespace lush::lushmq {

	constexpr int LMQ_VERS_MAJOR() {
		return LUSHMQ_VERSION_MAJOR;
	}

	constexpr int LMQ_VERS_MINOR() {
		return LUSHMQ_VERSION_MINOR;
	}

	constexpr int LMQ_VERS_PATCH() {
		return LUSHMQ_VERSION_PATCH;
	}

	int ZMQ_VERS_MAJOR() {
		return std::get<0>(zmq::version());
	}

	int ZMQ_VERS_MINOR() {
		return std::get<1>(zmq::version());
	}

	int ZMQ_VERS_PATCH() {
		return std::get<2>(zmq::version());
	}

	std::string LushMqVersion() {
		std::stringstream ss;
		ss << LMQ_VERS_MAJOR() << "." << LMQ_VERS_MINOR() << "." << LMQ_VERS_PATCH();
		return ss.str();
	}

	std::string ZeroMqVersion() {
		std::stringstream ss;
		ss << ZMQ_VERS_MAJOR() << "." << ZMQ_VERS_MINOR() << "." << ZMQ_VERS_PATCH();
		return ss.str();
	}

}  // namespace lush::lushmq
