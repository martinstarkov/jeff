#pragma once

void* operator new(size_t size)
{
    void* mem = malloc(size);
    if (!mem) {
        throw std::bad_alloc();
    }
    return mem;
}

void operator delete(void* ptr)
{
    free(ptr);
}

void* operator new[] (size_t size)
{
    return (operator new)(size);
}

void operator delete[](void* ptr)
{
    return (operator delete)(ptr);
}