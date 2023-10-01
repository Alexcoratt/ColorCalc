#ifndef I_COMMAND_HPP
#define I_COMMAND_HPP

class ICommand {
public:
    virtual ~ICommand() {}

    virtual void exec() = 0;
};

#endif