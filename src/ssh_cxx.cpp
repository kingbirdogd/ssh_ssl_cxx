#include <ssh_cxx.hpp>
#include <sftp_cxx.hpp>
#include <exception>

ssh_cxx::ssh_cxx():
	_s(nullptr),
	_sftp()
{
}

ssh_cxx::ssh_cxx(const std::string& host, const std::string& user, const std::string& pass, unsigned short int port):
	_s(nullptr),
	_sftp()
{
	login(host, user, pass, port);
}

ssh_cxx::~ssh_cxx()
{
	close();
}

sftp_cxx& ssh_cxx::get_sftp()
{
	if (!_s)
	{
		throw std::runtime_error("ssh not login");
	}
	return const_cast<sftp_cxx&>(*(_sftp.insert(std::move(sftp_cxx(*this))).first));
}

bool ssh_cxx::login(const std::string& host, const std::string& user, const std::string& pass, unsigned short int port)
{
	_s = ssh_new();
	if (!_s)
		return false;
	ssh_options_set(_s, SSH_OPTIONS_HOST, host.c_str());
	ssh_options_set(_s, SSH_OPTIONS_PORT, &port);
	int log_none = SSH_LOG_NONE;
	ssh_options_set(_s, SSH_OPTIONS_LOG_VERBOSITY, &log_none);
	if (ssh_connect(_s) != SSH_OK)
	{
		ssh_free(_s);
		_s = nullptr;
		return false;
	}
	ssh_options_set(_s, SSH_OPTIONS_USER, user.c_str());
	if (ssh_userauth_password(_s, nullptr, pass.c_str()) != SSH_AUTH_SUCCESS)
	{
		ssh_disconnect(_s);
		ssh_free(_s);
		_s = nullptr;
		return false;
	}
	return true;
}

void ssh_cxx::close()
{
	_sftp.clear();
	if (_s)
	{
		ssh_disconnect(_s);
		ssh_free(_s);
		_s = nullptr;

	}
}

ssh_cxx::ssh_cxx(ssh_cxx&& ssh):
	_s(ssh._s),
	_sftp(std::move(ssh._sftp))
{
	ssh._s = nullptr;
}

ssh_cxx& ssh_cxx::operator= (ssh_cxx&& ssh)
{
	_s = ssh._s;
	_sftp = std::move(ssh._sftp);
	ssh._s = nullptr;
	return *this;
}

ssh_cxx::operator bool() const
{
	return _s != nullptr;
}
