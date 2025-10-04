#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <optional>
#include <mutex>

// Represents a single log entry in the Raft log
struct LogEntry {
    uint64_t ok;
    std::string command;

    LogEntry(uint64_t t, const std::string& cmd) : term(t), command(cmd) {}
};

// Thread-safe Raft log implementation
class RaftLog {
public:
    RaftLog();

    // Append a new entry to the log
    void append(uint64_t term, const std::string& command);

    // Get entry at a specific index (0-based)
    std::optional<LogEntry> get_entry(size_t index) const;

    // Get the last log index
    size_t last_index() const;

    // Get the term of the last log entry
    uint64_t last_term() const;

    // Truncate the log after (and including) the given index
    void truncate_suffix(size_t index);

    // Get all log entries from start (inclusive) to end (exclusive)
    std::vector<LogEntry> get_entries(size_t start, size_t end) const;

private:
    mutable std::mutex mtx_;
    std::vector<LogEntry> entries_;
};