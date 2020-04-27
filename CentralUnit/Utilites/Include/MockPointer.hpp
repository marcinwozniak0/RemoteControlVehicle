#pragma once

#include <memory>
#include <exception>

struct OwnershipHandoverException : public std::exception
{
    const char* what() const noexcept override
    {
        return "Cannot handover ownership of pointer";
    }
};

template <typename T>
class MockPointer
{
public:
    MockPointer(T* ptr)
        : _storedPointer(ptr)
    {}

    ~MockPointer()
    {
        if (_hasOwnership)
        {
            delete _storedPointer;
        }
    }

    MockPointer() = delete;
    MockPointer(const T&) = delete;
    MockPointer& operator=(const T&) = delete;
    //TODO implement move operators
    MockPointer& operator=(T&&) noexcept = delete;
    MockPointer(T&&) noexcept = delete;

    T& operator*()
    {
        return *_storedPointer;
    }

    std::unique_ptr<T> ownershipHandover()
    {
        if (_hasOwnership and _storedPointer not_eq nullptr)
        {
            _hasOwnership = false;
            return std::unique_ptr<T>(_storedPointer);
        }
        else
        {
            throw OwnershipHandoverException();
        }
    }

private:
    T* _storedPointer;
    bool _hasOwnership = true;
};

template <typename T, typename... Args>
MockPointer<T> makeMockPointer(Args&&... args)
{
    return MockPointer<T>(new T(std::forward<Args>(args)...));
}
