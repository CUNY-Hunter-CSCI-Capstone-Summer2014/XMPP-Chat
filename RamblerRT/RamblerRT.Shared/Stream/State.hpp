namespace Rambler { namespace Stream {

public enum class State {
	Closed,
	Closing,
	Opening,
	Open,
	OpenAndSecuring,
	OpenAndSecured,
	OpenAndSecuredAndAuthenticated
};

}	}
	