#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include <ptoria/instance.h>

struct NetworkEvent : public InstanceBase,
                      public Object<NetworkEvent, "NetworkEvent", Unity::AssemblyCSharp> {
};

#endif /* NETWORKEVENT_H */
