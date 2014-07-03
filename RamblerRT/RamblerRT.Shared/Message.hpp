#pragma once
#include "types.hpp"
#include "JID.hpp"

using namespace Windows::Foundation;

namespace rambler{ namespace XMPP { namespace Client {

	class Message{
	public:
		const Core::JID sender;
		const Core::JID recipients;
		const String body;

	};
} } }