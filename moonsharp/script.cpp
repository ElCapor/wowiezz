#include <moonsharp/script.h>

Table* Script::Globals() {
    return Unity::GetFieldValue<Table*, "m_GlobalTable">(StaticClass<Script>(), this);
}