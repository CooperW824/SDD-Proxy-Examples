#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class File {
public:
  virtual ~File() = default;
  virtual std::string read(uint32_t length) = 0;
  virtual void write(const std::string &data) = 0;
  virtual std::string getName() = 0;
};

class NetworkAttachedFile : public File {
public:
  NetworkAttachedFile(const std::string &name,
                      const std::string &server_address)
      : m_name(name), m_server_address(server_address) {
    // Simulate the cost of opening a remote file handle
    std::cout << "[NetworkAttachedFile] Fetching \"" << m_name << "\" from "
              << m_server_address << " ...\n";
  }

  std::string read(uint32_t length) override {
    return "Data from " + m_server_address + "/" + m_name + " (first " +
           std::to_string(length) + " bytes)";
  }

  void write(const std::string &data) override {
    std::cout << "[NetworkAttachedFile] Writing to " << m_server_address << "/"
              << m_name << ": " << data << "\n";
  }

  std::string getName() override { return m_name; }

private:
  std::string m_name;
  std::string m_server_address;
};

class FileProxy : public File {
public:
  FileProxy(std::string name, std::string server_address)
      : m_name(std::move(name)), m_server_address(std::move(server_address)) {}

  void setUsername(const std::string &username) { m_username = username; }
  void setPassword(const std::string &password) { m_password = password; }

  File &operator*() { return *lazyAuthenticatedFile(); }

  File *operator->() { return lazyAuthenticatedFile(); }

  std::string read(uint32_t length) override {
    File *authd_file = lazyAuthenticatedFile();
    return authd_file->read(length);
  }

  void write(const std::string &data) override {
    File *authd_file = lazyAuthenticatedFile();
    authd_file->write(data);
  }

  std::string getName() override {
    File *authd_file = lazyAuthenticatedFile();
    return authd_file->getName();
  }

private:
  void authenticate() const {
    if (m_username.empty() || m_password.empty()) {
      throw std::runtime_error("Authentication failed: missing credentials");
    }
    // Real implementation would verify against an auth service here.
    std::cout << "[FileProxy] Authenticated as \"" << m_username << "\"\n";
  }

  File *lazyAuthenticatedFile() {
    authenticate(); // protection check first
    if (!m_file) {  // fetch only on first access
      m_file = std::make_unique<NetworkAttachedFile>(m_name, m_server_address);
    }
    return m_file.get();
  }

  std::string m_name;
  std::string m_server_address;
  std::string m_username;
  std::string m_password;

  std::unique_ptr<File> m_file; // null until first access
};

int main() {
  try {
    FileProxy proxy("important_data.txt", "fileserver.example.com");

    proxy.setUsername("cooper");
    proxy.setPassword("securepassword");

    std::cout << "\n-- First read (triggers lazy fetch) --\n";
    std::string data = proxy->read(100); // We can treat proxy like a pointer
    std::cout << "Read: " << data << "\n";

    std::cout << "\n-- Second read (uses cached file handle) --\n";
    std::string data2 = (*proxy).read(50);
    std::cout << "Read: " << data2 << "\n";

    std::cout << "\n-- Write --\n";
    proxy.write("Updated payload"); // Or we can use the proxy to write to the
                                    // file directly

    std::cout << "\n-- Access with missing credentials --\n";
    FileProxy badProxy("secret.txt", "fileserver.example.com");
    badProxy.read(10); // no username/password set

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
  return 0;
}