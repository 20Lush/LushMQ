#include "Subscriber.hpp"

namespace lush::lushmq {

	LushSubscriber::LushSubscriber(const int iothreads) {

		// Instantiate a new zmq context at the m_context shared memory. Other stuff can also point to it as a way to
		// keep it alive :)
		m_context = std::make_shared<zmq::context_t>(iothreads);

		// Instantiate the socket we'll be using to transact some data with the shared context
		m_socket = zmq::socket_t(*m_context, zmq::socket_type::sub);

		// Create a default Endpoint. Configure to use localhost
		m_endpoint = Endpoint();
		m_endpoint.address = lmq_addresses::localhost;

		// connect the socket to the Endpoint we created
		m_socket.connect(m_endpoint.AsString());
	}

	LushSubscriber::LushSubscriber(const std::shared_ptr<zmq::context_t> zmq_context) {

		// The zmq context already exists, so lets use the original ptr and pass it off as our own (stealing).
		m_context = std::move(zmq_context);

		// Instantiate the socket we'll be using to transact some data with the shared context
		m_socket = zmq::socket_t(*m_context, zmq::socket_type::sub);

		// Create a default Endpoint. Configure to use localhost
		m_endpoint = Endpoint();
		m_endpoint.address = lmq_addresses::localhost;

		// Connect the socket to the Endpoint we created
		m_socket.connect(m_endpoint.AsString());
	}

	std::shared_ptr<zmq::context_t> LushSubscriber::GetContext() const {

		// Just return our guy
		return m_context;
	}

	LushSubscriber::LushSubscriber(LushSubscriber const& derived_from) {

		// Pass the torch of ownership from who we are copying from to here. Its basically the same pointer and we're
		// all sharing it.
		m_context = std::move(derived_from.GetContext());

		// Instantiate the socket we'll be using to transact some data with the shared context
		m_socket = zmq::socket_t(*m_context, zmq::socket_type::sub);

		// Copy over Endpoint information from the origin
		m_endpoint = derived_from.m_endpoint;

		// Connect the socket to the Endpoint we created
		m_socket.connect(m_endpoint.AsString());
	}

	LushSubscriber& LushSubscriber::operator=(LushSubscriber const& rhs) {

		// Similar to copy constructor, we want to steal the pointer from the original to this instance.
		this->m_context = std::move(rhs.GetContext());

		// Copy the socket information from the right hand side
		this->m_socket = zmq::socket_t(*this->m_context, zmq::socket_type::sub);

		// Copt the Endpoint information from the right hand side
		this->m_endpoint = rhs.m_endpoint;

		// Send it. Calls the copy constructor(I THINK!!!!) so the socket should be taken care of there.
		return *this;
	}

	LushSubscriberStateMachine::State LushSubscriber::GetState() const {
		return m_state;
	}

	LushSubscriber::~LushSubscriber() {
	}

}  // namespace lush::lushmq