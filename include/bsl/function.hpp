#pragma once

#include <memory>
#include <cassert>
#include <utility>
#include <bsl/polymorph_variant.hpp>

template<typename ReturnType, typename ...ArgsType>
struct CallableFunction {
	virtual ~CallableFunction() = default;

	virtual bool IsValid()const = 0;

	virtual ReturnType Call(ArgsType...)const = 0;

	virtual bool IsEqual(const CallableFunction &other)const = 0;
};

template<typename ReturnType, typename ...ArgsType>
class CallableRawFunction : public CallableFunction<ReturnType, ArgsType...>{
	using RawFunctionPointerType = ReturnType (*)(ArgsType...);
private:
	RawFunctionPointerType m_Pointer = nullptr;
public:
	CallableRawFunction() = default;

	CallableRawFunction(RawFunctionPointerType pointer):
		m_Pointer(pointer)
	{}

	CallableRawFunction(const CallableRawFunction&) = delete;
	CallableRawFunction& operator=(const CallableRawFunction&) = delete;

	CallableRawFunction(CallableRawFunction &&other)noexcept:
		m_Pointer(std::exchange(other.m_Pointer, nullptr))
	{}

	CallableRawFunction& operator=(CallableRawFunction &&other)noexcept {
		m_Pointer = std::exchange(other.m_Pointer, nullptr);
		return *this;
	}

	virtual bool IsValid()const {
		return m_Pointer != nullptr;
	}

	virtual ReturnType Call(ArgsType...args)const {
		assert(IsValid());
		return m_Pointer(std::forward<ArgsType>(args)...);
	}

	virtual bool IsEqual(const CallableFunction<ReturnType, ArgsType...> &other)const {
		auto *casted = dynamic_cast<const CallableRawFunction*>(&other);
		if(!casted)
			return false;
		return m_Pointer == casted->m_Pointer;
	}
};

template<typename ReturnType, typename ...ArgsType>
class DynamicCallableFunction : public CallableFunction<ReturnType, ArgsType...>{
	using CallableFunctionType = CallableFunction<ReturnType, ArgsType...>;
private:
	std::unique_ptr<CallableFunctionType> m_Callable;
public:
	DynamicCallableFunction(std::unique_ptr<CallableFunctionType> callable):
		m_Callable(std::move(callable))
	{}

	DynamicCallableFunction(const DynamicCallableFunction&) = delete;
	DynamicCallableFunction& operator=(const DynamicCallableFunction&) = delete;

	DynamicCallableFunction(DynamicCallableFunction &&other)noexcept:
		m_Callable(std::move(other.m_Callable))
	{}

	DynamicCallableFunction& operator=(DynamicCallableFunction &&other)noexcept {
		m_Callable = std::move(other.m_Callable);
		return *this;
	}

	virtual bool IsValid()const {
		return m_Callable && m_Callable->IsValid();
	}

	virtual ReturnType Call(ArgsType...args)const {
		assert(IsValid());
		return m_Callable->Call(std::forward<ArgsType>(args)...);
	}

	virtual bool IsEqual(const CallableFunction<ReturnType, ArgsType...> &other)const {
		auto *casted = dynamic_cast<const DynamicCallableFunction*>(&other);
		if(!casted)
			return false;
		if(!m_Callable || !casted->m_Callable)
			return m_Callable == casted->m_Callable;
		return m_Callable->IsEqual(*casted->m_Callable);
	}
};

template<typename ObjectType, typename ReturnType, typename ...ArgsType>
class CallableRawMemberFunction : public CallableFunction<ReturnType, ArgsType...>{
	using MemberFunctionPointerType = ReturnType (ObjectType::*)(ArgsType...);
private:
	ObjectType *m_Object = nullptr;
	MemberFunctionPointerType m_Method = nullptr;
public:
	CallableRawMemberFunction(ObjectType *object, MemberFunctionPointerType method):
		m_Object(object),
		m_Method(method)
	{}

	CallableRawMemberFunction(const CallableRawMemberFunction&) = delete;
	CallableRawMemberFunction& operator=(const CallableRawMemberFunction&) = delete;

