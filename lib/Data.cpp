#include "Data.h"

std::shared_ptr<Data> Data::GetNext() {
    return next_;
}
