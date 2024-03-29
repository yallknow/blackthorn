#include "thorn_library_scope_profiler.hpp"

#include "thorn_library_logger.hpp"
#include "thorn_library_time.hpp"

std::atomic<bool> thorn::library::scope_profiler::msv_IsInitialized{false};

thorn::library::scope_profiler::scope_profiler(
    const std::string_view pc_FuncSig) noexcept
    : mc_Name{pc_FuncSig} {
  this->mv_Pid = logger::msf_get_pid();
  this->mv_Ts = time::msf_since_epoch();
}

thorn::library::scope_profiler::~scope_profiler() noexcept {
  this->mv_Dur = time::msf_since_epoch() - this->mv_Ts;

  logger::msf_profile(this->mf_create_record());
}

void thorn::library::scope_profiler::msf_init() noexcept {
  if (msf_is_initialized() || !logger::msf_is_initialized()) {
    return;
  }

  logger::msf_profile("[ {} ");
  const scope_profiler lc_ScopeProfiler{__FUNCSIG__};

  msv_IsInitialized = true;
}

void thorn::library::scope_profiler::msf_destroy() noexcept {
  if (!msf_is_initialized() || !logger::msf_is_initialized()) {
    return;
  }

  logger::msf_profile(" ]");

  msv_IsInitialized = false;
}

bool thorn::library::scope_profiler::msf_is_initialized() noexcept {
  return msv_IsInitialized;
}

std::string thorn::library::scope_profiler::mf_create_record() const noexcept {
  std::string lv_Record{};

  lv_Record += ", { \"cat\": \"" + this->mc_Cat;
  lv_Record += "\", \"dur\": " + std::to_string(this->mv_Dur);
  lv_Record += ", \"name\": \"" + this->mc_Name;
  lv_Record += "\", \"ph\": \"" + this->mc_Ph;
  lv_Record += "\", \"pid\": " + this->mv_Pid;
  lv_Record += ", \"tid\": " + this->mc_Tid;
  lv_Record += ", \"ts\": " + std::to_string(this->mv_Ts) + "}";

  return lv_Record;
}
