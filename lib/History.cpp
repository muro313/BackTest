#include "History.h"

std::shared_ptr<Data> History::GetNextData() {
    current_data_ = current_data_->GetNext();
    return current_data_;
}

History::History(std::string file_name) : file_name_(std::move(file_name)) {

}
