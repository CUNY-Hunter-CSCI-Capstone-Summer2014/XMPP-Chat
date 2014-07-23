#include "../../Utility.hpp"
#include "rambler/XMPP/Core/JID.hpp"
#include "W_JID.hpp"

W_JID::W_JID(){}

W_JID::W_JID(String^ string){
	std::string nativeString = Utility::DotNetToNative(string);
}
W_JID::W_JID(String^ localPart, String^ domainPart){

}
W_JID::W_JID(String^ localPart, String^ domainPart, String ^resourcePart){

}