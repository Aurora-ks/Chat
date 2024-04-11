#pragma once
#include <memory>
#include <mutex>

template<class T>
class Singlenton
{
public:
	Singlenton() = default;
	Singlenton(const Singlenton<T>&) = delete;
	Singlenton& operator = (const Singlenton<T>&) = delete;

	static std::shared_ptr<T> Instance() {
		std::call_once(flag_, [&] {
			instance_ = std::shared_ptr<T>(new T);
			});
		return instance_;
	}

private:
	static std::shared_ptr<T> instance_;
	static std::once_flag flag_;
};

template <class T>
std::shared_ptr<T> Singlenton<T>::instance_ = nullptr;
template <class T>
std::once_flag Singlenton<T>::flag_;