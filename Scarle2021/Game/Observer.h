#pragma once
#include "Event.h"

/**
 * \brief Base interface for an observer.
 * Get Notified will be called by its observable
 */
class IObserver
{
public:
	virtual ~IObserver() = default;

	/**
	 * \brief Main connection point to the Observable
	 */
	virtual void ReceiveData() = 0;
};


/**
 * \brief Observer design pattern for classes that
 * subscribe to receive Events
 */
class IEventReceiver
{
public:
	virtual ~IEventReceiver() = default;

	/**
	 * \brief Connection function to the Event Manager
	 */
	virtual void ReceiveEvents(AL::Event* event) = 0;
};


