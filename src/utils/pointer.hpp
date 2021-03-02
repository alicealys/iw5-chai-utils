#pragma once

namespace utils
{

// function pointer wrapper
template <typename func_type>
class function
{
public:
	using type = typename func_type;
	using result = typename std::function<func_type>::result_type;

private:
	const std::uintptr_t pointer_;

public:
	function() = delete;
	function& operator=(const function&) = delete;

	constexpr function(const std::uintptr_t& address) : pointer_(address)
	{
	}

	template <typename ...args_type>
	result operator()(args_type&& ...args)
	{
		return reinterpret_cast<func_type*>(this->pointer_)(args...);
	}

	result operator()()
	{
		return reinterpret_cast<func_type*>(this->pointer_)();
	}

	operator func_type* () const
	{
		return reinterpret_cast<func_type*>(this->pointer_);
	}

	operator std::uintptr_t() const
	{
		return this->pointer_;
	}
};

// variable pointer wrapper
template <typename var_type>
class variable
{
private:
	var_type* pointer_;

public:
	variable() = delete;
	variable(const variable&) = delete;
	variable& operator=(const variable&) = delete;

	variable(const std::uintptr_t& address) : pointer_(reinterpret_cast<var_type*>(address)) { }

	inline var_type& operator[](int idx)
	{
		return this->pointer_[idx];
	}

	inline var_type operator[](int idx) const
	{
		return this->pointer_[idx];
	}

	inline var_type* operator&()
	{
		return this->pointer_;
	}

	inline var_type* operator->()
	{
		return this->pointer_;
	}

	inline var_type& operator*()
	{
		return *this->pointer_;
	}

	inline void operator=(const var_type& value)
	{
		*this->pointer_ = value;
	}

	inline operator var_type*() const
	{
		return this->pointer_;
	}

	inline operator var_type() const
	{
		return *this->pointer_;
	}
};

} // namespace xsk
