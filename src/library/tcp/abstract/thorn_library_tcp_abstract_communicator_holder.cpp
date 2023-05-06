#include "thorn_library_tcp_abstract_communicator_holder.hpp"

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::communicator_holder::communicator_holder(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept
    : mv_Communicator{pl_Context, std::move(pr_Socket), this} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::communicator_holder::
    ~communicator_holder() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}
