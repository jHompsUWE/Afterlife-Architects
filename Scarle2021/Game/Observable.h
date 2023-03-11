#pragma once
#include <vector>

/**
 * \brief Base interface for an observable
 * Contains the functionality to add and remove observers
 * Notify will update all the observers 
 */
template<class ObserverType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	
	/**
	 * \param observer Adds the specified observer to the observer list
	 */
	virtual void AddObserver(ObserverType* observer)
	{
		observers.push_back(observer);
	}
	
	/**
	 * \param observer Removes the specified observer from the list
	 */
	virtual void RemoveObserver(ObserverType* observer)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}
	
	/**
	 * \brief When called, notifies all the observers
	 */
	virtual void BroadcastData() = 0;

protected:
	std::vector<ObserverType*> observers{};
};
