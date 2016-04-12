// observer.hpp
// the observer class. Inherit from this to be able to subscribe to the eventManager
#pragma once

#include "events.hpp"

class observer
    {
        protected:
            virtual void onAlert(eventData _data) = 0;

        public:
            void alert(eventData _data);

    };