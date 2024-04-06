#include "Subscriber.hpp"

namespace lush::lushmq {

    LushSubscriber::LushSubscriber(const int iothreads = 1){

        // Instantiate a new zmq context at the m_context shared memory. Other stuff can also point to it as a way to keep it alive :)
        m_context = std::make_shared<zmq::context_t>(new zmq::context_t(iothreads));

    }

    LushSubscriber::LushSubscriber(const zmq::context_t& zmq_context){

        // The zmq context already exists, lets just smart-point to it. It will probably outlast us.
        m_context = std::make_shared<zmq::context_t>(zmq_context);
        
    }

    LushSubscriber::~LushSubscriber(){

       //logging? 

    }

}