#pragma once
#include <string>

// Make sure to change the namespace LIBRARY to something more specific
namespace lush::lushmq {

	constexpr int LMQ_VERS_MAJOR();
	constexpr int LMQ_VERS_MINOR();
	constexpr int LMQ_VERS_PATCH();

	int ZMQ_VERS_MAJOR();
	int ZMQ_VERS_MINOR();
	int ZMQ_VERS_PATCH();

	std::string LushMqVersion();
	std::string ZeroMqVersion();

}  // namespace lush::lushmq