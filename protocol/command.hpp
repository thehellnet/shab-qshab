#ifndef COMMAND_HPP
#define COMMAND_HPP

enum Command {
    HabPosition,
    HabImage,
    HabTelemetry,
    ClientConnect,
    ClientUpdate,
    ClientDisconnect,
    ServerPing
};

#endif // COMMAND_HPP
