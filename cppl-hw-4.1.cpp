#pragma once

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};


TEST_CASE("test List") {

    SECTION("Size") {
        List testList = List();
        CHECK(testList.Size() == 0);

        testList.PushFront(5);
        CHECK(testList.Size() == 1);

        testList.PushBack(4);
        testList.PushBack(14);
        testList.PushBack(154);
        testList.PushFront(65);
        CHECK(testList.Size() == 5);
    }
    SECTION("Empty") {
        List testList = List();
        CHECK(testList.Empty());

        testList.PushFront(5);
        testList.PopFront();
        CHECK(testList.Empty());
    }
    SECTION("Clear") {
        List testList = List();
        testList.PushFront(5);
        testList.PushBack(4);
        testList.PushBack(14);
        testList.PushBack(154);
        testList.PushFront(65);
        CHECK(testList.Size() == 5);
        testList.Clear();
        CHECK(testList.Size() == 0);
    }
    /*************************************************/
    SECTION("PushBack") {
        List testList = List();
        testList.PushBack(1);
        CHECK(testList.Size() == 1);

        testList.PushBack(2);
        testList.PushBack(3);
        CHECK(testList.Size() == 3);
        CHECK(testList.PopBack() == 3);
        CHECK(testList.PopFront() == 1);
    }
    SECTION("PushFront") {
        List testList = List();
        testList.PushFront(1);
        CHECK(testList.Size() == 1);

        testList.PushFront(2);
        testList.PushFront(3);
        CHECK(testList.Size() == 3);
        CHECK(testList.PopBack() == 1);
        CHECK(testList.PopFront() == 3);
    }
    SECTION("PopBack") {
        List testList = List();
        CHECK_THROWS_AS(testList.PopBack(), std::runtime_error);
        //CHECK_THROWS_WITH(testList.PopBack(), "list is empty");

        testList.PushBack(2);
        CHECK(testList.PopBack() == 2);
        CHECK(testList.Size() == 0);

        testList.PushFront(1);
        testList.PushFront(2);
        testList.PushFront(3);
        int count = testList.Size();
        CHECK(testList.PopBack() == 1);
        CHECK((count - testList.Size()) == 1);
    }
    SECTION("PopFront") {
        List testList = List();
        CHECK_THROWS_AS(testList.PopFront(), std::runtime_error);
        //CHECK_THROWS_WITH(testList.PopBack(), "list is empty");

        testList.PushFront(2);
        CHECK(testList.PopFront() == 2);
        CHECK(testList.Size() == 0);

        testList.PushBack(1);
        testList.PushBack(2);
        testList.PushBack(3);
        int count = testList.Size();
        CHECK(testList.PopFront() == 1);
        CHECK((count - testList.Size()) == 1);
    }
}

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}