#include <cstdint>
#include <iostream>

class FibonacciGenerator {
public:
	FibonacciGenerator(uint16_t target) : m_a(0), 
	m_b(1), 
	m_target(target) 
	{}

	/**
	 * Generates the target-th Fibonacci number
		using the recursive approach. This
	 is intentionally inefficient to 
	 demonstrate the benefits of operator
	 overloading and proxy objects.
			* @return The target-th Fibonacci number.
	 */
	std::uint64_t generate() {
		if (m_target == 0) {
			return m_a;
		} else if (m_target == 1) {
			return m_b;
		} else {
			// Recursive calls to generate the Fibonacci number
			FibonacciGenerator fib1(m_target - 1);
			FibonacciGenerator fib2(m_target - 2);
			return fib1.generate() + fib2.generate();
		}
	}

private:
	std::uint64_t m_a;
	std::uint64_t m_b;
	uint16_t m_target;
};

class FibonacciProxy {
public:
	FibonacciProxy(uint16_t target) : 
	m_target(target),
	m_fib(target) {}

	uint64_t *operator->() {
		if (m_result == -1) {
			m_result = m_fib.generate();
		}
		return &m_result;
	}

	uint64_t &operator*() {
		if (m_result == -1) {
			m_result = m_fib.generate();
		}
		return m_result;
	}

private:
	FibonacciGenerator m_fib;
	uint16_t m_target;
	uint64_t m_result = -1; // Cache for the result
};

int main() {
	// Create a proxy for the 50th Fibonacci number
	FibonacciProxy fibProxy(50); 

	/** Then in this part of the code we do other 
	program initialization, processing, and application work. */

	// When we need the Fibonacci number, we can use the 
	// proxy object, and it will compute the value on demand.
	std::cout << "The 50th Fibonacci number is: " << *fibProxy << std::endl;


	// Then we can continue with other parts of the program, 
	// and if we need the Fibonacci number again, 
	// it will return the cached result without recomputation.
	std::cout << "Accessing the 50th Fibonacci number again: " << *fibProxy << std::endl;
	return 0;
}
