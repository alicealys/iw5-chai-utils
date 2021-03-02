#include "stdinc.hpp"

chaiscript::ChaiScript* chai;

void init()
{
    scheduler::init();

    command::add("chai_eval", [](command::params& params)
    {
        if (!chai)
        {
            return;
        }

        const auto code = params.join(1);
        printf("%s\n", code.data());

        scheduler::once([code]()
        {
            try 
            {
                chai->eval(code);
            }
            catch (const std::exception& e) 
            {
                printf("exception: %s\n", e.what());
            }
        });
    });
}

DLL_EXPORT void on_initialize_context(const char* script, chaiscript::ChaiScript* _chai)
{
    chai = _chai;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        init();
    }

    return TRUE;
}
