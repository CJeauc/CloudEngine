#pragma once

#define BIND(Function, Instance, ...)	\
		std::bind(Function, Instance, __VA_ARGS__)

#define HOLDER_1 std::placeholders::_1
#define HOLDER_2 std::placeholders::_2
#define HOLDER_3 std::placeholders::_3
#define HOLDER_4 std::placeholders::_4
#define HOLDER_5 std::placeholders::_5

#include "Tools/stdafx.h"

namespace Tools
{
	template<class... ArgTypes>
	class Event
	{
		using CallBack = std::function<void(ArgTypes...)>;

	public:
		uint16_t AddListener(CallBack p_callback)
		{
			m_callBacks[m_count] = std::move(p_callback);
			return m_count++;
		}

		void RemoveListener(uint16_t p_listener)
		{
			m_callBacks.erase(p_listener);
		}

		void Clear()
		{
			m_callBacks.clear();
		}

		void Invoke(ArgTypes... p_args)
		{
			for (auto iterator : m_callBacks)
				iterator.second(p_args...);
		}

		uint16_t operator +=(CallBack p_callback)
		{
			return AddListener(p_callback);
		}

		void operator -=(uint16_t p_listener)
		{
			RemoveListener(p_listener);
		}

	private:
		std::unordered_map<uint16_t, CallBack> m_callBacks;
		uint16_t m_count{0};

	};
}