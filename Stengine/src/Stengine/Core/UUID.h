#pragma once

#include <stdint.h>
#include <xhash>

namespace Sten
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}

namespace std
{
	template<>
	struct hash<Sten::UUID>
	{
		std::size_t operator()(const Sten::UUID& uuid) const 
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}