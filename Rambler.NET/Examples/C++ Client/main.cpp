#include <chrono>
#include <thread>
#include <iostream>

#include <rambler/XMPP/IM/Client/Client.hpp>

using namespace rambler::XMPP::IM::Client;

int wmain(int argc, wchar_t* argv[])
{
	std::cout << "Running\n";

	Client client("alpha@dampkeg.com");
	client.setRunloop([](){
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	});
	client.start();

	system("pause");

	return 0;
}

