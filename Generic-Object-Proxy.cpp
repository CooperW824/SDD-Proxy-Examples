#include <cstdint>
#include <iostream>
#include <memory>

namespace InternalApplicationLibrary {
class NumberSequenceInterface {
public:
  virtual ~NumberSequenceInterface() = default;
  virtual uint64_t getValue() const = 0;
};

class FibonacciSequence : public NumberSequenceInterface {
public:
  FibonacciSequence(uint16_t n) : m_n(n) {}
  // A naive recursive implementation of Fibonacci sequence,
  // intentionally inefficient for demonstration purposes.
  uint64_t getValue() const override {
    if (m_n == 0)
      return 0;
    if (m_n == 1)
      return 1;
    FibonacciSequence fib1(m_n - 1);
    FibonacciSequence fib2(m_n - 2);
    return fib1.getValue() + fib2.getValue();
  }

private:
  uint16_t m_n;
};

class LucasSequence : public NumberSequenceInterface {
public:
  LucasSequence(uint16_t n) : m_n(n) {}
  // A naive recursive implementation of Lucas sequence,
  // intentionally inefficient for demonstration purposes.
  uint64_t getValue() const override {
    if (m_n == 0)
      return 2;
    if (m_n == 1)
      return 1;
    LucasSequence lucas1(m_n - 1);
    LucasSequence lucas2(m_n - 2);
    return lucas1.getValue() + lucas2.getValue();
  }

private:
  uint16_t m_n;
};

class NumberSequenceProxy : public NumberSequenceInterface {
public:
  static NumberSequenceProxy createFibonacci(uint16_t n) {
    return NumberSequenceProxy(new FibonacciSequence(n));
  }
  static NumberSequenceProxy createLucas(uint16_t n) {
    return NumberSequenceProxy(new LucasSequence(n));
  }
  uint64_t getValue() const override {
    if (m_cachedValue == -1) {
      m_cachedValue = m_sequence->getValue();
    }
    return m_cachedValue;
  }

private:
  explicit NumberSequenceProxy(NumberSequenceInterface *sequence)
      : m_sequence(sequence), m_cachedValue(-1) {}
  std::unique_ptr<NumberSequenceInterface> m_sequence;
  mutable int64_t
      m_cachedValue; // Cache for the computed value, initialized to -1
};

} // namespace InternalApplicationLibrary

int main() {
  using namespace InternalApplicationLibrary;

  // Create a proxy for the 10th Fibonacci number
  NumberSequenceProxy fibProxy = NumberSequenceProxy::createFibonacci(10);
  // Create a proxy for the 10th Lucas number
  NumberSequenceProxy lucasProxy = NumberSequenceProxy::createLucas(10);

  // Access the values through the proxies, the values are only computed once
  // and cached for subsequent accesses
  uint64_t fibValue = fibProxy.getValue();
  uint64_t lucasValue = lucasProxy.getValue();

  // Output the results
  std::cout << "The 10th Fibonacci number is: " << fibValue << std::endl;
  std::cout << "The 10th Lucas number is: " << lucasValue << std::endl;

  // Subsequent access to the same values will return the cached results without
  // recomputation
  std::cout << "Accessing the 10th Fibonacci number again: "
            << fibProxy.getValue() << std::endl;
  std::cout << "Accessing the 10th Lucas number again: "
            << lucasProxy.getValue() << std::endl;

  return 0;
}
