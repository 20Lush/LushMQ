#pragma once
#include <functional>

#include "Endpoint.hpp"
#include "zmq.hpp"

namespace lush::lushmq {

	/** @brief LMQ's subscriber object, for use in a pubsub pattern. Automates some of ZMQ's logic on instantiation.
	 *	@note Extends nothing, has no virtual overrides. Anything extending this class aught to add its own methods but abide the same construction scheme.
	 */
	class LushSubscriber {

	public:
		/** @brief LushSubscriber's constructor overload you might want to use if there aren't any contexts in the
		 * program yet
		 *  @attention INHERENTLY EXPENSIVE OPERATION. Its easy, but bad practice to make a bunch of contexts and then
		 * throw them away.
		 *  @param iothreads number of iothreads to give the instantiated context
		 *  @note Useful if you know you aren't going to be using this to communicate between threads in the same
		 * process.
		 */
		LushSubscriber(const int iothreads = 1);

		/** @brief LushSubscriber constructor overload you might want to use if there is already a ZMQ context_t
		 * floating around
		 *  @note Useful if you know that you might be using this to communicate between threads, or otherwise don't
		 * want the context instantiation overhead
		 *  @param zmq_context ptr to pre-existing zmq::context_t
		 */
		LushSubscriber(const std::shared_ptr<zmq::context_t> zmq_context);

		/** @brief LushSubscriber's copy constructor.
		 *  @note Uses's the original's pointer to whatever context it was using. We want to copy the object but theres
		 * no reason to make a new context.
		 *  @param derived_from the original LushSubscriber object we are copying from.
		 */
		LushSubscriber(LushSubscriber const& derived_from);

		/** @brief LushSubscriber's assignment operator overload.
		 *  @note Uses's the original's pointer to whatever context it was using. We want to copy the object but theres
		 * no reason to make a new context.
		 */
		LushSubscriber& operator=(LushSubscriber const& rhs);

		/** @brief Gets a pointer to the context being used by the Subscriber. Pointer by necessity of the fact that the
		 * context could have been dynamically allocated
		 *  @note This should be safe to call at any point in the lifetime of the Subscriber, as you can't instantiate
		 * one without a context.
		 */
		std::shared_ptr<zmq::context_t> GetContext() const;

	protected:
		/** @brief LushSubscriber's protected destructor. This is probably the end of the polymorphic line, so we don't
		 * need to expose the deletion.
		 */
		~LushSubscriber();

		// Our subscriber's ZMQ context interfaced with a shared_ptr
		std::shared_ptr<zmq::context_t> m_context;

		// Set in constructors, not const. Please don't change me after im set. :(
		zmq::socket_t m_socket;

		// Set in constructors, but can also be re-set at great cost.
		endpoint m_endpoint;
	};

}  // namespace lush::lushmq