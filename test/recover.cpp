#include "cxx_function.hpp"

using namespace cxx_function;

struct fs {
    void operator () () const {}
};

int main() {
    function< void() > f = fs{};
    
    #if __cplusplus >= 201402
    fs & tl = recover< fs >( f );
    fs * tp = recover< fs >( & f );
    fs && tr = recover< fs >( std::move( f ) );
    try {
        recover< std::nullptr_t >( function< void() >{} );
        abort();
    } catch ( bad_type_recovery & ) {}
    (void) tl, (void) tp, (void) tr;
    
    f = + []{};
    assert ( (void const*) f == recover< void(*)() >( & f ) );
    #endif
}
