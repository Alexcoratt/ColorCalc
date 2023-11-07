#include "ConnectionStatus.hpp"

ConnectionStatus::ConnectionStatus(int num, std::string const & msg) : _num(num), _msg(msg) {}

int ConnectionStatus::getNum() const { return _num; }
std::string ConnectionStatus::getMsg() const { return _msg; }

std::string ConnectionStatus::toString() const {
	return "Status number: " + std::to_string(getNum()) + "\nMessage: " + getMsg();
}
