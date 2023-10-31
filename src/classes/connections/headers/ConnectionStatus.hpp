#ifndef CONNECTION_STATUS_HPP
#define CONNECTION_STATUS_HPP

#define CONNECTION_SUCCESSFUL_STATUS 0
#define UNABLE_TO_CONNECT_STATUS -1

#include <string>

class ConnectionStatus {
private:
	int _num;
	std::string _msg;

public:
	ConnectionStatus(int = CONNECTION_SUCCESSFUL_STATUS, std::string const & = "");

	int getNum() const;
	std::string getMsg() const;

	std::string toString() const;
};

#endif
