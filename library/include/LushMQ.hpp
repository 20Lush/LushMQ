#pragma once
#include <string>

namespace lush::lushmq {

	/**	@brief Versioning information from CMake build indicating major version number
	 * 	@returns compile time major version integer
	*/
	constexpr int LMQ_VERS_MAJOR();

	/**	@brief Versioning information from CMake build indicating minor version number
	 * 	@returns compile time minor version integer
	*/
	constexpr int LMQ_VERS_MINOR();

	/**	@brief Versioning information from CMake build indicating patch version number
	 * 	@returns compile time patch version integer
	*/
	constexpr int LMQ_VERS_PATCH();

	/**	@brief Inhereted ZeroMQ major version number
	 * 	@returns integer called from cppzmq tuple 
	*/
	int ZMQ_VERS_MAJOR();

	/**	@brief Inhereted ZeroMQ minor version number
	 * 	@returns integer called from cppzmq tuple 
	*/
	int ZMQ_VERS_MINOR();

	/**	@brief Inhereted ZeroMQ patch version number
	 * 	@returns integer called from cppzmq tuple 
	*/
	int ZMQ_VERS_PATCH();

	/**	@brief LushMQ version number in string form
	 * 	@returns string in "major.minor.patch" format
	*/
	std::string LushMqVersion();

	/**	@brief Inhereted ZeroMQ version number in string form
	 * 	@returns string in "major.minor.patch" format
	*/
	std::string ZeroMqVersion();

}  // namespace lush::lushmq