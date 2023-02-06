#include "thorn_library_poster.hpp"

thorn::library::poster::poster(boost::asio::io_context& pl_Context,
                               const std::function<void()>& pcl_Task) noexcept
    : ml_Context{pl_Context}, mv_Task{pcl_Task} {}

thorn::library::poster::~poster() noexcept {
  boost::asio::post(this->ml_Context, this->mv_Task);
}

thorn::library::poster::poster(const poster& pcl_Other) noexcept
    : ml_Context{pcl_Other.ml_Context}, mv_Task{pcl_Other.mv_Task} {}

thorn::library::poster::poster(poster&& pr_Other) noexcept
    : ml_Context{pr_Other.ml_Context}, mv_Task{std::move(pr_Other.mv_Task)} {}

void thorn::library::poster::mf_cancel() noexcept {
  this->mv_Task = []() -> void {};
}
