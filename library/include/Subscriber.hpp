#pragma once
#include "zmq.hpp"
#include <functional>

namespace lush::lushmq {

    /** @brief LMQ's subscriber object, extending & moderately automating ZMQ's socket_t type
     *
    */
    class LushSubscriber : public zmq::socket_t {
        public:
            /** @brief LushSubscriber's constructor overload you might want to use if there aren't any contexts in the program yet
             *  @attention INHERENTLY EXPENSIVE OPERATION. Its easy, but bad practice to make a bunch of contexts and then throw them away.
             *  @param iothreads number of iothreads to give the instantiated context
             *  @note Useful if you know you aren't going to be using this to communicate between threads in the same process.
            */
            LushSubscriber(const int iothreads = 1);

            /** @brief LushSubscriber constructor overload you might want to use if there is already a ZMQ context_t floating around
             *  @note Useful if you know that you might be using this to communicate between threads, or otherwise don't want the context instantiation overhead
             *  @param zmq_context reference to pre-existing zmq::context_t 
            */
            LushSubscriber(const zmq::context_t& zmq_context);

            /** @brief LushSubscriber's copy constructor.
             *
            */
            LushSubscriber(LushSubscriber const& derived);

            /** @brief LushSubscriber's assignment operator overload.
             *
            */
            LushSubscriber& operator=(LushSubscriber const& rhs);

            /** @brief Gets the current context of the Subscriber
             *  @note This should be safe to call at any point in the lifetime of the Subscriber, as you can't instantiate one without a context.
            */
            zmq::context_t GetContext();
        
        protected:
            /** @brief LushSubscriber's protected destructor. This is probably the end of the polymorphic line, so we don't need to expose the deletion.
             *
            */
            ~LushSubscriber();

            std::shared_ptr<zmq::context_t> m_context; 

    };

}