#pragma once
#include <functional>

#include "Endpoint.hpp"
#include "zmq.hpp"

namespace lush::lushmq {

	/** @brief LMQ's subscriber object, for use in a pubsub pattern. Automates some of ZMQ's logic on instantiation.
	 *	@note Extends nothing, has no virtual overrides. Anything extending this class aught to add its own methods but
	 *abide the same construction scheme.
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
		 *  @returns shared pointer to a `zmq::context_t` inherent to the object. Feel free to use it!
		 */
		std::shared_ptr<zmq::context_t> GetContext() const;

		/** @brief The Subscriber's states. Each has specific logic executed in order, cycling back to IDLE.
		 *  @note INIT and STOP are entry and exit states that shall only be found once each per lifetime of a
		 * subscriber
		 */
		enum State
		{

			/** @brief Initialization state, for when things in this object are getting set up.
			 *  @returns transitions to `IDLE` on successful initialization
			 *  @note Object only in this state once in its lifetime.
			 */
			INIT,

			/** @brief Idle state, for when the object isn't prompted to do work.
			 *  @returns when prompted to, will transition to `READ`
			 *  @note Resting state. Does not buffer data it might be seeing.
			 */
			IDLE,

			/** @brief Reading state, for when the object is currently reading data coming from its subscriptions
			 *  @returns when read process is complete, transitions to `ACK`
			 *  @note Any errors from reading will be carried forward to the `ACK` state
			 */
			READ,

			/** @brief Acknowledge state, for when the object notifies something or somebody that it has read data
			 *  @returns when acknowledge process is complete, transitions to `OUT`
			 *  @note Classifies and details errors from the read state, carries that foward to `OUT`
			 */
			ACK,

			/** @brief Output state, for when the state machine can finally release its acquired data to the caller
			 *  @returns when output process is complete, transitions back to `IDLE` to await more work
			 *  @note Outputs data as well as any errors that have been accrued through the object's work cycle.
			 */
			OUT,

			/** @brief Stop state, for when the object is tearing down.
			 *  @returns Does not transition out, object will die in this state
			 *  @note Object only in this state once in its lifetime.
			 */
			STOP

		};

		/** @brief Gets the current state of the object.
		 *  @note This should be safe to call at any point in the lifetime of the Subscriber, as it is a FSM at heart
		 *  @returns 
		 */
		State GetState() const;

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

		// Internal-use state value of the object.
		State m_state;
	};

}  // namespace lush::lushmq