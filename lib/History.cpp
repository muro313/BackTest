#include "History.h"

History::History(std::string file_name) : file_name_(std::move(file_name)) {
}

History::Iterator History::begin() {
    return data_.begin();
}

History::Iterator History::end() {
    return data_.end();
}
