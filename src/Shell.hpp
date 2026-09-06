#include "./Tokenize.hpp"
#include "./Interceptor.hpp"

class Shell {
    public:
        Shell();
        void execute(char * const *);
};