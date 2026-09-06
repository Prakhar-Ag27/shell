#include <set>
#include <string>

class Interceptor {
    public:
        Interceptor();
        bool intercept(char* const*);
        bool checkIfSupported(char * const);
    private:
        std::set<std::string> supportedOps_;
};