	CallableRawMemberFunction(CallableRawMemberFunction &&other)noexcept:
		m_Object(std::exchange(other.m_Object, nullptr)),
		m_Method(std::exchange(other.m_Method, nullptr))
	{}

	CallableRawMemberFunction& operator=(CallableRawMemberFunction &&other)noexcept {
		m_Object = std::exchange(other.m_Object, nullptr);
		m_Method = std::exchange(other.m_Method, nullptr);
		return *this;
	}

	virtual bool IsValid()const {
		return m_Object != nullptr && m_Method != nullptr;
	}

	virtual ReturnType Call(ArgsType...args)const {
		assert(IsValid());
		return (m_Object->*m_Method)(std::forward<ArgsType>(args)...);
	}

	virtual bool IsEqual(const CallableFunction<ReturnType, ArgsType...> &other)const {
		auto *casted = dynamic_cast<const CallableRawMemberFunction*>(&other);
		if(!casted)
			return false;
		return m_Object == casted->m_Object && m_Method == casted->m_Method;
	}
};

template<typename ObjectType, typename ReturnType, typename ...ArgsType>
class CallableWeakMemberFunction : public CallableFunction<ReturnType, ArgsType...>{
	using MemberFunctionPointerType = ReturnType (ObjectType::*)(ArgsType...);
private:
	std::weak_ptr<ObjectType> m_Object;
	MemberFunctionPointerType m_Method = nullptr;
public:
	CallableWeakMemberFunction(std::weak_ptr<ObjectType> object, MemberFunctionPointerType method):
		m_Object(std::move(object)),
		m_Method(method)
	{}

	CallableWeakMemberFunction(const CallableWeakMemberFunction&) = delete;
	CallableWeakMemberFunction& operator=(const CallableWeakMemberFunction&) = delete;

	CallableWeakMemberFunction(CallableWeakMemberFunction &&other)noexcept:
		m_Object(std::move(other.m_Object)),
		m_Method(std::exchange(other.m_Method, nullptr))
	{}

	CallableWeakMemberFunction& operator=(CallableWeakMemberFunction &&other)noexcept {
		m_Object = std::move(other.m_Object);
		m_Method = std::exchange(other.m_Method, nullptr);
		return *this;
	}

	virtual bool IsValid()const {
		return !m_Object.expired() && m_Method != nullptr;
	}

	virtual ReturnType Call(ArgsType...args)const {
		assert(IsValid());
		auto locked = m_Object.lock();
		return (locked.get()->*m_Method)(std::forward<ArgsType>(args)...);
	}

	virtual bool IsEqual(const CallableFunction<ReturnType, ArgsType...> &other)const {
		auto *casted = dynamic_cast<const CallableWeakMemberFunction*>(&other);
		if(!casted)
			return false;
		auto left = m_Object.lock();
		auto right = casted->m_Object.lock();
		return left.get() == right.get() && m_Method == casted->m_Method;
	}
};

template<typename ObjectType, typename ReturnType, typename ...ArgsType>
class CallableSharedMemberFunction : public CallableFunction<ReturnType, ArgsType...>{
	using MemberFunctionPointerType = ReturnType (ObjectType::*)(ArgsType...);
private:
	std::shared_ptr<ObjectType> m_Object;
	MemberFunctionPointerType m_Method = nullptr;
public:
	CallableSharedMemberFunction(std::shared_ptr<ObjectType> object, MemberFunctionPointerType method):
		m_Object(std::move(object)),
		m_Method(method)
	{}

	CallableSharedMemberFunction(const CallableSharedMemberFunction&) = delete;
	CallableSharedMemberFunction& operator=(const CallableSharedMemberFunction&) = delete;

	CallableSharedMemberFunction(CallableSharedMemberFunction &&other)noexcept:
		m_Object(std::move(other.m_Object)),
		m_Method(std::exchange(other.m_Method, nullptr))
	{}

	CallableSharedMemberFunction& operator=(CallableSharedMemberFunction &&other)noexcept {
		m_Object = std::move(other.m_Object);
		m_Method = std::exchange(other.m_Method, nullptr);
		return *this;
	}

