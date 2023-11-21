#include "valiantBase.h"

class WeakLiu2Way: public ValiantBase{
    public:
        WeakLiu2Way(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest);
};

class Liu2Way: public ValiantBase{
    public:
        Liu2Way(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest);
        void edge_embed_gamma1(DAG* g);
        void remove_x_switches();
};