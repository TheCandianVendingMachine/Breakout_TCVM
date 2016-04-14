// events.hpp
// all possible events to be passed to the eventManager
#pragma once

namespace
    {
        union data
            {
                int intDat;
                float floatDat;
                double doubleDat;
            };

        enum dataTypes
            {
                INTEGER,
                FLOAT,
                DOUBLE,
            };
    }

enum events
    {
        BALL_HIT_BLOCK
    };

struct eventData
    {
        // data to be passed if any data needs to be
        data _data;
        // what type of data would be passed through
        dataTypes _dataType;

        // what event will be passed through
        events _event;

        eventData(int data, events event) { _data.intDat = data, _dataType = INTEGER; _event = event; }
        eventData(float data, events event) { _data.doubleDat = data, _dataType = DOUBLE;_event = event; }
        eventData(double data, events event) { _data.floatDat = data, _dataType = FLOAT;_event = event; }

    };