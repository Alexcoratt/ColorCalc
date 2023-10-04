#ifndef I_COMMAND_HPP
#define I_COMMAND_HPP

#include <ostream>

class ICommand {
public:
    virtual ~ICommand() {}

    virtual void exec(std::ostream &) = 0;
};

#endif