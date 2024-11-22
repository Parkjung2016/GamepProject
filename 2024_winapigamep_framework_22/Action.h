#include <functional>
#include <vector>

template<typename... Args>
class Action {

public:
	using Subscriber = std::function<void(Args...)>;


	void invoke(Args... args) const {
		for (const auto& subscriber : subscribers) {
			subscriber(args...);
		}
	}
public:
	void operator +=(Subscriber sub)
	{
		AddSubscriber(std::move(sub));
	}
	void operator -=(Subscriber sub)
	{
		RemoveSubscriber(sub);
	}
private:
	void AddSubscriber(Subscriber subscriber) {
		subscribers.push_back(std::move(subscriber));
	}
	void RemoveSubscriber(const Subscriber& subscriber) {
		auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) {
			subscribers.erase(it);
		}
	}
private:
	std::vector<Subscriber> subscribers;
};