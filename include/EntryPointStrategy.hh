#include "MessageHandlerStrategy.hh"

class EntryPointStrategy : public MessageHandlerStrategy {
public:

    EntryPointStrategy();
    ~EntryPointStrategy();
    void handleMessage(Message* message) override;
};