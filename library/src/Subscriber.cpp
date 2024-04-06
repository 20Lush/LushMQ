#include "Subscriber.hpp"

namespace lush::lushmq {

	LushSubscriber::LushSubscriber(const int iothreads) {

		// Instantiate a new zmq context at the m_context shared memory. Other stuff can also point to it as a way to
		// keep it alive :)
		m_context = std::make_shared<zmq::context_t>(iothreads);
	}

	LushSubscriber::LushSubscriber(const std::shared_ptr<zmq::context_t> zmq_context) {

		// The zmq context already exists, so lets use the original ptr and pass it off as our own (stealing).
		m_context = std::move(zmq_context);
	}

	std::shared_ptr<zmq::context_t> LushSubscriber::GetContext() const {

		// Just return our guy
		return m_context;
	}

	LushSubscriber::LushSubscriber(LushSubscriber const& derived_from) : zmq::socket_t() {

		// Pass the torch of ownership from who we are copying from to here. Its basically the same pointer and we're
		// all sharing it.
		m_context = std::move(derived_from.GetContext());
	}

	LushSubscriber& LushSubscriber::operator=(LushSubscriber const& rhs) {

		// Similar to copy constructor, we want to steal the pointer from the original to this instance.
		this->m_context = std::move(rhs.GetContext());

		// Send it
		return *this;
	}

	LushSubscriber::~LushSubscriber() {
	}

}  // namespace lush::lushmq