	virtual bool IsValid()const {
		return m_Object != nullptr && m_Method != nullptr;
	}

	virtual ReturnType Call(ArgsType...args)const {
		assert(IsValid());
		return (m_Object.get()->*m_Method)(std::forward<ArgsType>(args)...);
	}

	virtual bool IsEqual(const CallableFunction<ReturnType, ArgsType...> &other)const {
		auto *casted = dynamic_cast<const CallableSharedMemberFunction*>(&other);
		if(!casted)
			return false;
		return m_Object.get() == casted->m_Object.get() && m_Method == casted->m_Method;
	}
};

template<typename T>
class Function;

template<typename ReturnType, typename ...ArgsType>
class Function<ReturnType(ArgsType...)>{
	using CallableFunctionType = CallableFunction<ReturnType, ArgsType...>;
	using RawFunctionType = CallableRawFunction<ReturnType, ArgsType...>;
	using DynamicFunctionType = DynamicCallableFunction<ReturnType, ArgsType...>;
	using StorageType = PolymorphVariant<CallableFunctionType, RawFunctionType, DynamicFunctionType>;

	using Signature = ReturnType (*)(ArgsType...);
private:
	StorageType m_Callable;
public:
	Function() = default;

	Function(Signature fptr) {
		Bind(fptr);
	}

	template<typename ObjectType>
	Function(ObjectType *object, ReturnType (ObjectType::*method)(ArgsType...)) {
		Bind(object, method);
	}

	template<typename ObjectType>
	Function(std::weak_ptr<ObjectType> object, ReturnType (ObjectType::*method)(ArgsType...)) {
		Bind(std::move(object), method);
	}

	template<typename ObjectType>
	Function(std::shared_ptr<ObjectType> object, ReturnType (ObjectType::*method)(ArgsType...)) {
		Bind(std::move(object), method);
	}

	Function(const Function&) = delete;
	Function& operator=(const Function&) = delete;

	Function(Function &&other)noexcept = default;
	Function& operator=(Function &&other)noexcept = default;

	Function& Bind(Signature fptr) {
		m_Callable = RawFunctionType(fptr);
		return *this;
	}

	template<typename ObjectType>
	Function& Bind(ObjectType *object, ReturnType (ObjectType::*method)(ArgsType...)) {
		m_Callable = DynamicFunctionType(std::make_unique<CallableRawMemberFunction<ObjectType, ReturnType, ArgsType...>>(object, method));
		return *this;
	}

	template<typename ObjectType>
	Function& Bind(std::weak_ptr<ObjectType> object, ReturnType (ObjectType::*method)(ArgsType...)) {
		m_Callable = DynamicFunctionType(std::make_unique<CallableWeakMemberFunction<ObjectType, ReturnType, ArgsType...>>(std::move(object), method));
		return *this;
	}

	template<typename ObjectType>
	Function& Bind(std::shared_ptr<ObjectType> object, ReturnType (ObjectType::*method)(ArgsType...)) {
		m_Callable = DynamicFunctionType(std::make_unique<CallableSharedMemberFunction<ObjectType, ReturnType, ArgsType...>>(std::move(object), method));
		return *this;
	}

	void Unbind() {
		m_Callable = RawFunctionType(nullptr);
	}

	bool IsBound()const {
		return m_Callable->IsValid();
	}

	operator bool()const {
		return IsBound();
	}

	ReturnType Call(ArgsType...args)const {
		assert(IsBound());
		return m_Callable->Call(std::forward<ArgsType>(args)...);
	}

	ReturnType operator()(ArgsType...args)const {
		return Call(std::forward<ArgsType>(args)...);
	}

	void TryCall(ArgsType...args)const {
		if(IsBound())
			(void)Call(std::forward<ArgsType>(args)...);
	}

	friend bool operator==(const Function &left, const Function &right) {
		return left.m_Callable->IsEqual(*right.m_Callable);
	}

	friend bool operator!=(const Function &left, const Function &right) {
		return !(left == right);
	}
};
