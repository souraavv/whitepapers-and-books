#include "raft/log.h"
#include <stdexcept>

namespace raft {

Log::Log() {
    // dummy sentinel at position 0 so real entries start at index 1
    entries_.push_back(LogEntry{0, ""});
}

Index Log::append(const LogEntry &entry) {
    entries_.push_back(entry);
    return lastIndex();
}

Index Log::append(const std::vector<LogEntry> &entries) {
    for (const auto &e : entries) entries_.push_back(e);
    return lastIndex();
}

std::vector<LogEntry> Log::read(Index from, Index to) const {
    if (from == 0) throw std::invalid_argument("Log::read - 'from' must be >= 1");
    Index li = lastIndex();
    if (to == 0 || to > li) to = li;
    if (from > to) return {};
    // entries_ is 0..li; we want subvector [from..to]
    std::vector<LogEntry> out;
    out.reserve(static_cast<size_t>(to - from + 1));
    for (Index i = from; i <= to; ++i) out.push_back(entries_.at(static_cast<size_t>(i)));
    return out;
}

void Log::deleteSuffix(Index fromIndex) {
    if (fromIndex == 0) throw std::invalid_argument("deleteSuffix: fromIndex must be >= 1");
    Index li = lastIndex();
    if (fromIndex > li) return; // nothing to do
    // resize to keep entries_[0 .. fromIndex-1]
    entries_.resize(static_cast<size_t>(fromIndex));
}

Index Log::lastIndex() const noexcept {
    return static_cast<Index>(entries_.size() - 1);
}

Term Log::lastTerm() const noexcept {
    if (lastIndex() == 0) return 0;
    return entries_.back().term;
}

Index Log::size() const noexcept { return lastIndex(); }

} // namespace raft
