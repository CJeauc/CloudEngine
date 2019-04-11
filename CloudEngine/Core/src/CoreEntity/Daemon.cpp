#include <Core/stdafx.h>
#include <Core/CoreEntity/Daemon.h>

using namespace Core::Entities;

Daemon::Daemon(std::string p_name)
	: m_name {std::move(p_name)}
{
}
