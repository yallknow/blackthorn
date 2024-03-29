#include "thorn_library_poster.hpp"

#include <boost/asio/post.hpp>

#include "thorn_library_preprocessor.hpp"

thorn::library::poster::poster(boost::asio::io_context& pl_Context,
                               const std::function<void()>& pcl_Task) noexcept
    : ml_Context{pl_Context}, mv_Task{pcl_Task} {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();
}

thorn::library::poster::~poster() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  boost::asio::post(this->ml_Context, this->mv_Task);
}

void thorn::library::poster::mf_cancel() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mv_Task = []() noexcept -> void {};
}
