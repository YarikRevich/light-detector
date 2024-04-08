```plantuml
title

High-level design of "light-detector"

end title

actor "Client"

component "Board control plain" {
entity "ProtocolBuffers"
node "Scheduler"
node "State"
node "Device driver"


[Client] <--> [ProtocolBuffers]: " Send requests"
[ProtocolBuffers] --> [Scheduler]: " Schedule task"
[Scheduler] --> [Device driver]: " Retrieve ongoing data"
[Scheduler] --> [Device driver]: " Retrieve metadata information"
[Scheduler] --> [Device driver]: " Set options"
[Scheduler] --> [State]: " Update state"
```