#pragma once
#include "Event.h"

namespace AL
{
	/**
	 * \brief This overloads the main observer design pattern to
	 * allow receive data to take in a different argument
	 */
	class IObserverEvent
	{
		virtual ~IObserverEvent() = default;

		virtual void ReceiveData(Event* event) = 0;
	};
}

