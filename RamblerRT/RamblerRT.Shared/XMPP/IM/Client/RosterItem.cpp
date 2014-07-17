#include "RosterItem.hpp"
#include "rambler/XMPP/IM/Client/RosterItem.hpp"
namespace Rambler { namespace XMPP { namespace IM { namespace Client{

partial ref class RosterItem sealed{ 
	internal:
		std::shared_ptr<rambler::XMPP::IM::Client::RosterItem> itemProper;
};

}

}}}