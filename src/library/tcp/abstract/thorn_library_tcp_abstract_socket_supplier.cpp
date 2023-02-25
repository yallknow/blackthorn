#include "thorn_library_tcp_abstract_socket_supplier.hpp"

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::socket_supplier::socket_supplier(
    boost::asio::io_context& pl_Context, const std::string_view pc_Address,
    const std::uint16_t pc_Port) noexcept
    : ml_Context{pl_Context}, mv_Address{pc_Address}, mv_Port{pc_Port} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::socket_supplier::~socket_supplier() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::abstract::socket_supplier::mf_set_address(
    const std::string_view pc_Address) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Address = pc_Address;
}

void thorn::library::tcp::abstract::socket_supplier::mf_set_port(
    const std::uint16_t pc_Port) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Port = pc_Port;
}

std::optional<boost::asio::ip::tcp::socket>
thorn::library::tcp::abstract::socket_supplier::mf_get_socket() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  // NOTE: You should only call this method if mf_is_running returns true
  if (!this->mf_is_running()) {
    _THORN_LIBRARY_LOG_WARNING_("Unable to get socket!");

    return std::nullopt;
  }

  std::optional<boost::asio::ip::tcp::socket> lv_OptionalSocketHolder{
      std::nullopt};
  lv_OptionalSocketHolder.swap(this->mv_OptionalSocket);

  // NOTE: Socket holder doesn't run without a working socket
  this->mf_stop();

  return lv_OptionalSocketHolder;
}
